
#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv; 
using namespace std;

void Arithmetic_Add(Mat src, Mat &dst, int value);

int main()
{
	Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat dst = src.clone(); 
	imshow("Original", src); 
	Arithmetic_Add(src, dst, 40); 
	imshow("Result", dst); 
	waitKey(0); 
	src.release();
	dst.release();
}

void Arithmetic_Add(Mat src, Mat &dst, int value)
{
	int width = src.cols; 
	int height = src.rows;
	uchar *srcData = src.data;
	uchar *dstData = dst.data;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int temp = srcData[(y*width) + x] + value;

			if (temp > 255)
				dstData[(y*width) + x] = 255;
			else
				dstData[(y*width) + x] = temp;
		}
	}
}
