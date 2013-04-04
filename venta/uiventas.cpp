#include "uiventas.h"
#include "ui_uiventas.h"

uiventas::uiventas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiventas)
{
    ui->setupUi(this);
}

uiventas::~uiventas()
{
    delete ui;
}

void uiventas::on_pushButton_buscarCliente_clicked()
{
    ui_cliente* form=new ui_cliente;
    form->setComportamiento(1);
    form->setWindowTitle("Cliente");
    form->show();
    connect(form,SIGNAL(sentCliente(QString,QString,QString)),this,SLOT(recojeCliente(QString,QString,QString)));
    connect(form,SIGNAL(sentCliente(QString,QString,QString)),form,SLOT(close()));
}
void uiventas::recojeCliente(QString razon,QString ruc,QString direccion)
{
    ui->lineEdit_razonSocial->setText(razon);
    ui->lineEdit_ruc->setText(ruc);
    ui->lineEdit_direccion->setText(direccion);
}
void uiventas::on_pushButton_buscarProducto_clicked()
{
    ui_producto* form=new ui_producto;
    form->setComportamiento(1);
    form->setWindowTitle("Producto");
    form->show();
    connect(form,SIGNAL(sentProductoVenta(QString,QString,QString,QString,QString)),this,SLOT(recojeProducto(QString,QString,QString,QString,QString)));
}

void uiventas::recojeProducto(QString codigo,QString descripcion,QString precioVenta,QString Descuento,QString stock)
{
    ui->tableWidget_producto->insertRow(ui->tableWidget_producto->rowCount());
    QTableWidgetItem* item=new QTableWidgetItem(codigo);
    ui->tableWidget_producto->setItem(ui->tableWidget_producto->rowCount()-1,0,item);
    /*ui->lineEdit_razonSocial->setText(razon);
    ui->lineEdit_ruc->setText(ruc);
    ui->lineEdit_direccion->setText(direccion);*/
}
