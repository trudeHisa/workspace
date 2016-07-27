#include"SceneManager.h"
SceneManager::SceneManager(){}
void SceneManager::add(Scene name,Scene_Ptr scene)
{
	scenes[name] = scene;
}
void SceneManager::change(Scene name)
{
	currentScene = scenes[name];
	currentScene->init();
}
void SceneManager::update()
{
	currentScene->update();
	if (currentScene->isEnd())
	{
		currentScene->finish();
		change(currentScene->next());
	}
}
void SceneManager::draw(const Renderer& renderer)
{
	currentScene->draw(renderer);
}
void SceneManager::finish()
{

}