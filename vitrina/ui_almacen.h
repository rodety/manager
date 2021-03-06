#ifndef UI_ALMACEN_H
#define UI_ALMACEN_H

#include <QWidget>
#include <QTableWidgetItem>
#include <map>
#include <QSqlQuery>
#include <QSqlError>
#include <producto/montura.h>

#include <iostream>
using namespace std;

namespace Ui {
class ui_almacen;
}

class ui_almacen : public QWidget
{
    Q_OBJECT

private:
    QSqlQuery sqlQuery;
    bool fromVitrina;

    bool toAlmacen;
    int cantidadProducto;

    QString currentIdEmpresa;
    QString currentIdTienda;
    QString currentIdAlmacen;
    QString currentIdAndamio;
    QString currentIdContenedor;

    QString currentCod;

    //key = name, map = id_entity;
    map<QString,QString> Empresas;
    map<QString,QString> Tiendas;
    map<QString,QString> Almacenes;
    map<QString,QString> Andamios;
    map<QString,QString> Contenedor;


public:
    QString get_currentIdEmpresa();
    QString get_currentIdTienda();
    QString get_currentIdAlmacen();
    QString get_currentIdAndamio();
    QString get_currentIdContenedor();

    void setFromVitrina(bool b);
    void setToAlmacen(bool b);

    void set_currentIdEmpresa(QString);
    void set_currentIdTienda(QString);
    void set_currentIdAlmacen(QString);
    void set_currentIdAndamio(QString);
    void set_currentIdContenedor(QString);
    void set_currentCode(QString);
    void set_cantidad(int tmp)               { cantidadProducto=tmp;}
    void set_query(QSqlQuery query);

    void update_comboBox_Empresa();
    void update_comboBox_Tienda(QString idEmpresa);
    void update_comboBox_Almacen(QString idTienda);
    void update_comboBox_Andamio(QString idAlmacen);

    void clear_widget_Contenedores();
    void set_dimension_widget_Contenedores();
    void update_widget_Contenedores();
    
public:
    explicit ui_almacen(QWidget *parent = 0);
    ~ui_almacen();
    
private slots:
    void on_comboBox_Empresa_currentIndexChanged(const QString &arg1);

    void on_comboBox_Tienda_currentIndexChanged(const QString &arg1);

    void on_comboBox_Almacen_currentIndexChanged(const QString &arg1);

    void on_comboBox_Andamio_currentIndexChanged(const QString &arg1);

    void on_pushButton_addAlmacen_clicked();

    void on_pushButton_editAlmacen_clicked();

    void on_pushButton_deleteAlmacen_clicked();

    void on_pushButton_addAndamio_clicked();

    void on_pushButton_editAndamio_clicked();

    void on_pushButton_deleteAndamio_clicked();

    void on_tableWidget_griContenedores_cellDoubleClicked(int row, int column);

    void on_tableWidget_griContenedores_itemSelectionChanged();

    void on_botonGenerarReporte_clicked();

private:
    Ui::ui_almacen *ui;
};

#endif // UI_ALMACEN_H
