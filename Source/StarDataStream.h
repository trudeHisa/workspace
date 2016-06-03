#ifndef _STARDATASTREAM_H_
#define _STARDATASTREAM_H_

#include <vector>
#include<string>
class StarDataStream
{
public:
	StarDataStream();
	~StarDataStream();
	void input(std::vector<std::vector<std::string>>* data, const char* name);
private:

};
#endif