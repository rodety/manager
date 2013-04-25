#include "uiventas.h"
#include "ui_uiventas.h"

uiventas::uiventas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiventas)
{
    ui->setupUi(this);
    count_row=0;

    QDate hoy=QDate::currentDate();
    ui->dateEdit_fecha->setDate(hoy);
    ui->dateEdit_fecha->setMaximumDate(hoy);
    ui->dateTimeEdit_entrega->setDate(hoy);
    ui->dateTimeEdit_entrega->setMinimumDate(hoy);

    QSqlQuery query;
    query.prepare("SELECT igv,serieBoleta FROM Configuracion WHERE (Tienda_idTienda = 1)");
    query.exec();
    query.next();
    ui->lineEdit_igv->setText(query.value(0).toString());
    ui->label_numero->setText("Numero #"+query.value(1).toString());
    ui->lineEdit_usuario->setText("admin");
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
    form->setComportamiento(2);
    form->setWindowTitle("Productos");
    form->show();
    connect(form,SIGNAL(sentProductoVenta(QString,QString,QString,QString,int)),this,SLOT(recojeProducto(QString,QString,QString,QString,int)));
    connect(form,SIGNAL(sentProductoVenta(QString,QString,QString,QString,int)),form,SLOT(close()));
}

void uiventas::recojeProducto(QString codigo,QString descripcion,QString precioVenta,QString precioDescuento,int cant)
{
    ui->tableWidget_producto->insertRow(count_row);

    ui->tableWidget_producto->setItem(count_row,0,new QTableWidgetItem(codigo));
    ui->tableWidget_producto->setItem(count_row,1,new QTableWidgetItem(descripcion));
    ui->tableWidget_producto->setItem(count_row,2,new QTableWidgetItem(precioVenta));
    ui->tableWidget_producto->setItem(count_row,3,new QTableWidgetItem(precioDescuento));
    ui->tableWidget_producto->setItem(count_row,4,new QTableWidgetItem(QString::number(cant)));
    ui->tableWidget_producto->setItem(count_row,5,new QTableWidgetItem("si"));
    ui->tableWidget_producto->setItem(count_row,6,new QTableWidgetItem(QString::number(cant*(precioVenta.toDouble()-precioDescuento.toDouble()))));
    count_row++;

    ui->lineEdit_subtotal->setText(QString::number(cant*(precioVenta.toDouble()-precioDescuento.toDouble()) + ui->lineEdit_subtotal->text().toDouble()));
    ui->lineEdit_total->setText(QString::number(ui->lineEdit_subtotal->text().toDouble()+ui->lineEdit_subtotal->text().toDouble()*ui->lineEdit_igv->text().toDouble()/100));
}

void uiventas::on_pushButton_completar_clicked()
{

}
