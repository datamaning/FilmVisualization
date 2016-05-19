/********************************************************************************
** Form generated from reading UI file 'qcolorbar.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOLORBAR_H
#define UI_QCOLORBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QColorBar
{
public:

    void setupUi(QWidget *QColorBar)
    {
        if (QColorBar->objectName().isEmpty())
            QColorBar->setObjectName(QStringLiteral("QColorBar"));
        QColorBar->resize(400, 300);

        retranslateUi(QColorBar);

        QMetaObject::connectSlotsByName(QColorBar);
    } // setupUi

    void retranslateUi(QWidget *QColorBar)
    {
        QColorBar->setWindowTitle(QApplication::translate("QColorBar", "QColorBar", 0));
    } // retranslateUi

};

namespace Ui {
    class QColorBar: public Ui_QColorBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOLORBAR_H
