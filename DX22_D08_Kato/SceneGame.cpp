
#include "SceneGame.h"



SceneGame::SceneGame()
	: m_SceneManeger(nullptr)
{
	//シーンマネージャーInit();
	m_SceneManeger = new SceneManeger();
	m_SceneManeger->InitManeger();
}

SceneGame::~SceneGame()
{
	//シーンマネージャーのデストラクタ
	if (m_SceneManeger != nullptr)
	{
		m_SceneManeger->Destructor();

		delete m_SceneManeger;
		m_SceneManeger = nullptr;
	}
}

void SceneGame::Update()
{
	m_SceneManeger->UpdateManeger();
	
}

void SceneGame::Draw()
{
	m_SceneManeger->DrawManeger();
	
}

