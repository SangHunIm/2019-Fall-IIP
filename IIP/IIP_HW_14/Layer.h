#pragma once
class Layer
{
public:
	int n;//��ǲ ����� ����
	int m;//�ƿ�ǲ ����� ����
	float* input; //��ǲ ���
	float* output; //�ƿ�ǲ ���
	float** w; //����Ʈ
	float* b; //���̾
	float* delta; //�߰� ����� ���� ��Ÿ
	float* backError; //backPropagation�� ���� ���̵Ǵ� ����
	Layer(int n, int m);
	~Layer();
	void feedForward(float* input);
	void calcError(float* y, float* error); //���� ���� ���
	void backPropagation(float* error, float alpha);
	void printWeight();	void printOutput();
};

