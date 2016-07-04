#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "IScene.h"
#include <unordered_map>
#include <memory>
typedef std::shared_ptr<IScene>Scene_Ptr;
typedef std::unordered_map<Scene, Scene_Ptr> Scenes;
class SceneManager
{
public:
	SceneManager();
	void Add(Scene name, Scene_Ptr scene);
	void Change(Scene name);
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
private:
	Scenes scenes;
	Scene_Ptr currentScene;
};
#endif