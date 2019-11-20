// IIP_OpenCV_HW_11.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src8 = imread("lena.bmp", CV_8UC1);
	Mat src32 = Mat(src8.size(), CV_32FC1, 1);
	Mat dct32 = Mat(src8.size(), CV_32FC1, 1);
	Mat inversed32 = Mat(src8.size(), CV_32FC1, 0);
	src8.convertTo(src32, CV_32FC1);
	dct(src32, dct32, CV_DXT_FORWARD);
	dct(dct32, inversed32, CV_DXT_INVERSE);

	Mat dct8 = Mat(src8.size(), CV_8UC1, 0);
	Mat inversed8 = Mat(src8.size(), CV_8UC1, 0);

	dct32.convertTo(dct8, CV_8UC1, 0.5);	inversed32.convertTo(inversed8, CV_8UC1);
	imshow("original", src8);
	imshow("FDCT", dct8);
	imshow("restore", inversed8);
	waitKey(0);
}
