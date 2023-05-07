/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QLionTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_new_file;
    QAction *action_open_file;
    QAction *action_open_folder;
    QAction *action_save;
    QAction *action_save_as;
    QAction *action_setting;
    QAction *action_new_window;
    QAction *action_undo;
    QAction *action_redo;
    QAction *action_cut;
    QAction *action_copy;
    QAction *action_paste;
    QAction *action_find;
    QAction *action_replace;
    QAction *action_denote;
    QAction *action_show_shotcut;
    QAction *action_info;
    QAction *action_tool_tree_view;
    QAction *action_exit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLionTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *sideDock;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 479);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/qlion.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_new_file = new QAction(MainWindow);
        action_new_file->setObjectName("action_new_file");
        action_open_file = new QAction(MainWindow);
        action_open_file->setObjectName("action_open_file");
        action_open_folder = new QAction(MainWindow);
        action_open_folder->setObjectName("action_open_folder");
        action_save = new QAction(MainWindow);
        action_save->setObjectName("action_save");
        action_save_as = new QAction(MainWindow);
        action_save_as->setObjectName("action_save_as");
        action_setting = new QAction(MainWindow);
        action_setting->setObjectName("action_setting");
        action_new_window = new QAction(MainWindow);
        action_new_window->setObjectName("action_new_window");
        action_undo = new QAction(MainWindow);
        action_undo->setObjectName("action_undo");
        action_redo = new QAction(MainWindow);
        action_redo->setObjectName("action_redo");
        action_cut = new QAction(MainWindow);
        action_cut->setObjectName("action_cut");
        action_copy = new QAction(MainWindow);
        action_copy->setObjectName("action_copy");
        action_paste = new QAction(MainWindow);
        action_paste->setObjectName("action_paste");
        action_find = new QAction(MainWindow);
        action_find->setObjectName("action_find");
        action_replace = new QAction(MainWindow);
        action_replace->setObjectName("action_replace");
        action_denote = new QAction(MainWindow);
        action_denote->setObjectName("action_denote");
        action_show_shotcut = new QAction(MainWindow);
        action_show_shotcut->setObjectName("action_show_shotcut");
        action_info = new QAction(MainWindow);
        action_info->setObjectName("action_info");
        action_tool_tree_view = new QAction(MainWindow);
        action_tool_tree_view->setObjectName("action_tool_tree_view");
        action_tool_tree_view->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("resources/icons/folder.png"), QSize(), QIcon::Normal, QIcon::On);
        action_tool_tree_view->setIcon(icon1);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName("action_exit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QLionTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName("menu_F");
        menu_E = new QMenu(menubar);
        menu_E->setObjectName("menu_E");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);
        sideDock = new QDockWidget(MainWindow);
        sideDock->setObjectName("sideDock");
        sideDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        sideDock->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, sideDock);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_E->menuAction());
        menu_F->addAction(action_new_file);
        menu_F->addAction(action_new_window);
        menu_F->addSeparator();
        menu_F->addAction(action_open_file);
        menu_F->addAction(action_open_folder);
        menu_F->addSeparator();
        menu_F->addAction(action_save);
        menu_F->addAction(action_save_as);
        menu_F->addSeparator();
        menu_F->addAction(action_setting);
        menu_F->addSeparator();
        menu_F->addAction(action_exit);
        menu_E->addAction(action_undo);
        menu_E->addAction(action_redo);
        menu_E->addSeparator();
        menu_E->addAction(action_cut);
        menu_E->addAction(action_copy);
        menu_E->addAction(action_paste);
        menu_E->addSeparator();
        menu_E->addAction(action_find);
        menu_E->addAction(action_replace);
        menu_E->addAction(action_denote);
        toolBar->addAction(action_tool_tree_view);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qlion", nullptr));
        action_new_file->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\346\234\254\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_new_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_open_file->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_open_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_open_folder->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
#if QT_CONFIG(shortcut)
        action_open_folder->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(shortcut)
        action_save->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_save_as->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#if QT_CONFIG(shortcut)
        action_save_as->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_setting->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
#if QT_CONFIG(shortcut)
        action_setting->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_CONFIG(shortcut)
        action_new_window->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\347\252\227\345\217\243", nullptr));
#if QT_CONFIG(shortcut)
        action_new_window->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_undo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#if QT_CONFIG(shortcut)
        action_undo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_redo->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#if QT_CONFIG(shortcut)
        action_redo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        action_cut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#if QT_CONFIG(shortcut)
        action_cut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_copy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#if QT_CONFIG(shortcut)
        action_copy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_paste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#if QT_CONFIG(shortcut)
        action_paste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        action_find->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#if QT_CONFIG(shortcut)
        action_find->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_replace->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242", nullptr));
#if QT_CONFIG(shortcut)
        action_replace->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        action_denote->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\350\241\214\346\263\250\351\207\212", nullptr));
#if QT_CONFIG(shortcut)
        action_denote->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+/", nullptr));
#endif // QT_CONFIG(shortcut)
        action_show_shotcut->setText(QCoreApplication::translate("MainWindow", "\345\277\253\346\215\267\351\224\256", nullptr));
#if QT_CONFIG(shortcut)
        action_show_shotcut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+K", nullptr));
#endif // QT_CONFIG(shortcut)
        action_info->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#if QT_CONFIG(shortcut)
        action_info->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        action_tool_tree_view->setText(QCoreApplication::translate("MainWindow", "\350\265\204\346\272\220\347\256\241\347\220\206\345\231\250", nullptr));
#if QT_CONFIG(shortcut)
        action_tool_tree_view->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+E", nullptr));
#endif // QT_CONFIG(shortcut)
        action_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        menu_F->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_E->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
