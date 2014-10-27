//facedetect.cpp
//writen by ethan
//2014.10.12


#include "faceDetect.h"


static CvMemStorage* storage_faces=0;
static CvHaarClassifierCascade* cascade_faces=0;

FaceDetector::FaceDetector(IplImage* img)
{
	width=img->width;

	height=img->height;

	scale=2;

	gray_img=cvCreateImage(cvSize(width,height),8,1);

	if(img->nChannels==3)
	{
		cvCvtColor(img,gray_img,CV_BGR2GRAY);
	}
	else
		cvCopy(img,gray_img);

	small_img=cvCreateImage(cvSize(cvRound(width/scale),cvRound(height/scale)),8,1);

	char* cascade_name_faces="face.xml";

	cascade_faces=(CvHaarClassifierCascade*)cvLoad(cascade_name_faces,0,0,0);

	if(!cascade_faces)
	{
		printf("ERROR:Could not load classifier cascade\n");

	}

	storage_faces = cvCreateMemStorage(0);

	faceCount=0;

	facePos=new _Rect[MAX_FACE_COUNT_D_USTC];

}

FaceDetector::~FaceDetector()
{
	if(gray_img)
		cvReleaseImage(&gray_img);

	if(small_img)
		cvReleaseImage(&small_img);

	if(facePos)
		delete[] facePos;

	cvReleaseMemStorage(&storage_faces);

	cvReleaseHaarClassifierCascade(&cascade_faces);
	
}


void FaceDetector::runFaceDetector()
{
	CvSeq* faces =NULL;

	cvClearMemStorage( storage_faces);

	cvResize(gray_img,small_img, CV_INTER_LINEAR );

	cvEqualizeHist(small_img,small_img);

	faces = cvHaarDetectObjects(small_img , cascade_faces, storage_faces,1.6,2,0,cvSize(30,30));

	if(faces->total==1)
	{
		faceCount=faces->total;

		CvRect* r = (CvRect*)cvGetSeqElem(faces,0);

		facePos[0].left=cvRound(r->x*scale);

		facePos[0].top=cvRound(r->y*scale);

		facePos[0].right=facePos[0].left+cvRound(r->width*scale);

		facePos[0].bottom=facePos[0].top+cvRound(r->height*scale);
	}
	else
	{
		printf("检测到多于一个人脸，请调节参数！");
	}
}

int FaceDetector::getFaceCount()
{
	return faceCount;
}

int FaceDetector::getFacePosition(int* pos)
{
	pos[0]=facePos[0].left;

	pos[1]=facePos[0].top;

	pos[2]=facePos[0].right;

	pos[3]=facePos[0].bottom;

	return 0;
}

IplImage* FaceDetector::getGrayimage()
{
	if(gray_img)return gray_img;
}