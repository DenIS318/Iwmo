#include "GameHandler.h"



void GameHandler::m_hookEvent(CSource* pSource) {
	cout << "Hooked! Called from GameHandler!" << endl;

	__hook(&CSource::OnEvent, pSource, &GameHandler::OnEvent, this);
}

void GameHandler::m_unhookEvent(CSource* pSource) {
	__unhook(&CSource::OnEvent, pSource, &GameHandler::OnEvent);
}
void GameHandler::OnEvent(Event eventt)
{
	event = eventt;

	if (debug)
	{
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::X)
		{

			if (debug)
			{
				int x = 0;
				int y = 0;
				cout << "Enter x" << endl;
				cin >> x;
				cout << "Enter y" << endl;
				cin >> y;
				Vector2f vec(x, y);
				cout << "Camera centered to " << x << ", " << y << endl;
				gameinstance->camera.setCenter(vec);
				//cout << "Camera pointer in derived is %p" << camerapointer << endl;
				cout << "And now camera centered to " << camerapointer->getCenter().x << ", " << camerapointer->getCenter().y << endl;
			}
		}
	}
}