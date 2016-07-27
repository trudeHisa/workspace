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
	void add(Scene name, Scene_Ptr scene);
	void change(Scene name);
	void update();
	void draw(const Renderer& renderer);
	void finish();
private:
	Scenes scenes;
	Scene_Ptr currentScene;
};
#endif