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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QLionTerminal
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_hide;
    QWidget *widget_3;
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
        QLionTerminal->resize(400, 128);
        verticalLayout_2 = new QVBoxLayout(QLionTerminal);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_2 = new QWidget(QLionTerminal);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, 9, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        toolButton_hide = new QToolButton(widget_2);
        toolButton_hide->setObjectName("toolButton_hide");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/terminal_hide.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_hide->setIcon(icon);

        horizontalLayout_2->addWidget(toolButton_hide);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(QLionTerminal);
        widget_3->setObjectName("widget_3");
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        toolButton_run = new QToolButton(widget);
        toolButton_run->setObjectName("toolButton_run");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/execute_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_run->setIcon(icon1);

        verticalLayout->addWidget(toolButton_run);

        toolButton_stop = new QToolButton(widget);
        toolButton_stop->setObjectName("toolButton_stop");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/suspend_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_stop->setIcon(icon2);

        verticalLayout->addWidget(toolButton_stop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        plainTextEdit = new QPlainTextEdit(widget_3);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addWidget(widget_3);


        retranslateUi(QLionTerminal);

        QMetaObject::connectSlotsByName(QLionTerminal);
    } // setupUi

    void retranslateUi(QWidget *QLionTerminal)
    {
        QLionTerminal->setWindowTitle(QCoreApplication::translate("QLionTerminal", "QLionTerminal", nullptr));
        label->setText(QCoreApplication::translate("QLionTerminal", "Terminal", nullptr));
        toolButton_hide->setText(QCoreApplication::translate("QLionTerminal", "...", nullptr));
        toolButton_run->setText(QCoreApplication::translate("QLionTerminal", "...", nullptr));
        toolButton_stop->setText(QCoreApplication::translate("QLionTerminal", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QLionTerminal: public Ui_QLionTerminal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLIONTERMINAL_H
