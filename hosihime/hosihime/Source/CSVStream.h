/*
CSVStream.h
*/
#include "Array2D.h"
class CSVStream
{
public:
	CSVStream();
	/*o—Í*/
	void output(Array2D<int>* out, const char* name);
	/*“ü—Í*/
	void input(Array2D<int>* out, const char* name);
};
