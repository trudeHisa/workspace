/*
CSVStream.h
*/
#include "Array2D.h"
class CSVStream
{
public:
	CSVStream();
	/*�o��*/
	void output(Array2D<int>* out, const char* name)const;
	/*����*/
	void input(Array2D<int>* out, const char* name)const;
};
