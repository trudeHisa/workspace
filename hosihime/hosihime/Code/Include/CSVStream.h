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
	void output(int& out, const char* name)const;
	/*����*/
	void input(Array2D<int>* out, const char* name)const;
	void input(int& out, const char* name)const;
	void loadScore(int& input, const int stage, const char* name)const;
	void save(const int& out, int stage,const char* name)const;
};
