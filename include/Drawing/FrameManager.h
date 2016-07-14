#ifndef CLASSES_DRAWING_FRAMEMANAGER_H_
#define CLASSES_DRAWING_FRAMEMANAGER_H_

/*

Resource identifier passed to Image Factory to get the
required resource.

Used-by DrawableUnit

*/

class FrameManager {
public:
	FrameManager();

	int getFrameCur();
	void setFrameCur(int);

	int getFrameH();
	void setFrameH(int);

	int getFrameMax();
	void setFrameMax(int);

	int getFrameOffsetX();
	void setFrameOffsetX(int);

	int getFrameOffsetY();
	void setFrameOffsetY(int);

	int getFrameW();
	void setFrameW(int);

	int getFrameX();
	void setFrameX(int);

	int getFrameY();
	void setFrameY(int);

	void incrementFrame();
private:
	int frameMax;
	int frameCur;
	int frameX;
	int frameY;
	int frameW;
	int frameH;
	int frameOffsetX;
	int frameOffsetY;
};


#endif
