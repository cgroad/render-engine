#include "Core/MathTool.h"
#include <sys/timeb.h>
#include <stdlib.h>
MathTool::MathTool()
{
}

MathTool::~MathTool()
{
}

float MathTool::getPercent(int loopSecond)
{
	struct timeb tb;
	ftime(&tb);
	time_t milliSecond = tb.time * 1000 + tb.millitm;
	return (milliSecond % (loopSecond * 1000)) / (loopSecond * 1000.0f);
}