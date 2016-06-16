#include"SceneManager.h"
SceneManager::SceneManager(){}
void SceneManager::Add(Scene name,Scene_Ptr scene)
{
	scenes[name] = scene;
}
void SceneManager::Change(Scene name)
{
	currentScene = scenes[name];
	currentScene->Init();
}
void SceneManager::Update()
{
	currentScene->Update();
	if (currentScene->IsEnd())
	{
		currentScene->Finish();
		Change(currentScene->Next());
	}
}
void SceneManager::Draw(const Renderer& renderer)
{
	currentScene->Draw(renderer);
}
void SceneManager::Finish()
{

}