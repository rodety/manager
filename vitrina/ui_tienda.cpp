#include "ui_tienda.h"
#include "ui_ui_tienda.h"
#include "ui_tienda_agregar.h"
#include "ui_vitrina_agregar.h"
#include "ui_item_posicion.h"
#include "vitrina/ui_almacen.h"
#include "empresa.h"
//#include "ui_datos_empresa.h"
#include "ui_agregar_empresa.h"
//#include "sesion.h"
#include "mainwindow.h"
#include <QtGui>

ui_tienda::ui_tienda(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_tienda)
{
    ui->setupUi(this);
    actualizar_combo_empresa();
    caso=false;    traspaso=false;
    habilitar_botones();
    actual=Empresa;
    ui->pushButton_aceptar_traspaso->hide();    
}

ui_tienda::~ui_tienda()
{
    delete ui;
}
void ui_tienda::actualizar_combo_empresa()
{
    ui->comboBox_empresa->clear();

    QSqlQuery query;
    query.prepare("SELECT idEmpresa,razonSocial FROM Empresa");
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idempresa = query.value(0).toString();
        QString raz_social = query.value(1).toString();

        Empresas[raz_social] = idempresa;
        ui->comboBox_empresa->insertItem(c++,raz_social);
    }
}

void ui_tienda::actualizar_combo_tienda(QString empresa)
{
    ui->comboBox_tienda->clear();

    QSqlQuery query;
    query.prepare("SELECT idTienda,nombre FROM Tienda WHERE Empresa_idEmpresa=?");
    query.bindValue(0,empresa);
    query.exec();

    int c = 0;

    if(!query.next())
        ui->comboBox_tienda->insertItem(c++,"");
    else
    {
        QString idtienda = query.value(0).toString();
        QString alias = query.value(1).toString();

        Tiendas[alias] = idtienda;

        ui->comboBox_tienda->insertItem(c++,alias);
        while(query.next())
        {
            idtienda = query.value(0).toString();
            alias = query.value(1).toString();

            Tiendas[alias] = idtienda;

            ui->comboBox_tienda->insertItem(c++,alias);
        }
    }
}

void ui_tienda::actualizar_combo_vitrina(QString vitrin)
{
    ui->comboBox_vitrina->clear();

    QSqlQuery query;
    query.prepare("SELECT Ubicacion_idUbicacion,nombre FROM Vitrina WHERE Tienda_idTienda=?");
    query.bindValue(0,vitrin);
    query.exec();

    int c = 0;
    if(!query.next())
        ui->comboBox_vitrina->insertItem(c++,"");
    else
    {
        QString idvitrina = query.value(0).toString();
        QString nombre = query.value(1).toString();

        Vitrinas[nombre] = idvitrina;

        ui->comboBox_vitrina->insertItem(c++,nombre);
        while(query.next())
        {
            idvitrina = query.value(0).toString();
            nombre = query.value(1).toString();

            Vitrinas[nombre] = idvitrina;

            ui->comboBox_vitrina->insertItem(c++,nombre);
        }
    }
}

void ui_tienda::actualizar_combo_niveles(QString vitrin)
{
    ui->comboBox_niveles->clear();

    QSqlQuery query;
    query.prepare("SELECT numeroNivel FROM Vitrina WHERE Ubicacion_idUbicacion=?");
    query.bindValue(0,vitrin.toInt());
    query.exec();
    query.next();

    int niveles = query.value(0).toInt();

    for(int i=0;i<niveles;i++)
    {
       //c=i+1;
        QString str;
        ui->comboBox_niveles->insertItem(i,str.append(QString("%1").arg(i+1)));
    }
}

void ui_tienda::limpiar_grilla()
{
    ui->grilla->clear();
}

void ui_tienda::set_dimension_grilla()      //podria recibir de frente filas y columnas
{
    limpiar_grilla();

    QSqlQuery query;
    query.prepare("SELECT numeroFila,numeroColumna FROM Vitrina WHERE Ubicacion_idUbicacion=?");
    query.bindValue(0,idVitrina);
    query.exec();    query.next();

    int fila = query.value(0).toInt();
    int columna = query.value(1).toInt();

    ui->grilla->setColumnCount(columna);
    ui->grilla->setRowCount(fila);
}

void ui_tienda::actualizar_grilla()
{
    Posiciones.clear();
    QSqlQuery query1, query;
    query.prepare("SELECT Producto_idProducto,fila,columna,nivel FROM Producto_has_Vitrina WHERE Vitrina_Ubicacion_idUbicacion=? and nivel=?");
    query.bindValue(0,idVitrina);
    query.bindValue(1,actual_nivel);
    query.exec();

    while(query.next())
    {
        QString idproducto = query.value(0).toString();
        int pos_fila = query.value(1).toInt();
        int pos_columna = query.value(2).toInt();
        int pos_nivel = query.value(3).toInt();

        QString key = QString::number(pos_fila)+"-"+QString::number(pos_columna);
        Posiciones[key] = idproducto;

        query1.prepare("SELECT codigo, descripcion FROM Producto WHERE idproducto=?");
        query1.bindValue(0,idproducto);
        query1.exec();
        query1.next();
        QString codigo=query1.value(0).toString();
        QString descripcion=query1.value(1).toString();

        ui->grilla->setItem(pos_fila-1,pos_columna-1,new QTableWidgetItem(codigo+"-"+descripcion));
    }
}

void ui_tienda::habilitar_botones()
{
    if(caso)
    {
        ui->btnAgregar->close();
        ui->btnDeshabilitar->close();
        ui->btnEditar->close();
        ui->btnImprimir->close();
        ui->pushButton_traspaso->close();
        ui->button_traspaso_almacen->close();
    }

}

//ACCION CUANDO CAMBIA LOS COMBOS
void ui_tienda::changeActual(lbls num)
{
    switch(ui_tienda::actual)
    {
        case Empresa:
            ui->lblEmpresa->setStyleSheet("QLabel { color:black }"); break;

        case Tienda:
            ui->lblTienda->setStyleSheet("QLabel { color:black }");  break;

        case Vitrina:
            ui->lblVitrina->setStyleSheet("QLabel { color:black }"); break;
    }

    ui_tienda::actual=num;
    switch(ui_tienda::actual)
    {
        case Empresa:
            ui->lblEmpresa->setStyleSheet("QLabel { color:red }"); break;

        case Tienda:
            ui->lblTienda->setStyleSheet("QLabel { color:red }");  break;

        case Vitrina:
            ui->lblVitrina->setStyleSheet("QLabel { color:red }"); break;
    }

}

void ui_tienda::on_comboBox_empresa_currentIndexChanged(const QString &arg1)
{
    set_idEmpresa(Empresas[arg1]);
    actualizar_combo_tienda(get_idEmpresa());

    changeActual(Empresa);
}

void ui_tienda::on_comboBox_tienda_currentIndexChanged(const QString &arg1)
{
    set_idTienda(Tiendas[arg1]);
    actualizar_combo_vitrina(get_idTienda());

    changeActual(Tienda);
}

void ui_tienda::on_comboBox_vitrina_currentIndexChanged(const QString &arg1)
{
    set_idVitrina(Vitrinas[arg1]);
    actualizar_combo_niveles(get_idVitrina());

    changeActual(Vitrina);
}


void ui_tienda::on_comboBox_niveles_currentIndexChanged(int index)
{
    set_actual_nivel(index+1);
    set_dimension_grilla();
    actualizar_grilla();
}


//BOTONES DE TIENDA
void ui_tienda::agregarTienda(bool b)
{
    if(get_idEmpresa().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Empresa válida!");
        msgBox->exec();
    }
    else
    {

        tienda_agregar = new ui_tienda_agregar;
        connect(tienda_agregar,SIGNAL(actualizarParent(QString)),this,SLOT(actualizar_combo_tienda(QString)));
        tienda_agregar->set_idEmpresa(get_idEmpresa());
        tienda_agregar->set_idTienda(idTienda);
        tienda_agregar->set_caso(b);
        tienda_agregar->setWindowTitle("Agregar Tienda");
        tienda_agregar->show();
    }
}

void ui_tienda::deshabilitarTienda()
{
    if(get_idTienda().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Tienda válida!");
        msgBox->exec();
    }
    else
    {
        tienda*del=new tienda(get_idTienda(),"","","","","","");

        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmar");
        msgBox->setText("Desea eliminar la Tienda?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        switch(ret)
        {
            case QMessageBox::Ok:
                del->eliminar();
                actualizar_combo_tienda(idEmpresa);
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

void ui_tienda::on_imprimir_tienda_clicked()
{}

//BOTONES DE VITRINA
void ui_tienda::agregarVitrina(bool b)
{
    if(get_idTienda().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Vitrina válida!");
        msgBox->exec();
    }
    else
    {
        ui_vitrina_agregar * vitrina_agregar=new ui_vitrina_agregar;
        vitrina_agregar->set_idTienda(get_idTienda());
        vitrina_agregar->set_ui_tienda_actual(this);
        vitrina_agregar->set_caso(b);
        vitrina_agregar->setWindowTitle("Vitrina");
        vitrina_agregar->show();
    }
}

void ui_tienda::deshabilitarVitrina()
{
    if(get_idVitrina().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Vitrina válida!");
        msgBox->exec();
    }
    else
    {
        vitrina*del=new vitrina(get_idVitrina(),"","",0,0,0,0);
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmar");
        msgBox->setText("Desea eliminar la Tienda?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        switch(ret)
        {
            case QMessageBox::Ok:
                del->eliminar();
                actualizar_combo_vitrina(idTienda);
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

void ui_tienda::agregarEmpresa(bool b)
{
    add_empresa = new ui_agregar_empresa;
    connect(add_empresa,SIGNAL(actualizarParent()),this,SLOT(actualizar_combo_empresa()));
    add_empresa->show();    
    add_empresa->set_behavior(b);

    if (!b)
    {
        add_empresa->setWindowTitle("Editar Empresa");
        add_empresa->set_idEmpresa(get_idEmpresa());
        add_empresa->update_form();

    }
    else
        add_empresa->setWindowTitle("Agregar Empresa");
    add_empresa->show();
}
void ui_tienda::deshabilitarEmpresa()
{
    if(get_idEmpresa().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una empresa");
        msgBox->exec();
    }
    else
    {
        empresa *del=new empresa;
        del->setId(get_idEmpresa());
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmar");
        msgBox->setText("Desea eliminar la empresa?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        switch(ret)
        {
            case QMessageBox::Ok:
                del->eliminar();
                actualizar_combo_empresa();
                break;
            case QMessageBox::Cancel:
                break;
        }
    }

}

void ui_tienda::on_imprimir_vitrina_clicked()
{}

void ui_tienda::on_grilla_cellDoubleClicked(int row, int column)
{
    cout<<idItem.toStdString()<<endl;
    ui_item_posicion* posicion_agregar = new ui_item_posicion;
    posicion_agregar->set_ui_tienda_actual(this);
    if(traspaso)
    {
        posicion_agregar->set_caso(true);
        posicion_agregar->setWindowTitle("Nueva Posicion");
        posicion_agregar->set_posicion(row+1,column+1,actual_nivel);
        posicion_agregar->habilitar();
//        posicion_agregar->set_iditem(get_idItem_tras());
        posicion_agregar->fillText(get_idItem_tras());
//        posicion_agregar->on_pushButton_addProducto_clicked();
//        posicion_agregar->on_pushButton_guardar_clicked();
    }
    if(idItem.isEmpty())
    {
        posicion_agregar->set_caso(true);
        posicion_agregar->setWindowTitle("Nueva Posicion");
        posicion_agregar->set_posicion(row+1,column+1,actual_nivel);
        posicion_agregar->habilitar();

    }else   //deshabilitar ciertos botones
    {
        posicion_agregar->set_iditem(get_idItem());
        posicion_agregar->set_caso(false);
        posicion_agregar->actualizar();
        posicion_agregar->setWindowTitle("Editar Posicion");
        posicion_agregar->set_posicion(row+1,column+1,actual_nivel);
        posicion_agregar->deshabilitar();

    }
    posicion_agregar->show();
}

void ui_tienda::on_grilla_itemSelectionChanged()
{
    QString fila = QString::number(ui->grilla->currentRow()+1);

    QString columna = QString::number(ui->grilla->currentColumn()+1);

    QString pos = fila+"-"+columna;

    set_idItem(Posiciones[pos]);
}

void ui_tienda::on_pushButton_traspaso_clicked()
{
    if(!idItem.isEmpty())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM Producto_has_Vitrina WHERE Vitrina_Ubicacion_idUbicacion=? and nivel=? and fila=? and columna=? ");
        query.bindValue(0,idVitrina);
        query.bindValue(1,actual_nivel);
        query.bindValue(2,ui->grilla->currentRow()+1);
        query.bindValue(3,ui->grilla->currentColumn()+1);
        query.exec();
        query.next();

        ui_tienda * tienda_traspaso=new ui_tienda;
        tienda_traspaso->enableButtonAceptar();
        tienda_traspaso->set_query(query);
        tienda_traspaso->set_caso(true);
        tienda_traspaso->set_idItem_tras(get_idItem());
        tienda_traspaso->habilitar_botones();
        tienda_traspaso->set_ui_tienda_traspaso(this);
        tienda_traspaso->set_caso_traspaso(true);
        tienda_traspaso->show();

        actualizar_grilla();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un producto");
        msgBox.exec();
    }
}

void ui_tienda::on_pushButton_aceptar_traspaso_clicked()
{
    if(traspaso)
    {
        int row=ui->grilla->currentRow()+1;
        int col=ui->grilla->currentColumn()+1;
        int level=actual_nivel;
        //aki va traspaso de almacen a vitrina

        Sesion* s= Sesion::getSesion();

        QSqlQuery query;
        query.prepare("INSERT INTO Producto_has_Vitrina(Producto_idProducto,Vitrina_Ubicacion_idUbicacion,fila,columna,nivel,fecha,Colaborador_Persona_idPersona) VALUES(?,?,?,?,?,now(),?) ");
        query.bindValue(0,idTraspaso);
        query.bindValue(1,idVitrina);
        query.bindValue(2,row);
        query.bindValue(3,col);
        query.bindValue(4,level);
        query.bindValue(5,s->getIdColaborador());
        if(query.exec())
        {
            montura * m=new montura;
            m->setIdProducto(idTraspaso);
            m->addToVitrina();
            close();
        }
        else
        {
            cout<<query.lastError().text().toStdString()<<endl;
            close();
        }
    }

    if(caso)
    if(idItem.isEmpty())
    {
        if(caso_traspaso)
        {
            QString oldVitrina=sqlQuery.value(1).toString();
            QString oldRow=sqlQuery.value(2).toString();
            QString oldCol=sqlQuery.value(3).toString();
            QString oldLevel=sqlQuery.value(4).toString();

            int row=ui->grilla->currentRow()+1;
            int col=ui->grilla->currentColumn()+1;
            int level=actual_nivel;


            QSqlQuery query;
            query.prepare("UPDATE Producto_has_Vitrina SET Vitrina_Ubicacion_idUbicacion='"+idVitrina+"', fila=? , columna=? , nivel=? WHERE Vitrina_Ubicacion_idUbicacion=? and fila=? and columna=? and nivel=? ");
            query.bindValue(0,row);
            query.bindValue(1,col);
            query.bindValue(2,level);
            query.bindValue(3,oldVitrina);
            query.bindValue(4,oldRow);
            query.bindValue(5,oldCol);
            query.bindValue(6,oldLevel);
            query.exec();

            close();
            ui_tienda_traspaso->set_dimension_grilla();
            ui_tienda_traspaso->actualizar_grilla();
        }
        else
        {
            int row=ui->grilla->currentRow()+1;
            int col=ui->grilla->currentColumn()+1;
            int level=actual_nivel;
            //aki va traspaso de almacen a vitrina

            Sesion* s= Sesion::getSesion();

            QSqlQuery query;
            query.prepare("INSERT INTO Producto_has_Vitrina(Producto_idProducto,Vitrina_Ubicacion_idUbicacion,fila,columna,nivel,fecha,Colaborador_Persona_idPersona) VALUES(?,?,?,?,?,now(),?) ");
            query.bindValue(0,idProducto_tras);
            query.bindValue(1,idVitrina);
            query.bindValue(2,row);
            query.bindValue(3,col);
            query.bindValue(4,level);
            query.bindValue(5,s->getIdColaborador());

            if(query.exec())
            {
                montura* mont= new montura;
                mont->setIdProducto(idProducto_tras);
                mont->almacenToVitrina();    //resta 1 de cantidadAlmacen y lo añade a cantidadVitrina
                close();
            }
            else
                cout<<query.lastError().text().toStdString()<<endl;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un espacio vacio");
        msgBox.exec();
    }
}

void ui_tienda::on_button_traspaso_almacen_clicked()
{
    if(!idItem.isEmpty())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM Producto_has_Vitrina WHERE Vitrina_Ubicacion_idUbicacion=? and nivel=? and fila=? and columna=? ");
        query.bindValue(0,idVitrina);
        query.bindValue(1,actual_nivel);
        query.bindValue(2,ui->grilla->currentRow()+1);
        query.bindValue(3,ui->grilla->currentColumn()+1);
        query.exec();
        query.next();

        ui_almacen* traspaso_almacen=new ui_almacen;
        traspaso_almacen->set_query(query);
        traspaso_almacen->setFromVitrina(true);
        traspaso_almacen->show();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un producto");
        msgBox.exec();
    }
}

void ui_tienda::on_btnAgregar_clicked()
{
    switch(actual)
    {
        case Empresa:
            agregarEmpresa(true);
            break;

        case Tienda:
            agregarTienda(true);
            break;

        case Vitrina:
            agregarVitrina(true);
            break;
    }
}

void ui_tienda::on_btnEditar_clicked()
{
    switch(actual)
    {
        case Empresa:
            agregarEmpresa(false);
            break;

        case Tienda:
            agregarTienda(false);
            break;

        case Vitrina:
            agregarVitrina(false);
            break;
    }
}

void ui_tienda::on_btnDeshabilitar_clicked()
{
    switch(actual)
    {
        case Empresa:
            deshabilitarEmpresa();
            break;

        case Tienda:
            deshabilitarTienda();
            break;

        case Vitrina:
            deshabilitarVitrina();
            break;
    }
}

void ui_tienda::on_comboBox_vitrina_activated(int index)
{
    changeActual(Vitrina);
}

void ui_tienda::on_comboBox_empresa_activated(const QString &arg1)
{
    changeActual(Empresa);
}

void ui_tienda::on_comboBox_tienda_activated(const QString &arg1)
{
    changeActual(Tienda);
}

void ui_tienda::enableButtonAceptar()
{
    ui->pushButton_aceptar_traspaso->show();
}
