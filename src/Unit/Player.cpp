#include "../../include/Unit/Player.h"

#include <cstdio>
#include <string>


#define PLAYER_BASE_SPEED 4.0f

Player::Player(std::string name, double x, double y, double w,double h) : DrawableUnit(name,x,y,w,h){

}

void Player::moveUpEvent(){
	setYAcceleration(-PLAYER_BASE_SPEED);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	setAction("walk-up");
}

void Player::moveDownEvent(){
	setYAcceleration(PLAYER_BASE_SPEED);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	setAction("walk-down");
}

void Player::moveLeftEvent(){
	this->setXAcceleration(-PLAYER_BASE_SPEED);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("walk-left");
}

void Player::moveRightEvent(){
	this->setXAcceleration(PLAYER_BASE_SPEED);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("walk-right");;
}

void Player::releaseUpEvent(){
	this->setYAcceleration(0);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("idle-up");
}

void Player::releaseDownEvent(){
	this->setYAcceleration(0);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("idle-down");
}

void Player::releaseLeftEvent(){
	this->setXAcceleration(0);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("idle-left");
}

void Player::releaseRightEvent(){
	this->setXAcceleration(0);
	this->setWidth(this->getFrameMgrFromCurAction()->getFrameW());
	this->setHeight(this->getFrameMgrFromCurAction()->getFrameH());
	this->setAction("idle-right");
}

void Player::move(){
	this->Unit::move();
}

