#pragma once
class Layer
{
public:
	int n;//인풋 노드의 개수
	int m;//아웃풋 노드의 개수
	float* input; //인풋 노드
	float* output; //아웃풋 노드
	float** w; //웨이트
	float* b; //바이어스
	float* delta; //중간 계산을 위한 델타
	float* backError; //backPropagation을 위해 전이되는 에러
	Layer(int n, int m);
	~Layer();
	void feedForward(float* input);
	void calcError(float* y, float* error); //최종 에러 계산
	void backPropagation(float* error, float alpha);
	void printWeight();	void printOutput();
};

