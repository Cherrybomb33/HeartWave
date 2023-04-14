#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QVector>

//menu object displayed and interacted with user
class Menu {

public:
    //constructor and destructor
    explicit Menu(QString, QStringList, Menu*);  
    ~Menu();

    //getters and setters
    QString getName();
    QStringList getMenuOptions();
    Menu* getParentMenu();
    int getPosition();
    void setName(QString n);
    void setMenuOptions(QStringList options);
    Menu* get(int);
    void addChildMenu(Menu*);
    void deleteChildMenu(Menu* menu);
    void deleteAllSubMenus();

private:
    QString name;               //menu title
    QStringList menuOptions;    //a list of menu items for each menu object
    int position;               //position of the item in a menu list
    QVector<Menu*> subMenu;     //a list of sub menu objects
    Menu* parentMenu;           //parent menu object

};

#endif
