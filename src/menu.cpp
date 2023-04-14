#include "menu.h"

//constructor
Menu::Menu(QString name, QStringList menuOptions, Menu* parentMenu)
    : name(name), menuOptions(menuOptions), parentMenu(parentMenu)
{
    position = -1;
}

//destructor that destroys the Menu object and any childmenu objects
Menu::~Menu() {
    for (Menu* sub : subMenu) {
        delete sub;
    }
}

//getters and setters
//get the menu name
QString Menu::getName() {
    return name;
}

//get a list of submenu names
QStringList Menu::getMenuOptions() {
    return menuOptions;
}

//get a pointer to the parent menu
Menu* Menu::getParentMenu() {
    return parentMenu;
}

//get the position of the menu in a menu list
int Menu::getPosition() {
    return position;
}

//set the menu name
void Menu::setName(QString n){
    name = n;
}

//set the display of menu items of a menu
void Menu::setMenuOptions(QStringList options){
    menuOptions = options;
}


//get a pointer to a child menu object at a given index
Menu* Menu::get(int index) {
    if (index < 0 || index >= subMenu.size()) {
        return nullptr;
    }
    return subMenu[index];
}

//add a new child menu object to this menu object
void Menu::addChildMenu(Menu* menu) {
    if (menu != nullptr) {
        menu->position = subMenu.size();
        subMenu.push_back(menu);
    }
}

//delete a child menu of a menu object
void Menu::deleteChildMenu(Menu* menu) {
    //find the index of the menu to be deleted
    int index = menu->getPosition();

    //remove the menu from the child menu list
    subMenu.removeAt(index);

    //update the positions of the remaining submenus
    for (int i = index; i < subMenu.size(); i++) {
        subMenu[i]->position = i;
    }

    //remove the menu's name from the menuOptions list
    menuOptions.removeAt(index);

    delete menu;
}

//recursively delete a menu's all submenus
void Menu::deleteAllSubMenus() {
    for (Menu* sub : subMenu) {
        sub->deleteAllSubMenus();
        delete sub;
    }

    //clear the submenu list and menuOptions list
    subMenu.clear();
    menuOptions.clear();
}
