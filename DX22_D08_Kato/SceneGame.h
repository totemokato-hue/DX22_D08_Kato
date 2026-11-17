#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include "Ground.h"

#include"SceneManeger.h"
class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;

private:
	//==================================================
	// ƒƒ“ƒo•Ï”
	//==================================================
	SceneManeger* m_SceneManeger;
	
};

#endif // __SCENE_GAME_H__