#include "Menu.h"
#include "UI.h"

namespace ApplesGame
{
	void SetMenuItem(MenuItem& menuItem, std::string textTitle, const MenuItemType& menuItemType)
	{
		menuItem.isActive = true;
		UpdateTextAndPosition(menuItem.text, textTitle);
		menuItem.itemType = menuItemType;
	}

	void UpdateItemString(MenuItem& menuItem, std::string textTitle)
	{
		UpdateTextAndPosition(menuItem.text, textTitle);
	}
}