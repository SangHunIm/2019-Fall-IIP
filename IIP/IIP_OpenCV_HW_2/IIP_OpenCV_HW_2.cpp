// IPP_OpenCV_HW_2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define thresh 100 
#define maxValue 255

int main()
{
	Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat dst = src.clone(); 

	threshold(src, dst, thresh, maxValue, THRESH_BINARY);

	imshow("Original", src);
	imshow("Result", dst);

	waitKey(0);

	src.release();
	dst.release();
}
