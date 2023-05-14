/********************************************************************************
** Form generated from reading UI file 'runconfig.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNCONFIG_H
#define UI_RUNCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RunConfig
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *cmakePath;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *ninjaPath;
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

    void setupUi(QWidget *RunConfig)
    {
        if (RunConfig->objectName().isEmpty())
            RunConfig->setObjectName("RunConfig");
        RunConfig->resize(400, 300);
        verticalLayout = new QVBoxLayout(RunConfig);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(RunConfig);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        cmakePath = new QLineEdit(widget);
        cmakePath->setObjectName("cmakePath");

        horizontalLayout->addWidget(cmakePath);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(RunConfig);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        ninjaPath = new QLineEdit(widget_2);
        ninjaPath->setObjectName("ninjaPath");

        horizontalLayout_2->addWidget(ninjaPath);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(RunConfig);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        genPara = new QLineEdit(widget_3);
        genPara->setObjectName("genPara");

        horizontalLayout_3->addWidget(genPara);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(RunConfig);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        budPara = new QLineEdit(widget_4);
        budPara->setObjectName("budPara");

        horizontalLayout_4->addWidget(budPara);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(RunConfig);
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

        retranslateUi(RunConfig);

        QMetaObject::connectSlotsByName(RunConfig);
    } // setupUi

    void retranslateUi(QWidget *RunConfig)
    {
        RunConfig->setWindowTitle(QCoreApplication::translate("RunConfig", "RunConfig", nullptr));
        label->setText(QCoreApplication::translate("RunConfig", "CMake Path", nullptr));
        cmakePath->setPlaceholderText(QCoreApplication::translate("RunConfig", "cmake", nullptr));
        label_2->setText(QCoreApplication::translate("RunConfig", "Generator Path", nullptr));
        ninjaPath->setPlaceholderText(QCoreApplication::translate("RunConfig", "ninja", nullptr));
        label_3->setText(QCoreApplication::translate("RunConfig", "Additional Generating Parameter", nullptr));
        genPara->setPlaceholderText(QCoreApplication::translate("RunConfig", "-DCMAKE_BUILD_TYPE=Debug", nullptr));
        label_4->setText(QCoreApplication::translate("RunConfig", "Additional Building Parameter", nullptr));
        budPara->setPlaceholderText(QCoreApplication::translate("RunConfig", "-j 10", nullptr));
        apply->setText(QCoreApplication::translate("RunConfig", "Apply", nullptr));
        cancel->setText(QCoreApplication::translate("RunConfig", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RunConfig: public Ui_RunConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNCONFIG_H
