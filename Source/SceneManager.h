#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "IScene.h"
#include <map>
typedef std::map<Scene, IScene*> Scenes;
typedef Scenes::iterator ScenesIter;
class SceneManager
{
public:
	SceneManager();
	void Add(Scene name,IScene* scene);
	void Change(Scene name);
	void Update();
	void Draw(Renderer& renderer);
	void Finish();
private:
	Scenes scenes;
	IScene* currentScene;
};
#endif