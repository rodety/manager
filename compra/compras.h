#ifndef COMPRAS_H
#define COMPRAS_H

#include <QWidget>
#include<QTableWidgetItem>
#include<map>
using namespace std;

namespace Ui {
class compras;
}

class compras : public QWidget
{
    Q_OBJECT
public:
    void setCant(int cant){currentCant = cant;}
    void addItemProductos(int cant, int row);
    void updateListCompras();
public:
    explicit compras(QWidget *parent = 0);
    ~compras();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_buscar_proveedor_clicked();

    void on_pushButton_buscar_producto_clicked();

    void on_tableWidget_proveedores_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_productos_itemClicked(QTableWidgetItem *item);

    void on_pushButton_guardar_clicked();

    void on_tableWidget_Compras_itemClicked(QTableWidgetItem *item);

    void on_pushButton_ver_compra_clicked();

    void on_lineEdit_proveedor_returnPressed();

    void on_lineEdit_productos_returnPressed();

    void on_tableWidget_Compras_doubleClicked(const QModelIndex &index);


    void on_tableWidget__items_productos_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_eliminar_compra_clicked();

private:
    Ui::compras *ui;
    map<QString,QString> Proveedores;
    map<QString,QString> Productos;
    map<QString,QString> Productos_Agregados;
    map<QString,QString> Compras;
    int contador;
    int currentCant;
    double compra_total;
    QString current_idCompras;
    int currentItem;
};

#endif // COMPRAS_H
