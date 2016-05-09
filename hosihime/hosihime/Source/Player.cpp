#include "Player.h"
#include "renderer.h"
#include "game.h"

bool jflag = false;
int y_temp = 0;
int y_prev = 0;
Player::Player()
:ang(0), pos(800,600)
{

}
Player::~Player()
{
	
}
void Player::Init()
{
	isEnd = false;
	
}
void Player::Update()
{
	move();
}
void Player::move()
{
	if (jflag == true){
		y_temp = pos.y;
		pos.y += (pos.y - y_prev)+1;
		y_prev = y_temp;
		if (pos.y == 600)
			jflag = false;
	}
	if (GetAsyncKeyState(VK_UP) && jflag == false)
	{
			jflag = true;
			y_prev = pos.y;
			pos.y = pos.y - 20;
	}
}
void Player::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("player.bmp",&pos,NULL,&GSvector2(0, 0),NULL,ang,NULL);
}

void Player::Finish()
{
}
bool Player::IsEnd()
{
	return isEnd;
}