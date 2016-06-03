#include "StarDataStream.h"
#include<iostream>
#include<fstream>
#include<sstream>
StarDataStream::StarDataStream()
{
}

StarDataStream::~StarDataStream()
{
}
void StarDataStream::input(std::vector<std::vector<std::string>>* data, const char* name)
{
	std::ifstream ifs(name);
	if (!ifs)
	{
		return;
	}
	std::string str;
	std::vector<std::string>param;
	data->clear();
	while (getline(ifs, str))
	{
		std::string token;
		std::istringstream stream(str);
		param.clear();
		while (getline(stream, token, ','))
		{
			param.push_back(token);
		}
		data->push_back(param);
	}
	ifs.close();
}