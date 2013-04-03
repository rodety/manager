#ifndef UI_PRODUCTO_H
#define UI_PRODUCTO_H

#include <QWidget>
#include <producto/ui_agregarluna.h>
#include <producto/ui_agregarmontura.h>
#include <producto/ui_agregarlente.h>
#include <producto/ui_agregarotros.h>
#include <extras/ui_trabajosextras.h>
#include <vitrina/ui_tienda.h>
//#include <producto/estado.h>
#include <extras/etiqueta.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextEdit>
#include <QPoint>

namespace Ui {
class ui_producto;
}

class ui_producto : public QWidget
{
    Q_OBJECT
    
public:
    explicit ui_producto(QWidget *parent = 0);
    ~ui_producto();
    
private slots:
    void cambiarModeloLuna();
    void cambiarModeloMontura();
    void cambiarModeloLenteContacto();
    void cambiarModeloOtros();
    void cambiarModeloTrabajosExtras();
    void on_comboBox_tipoProducto_currentIndexChanged(int index);
    void on_pushButton_agregar_2_clicked();
    void on_pushButton_editar_clicked();
    void on_pushButton_eliminar_clicked();

    void agregar_etiqueta(const QModelIndex & model);
    void eliminar_etiqueta(const QModelIndex & model);
    void enviar_producto(const QModelIndex & model);
    void on_pushButton_previsualizar_clicked();
    void on_pushButton_imprimir_clicked();
    void on_pushButton_anterior_clicked();
    void on_pushButton_siguiente_clicked();
    void on_tabWidget_currentChanged(int index);

    void on_btnToVitrina_clicked();
    void on_btnToAlmacen_clicked();







private:
    Ui::ui_producto *ui;
    int posicion;

    QList<etiqueta> etiquetas;

    int act;
    int pag;
    int comportamiento;

public slots:
    void setComportamiento(int);
signals:
    void sentProductoCompra(QString,QString,QString,int);//codigo,descripcion,precioCompra,cantidad
    void sentProductoVenta(QString,QString,QString,QString,QString);//codigo,descripcion,precioVenta,Descuento,stock

};

#endif // UI_PRODUCTO_H
