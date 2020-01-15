// IIP_HW_14.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#pragma once

#include "pch.h"
#include "layer.h"
#include <iostream>
#include <time.h>

void test_xor()
{
	srand(time(0));
	//데이터 준비
	float* x[4];
	float* y[4];
	float error[1];
	for (int s = 0; s < 4; s++)
	{
		x[s] = new float[2];
		y[s] = new float[1];
	}
	x[0][0] = 0;
	x[0][1] = 0;
	x[1][0] = 0;
	x[1][1] = 1;
	x[2][0] = 1;
	x[2][1] = 0;
	x[3][0] = 1;
	x[3][1] = 1;
	y[0][0] = 0;
	y[1][0] = 1;
	y[2][0] = 1;
	y[3][0] = 0;
	Layer layer1(2, 3);
	Layer layer2(3, 1);
	for (int t = 0; t < 60000; t++)
	{
		int s = t % 4;
		layer1.feedForward(x[s]);
		layer2.feedForward(layer1.output);
		layer2.calcError(y[s], error);
		layer2.backPropagation(error, 0.1);
		layer1.backPropagation(layer2.backError, 0.1);
		if (t % 1000 == 0)
		{
			printf("%d :: \n", t);
			for (int i = 0; i < 4; i++)
			{
				layer1.feedForward(x[i]);
				layer2.feedForward(layer1.output);
				layer2.printOutput();
			}
		}
	}
	printf("the final tuned weight\n");
	layer2.printWeight();
}
void main()
{
	test_xor();
	printf("done.\n");
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
