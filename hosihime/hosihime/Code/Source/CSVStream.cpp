/*
CSVStream.cpp
*/
#include "CSVStream.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <vector>
CSVStream::CSVStream()
{
}
void CSVStream::output(Array2D<int>* out, const char* name)const
{
	std::ofstream ofs(name);
	for (int y = 0; y < out->getSize0(); y++)
	{
		for (int x = 0; x < out->getSize1(); x++)
		{
			ofs << (*out)(y, x) << ',';
		}
		ofs << std::endl;
	}
	ofs.close();
}


void CSVStream::output(int& out, const char* name)const
{
	std::ofstream ofs(name);

	ofs << (out);
	ofs << std::endl;

	ofs.close();
}

void CSVStream::input(Array2D<int>* input, const char* name)const
{
	std::ifstream ifs(name);
	if (!ifs)
	{
		return;
	}
	std::vector<int> values;
	std::string str;
	int width = 0;
	int height = 0;
	while (getline(ifs, str))
	{
		width = 0;
		std::string token;
		std::istringstream stream(str);
		while (getline(stream, token, ','))
		{
			values.push_back(stoi(token));
			width++;
		}
		height++;
	}
	ifs.close();
	input->setSize(height, width);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			(*input)(y, x) = values[y*width + x];
		}
	}
}
void CSVStream::input(int& input, const char* name)const
{
	std::ifstream ifs(name);
	if (!ifs)
	{
		return;
	}
	std::string str;
	while (std::getline(ifs, str))
	{
		std::string token;
		std::istringstream stream(str);
		while (std::getline(stream, token))
		{
			int temp = std::stoi(token);//数値に変換
			input = temp;
		}
	}
	ifs.close();
}
//ｎ行目を読み込み OK
void CSVStream::loadScore(int& input, const int stage, const char* name)const
{
	std::ifstream ifs(name);
	if (!ifs)
	{
		return;
	}
	std::string str;
	std::vector<int> vec;
	while (std::getline(ifs, str))
	{
		std::string token;
		std::istringstream stream(str);
		while (std::getline(stream, token))
		{
			int temp = std::stoi(token);//数値に変換
			vec.push_back(temp);
		}
	}
	ifs.close();
	input = vec[stage];
}

//ｎ行目を書き込み
void CSVStream::save(const int& out, int stage, const char* name)const
{
	int temp[3];
	for (int i = 0; i < 3; i++)//一時保存
	{
		loadScore(temp[i], i, name);
	}
	temp[stage] = out;//指定したステージの箇所を書き換え


	std::ofstream ofs(name);
	for (int i = 0; i < 3; i++)//書き換えた箇所を含む全てを出力
	{
		ofs << temp[i] << std::endl;
	}
//	ofs << (out);
	//ofs << std::endl;

	ofs.close();
}
