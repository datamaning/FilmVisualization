/********************************************************************************
** Form generated from reading UI file 'visualization.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZATION_H
#define UI_VISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcolorbar.h"

QT_BEGIN_NAMESPACE

class Ui_VisualizationClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_Users;
    QSpinBox *spinBox_DataNum;
    QPushButton *pushButton_LoadData;
    QWebView *webView_UserRelation;
    QListWidget *listWidget_Movie;
    QWebView *webView_SMT;
    QWebView *webView_PieMovieType;
    QComboBox *comboBox_MoviePie;
    QWebView *webView_TreeMap;
    QSpinBox *spinBox_NeighborNum;
    QPushButton *pushButton_SetNeighborNum;
    QWebView *webView_Chord;
    QWebView *webView_Recommend;
    QColorBar *widget_ColorBar;
    QLabel *label_character;
    QListWidget *listWidget_Users;
    QLabel *label_movie_seen;
    QLabel *label_character_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VisualizationClass)
    {
        if (VisualizationClass->objectName().isEmpty())
            VisualizationClass->setObjectName(QStringLiteral("VisualizationClass"));
        VisualizationClass->resize(1827, 1142);
        centralWidget = new QWidget(VisualizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1831, 1091));
        tab_Users = new QWidget();
        tab_Users->setObjectName(QStringLiteral("tab_Users"));
        spinBox_DataNum = new QSpinBox(tab_Users);
        spinBox_DataNum->setObjectName(QStringLiteral("spinBox_DataNum"));
        spinBox_DataNum->setGeometry(QRect(610, 10, 71, 22));
        spinBox_DataNum->setMinimum(10);
        spinBox_DataNum->setMaximum(100);
        spinBox_DataNum->setValue(30);
        pushButton_LoadData = new QPushButton(tab_Users);
        pushButton_LoadData->setObjectName(QStringLiteral("pushButton_LoadData"));
        pushButton_LoadData->setGeometry(QRect(610, 40, 81, 23));
        webView_UserRelation = new QWebView(tab_Users);
        webView_UserRelation->setObjectName(QStringLiteral("webView_UserRelation"));
        webView_UserRelation->setGeometry(QRect(0, -30, 601, 571));
        webView_UserRelation->setUrl(QUrl(QStringLiteral("about:blank")));
        listWidget_Movie = new QListWidget(tab_Users);
        listWidget_Movie->setObjectName(QStringLiteral("listWidget_Movie"));
        listWidget_Movie->setGeometry(QRect(1670, 610, 151, 451));
        webView_SMT = new QWebView(tab_Users);
        webView_SMT->setObjectName(QStringLiteral("webView_SMT"));
        webView_SMT->setGeometry(QRect(530, 160, 401, 421));
        webView_SMT->setUrl(QUrl(QStringLiteral("about:blank")));
        webView_PieMovieType = new QWebView(tab_Users);
        webView_PieMovieType->setObjectName(QStringLiteral("webView_PieMovieType"));
        webView_PieMovieType->setGeometry(QRect(970, 540, 561, 561));
        webView_PieMovieType->setUrl(QUrl(QStringLiteral("about:blank")));
        comboBox_MoviePie = new QComboBox(tab_Users);
        comboBox_MoviePie->setObjectName(QStringLiteral("comboBox_MoviePie"));
        comboBox_MoviePie->setGeometry(QRect(610, 150, 69, 22));
        webView_TreeMap = new QWebView(tab_Users);
        webView_TreeMap->setObjectName(QStringLiteral("webView_TreeMap"));
        webView_TreeMap->setGeometry(QRect(0, 529, 990, 530));
        webView_TreeMap->setUrl(QUrl(QStringLiteral("about:blank")));
        spinBox_NeighborNum = new QSpinBox(tab_Users);
        spinBox_NeighborNum->setObjectName(QStringLiteral("spinBox_NeighborNum"));
        spinBox_NeighborNum->setGeometry(QRect(610, 80, 71, 20));
        spinBox_NeighborNum->setMinimum(1);
        spinBox_NeighborNum->setMaximum(20);
        spinBox_NeighborNum->setValue(5);
        pushButton_SetNeighborNum = new QPushButton(tab_Users);
        pushButton_SetNeighborNum->setObjectName(QStringLiteral("pushButton_SetNeighborNum"));
        pushButton_SetNeighborNum->setGeometry(QRect(610, 110, 81, 23));
        webView_Chord = new QWebView(tab_Users);
        webView_Chord->setObjectName(QStringLiteral("webView_Chord"));
        webView_Chord->setGeometry(QRect(910, 10, 511, 551));
        webView_Chord->setUrl(QUrl(QStringLiteral("about:blank")));
        webView_Recommend = new QWebView(tab_Users);
        webView_Recommend->setObjectName(QStringLiteral("webView_Recommend"));
        webView_Recommend->setGeometry(QRect(1420, 0, 400, 560));
        webView_Recommend->setUrl(QUrl(QStringLiteral("about:blank")));
        widget_ColorBar = new QColorBar(tab_Users);
        widget_ColorBar->setObjectName(QStringLiteral("widget_ColorBar"));
        widget_ColorBar->setGeometry(QRect(1490, 605, 160, 500));
        label_character = new QLabel(tab_Users);
        label_character->setObjectName(QStringLiteral("label_character"));
        label_character->setGeometry(QRect(1500, 580, 111, 21));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        label_character->setFont(font);
        listWidget_Users = new QListWidget(tab_Users);
        listWidget_Users->setObjectName(QStringLiteral("listWidget_Users"));
        listWidget_Users->setGeometry(QRect(720, 30, 211, 191));
        label_movie_seen = new QLabel(tab_Users);
        label_movie_seen->setObjectName(QStringLiteral("label_movie_seen"));
        label_movie_seen->setGeometry(QRect(1685, 580, 131, 21));
        label_movie_seen->setFont(font);
        label_character_2 = new QLabel(tab_Users);
        label_character_2->setObjectName(QStringLiteral("label_character_2"));
        label_character_2->setGeometry(QRect(760, 5, 111, 21));
        label_character_2->setFont(font);
        tabWidget->addTab(tab_Users, QString());
        spinBox_DataNum->raise();
        pushButton_LoadData->raise();
        webView_UserRelation->raise();
        webView_SMT->raise();
        spinBox_NeighborNum->raise();
        pushButton_SetNeighborNum->raise();
        webView_Chord->raise();
        webView_PieMovieType->raise();
        webView_Recommend->raise();
        webView_TreeMap->raise();
        listWidget_Movie->raise();
        listWidget_Users->raise();
        widget_ColorBar->raise();
        label_movie_seen->raise();
        label_character_2->raise();
        comboBox_MoviePie->raise();
        label_character->raise();
        VisualizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VisualizationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1827, 23));
        VisualizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VisualizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VisualizationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VisualizationClass->setStatusBar(statusBar);

        retranslateUi(VisualizationClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *VisualizationClass)
    {
        VisualizationClass->setWindowTitle(QApplication::translate("VisualizationClass", "Visualization", 0));
        pushButton_LoadData->setText(QApplication::translate("VisualizationClass", "load data", 0));
        pushButton_SetNeighborNum->setText(QApplication::translate("VisualizationClass", "neighbor num", 0));
        label_character->setText(QApplication::translate("VisualizationClass", "Character", 0));
        label_movie_seen->setText(QApplication::translate("VisualizationClass", "Movie Seen", 0));
        label_character_2->setText(QApplication::translate("VisualizationClass", "User List", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_Users), QApplication::translate("VisualizationClass", "users", 0));
    } // retranslateUi

};

namespace Ui {
    class VisualizationClass: public Ui_VisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZATION_H
