// IIP_OpenCV_HW_06.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <opencv2\opencv.hpp>

#define COUNT 3

using namespace std;
using namespace cv;

int main()
{
	Mat image1 = imread("image1.jpg");
	Mat image2 = imread("image2.jpg");
	Mat gray1 = Mat::zeros(image1.size(), CV_8UC1); 
	Mat gray2 = Mat::zeros(image1.size(), CV_8UC1);
	cvtColor(image1, gray1, CV_BGR2GRAY);
	cvtColor(image2, gray2, CV_BGR2GRAY);
	vector<Point2f> points1, points2;
	vector<uchar> isFound; 
	vector<float> error;
	points1.push_back(Point2f(223, 86));
	points1.push_back(Point2f(212, 69));
	points1.push_back(Point2f(67, 291));
	calcOpticalFlowPyrLK(gray1, gray2, points1, points2, isFound, error, 
		Size(5, 5), 3, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3));
	for (int i = 0; i < COUNT; i++)
	{
		if (isFound[i])
		{
			circle(image1, points1[i], 2, Scalar(255, 255, 0));
			line(image1, points1[i], points2[i], Scalar(255, 255, 0), 2);
			circle(image2, points2[i], 2, Scalar(255, 255, 0));
		}
		else
		{
			circle(image1, points1[i], 2, Scalar(255, 255, 0));
		}
	}
	imshow("image1", image1);
	imshow("image2", image2);
	waitKey();
	return 0;
}