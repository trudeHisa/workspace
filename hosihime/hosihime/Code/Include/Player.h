#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
#include "Animation.h"
#include "Star.h"
#include "IEffectMediator.h"
class Device;
class Player :public GameObject
{
public:
	Player(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		Scroll* scroll, Device& device,IEffectMediator* effectMediator);
	virtual ~Player();
	void updata();
    void initialize();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);
	GameObject* clone(const GSvector2& position);
	void endMove();
	bool getIsClear();
	void nonCollision();
private:
	void moving();
	void gravity();
	//向きを返す
	const float moveHorizontal();
	void rideUpDown();	
	//jump
	void jumpStart();
	void jump();
	void jumpEnd();

	const bool respawn();

	void ride(const GameObject* obj);

	const bool isRide()const;
	//collision
	void collisionGround(const GameObject* obj);
	void collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);

	//anim
	void changeAnimation(int dir);
	const std::string getDirKey(int dir);
private:
	
	float jumpPower;
	float speed;
	Timer respawnCount;

	bool isMagpieRide;
	bool isJump;
	bool isGround;
	bool isClear;
	bool JumpEndSE;
	int count;

	bool ishold;
	/**
	*リスポン中か？
	*プレイヤーが画面外だとリスポンするため
	*画面外にリスポンし続ける
	*取りあえず回避するための変数
	*
	*********************
	**要リファクタリング*
	*********************
	*/
	bool isRespawn;

	GSvector2 respawnPos;
	Scroll* scroll;
	Device& device;

	GSvector2 positionsRight;
	GSvector2 positionsLeft;

	unsigned int rideStarPointerNum;


	const float GRAVITY;
	const float JUMPMAXPOW;
	const float JUMPSPEED;
	const float VERTICAL;
	const float JUMPVERTICAL;
	const GSvector2 SCROLLOFFSET;
	


	//int direction;
	std::string currentDirAnimeKey;
	//float lr;
	Animation animation;
	AnimationTimer animeTimer;

	IEffectMediator* effectMediator;
};
#endif