/********************************************************************************
** Form generated from reading UI file 'findreplaceview.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDREPLACEVIEW_H
#define UI_FINDREPLACEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindReplaceView
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditFind;
    QToolButton *prevoiusOccurence;
    QToolButton *nextOccurence;
    QLabel *countLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditReplace;
    QToolButton *replace;
    QToolButton *findAndReplace;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FindReplaceView)
    {
        if (FindReplaceView->objectName().isEmpty())
            FindReplaceView->setObjectName("FindReplaceView");
        FindReplaceView->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(FindReplaceView);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 14, 0, 7);
        label = new QLabel(FindReplaceView);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEditFind = new QLineEdit(FindReplaceView);
        lineEditFind->setObjectName("lineEditFind");

        horizontalLayout->addWidget(lineEditFind);

        prevoiusOccurence = new QToolButton(FindReplaceView);
        prevoiusOccurence->setObjectName("prevoiusOccurence");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/previousOccurence_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevoiusOccurence->setIcon(icon);

        horizontalLayout->addWidget(prevoiusOccurence);

        nextOccurence = new QToolButton(FindReplaceView);
        nextOccurence->setObjectName("nextOccurence");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/nextOccurence_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextOccurence->setIcon(icon1);

        horizontalLayout->addWidget(nextOccurence);


        verticalLayout_2->addLayout(horizontalLayout);

        countLabel = new QLabel(FindReplaceView);
        countLabel->setObjectName("countLabel");

        verticalLayout_2->addWidget(countLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 7, 0, 14);
        label_2 = new QLabel(FindReplaceView);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEditReplace = new QLineEdit(FindReplaceView);
        lineEditReplace->setObjectName("lineEditReplace");

        horizontalLayout_2->addWidget(lineEditReplace);

        replace = new QToolButton(FindReplaceView);
        replace->setObjectName("replace");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/replace_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        replace->setIcon(icon2);

        horizontalLayout_2->addWidget(replace);

        findAndReplace = new QToolButton(FindReplaceView);
        findAndReplace->setObjectName("findAndReplace");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/find_replace_dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        findAndReplace->setIcon(icon3);

        horizontalLayout_2->addWidget(findAndReplace);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(FindReplaceView);

        QMetaObject::connectSlotsByName(FindReplaceView);
    } // setupUi

    void retranslateUi(QWidget *FindReplaceView)
    {
        FindReplaceView->setWindowTitle(QCoreApplication::translate("FindReplaceView", "FindReplaceView", nullptr));
        label->setText(QCoreApplication::translate("FindReplaceView", "Find", nullptr));
        prevoiusOccurence->setText(QCoreApplication::translate("FindReplaceView", "...", nullptr));
        nextOccurence->setText(QCoreApplication::translate("FindReplaceView", "...", nullptr));
        countLabel->setText(QCoreApplication::translate("FindReplaceView", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("FindReplaceView", "Replace", nullptr));
#if QT_CONFIG(tooltip)
        replace->setToolTip(QCoreApplication::translate("FindReplaceView", "Replace", nullptr));
#endif // QT_CONFIG(tooltip)
        replace->setText(QCoreApplication::translate("FindReplaceView", "...", nullptr));
#if QT_CONFIG(tooltip)
        findAndReplace->setToolTip(QCoreApplication::translate("FindReplaceView", "Find and Replace", nullptr));
#endif // QT_CONFIG(tooltip)
        findAndReplace->setText(QCoreApplication::translate("FindReplaceView", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindReplaceView: public Ui_FindReplaceView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDREPLACEVIEW_H
