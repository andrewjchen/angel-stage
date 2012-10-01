#ifndef _POSITION_H_
#define _POSITION_H_

typedef double coordinate_t;

class Position {
private:
	coordinate_t _x, _y;

public:
	virtual void init(const coordinate_t & x, const coordinate_t & y);
	Position(const coordinate_t & x, const coordinate_t & y) {this->init(x, y);}
	Position() {this->init(0.0, 0.0);}
	virtual ~Position() {}
	virtual coordinate_t get_x() const;
	virtual coordinate_t get_y() const;
	virtual coordinate_t set_x(const coordinate_t & x);
	virtual coordinate_t set_y(const coordinate_t & y);
	virtual Position relative(const Position & origin) const;
	virtual bool within(const coordinate_t & w, const coordinate_t & h) const;
	virtual coordinate_t distance(const Position & other) const;
	virtual bool operator==(const Position & other) {
		return (_x == other.get_x() && _y == other.get_y());
	};
	virtual bool operator!=(const Position & other) {
		return (_x != other.get_x() && _y != other.get_y());
	};
	virtual bool in_rect(const Position & corner1,
						 const Position & corner2) const;
};


Position gameFromScreen(const Position & viewpoint,
						const Position & screen_pos);

Position screenFromGame(const Position & viewpoint,
						const Position & game_pos);


#endif /* _POSITION_H_ */
