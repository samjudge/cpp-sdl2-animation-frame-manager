#include "../../include/Drawing/FrameManager.h"

#include <cstdio>

FrameManager::FrameManager() {
	frameMax = 0;
	frameCur = 0;
	frameX = 0;
	frameY = 0;
	frameW = 0;
	frameH = 0;
	frameOffsetX = 0;
	frameOffsetY = 0;
}

int FrameManager::getFrameCur() {
	return frameCur;
}

void FrameManager::setFrameCur(int frameCur) {
	this->frameCur = frameCur;
}

int FrameManager::getFrameH() {
	return frameH;
}

void FrameManager::setFrameH(int frameH) {
	this->frameH = frameH;
}

int FrameManager::getFrameMax() {
	return frameMax;
}

void FrameManager::setFrameMax(int frameMax) {
	this->frameMax = frameMax;
}

int FrameManager::getFrameOffsetX() {
	return frameOffsetX;
}

void FrameManager::setFrameOffsetX(int frameOffsetX) {
	this->frameOffsetX = frameOffsetX;
}

int FrameManager::getFrameOffsetY() {
	return frameOffsetY;
}

void FrameManager::setFrameOffsetY(int frameOffsetY) {
	this->frameOffsetY = frameOffsetY;
}

int FrameManager::getFrameW() {
	return frameW;
}

void FrameManager::setFrameW(int frameW) {
	this->frameW = frameW;
}

int FrameManager::getFrameX() {
	return frameX;
}

void FrameManager::setFrameX(int frameX) {
	this->frameX = frameX;
}

int FrameManager::getFrameY() {
	return frameY;
}

void FrameManager::setFrameY(int frameY) {
	this->frameY = frameY;
}

void FrameManager::incrementFrame(){
	if(this->frameCur != this->frameMax){
		this->frameCur = this->frameCur+1;
	} else {
		this->frameCur = 0;
	}
}
