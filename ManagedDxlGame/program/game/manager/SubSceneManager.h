#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../scene/ScenePlay.h"

class SubSceneManager final{
private :

	SubSceneManager();


public :

	static std::shared_ptr<SubSceneManager> GetInstance();

	~SubSceneManager();

	enum class ScenePlaySubScene {
		DUNGEON,
		BATTLE
	};

	void setScenePlay(std::shared_ptr<ScenePlay> scenePlay) { scenePlay_ = scenePlay; }

	void ChangeSubScene(ScenePlaySubScene nextSubScene);


private :

	std::shared_ptr<ScenePlay> scenePlay_ = nullptr;



};