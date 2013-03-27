#include "compras.h"
#include "ui_compras.h"
#include "ui_datos_compras.h"
#include <QString>
#include <QSqlQuery>
#include "ui_cant_item.h"
#include<QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <compra/ui_proveedores.h>
#include <producto/ui_producto.h>
compras::compras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::compras)
{
    ui->setupUi(this);
    contador = 0;

    currentCant = 0;
    compra_total = 0;
    ui->dateEdit->setDate(QDate::currentDate());
    updateListCompras();
    ui->lineEdit_ruc->setReadOnly(true);
    ui->lineEdit_direccion->setReadOnly(true);
    ui->lineEdit_subtotal->setReadOnly(true);
    ui->lineEdit_igv->setReadOnly(true);
    ui->lineEdit_total->setReadOnly(true);
    actualCompra = new compra;

}

compras::~compras()
{
    delete ui;
}

void compras::on_pushButton_clicked()
{
    ui_datos_compras* compras = new ui_datos_compras;
    compras->show();

}

void compras::on_pushButton_2_clicked()
{


}


void compras::on_pushButton_buscar_proveedor_clicked()
{
    ui_proveedores * form = new ui_proveedores;
    form->show();

    connect(form,SIGNAL(sentidProveedor(QString,QString,QString,QString)),this,SLOT(getProveedor(QString,QString,QString,QString)));
    /*for (int i=ui->tableWidget_proveedores->rowCount()-1; i >= 0; --i)
        ui->tableWidget_proveedores->removeRow(i);

    QString nombre_proveedor,nombre,ruc,idproveedor;
    nombre_proveedor = ui->lineEdit_proveedor->text();
    QSqlQuery query;
    query.prepare("SELECT idproveedor,ruc,raz_social FROM  proveedor WHERE raz_social REGEXP \""+nombre_proveedor+"\"");
    query.exec();
    int c = 0;

       while(query.next())
       {
           idproveedor = query.value(0).toString();
           ruc = query.value(1).toString();
           nombre = query.value(2).toString();
           Proveedores[nombre] = idproveedor;
           ui->tableWidget_proveedores->insertRow(c);
           ui->tableWidget_proveedores->setItem(c,0, new QTableWidgetItem(ruc));
           ui->tableWidget_proveedores->setItem(c,1, new QTableWidgetItem(nombre));
           c++;
       }*/
}

void compras::on_pushButton_buscar_producto_clicked()
{
    ui_producto * form = new ui_producto;
    form->setWindowTitle("Buscar Proveedor");
    form->show();
    /*for (int i=ui->tableWidget_productos->rowCount()-1; i >= 0; --i)
        ui->tableWidget_productos->removeRow(i);

    Productos.clear();
    QString codigo,descripcion,accesorios,precio,idproducto,descripcion_buscado;

    descripcion_buscado = ui->lineEdit_productos->text();
    QSqlQuery query;
    query.prepare("SELECT idproducto,codigo,descripcion,accesorios,precio_compra FROM  producto WHERE descripcion REGEXP \""+descripcion_buscado+"\"");
    query.exec();
    int c = 0;

       while(query.next())
       {
           idproducto = query.value(0).toString();
           codigo = query.value(1).toString();
           descripcion = query.value(2).toString();
           accesorios = query.value(3).toString();
           precio = query.value(4).toString();
           Productos[codigo] = idproducto;
           ui->tableWidget_productos->insertRow(c);
           ui->tableWidget_productos->setItem(c,0, new QTableWidgetItem(codigo));
           ui->tableWidget_productos->setItem(c,1, new QTableWidgetItem(descripcion));
           ui->tableWidget_productos->setItem(c,2, new QTableWidgetItem(accesorios));
           ui->tableWidget_productos->setItem(c,3, new QTableWidgetItem(precio));
           c++;
       }*/

}

void compras::on_tableWidget_proveedores_itemClicked(QTableWidgetItem *item)
{
    int count = item->row();
    QString raz_social = "hola";//ui->tableWidget_proveedores->item(count,1)->text();
    QString idproveedor = Proveedores[raz_social];
    QSqlQuery query;
    query.prepare("SELECT raz_social,ruc,direccion FROM  proveedor WHERE idproveedor = '"+idproveedor+"'");
    query.exec();query.next();
    ui->lineEdit_proveedor->setText(query.value(0).toString());
    ui->lineEdit_ruc->setText(query.value(1).toString());
    ui->lineEdit_direccion->setText(query.value(2).toString());
}

void compras::on_tableWidget_productos_itemClicked(QTableWidgetItem *item)
{
    ui_cant_item* viewCant = new ui_cant_item;
    viewCant->setCurrentParent(this);
    viewCant->setRow(item->row());
    viewCant->show();
}

void compras::on_pushButton_guardar_clicked()
{
    if(ui->lineEdit_ruc->text().size() == 0)
    {

        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setText("Seleccione un proveedor");
        msgBox->show();
        return;
    }
    if(ui->tableWidget__items_productos->rowCount() == 0)
    {

        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setText("Seleccione un producto");
        msgBox->show();
        return;
    }
    QString Codigo,Descripcion,Accesorios,Precio_unt,Cant,Total_item,Total_venta;
    QString idproveedor,idcompra,total;
    QDate fecha = ui->dateEdit->date();
    idproveedor = Proveedores[ui->lineEdit_proveedor->text()];    
    total = ui->lineEdit_total->text();
    QSqlQuery query;
    query.prepare("INSERT INTO compra (fecha,subtotal,proveedor_idproveedor) VALUES (?,?,?) ");
    query.bindValue(0,fecha);
    query.bindValue(1,total);
    query.bindValue(2,idproveedor);
    query.exec();


    query.exec("SELECT LAST_INSERT_ID()");
    query.next();
    idcompra = query.value(0).toString();

    for (int i = 0; i<ui->tableWidget__items_productos->rowCount(); i++)
           {               
               Codigo = ui->tableWidget__items_productos->item(i,0)->text();
               Descripcion = ui->tableWidget__items_productos->item(i,1)->text();
               Accesorios = ui->tableWidget__items_productos->item(i,2)->text();
               Precio_unt = ui->tableWidget__items_productos->item(i,3)->text();
               Cant =  ui->tableWidget__items_productos->item(i,4)->text();
               Total_item = ui->tableWidget__items_productos->item(i,5)->text();
               query.prepare("INSERT INTO linea_compra (compra_idcompra,producto_idproducto,cantidad,precio) VALUES (?,?,?,?)");
               query.bindValue(0,idcompra);
               query.bindValue(1,Productos_Agregados[Codigo]);
               query.bindValue(2,Cant);
               query.bindValue(3,Precio_unt.toFloat());
               if(query.exec() == TRUE)
               {
                   QMessageBox *msgBox =new QMessageBox;
                   msgBox->setIcon(QMessageBox::Information);
                   msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
                   msgBox->setText("Compra Agregada");
                   msgBox->show();
               }

               else
               {
                   QMessageBox *msgBox =new QMessageBox;
                   msgBox->setIcon(QMessageBox::Information);
                   msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
                   msgBox->setText("Ocurrió un problema al agregar la compra, revise la conexión con el servidor de base de datos");
                   msgBox->show();
                   return;
               }

           }
    updateListCompras();
    //LIMPIANDO DATOS
    ui->lineEdit_proveedor->clear();
    ui->lineEdit_ruc->clear();
    ui->lineEdit_direccion->clear();
    ui->lineEdit_productos->clear();
    for (int i=ui->tableWidget__items_productos->rowCount()-1; i >= 0; --i)
        ui->tableWidget__items_productos->removeRow(i);
    ui->lineEdit_subtotal->clear();
    ui->lineEdit_igv->clear();
    ui->lineEdit_total->clear();
    ui->lineEdit_proveedor->setFocus();
    contador = 0;
    currentCant = 0;
    compra_total = 0;

}
void compras::addItemProductos(int cant,int row)
{
        /*int cantidad = cant;
        int count = row;
        QString codigo = ui->tableWidget_productos->item(count,0)->text();
        QString descripcion = ui->tableWidget_productos->item(count,1)->text();
        QString accesorios = ui->tableWidget_productos->item(count,2)->text();
        QString precio = ui->tableWidget_productos->item(count,3)->text();
        double total = cantidad*precio.toDouble();
        compra_total += total;

        double monto_sub_total;
        double monto_impuesto;
        double monto_total;
        qDebug()<<compra_total<<endl;
        monto_sub_total = compra_total;
        monto_impuesto = (monto_sub_total * ui->spinBox->text().toDouble()/100);
        monto_total = monto_sub_total + monto_impuesto;

        ui->tableWidget__items_productos->insertRow(contador);
        ui->tableWidget__items_productos->setItem(contador,0, new QTableWidgetItem(codigo));
        ui->tableWidget__items_productos->setItem(contador,1, new QTableWidgetItem(descripcion));
        ui->tableWidget__items_productos->setItem(contador,2, new QTableWidgetItem(accesorios));
        ui->tableWidget__items_productos->setItem(contador,3, new QTableWidgetItem(precio));
        ui->tableWidget__items_productos->setItem(contador,4, new QTableWidgetItem(QString::number(cantidad)));
        ui->tableWidget__items_productos->setItem(contador,5, new QTableWidgetItem(QString::number(total)));

        contador++;
        Productos_Agregados[codigo] = Productos[codigo];

        ui->lineEdit_subtotal->setText(QString::number(monto_sub_total));
        ui->lineEdit_igv->setText(QString::number(monto_impuesto));
        ui->lineEdit_total->setText(QString::number(monto_total));*/
}
void compras::updateListCompras()
{
    for (int i=ui->tableWidget_Compras->rowCount()-1; i >= 0; --i)
        ui->tableWidget_Compras->removeRow(i);

    QString Razon_Social,Monto_total,idproveedor,idcompra;
    QDate Fecha;
    QSqlQuery query,sub_query;
    query.exec("SELECT idcompra,fecha,subtotal,proveedor_idproveedor FROM compra");
    int c = 0;

    while(query.next())
    {
        idcompra = query.value(0).toString();
        Fecha = query.value(1).toDate();
        Monto_total =  query.value(2).toString();
        idproveedor = query.value(3).toString();

        sub_query.exec("select raz_social from proveedor WHERE idproveedor = \""+idproveedor+"\"");
        sub_query.next();

        Razon_Social = sub_query.value(0).toString();

        ui->tableWidget_Compras->insertRow(c);
        ui->tableWidget_Compras->setItem(c,0,new QTableWidgetItem(Fecha.toString()));
        ui->tableWidget_Compras->setItem(c,1,new QTableWidgetItem(Razon_Social));
        ui->tableWidget_Compras->setItem(c,2,new QTableWidgetItem(Monto_total));
        Compras[Razon_Social] = idcompra;
        c++;
    }
}

void compras::on_tableWidget_Compras_itemClicked(QTableWidgetItem *item)
{
    int count = item->row();
    currentItem = item->row();
    QString Razon_Social = ui->tableWidget_Compras->item(count,1)->text();
    current_idCompras = Compras[Razon_Social];
}

void compras::on_pushButton_ver_compra_clicked()
{
    if(current_idCompras.size() == 0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setText("Seleccione una compra de la lista");
        msgBox->show();
        return;
    }
    QDate fecha;
    QString proveedor,ruc,direccion,total,idproveedor,idproducto;
    QSqlQuery query;
    query.prepare("SELECT fecha,subtotal,proveedor_idproveedor FROM compra WHERE idcompra = \""+current_idCompras+"\"");
    query.exec();
    query.next();
    fecha = query.value(0).toDate();
    total = query.value(1).toString();
    idproveedor = query.value(2).toString();

    query.prepare("SELECT raz_social,ruc,direccion FROM proveedor WHERE idproveedor = \""+idproveedor+"\"");
    query.exec(); query.next();
    proveedor = query.value(0).toString();
    ruc =  query.value(1).toString();
    direccion = query.value(2).toString();

    ui_datos_compras * datos_compras = new ui_datos_compras;

    datos_compras->setdataproveedor(fecha,proveedor,ruc,direccion,total);
    QString codigo,descripcion,accesorios,precio_unit,cant;
    double total_item;
    query.prepare("SELECT producto_idproducto,cantidad,precio FROM linea_compra WHERE compra_idcompra = \""+current_idCompras+"\"");
    query.exec();
    QSqlQuery subquery;
    while(query.next())
    {
        idproducto = query.value(0).toString();
        cant = query.value(1).toString();
        precio_unit = query.value(2).toString();

        subquery.exec("SELECT codigo,descripcion,accesorios FROM producto WHERE idproducto = \""+idproducto+"\"");
        subquery.next();
        codigo = subquery.value(0).toString();
        descripcion = subquery.value(1).toString();
        accesorios = subquery.value(2).toString();
        total_item = cant.toDouble() * precio_unit.toDouble();
        datos_compras->additemproducto(codigo,descripcion,accesorios,precio_unit,cant,QString::number(total_item));
    }
    datos_compras->show();
}

void compras::on_lineEdit_proveedor_returnPressed()
{
    on_pushButton_buscar_proveedor_clicked();
}

void compras::on_lineEdit_productos_returnPressed()
{
    on_pushButton_buscar_producto_clicked();
}

void compras::on_tableWidget_Compras_doubleClicked(const QModelIndex &index)
{
    /*on_tableWidget_Compras_itemClicked();
    on_pushButton_ver_compra_clicked();*/
}


void compras::on_tableWidget__items_productos_itemDoubleClicked(QTableWidgetItem *item)
{
    int count = item->row();
    double total = ui->tableWidget__items_productos->item(count,5)->text().toDouble();
    compra_total -= total;
    double monto_sub_total;
    double monto_impuesto;
    double monto_total;
    qDebug()<<compra_total<<endl;
    monto_sub_total = compra_total;
    monto_impuesto = (monto_sub_total * ui->spinBox->text().toDouble()/100);
    monto_total = monto_sub_total + monto_impuesto;
    ui->lineEdit_subtotal->setText(QString::number(monto_sub_total));
    ui->lineEdit_igv->setText(QString::number(monto_impuesto));
    ui->lineEdit_total->setText(QString::number(monto_total));
    ui->tableWidget__items_productos->removeRow(count);
    contador--;
}


void compras::on_pushButton_eliminar_compra_clicked()
{

    QMessageBox *msgBox =new QMessageBox;
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
    msgBox->setWindowTitle("Confirmar");
    msgBox->setText("Desea eliminar el la compra seleccionada?");
    msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
    msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

    int ret = msgBox->exec();

    switch(ret)
    {
        case QMessageBox::Ok:
    {
            QSqlQuery query;
            query.prepare("DELETE FROM compra WHERE idcompra = \""+current_idCompras+"\"");
            if(query.exec() == true)
            {
                qDebug()<<"Borrador compra"<<endl;
            }
            updateListCompras();
            break;
    }
        case QMessageBox::Cancel:
            break;
    }

}
void compras::getProveedor(QString id,QString ruc,QString razon,QString direccion)
{
    actualCompra->setDatosProveedor(id,ruc,razon,direccion);
    ui->lineEdit_ruc->setText(ruc);
    ui->lineEdit_proveedor->setText(razon);
    ui->lineEdit_direccion->setText(direccion);


}
