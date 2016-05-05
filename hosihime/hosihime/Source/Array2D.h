/*
Array2D.h
*/
#ifndef _ARRAY2D_H_
#define _ARRAY2D_H_
//配列（ポインタ）を2次元配列風に扱う
//色々な方で利用できるようtemplateを使っている
template< class T > class Array2D{
public:
	Array2D() : mArray(0){}
	~Array2D()
	{
		delete[] mArray;
		mArray = 0;
	}
	/*0=height,1=width*/
	void setSize(int size0, int size1)
	{
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[size0 * size1];
	}
	T& operator()(int index0, int index1){
		return mArray[index1 * mSize0 + index0];
	}
	const T& operator()(int index0, int index1) const {
		return mArray[index1 * mSize0 + index0];
	}
	const int& getSize0()const
	{
		return mSize0;
	}
	const int& getSize1()const
	{
		return mSize1;
	}
private:
	T* mArray;
	int mSize0;
	int mSize1;
};

#endif