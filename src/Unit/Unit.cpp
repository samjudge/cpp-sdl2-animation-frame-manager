/*
 * Unit.cpp
 *
 *  Created on: 7 Jul 2015
 *      Author: sjudge
 */

#include "../../include/Unit/Unit.h"

#include <cstdio>

Unit::Unit(std::string name, double x, double y, double w, double h) {
	this->name = name;
	this->xAcceleration = 0;
	this->yAcceleration = 0;
	this->xPos = x;
	this->yPos = y;
	this->width = w;
	this->height = h;
	this->Str = 0;
	this->Luk = 0;
	this->Int = 0;
	this->Dex = 0;

}

double Unit::getHeight() {
	return height;
}

void Unit::setHeight(double height) {
	this->height = height;
}

std::string Unit::getName() {
	return name;
}

void Unit::setName(std::string name) {
	this->name = name;
}

double Unit::getWidth() {
	return width;
}

void Unit::setWidth(double width) {
	this->width = width;
}

double Unit::getXPos() {
	return xPos;
}

void Unit::setXPos(double pos) {
	this->xPos = pos;
}

double Unit::getYPos() {
	return yPos;
}

void Unit::setYPos(double pos) {
	this->yPos = pos;
}

double Unit::getXAcceleration(){
	return xAcceleration;
}
void Unit::setXAcceleration(double xAcceleration){
	this->xAcceleration = xAcceleration;
}

double Unit::getYAcceleration(){
	return yAcceleration;
}

void Unit::setYAcceleration(double yAcceleration){
	this->yAcceleration = yAcceleration;
}

void Unit::setAction(std::string action){
	this->curAction = action;
}

std::string Unit::getAction(){
	return this->curAction;
}

void Unit::move(){
	xPos += xAcceleration;
	yPos += yAcceleration;
}
