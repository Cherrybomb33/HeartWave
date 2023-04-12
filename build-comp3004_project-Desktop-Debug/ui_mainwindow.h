/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "src/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *powerOffView;
    QListWidget *menuListWidget;
    QFrame *status;
    QProgressBar *battery;
    QLabel *contact;
    QPushButton *backButton;
    QPushButton *menuButton;
    QPushButton *upButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *downButton;
    QPushButton *powerButton;
    QPushButton *selectButton;
    QLabel *lowLabel;
    QLabel *medLabel;
    QLabel *highLabel;
    QStackedWidget *stackedWidget;
    QWidget *sessionView;
    QLabel *coherenceLabel;
    QLabel *lengthLabel;
    QLabel *achievementLabel;
    QLabel *coherenceValue;
    QLabel *lengthValue;
    QLabel *achievementScore;
    QProgressBar *bp;
    QCustomPlot *sessionGraph;
    QWidget *historyView;
    QLabel *avgLabel;
    QLabel *achLabel;
    QLabel *lenLabel;
    QLabel *distributionLabel;
    QLabel *low;
    QLabel *medium;
    QLabel *high;
    QLabel *avgScore;
    QLabel *achScore;
    QLabel *lenScore;
    QLabel *lowPercentage;
    QLabel *mediumPercentage;
    QLabel *highPercentage;
    QLabel *dateLabel;
    QLabel *date;
    QCustomPlot *historyGraph;
    QLabel *menuLabel;
    QPushButton *sensorButton;
    QWidget *BatteryWidget;
    QLabel *batteryLabel;
    QDoubleSpinBox *batterySpinBox;
    QPushButton *batteryPushButton;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuHeart_Wave;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(864, 670);
        QFont font;
        font.setFamily(QString::fromUtf8("System-ui"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerOffView = new QGraphicsView(centralwidget);
        powerOffView->setObjectName(QString::fromUtf8("powerOffView"));
        powerOffView->setGeometry(QRect(10, 40, 600, 310));
        powerOffView->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 0, 0);"));
        menuListWidget = new QListWidget(centralwidget);
        menuListWidget->setObjectName(QString::fromUtf8("menuListWidget"));
        menuListWidget->setGeometry(QRect(10, 85, 600, 265));
        status = new QFrame(centralwidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 40, 600, 25));
        status->setStyleSheet(QString::fromUtf8("background-color:rgb(211, 215, 207);"));
        status->setFrameShape(QFrame::StyledPanel);
        status->setFrameShadow(QFrame::Raised);
        battery = new QProgressBar(status);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(10, 2, 75, 20));
        battery->setValue(100);
        contact = new QLabel(status);
        contact->setObjectName(QString::fromUtf8("contact"));
        contact->setGeometry(QRect(570, 3, 16, 17));
        contact->setPixmap(QPixmap(QString::fromUtf8(":/check.png")));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setEnabled(true);
        backButton->setGeometry(QRect(10, 370, 50, 50));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/back.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        menuButton = new QPushButton(centralwidget);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));
        menuButton->setEnabled(true);
        menuButton->setGeometry(QRect(560, 370, 50, 50));
        menuButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/menu.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setEnabled(true);
        upButton->setGeometry(QRect(280, 440, 50, 50));
        upButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/up.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        leftButton = new QPushButton(centralwidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setEnabled(true);
        leftButton->setGeometry(QRect(210, 510, 45, 45));
        leftButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/left.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        rightButton = new QPushButton(centralwidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setEnabled(true);
        rightButton->setGeometry(QRect(350, 510, 45, 45));
        rightButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/right.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setEnabled(true);
        downButton->setGeometry(QRect(280, 580, 50, 50));
        downButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/down.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setEnabled(true);
        powerButton->setGeometry(QRect(280, 370, 50, 50));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/power.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        selectButton = new QPushButton(centralwidget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setEnabled(true);
        selectButton->setGeometry(QRect(280, 510, 50, 50));
        selectButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/select.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        lowLabel = new QLabel(centralwidget);
        lowLabel->setObjectName(QString::fromUtf8("lowLabel"));
        lowLabel->setGeometry(QRect(130, 10, 91, 21));
        lowLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color:rgb(239, 41, 41);\n"
"}"));
        medLabel = new QLabel(centralwidget);
        medLabel->setObjectName(QString::fromUtf8("medLabel"));
        medLabel->setGeometry(QRect(250, 10, 91, 21));
        medLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: rgb(52, 101, 164);\n"
"}"));
        highLabel = new QLabel(centralwidget);
        highLabel->setObjectName(QString::fromUtf8("highLabel"));
        highLabel->setGeometry(QRect(370, 10, 91, 21));
        highLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: rgb(78, 154, 6);\n"
"}"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 90, 600, 260));
        QFont font1;
        font1.setPointSize(8);
        stackedWidget->setFont(font1);
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        sessionView = new QWidget();
        sessionView->setObjectName(QString::fromUtf8("sessionView"));
        coherenceLabel = new QLabel(sessionView);
        coherenceLabel->setObjectName(QString::fromUtf8("coherenceLabel"));
        coherenceLabel->setGeometry(QRect(100, 10, 101, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("FreeSerif"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        coherenceLabel->setFont(font2);
        lengthLabel = new QLabel(sessionView);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));
        lengthLabel->setGeometry(QRect(270, 10, 54, 17));
        lengthLabel->setFont(font2);
        achievementLabel = new QLabel(sessionView);
        achievementLabel->setObjectName(QString::fromUtf8("achievementLabel"));
        achievementLabel->setGeometry(QRect(410, 10, 91, 20));
        achievementLabel->setFont(font2);
        coherenceValue = new QLabel(sessionView);
        coherenceValue->setObjectName(QString::fromUtf8("coherenceValue"));
        coherenceValue->setGeometry(QRect(130, 30, 41, 16));
        coherenceValue->setFont(font2);
        coherenceValue->setStyleSheet(QString::fromUtf8(""));
        lengthValue = new QLabel(sessionView);
        lengthValue->setObjectName(QString::fromUtf8("lengthValue"));
        lengthValue->setGeometry(QRect(275, 30, 41, 16));
        lengthValue->setFont(font2);
        achievementScore = new QLabel(sessionView);
        achievementScore->setObjectName(QString::fromUtf8("achievementScore"));
        achievementScore->setGeometry(QRect(430, 30, 41, 16));
        achievementScore->setFont(font2);
        bp = new QProgressBar(sessionView);
        bp->setObjectName(QString::fromUtf8("bp"));
        bp->setGeometry(QRect(120, 220, 381, 20));
        bp->setStyleSheet(QString::fromUtf8("QProgressBar { border: none; }"));
        bp->setValue(0);
        bp->setTextVisible(false);
        sessionGraph = new QCustomPlot(sessionView);
        sessionGraph->setObjectName(QString::fromUtf8("sessionGraph"));
        sessionGraph->setGeometry(QRect(100, 60, 411, 151));
        stackedWidget->addWidget(sessionView);
        historyView = new QWidget();
        historyView->setObjectName(QString::fromUtf8("historyView"));
        avgLabel = new QLabel(historyView);
        avgLabel->setObjectName(QString::fromUtf8("avgLabel"));
        avgLabel->setGeometry(QRect(410, 50, 101, 16));
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Sans"));
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        avgLabel->setFont(font3);
        achLabel = new QLabel(historyView);
        achLabel->setObjectName(QString::fromUtf8("achLabel"));
        achLabel->setGeometry(QRect(410, 80, 141, 16));
        QFont font4;
        font4.setFamily(QString::fromUtf8("System-ui"));
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        achLabel->setFont(font4);
        lenLabel = new QLabel(historyView);
        lenLabel->setObjectName(QString::fromUtf8("lenLabel"));
        lenLabel->setGeometry(QRect(410, 110, 51, 16));
        lenLabel->setFont(font4);
        distributionLabel = new QLabel(historyView);
        distributionLabel->setObjectName(QString::fromUtf8("distributionLabel"));
        distributionLabel->setGeometry(QRect(410, 140, 181, 16));
        QFont font5;
        font5.setFamily(QString::fromUtf8("System-ui"));
        font5.setPointSize(8);
        font5.setBold(true);
        font5.setWeight(75);
        distributionLabel->setFont(font5);
        low = new QLabel(historyView);
        low->setObjectName(QString::fromUtf8("low"));
        low->setGeometry(QRect(410, 160, 41, 16));
        low->setFont(font4);
        medium = new QLabel(historyView);
        medium->setObjectName(QString::fromUtf8("medium"));
        medium->setGeometry(QRect(410, 190, 61, 16));
        medium->setFont(font4);
        high = new QLabel(historyView);
        high->setObjectName(QString::fromUtf8("high"));
        high->setGeometry(QRect(410, 220, 41, 16));
        high->setFont(font4);
        avgScore = new QLabel(historyView);
        avgScore->setObjectName(QString::fromUtf8("avgScore"));
        avgScore->setGeometry(QRect(520, 50, 54, 17));
        QFont font6;
        font6.setFamily(QString::fromUtf8("System-ui"));
        font6.setBold(true);
        font6.setWeight(75);
        avgScore->setFont(font6);
        achScore = new QLabel(historyView);
        achScore->setObjectName(QString::fromUtf8("achScore"));
        achScore->setGeometry(QRect(550, 80, 51, 16));
        achScore->setFont(font6);
        lenScore = new QLabel(historyView);
        lenScore->setObjectName(QString::fromUtf8("lenScore"));
        lenScore->setGeometry(QRect(470, 110, 61, 17));
        lenScore->setFont(font6);
        lowPercentage = new QLabel(historyView);
        lowPercentage->setObjectName(QString::fromUtf8("lowPercentage"));
        lowPercentage->setGeometry(QRect(450, 160, 71, 17));
        lowPercentage->setFont(font6);
        mediumPercentage = new QLabel(historyView);
        mediumPercentage->setObjectName(QString::fromUtf8("mediumPercentage"));
        mediumPercentage->setGeometry(QRect(480, 190, 71, 17));
        mediumPercentage->setFont(font6);
        highPercentage = new QLabel(historyView);
        highPercentage->setObjectName(QString::fromUtf8("highPercentage"));
        highPercentage->setGeometry(QRect(460, 220, 91, 17));
        highPercentage->setFont(font6);
        dateLabel = new QLabel(historyView);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
        dateLabel->setGeometry(QRect(410, 20, 51, 21));
        dateLabel->setFont(font3);
        date = new QLabel(historyView);
        date->setObjectName(QString::fromUtf8("date"));
        date->setGeometry(QRect(450, 20, 151, 20));
        date->setFont(font6);
        historyGraph = new QCustomPlot(historyView);
        historyGraph->setObjectName(QString::fromUtf8("historyGraph"));
        historyGraph->setGeometry(QRect(30, 20, 361, 221));
        stackedWidget->addWidget(historyView);
        menuLabel = new QLabel(centralwidget);
        menuLabel->setObjectName(QString::fromUtf8("menuLabel"));
        menuLabel->setGeometry(QRect(10, 65, 601, 20));
        QFont font7;
        font7.setFamily(QString::fromUtf8("System-ui"));
        font7.setPointSize(11);
        font7.setBold(true);
        font7.setWeight(75);
        menuLabel->setFont(font7);
        menuLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        sensorButton = new QPushButton(centralwidget);
        sensorButton->setObjectName(QString::fromUtf8("sensorButton"));
        sensorButton->setGeometry(QRect(20, 560, 51, 51));
        sensorButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/sensor.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        BatteryWidget = new QWidget(centralwidget);
        BatteryWidget->setObjectName(QString::fromUtf8("BatteryWidget"));
        BatteryWidget->setGeometry(QRect(630, 40, 221, 311));
        batteryLabel = new QLabel(BatteryWidget);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));
        batteryLabel->setGeometry(QRect(10, 30, 91, 21));
        QFont font8;
        font8.setFamily(QString::fromUtf8("DejaVu Sans"));
        font8.setPointSize(11);
        batteryLabel->setFont(font8);
        batterySpinBox = new QDoubleSpinBox(BatteryWidget);
        batterySpinBox->setObjectName(QString::fromUtf8("batterySpinBox"));
        batterySpinBox->setGeometry(QRect(130, 30, 81, 21));
        batterySpinBox->setFont(font8);
        batteryPushButton = new QPushButton(BatteryWidget);
        batteryPushButton->setObjectName(QString::fromUtf8("batteryPushButton"));
        batteryPushButton->setGeometry(QRect(100, 30, 21, 21));
        batteryPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: none;\n"
"	border-image: url(:/charge.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(85, 87, 83);\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 864, 22));
        menuHeart_Wave = new QMenu(menubar);
        menuHeart_Wave->setObjectName(QString::fromUtf8("menuHeart_Wave"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuHeart_Wave->menuAction());

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        contact->setText(QString());
        backButton->setText(QString());
        menuButton->setText(QString());
        upButton->setText(QString());
        leftButton->setText(QString());
        rightButton->setText(QString());
        downButton->setText(QString());
        powerButton->setText(QString());
        selectButton->setText(QString());
        lowLabel->setText(QString());
        medLabel->setText(QString());
        highLabel->setText(QString());
        coherenceLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Coherence</p></body></html>", nullptr));
        lengthLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Length</p></body></html>", nullptr));
        achievementLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Achievement</p></body></html>", nullptr));
        coherenceValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">0.00</p></body></html>", nullptr));
        lengthValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">00.00</p></body></html>", nullptr));
        achievementScore->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">0.00</p></body></html>", nullptr));
        avgLabel->setText(QApplication::translate("MainWindow", "Average Score:", nullptr));
        achLabel->setText(QApplication::translate("MainWindow", "Achievement Score:", nullptr));
        lenLabel->setText(QApplication::translate("MainWindow", "Length:", nullptr));
        distributionLabel->setText(QApplication::translate("MainWindow", "Coherence Level Distribution:", nullptr));
        low->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#cc0000;\">Low:</span></p></body></html>", nullptr));
        medium->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#204a87;\">Mediium:</span></p></body></html>", nullptr));
        high->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#4e9a06;\">High:</span></p></body></html>", nullptr));
        avgScore->setText(QApplication::translate("MainWindow", "0.0", nullptr));
        achScore->setText(QApplication::translate("MainWindow", "0.0", nullptr));
        lenScore->setText(QApplication::translate("MainWindow", "00:00", nullptr));
        lowPercentage->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#a40000;\">0.0%</span></p></body></html>", nullptr));
        mediumPercentage->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#204a87;\">0.0%</span></p></body></html>", nullptr));
        highPercentage->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#4e9a06;\">0.0%</span></p></body></html>", nullptr));
        dateLabel->setText(QApplication::translate("MainWindow", "Date:", nullptr));
        date->setText(QApplication::translate("MainWindow", "2023-04-10 13:00:00", nullptr));
        menuLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; color:#e9b96e;\">MENU</span></p></body></html>", nullptr));
        sensorButton->setText(QString());
        batteryLabel->setText(QApplication::translate("MainWindow", "Battery:", nullptr));
        batteryPushButton->setText(QString());
        menuHeart_Wave->setTitle(QApplication::translate("MainWindow", "HeartWave", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
