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

    for(size_t i = 0; i<modulos.size();i++)
        modulos[i]->setEnabled(false);
    aplicarPermisos();
    ui->actionUsuario->setEnabled(true);

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
    {
        modulos[(*it).first-1]->setEnabled((*it).second);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionProducto_triggered()
{
    ui_producto* form=new ui_producto;
    setCentralWidget(form);
}

void MainWindow::on_actionUsuario_triggered()
{
    UsuariosForm* form= new UsuariosForm;
    setCentralWidget(form);
}

void MainWindow::on_actionCliente_triggered()
{
    ui_cliente* form=new ui_cliente;
    setCentralWidget(form);
}

void MainWindow::on_actionVitrina_triggered()
{
    ui_tienda* form = new ui_tienda;
    setCentralWidget(form);
}

void MainWindow::on_actionAlmacen_triggered()
{
    ui_almacen* form = new ui_almacen;
    setCentralWidget(form);
}

void MainWindow::on_actionConfiguracion_triggered()
{
    ui_configuracion *form = new ui_configuracion;
    setCentralWidget(form);
}
