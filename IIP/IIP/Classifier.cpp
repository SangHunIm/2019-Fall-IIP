#include "stdafx.h"
#include "Classifier.h"


Classifier::Classifier()
{
}

Classifier::Classifier(int direction, int th, int axis)
{
	Direction = direction;
	Th = th;
	Axis = axis;
}


Classifier::~Classifier()
{
}

int Classifier::Classify(Sample& sample)
{
	if (Axis == 1)  //u�� ����
	{
		if (Direction * sample.x_u >= Direction * Th)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if (Axis == 2)  //v�� ����
	{
		if (Direction * sample.x_v >= Direction * Th)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else//����
	{
		return 0;
	}
}