#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modulos.push_back(ui->actionProducto);
    modulos.push_back(ui->actionUsuario);
    modulos.push_back(ui->actionCliente);
    modulos.push_back(ui->actionVitrina);
    modulos.push_back(ui->actionAlmacen);
    modulos.push_back(ui->actionCompras);
    modulos.push_back(ui->actionReportes);
    modulos.push_back(ui->actionVentas);
    modulos.push_back(ui->actionConfiguracion);

    for(size_t i = 0; i<modulos.size();i++)
        modulos[i]->setEnabled(false);
    aplicarPermisos();









}

void MainWindow::aplicarPermisos()
{
    Sesion * s = Sesion::getSesion();
    std::map<int,bool> v ;

    v = s->get_Permisos();

    std::map<int,bool>::iterator it = v.begin();
    if(!v.size())
    {
        QMessageBox::warning(0,"Error de Permisos","No se definieron permisos para este usuario",0,0);
        return;
    }

    for(;it!=v.end();it++)
        modulos[(*it).first-1]->setEnabled((*it).second);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionProducto_triggered()
{
    formProducto=new ui_producto;
    setCentralWidget(formProducto);
}

void MainWindow::on_actionUsuario_triggered()
{
    formUsuarios= new UsuariosForm;
    setCentralWidget(formUsuarios);
}

void MainWindow::on_actionCliente_triggered()
{
    formCliente=new ui_cliente;
    setCentralWidget(formCliente);
}

void MainWindow::on_actionVitrina_triggered()
{
    formTienda = new ui_tienda;
    setCentralWidget(formTienda);
}

void MainWindow::on_actionAlmacen_triggered()
{
    formAlmacen = new ui_almacen;
    setCentralWidget(formAlmacen);
}

void MainWindow::on_actionConfiguracion_triggered()
{
    formConfiguracion = new ui_configuracion;
    setCentralWidget(formConfiguracion);
}

void MainWindow::on_actionVentas_triggered()
{
    formVentas = new uiventas;
    setCentralWidget(formVentas);
}

void MainWindow::on_actionReportes_triggered()
{
    formReporte = new ui_reporte;
    setCentralWidget(formReporte);
}
