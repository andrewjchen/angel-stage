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
	virtual coordinate_t getX() const;
	virtual coordinate_t getY() const;
	virtual coordinate_t setX(const coordinate_t & x);
	virtual coordinate_t setY(const coordinate_t & y);
	virtual Position relative(const Position & origin) const;
	virtual bool within(const coordinate_t & w, const coordinate_t & h) const;
	virtual coordinate_t distance(const Position & other) const;
};


Position gameFromScreen(const Position & viewpoint,
						const Position & screen_pos);

Position screenFromGame(const Position & viewpoint,
						const Position & game_pos);

#endif /* _POSITION_H_ */
