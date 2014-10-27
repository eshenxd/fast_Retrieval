#ifndef FACEDETECT_H

#define FACEDETECT_H

#pragma once

#include "header.h"

#define MAX_FACE_COUNT_D_USTC  100 

struct _Rect
{
	int left;
	int right;
	int top;
	int bottom;
};

class FaceDetector
{
public:
	FaceDetector(IplImage*);
	~FaceDetector();

	void runFaceDetector();
	int getFacePosition(int* pos);
	int getFaceCount();
	IplImage* getGrayimage();


protected:
private:
	int width;
	int height;

	IplImage* gray_img;
	IplImage* small_img;

	int faceCount;
	double scale;

	_Rect* facePos;


};

#endif



