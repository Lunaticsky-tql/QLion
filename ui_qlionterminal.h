/********************************************************************************
** Form generated from reading UI file 'qlionterminal.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLIONTERMINAL_H
#define UI_QLIONTERMINAL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QLionTerminal
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton_run;
    QToolButton *toolButton_stop;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *QLionTerminal)
    {
        if (QLionTerminal->objectName().isEmpty())
            QLionTerminal->setObjectName("QLionTerminal");
        QLionTerminal->resize(400, 300);
        horizontalLayout = new QHBoxLayout(QLionTerminal);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(QLionTerminal);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        toolButton_run = new QToolButton(widget);
        toolButton_run->setObjectName("toolButton_run");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/execute_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_run->setIcon(icon);

        verticalLayout->addWidget(toolButton_run);

        toolButton_stop = new QToolButton(widget);
        toolButton_stop->setObjectName("toolButton_stop");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/suspend_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_stop->setIcon(icon1);

        verticalLayout->addWidget(toolButton_stop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        plainTextEdit = new QPlainTextEdit(QLionTerminal);
        plainTextEdit->setObjectName("plainTextEdit");

        horizontalLayout->addWidget(plainTextEdit);


        retranslateUi(QLionTerminal);

        QMetaObject::connectSlotsByName(QLionTerminal);
    } // setupUi

    void retranslateUi(QWidget *QLionTerminal)
    {
        QLionTerminal->setWindowTitle(QCoreApplication::translate("QLionTerminal", "QLionTerminal", nullptr));
        toolButton_run->setText(QCoreApplication::translate("QLionTerminal", "...", nullptr));
        toolButton_stop->setText(QCoreApplication::translate("QLionTerminal", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QLionTerminal: public Ui_QLionTerminal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLIONTERMINAL_H
