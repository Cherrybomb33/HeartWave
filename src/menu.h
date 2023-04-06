#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QVector>

//Menu class serves as an object that will be displayed and interacted with on the main window
class Menu {

public:
    //Constructor that creates a new Menu object with a given name, list of menu items, and parent menu.
    explicit Menu(QString, QStringList, Menu*);  
    ~Menu();  //Destructor that destroys the Menu object and any sub-menu objects that it contains

    QString getName();   //return the name of the menu
    QStringList getMenuOptions();   //return the list of submenu titles
    Menu* getParentMenu();   //return a pointer to the parent menu
    int getPosition();    //return the position of the menu in a list of menus
    Menu* get(int);  //return a pointer to a submenu object at a given index in the list of submenus
    void addChildMenu(Menu*);  //add a new sub-menu object to the list of sub-menus contained within this menu object

private:
	QString name;   //menu title
	QStringList menuOptions;    //a list of selection items for each menu object
	int position;  // the position of the item in a menu list
	QVector<Menu*> subMenu;  //a list of subMenu objects contained within this menu object
	Menu* parentMenu;    //represents the parent menu of this menu object in a tree structure

};

#endif
