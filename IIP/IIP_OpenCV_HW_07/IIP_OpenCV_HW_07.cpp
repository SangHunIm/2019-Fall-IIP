

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat bin = Mat(src.size(), CV_8UC1, Scalar(1));
	Mat dst = Mat(src.size(), CV_8UC1, Scalar(1)); 
	threshold(src, bin, 0, 255, THRESH_OTSU);
	dilate(bin, dst, Mat());
	imshow("dst", dst);
	waitKey(0);
	erode(src, dst, Mat(), Point(-1, -1), 2);
	imshow("dst", dst);
	waitKey(0);
	src.release();
	bin.release();
	dst.release();
}
