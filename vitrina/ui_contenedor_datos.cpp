#include "ui_contenedor_datos.h"
#include "ui_ui_contenedor_datos.h"
#include <QSqlQuery>
#include <QDebug>
#include "contenedor.h"
#include <QMessageBox>
#include <QSqlError>
#include "ui_tienda.h"

ui_contenedor_datos::ui_contenedor_datos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_contenedor_datos)
{
    ui->setupUi(this);
}


ui_contenedor_datos::~ui_contenedor_datos()
{
    delete ui;
}

QString ui_contenedor_datos::get_idContenedor(){return idContenedor;}
void ui_contenedor_datos::set_idContenedor(QString c){idContenedor = c;}

ui_almacen* ui_contenedor_datos::get_ui_almacen_parent(){return ui_almacen_parent;}
void ui_contenedor_datos::set_ui_almacen_parent(ui_almacen * al){ui_almacen_parent = al;}

int ui_contenedor_datos::get_behavior(){return behavior;}
void ui_contenedor_datos::set_behavior(int b){behavior = b;}

void ui_contenedor_datos::set_idProducto(QString tmp){ui->lineEdit_codigoProducto->setText(tmp);}
bool ui_contenedor_datos::add_Product(){return on_pushButton_addProducto_clicked();}

void ui_contenedor_datos::set_spinBox_fila(int f){ui->spinBox_fila->setValue(f);}
void ui_contenedor_datos::set_spinBox_columna(int c){ui->spinBox_columna->setValue(c);}

void ui_contenedor_datos::clear_widget_list_productos()
{
    qDebug()<<ui->tableWidget_list_productos->rowCount();
    for(int i=ui->tableWidget_list_productos->rowCount()-1; i>=0;--i)
        ui->tableWidget_list_productos->removeRow(i);
}

void ui_contenedor_datos::uptate_widget_list_productos()
{
    QString s_query = "SELECT idProducto,codigo as Codigo,descripcion as Descripcion,Marca_idMarca as Marca,stock,precioVenta,accesorios,precioDescuento,Estado_idEstado FROM Producto ";
            s_query+= "INNER JOIN Contenedor_has_Producto ON idProducto = Producto_idProducto ";
            s_query+= "WHERE contenedor_idcontenedor = "+idContenedor;

    QSqlQuery query;
    query.prepare(s_query);

    if(!query.exec(s_query))
       qDebug() << "Error al introducir los datos";

    int row=0;
    while(query.next())
    {
        QString idproducto = query.value(0).toString();
        QString codigo = query.value(1).toString();
        QString descripcion = query.value(2).toString();
        QString idmarca = query.value(3).toString();
        QString stock = query.value(4).toString();
        QString precio = query.value(5).toString();
        QString accesorios = query.value(6).toString();
        QString p_descuento = query.value(7).toString();
        QString habilitado = query.value(8).toString();

        ui->tableWidget_list_productos->insertRow(row);
        ui->tableWidget_list_productos->setItem(row,0,new QTableWidgetItem(codigo));
        ui->tableWidget_list_productos->setItem(row,1,new QTableWidgetItem(descripcion));
        ui->tableWidget_list_productos->setItem(row,2,new QTableWidgetItem(idmarca));
        ui->tableWidget_list_productos->setItem(row,3,new QTableWidgetItem(precio));
    }

    QHeaderView *header = ui->tableWidget_list_productos->horizontalHeader();
    header->setResizeMode(QHeaderView::Stretch);

    /*QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);

    if(model->lastError().isValid())
        qDebug()<<model->lastError();*/
}

void ui_contenedor_datos::update_form()
{
    switch(behavior)
    {
        case 0:
            ui->pushButton_saveContenedor->setText("Crear");
            break;
        case 1:
            ui->pushButton_saveContenedor->setText("Guardar");
            break;
    }


    ui->lineEdit_nombre->clear();
    ui->lineEdit_descripcion->clear();

    QSqlQuery query;
    query.prepare("SELECT nombre,descripcion,posFila,posColumna,capacidad FROM Contenedor WHERE idContenedor=?");
    query.bindValue(0,idContenedor);
    query.exec();

    query.next();

    QString nombre = query.value(0).toString();
    QString descripcion = query.value(1).toString();
    int pos_fila = query.value(2).toInt();
    int pos_columna = query.value(3).toInt();
    int capacidad = query.value(4).toInt();

    ui->lineEdit_nombre->setText(nombre);
    ui->lineEdit_descripcion->setText(descripcion);
    ui->spinBox_fila->setValue(pos_fila);
    ui->spinBox_columna->setValue(pos_columna);
    ui->spinBox_capacidad->setValue(capacidad);

    uptate_widget_list_productos();
}

void ui_contenedor_datos::on_pushButton_salir_clicked()
{
    close();
}

bool ui_contenedor_datos::on_pushButton_addProducto_clicked()
{
    if(ui->lineEdit_codigoProducto->text().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Informacion");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe escribir un codigo primero.");
        msgBox->exec();

        close();
        return false;
    }
    else
    {
        QString producto_codigo = ui->lineEdit_codigoProducto->text(); //verificar si el producto existe;

        QSqlQuery query;
        query.prepare("SELECT idProducto FROM Producto WHERE codigo=?");
        query.bindValue(0,producto_codigo);
        query.exec();
        if(!query.next())
        {
            QMessageBox *msgBox =new QMessageBox;
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
            msgBox->setWindowTitle("Información");
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
            msgBox->setText("El producto asociado al código que ingreso no existe!");
            msgBox->exec();
        }
        else
        {
            QString idProducto = query.value(0).toString();

            query.prepare("SELECT * from Contenedor_has_Producto WHERE Producto_idProducto=?");
            query.bindValue(0,idProducto);
            query.exec();

            if(query.next())
            {
                QString idCont=query.value(1).toString();
                query.prepare("SELECT nombre,Andamio_idAndamio from Contenedor WHERE idContenedor=?");
                query.bindValue(0,idCont);
                query.exec();   query.next();

                QString contenedorName=query.value(0).toString(), idAndamio=query.value(1).toString();

                query.prepare("SELECT nombre,Almacen_idAlmacen from Andamio WHERE idAndamio=?");
                query.bindValue(0,idAndamio);
                query.exec();   query.next();

                QString andamioName=query.value(0).toString(), idAlmacen=query.value(1).toString();

                query.prepare("SELECT nombre,Tienda_idTienda from Almacen WHERE idAlmacen=?");
                query.bindValue(0,idAlmacen);
                query.exec();   query.next();

                QString almacenName=query.value(0).toString(), idTienda=query.value(1).toString();

                query.prepare("SELECT nombre FROM Tienda WHERE IdTienda=?");
                query.bindValue(0,idTienda);
                query.exec();   query.next();

                QString tiendaName=query.value(0).toString();

                QMessageBox *msgBox =new QMessageBox;
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
                msgBox->setWindowTitle("Informacion");
                msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox->setText("El producto ya esta asignado a otro contenedor : Tienda:'"+tiendaName+"', Almacen:'"+almacenName+"', Andamio:'"+andamioName+"', Contenedor:'"+contenedorName+"' ¿Aun desea asignarlo en esta posicion? ");
                int op=msgBox->exec();
                Sesion* s=Sesion::getSesion();
                switch(op)
                {
                    case QMessageBox::Ok:

                        if(idCont.compare(idContenedor)==0)
                        {
                            return true;
                        }
                        else
                        {   query.prepare("INSERT INTO Contenedor_has_Producto(Contenedor_idContenedor,Producto_idProducto,fecha,Colaborador_Persona_idPersona) VALUES(?,?,now(),?)");
                            query.bindValue(0,idContenedor);
                            query.bindValue(1,idProducto);
                            query.bindValue(2,s->getIdColaborador());

                            if(query.exec())
                            {
                                //algo con historial de almacen
                                return true;
                            }
                            else return false;
                        }
                        break;

                    case QMessageBox::Cancel:
                        return false;
                        break;
                }
            }
            else
            {
                Sesion* s=Sesion::getSesion();

                query.prepare("INSERT INTO Contenedor_has_Producto(Contenedor_idContenedor,Producto_idProducto,fecha,Colaborador_Persona_idPersona) VALUES(?,?,now(),?)");
                query.bindValue(0,idContenedor);
                query.bindValue(1,idProducto);
                query.bindValue(2,s->getIdColaborador());

                if(query.exec())
                {
                    //algo con historial de almacen
                    return true;
                }
                else return false;
            }
        }
    }
}

void ui_contenedor_datos::on_pushButton_saveContenedor_clicked()
{
    QString idAndamio = ui_almacen_parent->get_currentIdAndamio();
    QString nombre = ui->lineEdit_nombre->text();
    QString descripcion = ui->lineEdit_descripcion->text();
    QString pos_fila = ui->spinBox_fila->text();
    QString pos_columna = ui->spinBox_columna->text();
    QString capacidad = ui->spinBox_capacidad->text();

    contenedor *contenedor_data;

    QMessageBox *msgBox =new QMessageBox;
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
    msgBox->setWindowTitle("Resultado");
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setButtonText(QMessageBox::Ok,"Aceptar");

    if(nombre.compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("El nombre de un contenedor no puede quedar en blanco!");
        msgBox->exec();
    }
    else
    {
        switch(behavior)
        {
            case 0:
                contenedor_data = new contenedor("0",idAndamio,nombre,descripcion,pos_fila,pos_columna,capacidad);
                contenedor_data->agregar();
                //ui_almacen_parent->set_currentIdContenedor((pos_fila.toInt()-1)+"-"+(pos_columna.toInt()-1));
                ui_almacen_parent->update_widget_Contenedores();
                close();

                msgBox->setText("Contenedor creado correctamente.");
                //ui_almacen_parent->clear_widget_Contenedores();

                break;
            case 1:
                contenedor_data = new contenedor(idContenedor,idAndamio,nombre,descripcion,pos_fila,pos_columna,capacidad);
                contenedor_data->actualizar();
                ui_almacen_parent->update_widget_Contenedores();
                close();

                msgBox->setText("Datos actualizados correctamente.");
                break;
        }

        msgBox->exec();
    }
}

void ui_contenedor_datos::on_pushButton_deleteContenedor_clicked()
{
    contenedor *any_contenedor = new contenedor(idContenedor,"","","","","","");

    QMessageBox *msgBox =new QMessageBox;
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
    msgBox->setWindowTitle("Confirmar");
    msgBox->setText("Desea elminiar el contenedor?");
    msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
    msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

    int ret = msgBox->exec();

    switch(ret)
    {
        case QMessageBox::Ok:

            any_contenedor->eliminar();
            ui_almacen_parent->set_dimension_widget_Contenedores();
            ui_almacen_parent->update_widget_Contenedores();
            close();
            break;
        case QMessageBox::Cancel:
            break;
    }
}

void ui_contenedor_datos::on_pushButton_deleteProducto_clicked()
{
    if(ui->tableWidget_list_productos->currentItem() != NULL)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmación");
        msgBox->setText("Desea eliminar el contenedor?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        int row,column;
        QSqlQuery query;
        QString codigo_producto,idproducto;

        switch(ret)
        {
            case QMessageBox::Ok:
                qDebug()<< ui->tableWidget_list_productos->currentItem()->row()<<"???";

                row = ui->tableWidget_list_productos->currentItem()->row();
                column = 0;

                qDebug()<<row<<" "<<column<<endl;

                codigo_producto = ui->tableWidget_list_productos->itemAt(row,column)->text();

                query.prepare("SELECT idproducto FROM producto WHERE codigo=?");
                query.bindValue(0,codigo_producto);
                query.exec();
                query.next();

                idproducto = query.value(0).toString();

                qDebug()<<idproducto<<endl;

                query.prepare("DELETE FROM producto_contenedor WHERE producto_idproducto=?");
                query.bindValue(0,idproducto);
                query.exec();

                query.prepare("INSERT INTO historial_almacen(entidad_1,id_1,entidad_2,id_2,operacion,fecha) VALUES('Producto',?,'Contenedor',?,'quitar',now())");
                query.bindValue(0,idproducto);
                query.bindValue(1,idContenedor);
                query.exec();

                clear_widget_list_productos();
                uptate_widget_list_productos();
                break;

            case QMessageBox::Cancel:
                break;
        }
    }
    else
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionar un producto primero.");
        msgBox->exec();
    }
}

void ui_contenedor_datos::on_traspaso_clicked()
{
    if(ui->tableWidget_list_productos->currentItem() != NULL)
    {
        QString codigo_producto,idproducto;
        QSqlQuery query;
        int row,column;
        row = ui->tableWidget_list_productos->currentItem()->row();
        column = 0;
        codigo_producto = ui->tableWidget_list_productos->itemAt(row,column)->text();

        query.prepare("SELECT idProducto FROM Producto WHERE codigo=?");
        query.bindValue(0,codigo_producto);
        query.exec();
        query.next();

        idproducto = query.value(0).toString();

        ui_tienda * tienda_traspaso=new ui_tienda;
        tienda_traspaso->set_caso(true);
        tienda_traspaso->set_idProducto_tras(idproducto);
        tienda_traspaso->set_row_traspaso(row);
        tienda_traspaso->habilitar_botones();
        tienda_traspaso->set_ui_almacen_traspaso(get_ui_almacen_parent());
        tienda_traspaso->set_caso_traspaso(false);
        tienda_traspaso->enableButtonAceptar();
        tienda_traspaso->show();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un producto");
        msgBox.exec();
    }
}

