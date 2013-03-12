/********************************************************************************
** Form generated from reading UI file 'ui_almacen_datos.ui'
**
** Created: Thu 27. Dec 12:00:27 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ALMACEN_DATOS_H
#define UI_UI_ALMACEN_DATOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ui_almacen_datos
{
public:
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_nombre;
    QLineEdit *lineEdit_descripcion;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_aceptar;
    QPushButton *pushButton_cancelar;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ui_almacen_datos)
    {
        if (ui_almacen_datos->objectName().isEmpty())
            ui_almacen_datos->setObjectName(QString::fromUtf8("ui_almacen_datos"));
        ui_almacen_datos->resize(330, 112);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/file-roller.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui_almacen_datos->setWindowIcon(icon);
        gridLayout_6 = new QGridLayout(ui_almacen_datos);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(ui_almacen_datos);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(ui_almacen_datos);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEdit_nombre = new QLineEdit(ui_almacen_datos);
        lineEdit_nombre->setObjectName(QString::fromUtf8("lineEdit_nombre"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_nombre->sizePolicy().hasHeightForWidth());
        lineEdit_nombre->setSizePolicy(sizePolicy);
        lineEdit_nombre->setMinimumSize(QSize(120, 0));
        lineEdit_nombre->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(lineEdit_nombre, 0, 0, 1, 1);

        lineEdit_descripcion = new QLineEdit(ui_almacen_datos);
        lineEdit_descripcion->setObjectName(QString::fromUtf8("lineEdit_descripcion"));
        sizePolicy.setHeightForWidth(lineEdit_descripcion->sizePolicy().hasHeightForWidth());
        lineEdit_descripcion->setSizePolicy(sizePolicy);
        lineEdit_descripcion->setMinimumSize(QSize(240, 0));
        lineEdit_descripcion->setMaximumSize(QSize(240, 16777215));

        gridLayout_3->addWidget(lineEdit_descripcion, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton_aceptar = new QPushButton(ui_almacen_datos);
        pushButton_aceptar->setObjectName(QString::fromUtf8("pushButton_aceptar"));

        gridLayout->addWidget(pushButton_aceptar, 0, 1, 1, 1);

        pushButton_cancelar = new QPushButton(ui_almacen_datos);
        pushButton_cancelar->setObjectName(QString::fromUtf8("pushButton_cancelar"));

        gridLayout->addWidget(pushButton_cancelar, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        retranslateUi(ui_almacen_datos);

        QMetaObject::connectSlotsByName(ui_almacen_datos);
    } // setupUi

    void retranslateUi(QWidget *ui_almacen_datos)
    {
        ui_almacen_datos->setWindowTitle(QApplication::translate("ui_almacen_datos", "Almacen", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ui_almacen_datos", "Nombre", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ui_almacen_datos", "Descripcion", 0, QApplication::UnicodeUTF8));
        pushButton_aceptar->setText(QApplication::translate("ui_almacen_datos", "Aceptar", 0, QApplication::UnicodeUTF8));
        pushButton_cancelar->setText(QApplication::translate("ui_almacen_datos", "Cancelar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ui_almacen_datos: public Ui_ui_almacen_datos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ALMACEN_DATOS_H
