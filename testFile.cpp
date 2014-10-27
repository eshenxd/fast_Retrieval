#include "header.h"
#include "faceDetect.h"
#include "facePoint.h"
#include "faceAlign.h"
#include "featureExtract.h"


#include "../include/index.h"
#include "../include/hash.h"

using namespace std;
using namespace hash;


struct info_type
{
	int id;
	HashBuilder::code_type code;
};

int main(int argc,char* argv[])
{
	IplImage* img_in=cvLoadImage("2.jpg",CV_LOAD_IMAGE_ANYCOLOR);

	//facedetect
	FaceDetector FD(img_in);

	FD.runFaceDetector();

	int num=FD.getFaceCount();

	if(num==0)
	{
		cout<<"no face detected!"<<endl;
	}
	else
	{
		int* rect=new int[4];

		FD.getFacePosition(rect);

		//facepoint

		FacePoints FP(FD.getGrayimage());

		FP.runFacePoints(num,rect);

		int *pos=new int[10];//pos存储的是关键点的位置坐标

		pos=FP.getFacePoints();

		//facealign
		FaceAlign FA(FD.getGrayimage(),rect,pos);

		FA.runFaceAlign();

		int* F_pos=new int[10];

		F_pos=FA.getFaceAlignPos();//获取归一化后的特征点坐标

		IplImage* AlignFace=FA.getAlignimg();//获取归一化后的图片

		
		cvSaveImage("alingface.jpg",AlignFace);

		/*
		    feature extract
		*/
		
		float* feature = new float[128];

		featureExtract(feature);
		/*
		    hash
		*/
		string hashconfig = "";


		// initialize hasher for hash code generation
		KernelHash hasher;
		hasher.load(hashconfig);	// initialize hash from config file
		int codelen = hasher.length();

		// initialize fast indexing for retrieving
		const int nhashtables = 5;
		FastRetriever<info_type> retriever(nhashtables, codelen);

		// type aliasing
		typedef HashBuilder::code_type                   code_type;
		typedef FastRetriever<info_type>::candidate_type candidate_type;

		//// insert
		//info_type t = { 0, 0 };

		// retrieve
		//float feature[128] = { 0 };
		code_type c = hasher.hash(feature, sizeof(feature) / sizeof(float));
		auto results = retriever.query(c);


		delete[] rect;
		delete[] pos;
		delete[] F_pos;
		delete[] feature;

	
	}
	

	


	
	
	

	return 0;
}