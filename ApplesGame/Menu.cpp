#include "Menu.h"
#include "UI.h"

namespace ApplesGame
{
	void SetMenuItem(MenuItem& menuItem, std::string textTitle, const MenuEvent& menuEvent)
	{
		menuItem.isActive = true;
		UpdateTextAndPosition(menuItem.text, textTitle);
		menuItem.event = menuEvent;
	}
}