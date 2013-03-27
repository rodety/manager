#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <producto/ui_producto.h>
#include <cliente/ui_cliente.h>
#include <vitrina/ui_tienda.h>
#include <vitrina/ui_almacen.h>
#include <configuracion/usuariosform.h>
#include <configuracion/sesion.h>
#include "configuracion/ui_configuracion.h"
#include <venta/uiventas.h>
#include <reporte/ui_reporte.h>
#include <compra/compras.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void aplicarPermisos();
    
private slots:
    void on_actionProducto_triggered();
    void on_actionUsuario_triggered();
    void on_actionCliente_triggered();
    void on_actionVitrina_triggered();

    void on_actionAlmacen_triggered();

    void on_actionConfiguracion_triggered();

    void on_actionVentas_triggered();

    void on_actionReportes_triggered();

    void on_actionCompras_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<QAction*> modulos;

    ui_producto* formProducto;
    UsuariosForm* formUsuarios;
    ui_cliente* formCliente;
    ui_tienda* formTienda;
    ui_almacen* formAlmacen;
    ui_configuracion *formConfiguracion;
    uiventas * formVentas;
    ui_reporte* formReporte;
    compras* formCompras;

};

#endif // MAINWINDOW_H
