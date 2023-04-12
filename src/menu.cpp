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

void Menu::deleteChildMenu(Menu* menu) {
    //find the index of the menu to be deleted
    int index = menu->getPosition();

    //remove the menu from the subMenu list
    subMenu.removeAt(index);

    //update the positions of the remaining sub-menus
    for (int i = index; i < subMenu.size(); i++) {
        subMenu[i]->position = i;
    }

    //remove the menu's name from the menuOptions list
    menuOptions.removeAt(index);

    //delete the menu
    delete menu;
}

void Menu::deleteAllSubMenus() {
    //delete all submenus
    for (Menu* sub : subMenu) {
        sub->deleteAllSubMenus();
        delete sub;
    }

    // Clear the subMenu list and menuOptions list
    subMenu.clear();
    menuOptions.clear();
}
