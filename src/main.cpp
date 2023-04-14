#include "mainwindow.h"
#include <QApplication>

//main function of the application
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   //create a QApplication object with command line arguments.
    MainWindow w;
    w.show();          //display MainWindow object on the screen
    return a.exec();   //start the QApplication
}
