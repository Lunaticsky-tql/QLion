/********************************************************************************
** Form generated from reading UI file 'runconfigwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNCONFIGWINDOW_H
#define UI_RUNCONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RunConfigWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *cmakePath;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *generator;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *genPara;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *budPara;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *apply;
    QPushButton *cancel;

    void setupUi(QWidget *RunConfigWindow)
    {
        if (RunConfigWindow->objectName().isEmpty())
            RunConfigWindow->setObjectName("RunConfigWindow");
        RunConfigWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(RunConfigWindow);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(RunConfigWindow);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        cmakePath = new QLineEdit(widget);
        cmakePath->setObjectName("cmakePath");

        horizontalLayout->addWidget(cmakePath);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        generator = new QLineEdit(widget_2);
        generator->setObjectName("generator");

        horizontalLayout_2->addWidget(generator);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(tab);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        genPara = new QLineEdit(widget_3);
        genPara->setObjectName("genPara");

        horizontalLayout_3->addWidget(genPara);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(tab);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        budPara = new QLineEdit(widget_4);
        budPara->setObjectName("budPara");

        horizontalLayout_4->addWidget(budPara);


        verticalLayout_2->addWidget(widget_4);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        widget_5 = new QWidget(RunConfigWindow);
        widget_5->setObjectName("widget_5");
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        apply = new QPushButton(widget_5);
        apply->setObjectName("apply");

        horizontalLayout_5->addWidget(apply);

        cancel = new QPushButton(widget_5);
        cancel->setObjectName("cancel");

        horizontalLayout_5->addWidget(cancel);


        verticalLayout->addWidget(widget_5);

#if QT_CONFIG(shortcut)
        label->setBuddy(cmakePath);
#endif // QT_CONFIG(shortcut)

        retranslateUi(RunConfigWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RunConfigWindow);
    } // setupUi

    void retranslateUi(QWidget *RunConfigWindow)
    {
        RunConfigWindow->setWindowTitle(QCoreApplication::translate("RunConfigWindow", "RunConfigWindow", nullptr));
        label->setText(QCoreApplication::translate("RunConfigWindow", "CMake Path", nullptr));
        cmakePath->setPlaceholderText(QCoreApplication::translate("RunConfigWindow", "cmake", nullptr));
        label_2->setText(QCoreApplication::translate("RunConfigWindow", "Generator", nullptr));
        generator->setPlaceholderText(QCoreApplication::translate("RunConfigWindow", "Ninja", nullptr));
        label_3->setText(QCoreApplication::translate("RunConfigWindow", "Additional Generating Parameter", nullptr));
        genPara->setPlaceholderText(QCoreApplication::translate("RunConfigWindow", "-DCMAKE_BUILD_TYPE=Debug", nullptr));
        label_4->setText(QCoreApplication::translate("RunConfigWindow", "Additional Building Parameter", nullptr));
        budPara->setPlaceholderText(QCoreApplication::translate("RunConfigWindow", "-j 10", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("RunConfigWindow", "Cmake", nullptr));
        apply->setText(QCoreApplication::translate("RunConfigWindow", "Apply", nullptr));
        cancel->setText(QCoreApplication::translate("RunConfigWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RunConfigWindow: public Ui_RunConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNCONFIGWINDOW_H
