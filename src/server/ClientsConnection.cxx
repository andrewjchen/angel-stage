#include <iostream>
#include <iomanip>
#include <cstdio>
#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"

#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Debug.hxx"

ClientsConnection::ClientsConnection(uint16_t port, boost::function<void (uint64_t, int)> _onLoginCallback) {
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
		throw "socket error";
	
	if(bind(listenfd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
		throw "bind error";
	
	onLoginCallback = _onLoginCallback;
	
	valid = true;
	running = false;
}

ClientsConnection::~ClientsConnection() {
	if(running)
		stop();
}

void ClientsConnection::start() {
	if(running)
		throw "Already running!";
	if(!valid)
		throw "Stopped! (and therefore invalid)";
	
	if(listen(listenfd, 2) == -1)
		throw "listen error";

	running = true;
	listenThread = new boost::thread(boost::bind(&ClientsConnection::listenthread, this));
	readThread = new boost::thread(boost::bind(&ClientsConnection::readthread, this));
}

void ClientsConnection::stop() {
	valid = false;
	running = false;
	
	readThread->join();
	delete readThread;
	readThread = NULL;
	
	listenThread->join();
	delete listenThread;
	listenThread = NULL;
	
	if(listenfd > 0) {
		close(listenfd);
		listenfd = -1;
	}
}

void ClientsConnection::listenthread() {
	try {
		while (running) {
			struct pollfd pfd[1];
			pfd[0].fd = listenfd;
			pfd[0].events = POLLIN;
			pfd[0].revents = 0;
			
			int pollres = poll(pfd, 1, 5000);
			
			if(pollres == -1)
			{
				valid = false;
				throw "poll error";
			}
			
			if(pollres == 1 && (pfd[0].revents & POLLIN))
			{
				//there are clients waiting
				struct sockaddr_in sa;
				socklen_t slen = sizeof(sa);
				int clientfd = accept(listenfd, (struct sockaddr *)&sa, &slen);
				
				if(clientfd == -1)
						throw "accept error";
				
				uint64_t peer_ip = ((uint64_t)(sa.sin_addr.s_addr) << 16) | (sa.sin_port);
				
				onLoginCallback(peer_ip, clientfd);
				
				clientfd_mutex.lock();
					clientfds[peer_ip] = clientfd;
					fd_to_client[clientfd] = peer_ip;
				clientfd_mutex.unlock();
			}
		}
	} catch (const char *e){
		std::cout << e << std::endl;
	}
}

uint8_t *ClientsConnection::crunchIntoBuffer(std::list<Packet *> ps, int *outsize)
{
	int size = 0;
	for(std::list<Packet *> ::iterator it = ps.begin(); it != ps.end(); it++)
		size += (*it)->estimateSize();
	
	uint8_t *buf = new uint8_t[size];
	int i = 0;
	for(std::list<Packet *> ::iterator it = ps.begin(); it != ps.end(); it++)
		i += (*it)->writeToBuf(buf + i);
	
	*outsize = i;
	return buf;
}

void ClientsConnection::readthread() {
	while(running)
	{
		std::map<uint64_t,int> clientfds_cache;
		std::map<int,uint64_t> fd_to_client_cache;
	
		clientfd_mutex.lock();
			clientfds_cache = clientfds;
			fd_to_client_cache = fd_to_client;
		clientfd_mutex.unlock();
		
		int size = clientfds_cache.size();
		struct pollfd *pfd = new struct pollfd[size];
		int i = 0;
		for(std::map<uint64_t,int>::iterator it = clientfds_cache.begin(); it != clientfds_cache.end(); it++, i++)
		{
			pfd[i].fd = (*it).second;
			pfd[i].events = POLLIN;
			pfd[i].revents = 0;
		}
			
		int pollres = poll(pfd, size, 5000);
			
		if(pollres == -1)
		{
			valid = false;
			throw "poll error";
		}
		
		if(pollres > 0)
		{
				for(i = 0; i < size; i++)
				{
					if((pfd[i].revents & POLLERR) || (pfd[i].revents & POLLNVAL))
					{
						std::cout << "Error poll from client " << std::hex << fd_to_client[pfd[i].fd] << "\n";
						clientfd_mutex.lock();
							clientfds.erase(fd_to_client[pfd[i].fd]);
							fd_to_client.erase(pfd[i].fd);
						clientfd_mutex.unlock();
						close(pfd[i].fd);
					}
					
					if(pfd[i].revents & POLLIN)
					{
						Packet *p = Packet::readByType(pfd[i].fd);
						if(p)
						{
							p->from = fd_to_client_cache[pfd[i].fd];
							queue_mutex.lock();
								rx_queue.push_back(p);
							queue_mutex.unlock();
						}
					}
				}
		}
		
		delete[] pfd;
	}
}

void ClientsConnection::closeClient(uint64_t client)
{
	clientfd_mutex.lock();
		int fd;
		fd_to_client.erase(fd = clientfds[client]);
		clientfds.erase(client);
	clientfd_mutex.unlock();

	close(fd);
}

void ClientsConnection::sendPacket(std::list<Packet *> ps, uint64_t client) {
	clientfd_mutex.lock();
		int fd = clientfds[client];
	clientfd_mutex.unlock();
	
	int size;
	uint8_t *b = crunchIntoBuffer(ps, &size);
	write(fd, b, size);
	delete[] b;
}

void ClientsConnection::sendPacket(Packet *p, uint64_t client) {
	std::list<Packet *> ps;
	ps.push_back(p);
	sendPacket(ps, client);
}

void ClientsConnection::sendPacket(std::list<Packet *> ps) {
	clientfd_mutex.lock();
		int size = clientfds.size();
		int *fds = new int[size];
		int i = 0;
		for(std::map<uint64_t,int>::iterator it = clientfds.begin(); it != clientfds.end(); it++, i++) {
			fds[i] = (*it).second;
		}
	clientfd_mutex.unlock();
	
	int bufsize;
	uint8_t *b = crunchIntoBuffer(ps, &bufsize);
	for(i = 0; i < size; i++)
		write(fds[i], b, bufsize);
	delete[] b;
}

void ClientsConnection::sendPacket(Packet *p) {
	std::list<Packet *> ps;
	ps.push_back(p);
	sendPacket(ps);
}

std::list<Packet*> ClientsConnection::getPackets(int n) {
	std::list<Packet*> retu;

	queue_mutex.lock();
		for(int i = 0; i < n; i++)
		{
			if(rx_queue.size() == 0) break;
			retu.push_back(rx_queue.front());
			rx_queue.pop_front();
		}
	queue_mutex.unlock();

	return retu;
}