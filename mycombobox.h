#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H
#include <QComboBox>
#include <QLineEdit>
#include <QKeyEvent>
#include <QIcon>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <producto/producto.h>

class MyComboBox:public QComboBox
{
    Q_OBJECT
private:
    QString tipo;
    QIcon*  icono_agregar;

public:
    MyComboBox(QWidget* parent=0);
    void setTipo(QString tmp);
    void buscarValor(QString tmp);
    bool selecciono();

public slots:
    void ActualizarItems(QSqlQueryModel* model);
    void nuevo();
    void agregar();
    void eliminar();
};

#endif // MYCOMBOBOX_H
