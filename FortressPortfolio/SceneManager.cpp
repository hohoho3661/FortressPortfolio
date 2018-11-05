#include "stdafx.h"
#include "SceneManager.h"

// 정보를 저장해놓고 바꾸고싶은 순간에 바꿈
// 씬 설계가 중요
// 릴리즈.. 등등. 꼬일수가 있다.
// 씬마다 공유되는 리소스들에 대해 .. 최상위(메인 게임)에서 씬마다 공유하는 리소스들을 작업을 해주고, 씬 별로 해제할수도있다.
// 직접 안꼬이게 작업해줘야 문제가 없음. ( 씬 단위로 )

//		 선생님의 추천 방식	-	씬 생성과 추가는 메인게임에서... 이미지 처리도 메인게임에서 ( 이게 안전하다 )
//


GameNode* SceneManager::currentScene = NULL;
GameNode* SceneManager::readyScene = NULL;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	currentScene = NULL;
	readyScene = NULL;
}

void SceneManager::Release()
{
	map<string, GameNode*>::iterator it;

	for (it = sceneList.begin(); it != sceneList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second == currentScene)
				it->second->Release();

			delete it->second;
			it = sceneList.erase(it);
		}
		else
			it++;
	}

	sceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
		currentScene->Render(hdc);
}

GameNode * SceneManager::AddScene(string sceneName, GameNode * scene)
{
	if (!scene)
		return NULL;

	sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

bool SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*>::iterator it;
	it = sceneList.find(sceneName);

	if (it == sceneList.end())
		return false;

	if (it->second == currentScene)
		return false;

	if (it->second->Init())
	{
		if (currentScene)
			currentScene->Release();

		currentScene = it->second;

		return true;
	}

	return false;
}