#pragma once

#include "header.h"


#define AlignWidth_A_USTC 140
#define AlignHeight_A_USTC 160

struct LastPos  //存放矫正过后的人脸关键点位置坐标
{
	int left_eye_x;
	int left_eye_y;

	int right_eye_x;
	int right_eye_y;

	int nose_x;
	int nose_y;

	int left_mouth_x;
	int left_mouth_y;

	int right_mouth_x;
	int right_mouth_y;
};

class FaceAlign
{
public:
	FaceAlign(IplImage*,int*,int*);//同样是灰度的
	~FaceAlign();

	int runFaceAlign();
	
	IplImage* getAlignimg();

	int* getFaceAlignPos();

protected:
private:
	int width,height;

	int* rect;
	int* pos;

	IplImage* grayimg;
	IplImage* rotaimg;
	IplImage* alignimg;

	LastPos* Pos;

	CvMat* map;

	int* FinalPos;
};