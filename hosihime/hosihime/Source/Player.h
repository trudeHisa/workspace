#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Renderer.h"
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void move();
	void Draw(Renderer& renderer);
	void Finish();
	bool IsEnd();
private:
	bool isEnd;
	GSvector2 pos;
	float ang;
};
#endif