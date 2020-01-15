#pragma once

#include "pch.h"
#include "Layer.h"
#include <cmath>
#include <stdio.h>


Layer::Layer(int n, int m)
{
	this->n = n;
	this->m = m;
	output = new float[m];
	w = new float*[n];
	for (int i = 0; i < n; i++)
	{
		w[i] = new float[m];
		for (int j = 0; j < m; j++)
		{
			w[i][j] = rand() / (float)RAND_MAX;
		}
	}
	b = new float[m];
	for (int j = 0; j < m; j++)
	{
		b[j] = rand() / (float)RAND_MAX;
	}
	delta = new float[m];
	backError = new float[n];
}
Layer::~Layer()
{
	delete output;
	for (int i = 0; i < n; i++)
	{
		delete w[i];
	}
	delete w;
	delete b;
	delete delta;
	delete backError;
}
float sigmoid(float val)
{
	return 1 / (1 + exp(-val));
}
void Layer::feedForward(float* input)
{
	for (int j = 0; j < m; j++)
	{
		float sum = 0;
		for (int i = 0; i < n; i++)
		{
			sum += w[i][j] * input[i]; 
		}
		output[j] = sigmoid(sum + b[j]); 
	}
	
	this->input = input;
}
void Layer::calcError(float* y, float* error)
{
	for (int j = 0; j < m; j++)
	{
		error[j] = output[j] - y[j];
	}
}
void Layer::backPropagation(float* error, float alpha)
{
	for (int j = 0; j < m; j++)
	{
		delta[j] = error[j] * output[j] * (1 - output[j]);
	}
	for (int i = 0; i < n; i++)
	{
		float sum = 0;
		for (int j = 0; j < m; j++)
		{
			sum += delta[j] * w[i][j];
		}
		backError[i] = sum;
	}
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			w[i][j] -= input[i] * delta[j] * alpha;
		}
		b[j] -= delta[j] * alpha;
	}
}
void Layer::printOutput()
{
	for (int i = 0; i < m; i++)
		printf("%0.3lf  ", output[i]);
	printf("\n");
}

void Layer::printWeight()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%0.3lf  ", w[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}