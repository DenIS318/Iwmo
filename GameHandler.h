#pragma once
#include "Game.h"
[event_receiver(native)]
class GameHandler : public Game
{

public:

	
	Event event;
	Game* gameinstance = Game::getGame();
	RenderWindow* windinst = Game::Getwindow();
	Event GameHandler::GetEvent()
	{
		return event;

	}
	void m_hookEvent(CSource* pSource);

	void m_unhookEvent(CSource* pSource);
private:
	View* camerapointer = gameinstance->GetCam();
	void GameHandler::OnEvent(Event eventt);


};