/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QLionTabWidget.h"
#include "qlionterminal.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_new_file;
    QAction *action_open_file;
    QAction *action_open_folder;
    QAction *action_save_file;
    QAction *action_save_as_file;
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
    QAction *action_search;
    QAction *action_run_project;
    QAction *action_edit_configurations;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QLionTabWidget *tabWidget;
    QLionTerminal *terminal;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QMenu *menuRun_R;
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
        action_save_file = new QAction(MainWindow);
        action_save_file->setObjectName("action_save_file");
        action_save_as_file = new QAction(MainWindow);
        action_save_as_file->setObjectName("action_save_as_file");
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
        action_tool_tree_view->setChecked(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("resources/icons/folder.png"), QSize(), QIcon::Normal, QIcon::On);
        action_tool_tree_view->setIcon(icon1);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName("action_exit");
        action_search = new QAction(MainWindow);
        action_search->setObjectName("action_search");
        action_search->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_search->setIcon(icon2);
        action_run_project = new QAction(MainWindow);
        action_run_project->setObjectName("action_run_project");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/execute_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_run_project->setIcon(icon3);
        action_edit_configurations = new QAction(MainWindow);
        action_edit_configurations->setObjectName("action_edit_configurations");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        tabWidget = new QLionTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setBaseSize(QSize(0, 0));
        splitter->addWidget(tabWidget);
        terminal = new QLionTerminal(splitter);
        terminal->setObjectName("terminal");
        sizePolicy.setHeightForWidth(terminal->sizePolicy().hasHeightForWidth());
        terminal->setSizePolicy(sizePolicy);
        terminal->setMinimumSize(QSize(0, 0));
        splitter->addWidget(terminal);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName("menu_F");
        menu_E = new QMenu(menubar);
        menu_E->setObjectName("menu_E");
        menuRun_R = new QMenu(menubar);
        menuRun_R->setObjectName("menuRun_R");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
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
        menubar->addAction(menuRun_R->menuAction());
        menu_F->addAction(action_new_file);
        menu_F->addAction(action_new_window);
        menu_F->addSeparator();
        menu_F->addAction(action_open_file);
        menu_F->addAction(action_open_folder);
        menu_F->addSeparator();
        menu_F->addAction(action_save_file);
        menu_F->addAction(action_save_as_file);
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
        menuRun_R->addAction(action_run_project);
        menuRun_R->addAction(action_edit_configurations);
        toolBar->addAction(action_tool_tree_view);
        toolBar->addAction(action_search);
        toolBar->addAction(action_run_project);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qlion", nullptr));
        action_new_file->setText(QCoreApplication::translate("MainWindow", "New Text File", nullptr));
#if QT_CONFIG(shortcut)
        action_new_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_open_file->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
#if QT_CONFIG(shortcut)
        action_open_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_open_folder->setText(QCoreApplication::translate("MainWindow", "Open Folder", nullptr));
#if QT_CONFIG(shortcut)
        action_open_folder->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_save_file->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        action_save_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_save_as_file->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
#if QT_CONFIG(shortcut)
        action_save_as_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_setting->setText(QCoreApplication::translate("MainWindow", "Setting", nullptr));
#if QT_CONFIG(shortcut)
        action_setting->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_CONFIG(shortcut)
        action_new_window->setText(QCoreApplication::translate("MainWindow", "New Window", nullptr));
#if QT_CONFIG(shortcut)
        action_new_window->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_undo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        action_undo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_redo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#if QT_CONFIG(shortcut)
        action_redo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        action_cut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#if QT_CONFIG(shortcut)
        action_cut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_copy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        action_copy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_paste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#if QT_CONFIG(shortcut)
        action_paste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        action_find->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
#if QT_CONFIG(shortcut)
        action_find->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_replace->setText(QCoreApplication::translate("MainWindow", "Replace", nullptr));
#if QT_CONFIG(shortcut)
        action_replace->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        action_denote->setText(QCoreApplication::translate("MainWindow", "Toggle Line Comment", nullptr));
#if QT_CONFIG(shortcut)
        action_denote->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+/", nullptr));
#endif // QT_CONFIG(shortcut)
        action_show_shotcut->setText(QCoreApplication::translate("MainWindow", "Short Cut List", nullptr));
#if QT_CONFIG(shortcut)
        action_show_shotcut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+K", nullptr));
#endif // QT_CONFIG(shortcut)
        action_info->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(shortcut)
        action_info->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        action_tool_tree_view->setText(QCoreApplication::translate("MainWindow", "Explorer", nullptr));
#if QT_CONFIG(shortcut)
        action_tool_tree_view->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+E", nullptr));
#endif // QT_CONFIG(shortcut)
        action_exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        action_search->setText(QCoreApplication::translate("MainWindow", "action_search", nullptr));
#if QT_CONFIG(tooltip)
        action_search->setToolTip(QCoreApplication::translate("MainWindow", "Search", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_search->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_run_project->setText(QCoreApplication::translate("MainWindow", "Run Project", nullptr));
#if QT_CONFIG(shortcut)
        action_run_project->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        action_edit_configurations->setText(QCoreApplication::translate("MainWindow", "Edit Configurations...", nullptr));
        menu_F->setTitle(QCoreApplication::translate("MainWindow", "File(&F)", nullptr));
        menu_E->setTitle(QCoreApplication::translate("MainWindow", "Edit(&E)", nullptr));
        menuRun_R->setTitle(QCoreApplication::translate("MainWindow", "Run(&R)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
