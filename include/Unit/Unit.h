#ifndef CLASSES_UNITS_UNIT_H_
#define CLASSES_UNITS_UNIT_H_

#include <string>

class Unit {
public:
	Unit();
	Unit(std::string,double,double,double,double);

	double getHeight();
	void setHeight(double height);

	std::string getName();
	void setName(std::string name);

	double getWidth();
	void setWidth(double width);

	double getXPos();
	void setXPos(double pos);

	double getYPos();
	void setYPos(double pos);

	double getXAcceleration();
	void setXAcceleration(double);

	double getYAcceleration();
	void setYAcceleration(double);

	void setAction(std::string);
	std::string getAction();

	void move();

	double xPos;
	double yPos;

private:

	std::string name;
	std::string curAction;
	double xAcceleration;
	double yAcceleration;
	double width;
	double height;
	double Str;
	double Luk;
	double Int;
	double Dex;

};

#endif
