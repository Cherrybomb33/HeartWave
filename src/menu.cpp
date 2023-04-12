#include "menu.h"

//Constructor that creates a new Menu object
Menu::Menu(QString name, QStringList menuOptions, Menu* parentMenu)
    : name(name), menuOptions(menuOptions), parentMenu(parentMenu)
{
    position = -1;
}

//Destructor that destroys the Menu object and any sub-menu objects it owns
Menu::~Menu() {
    for (Menu* sub : subMenu) {
        delete sub;
    }
}

//getters
QString Menu::getName() {
    return name;
}

void Menu::setName(QString n){
    name = n;
}

QStringList Menu::getMenuOptions() {
    return menuOptions;
}

void Menu::setMenuOptions(QStringList options){
    menuOptions = options;
}

Menu* Menu::getParentMenu() {
    return parentMenu;
}

int Menu::getPosition() {
    return position;
}

//get a pointer to a submenu object at a given index in the submenu list
Menu* Menu::get(int index) {
    if (index < 0 || index >= subMenu.size()) {
        return nullptr;
    }
    return subMenu[index];
}

//add a new submenu object to the sub-menu list of this menu object
void Menu::addChildMenu(Menu* menu) {
    if (menu != nullptr) {
        menu->position = subMenu.size();
        subMenu.push_back(menu);
    }
}
