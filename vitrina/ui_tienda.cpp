#include "ui_tienda.h"
#include "ui_ui_tienda.h"
#include "ui_tienda_agregar.h"
#include "ui_vitrina_agregar.h"
#include "ui_item_posicion.h"
#include "ui_traspaso_almacen.h"
//#include "sesion.h"
#include "mainwindow.h"
#include <QtGui>

ui_tienda::ui_tienda(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_tienda)
{
    ui->setupUi(this);
    //ui->grilla->setModel(tienda::mostrar());
    actualizar_combo_empresa();
    caso=false;
    habilitar_botones();
    actual=Empresa;
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

void ui_tienda::actualizar_combo_tienda(QString tienda)
{
    ui->comboBox_tienda->clear();

    QSqlQuery query;
    query.prepare("SELECT idTienda,nombre FROM Tienda WHERE Empresa_idEmpresa=?");
    query.bindValue(0,tienda);
    query.exec();

    int c = 0;

    ui->comboBox_tienda->insertItem(c++,"");
    while(query.next())
    {
        QString idtienda = query.value(0).toString();
        QString alias = query.value(1).toString();

        Tiendas[alias] = idtienda;

        ui->comboBox_tienda->insertItem(c++,alias);
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
    ui->comboBox_vitrina->insertItem(c++,"");
    while(query.next())
    {
        QString idvitrina = query.value(0).toString();
        QString nombre = query.value(1).toString();

        Vitrinas[nombre] = idvitrina;

        ui->comboBox_vitrina->insertItem(c++,nombre);
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////CHECKED//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void ui_tienda::limpiar_grilla()
{
    ui->grilla->clear();
//    for(int i=ui->grilla->rowCount()-1; i>=0;--i)
//        ui->grilla->removeRow(i);
//    for(int i=ui->grilla->columnCount()-1;i>=0;--i)
//        ui->grilla->removeColumn(i);
}

void ui_tienda::set_dimension_grilla()      //podria recibir de frente filas y columnas
{
    limpiar_grilla();

    QSqlQuery query;
    query.prepare("SELECT numeroFila,numeroColumna FROM Vitrina WHERE Ubicacion_idUbicacion=?");
    query.bindValue(0,idVitrina);
    query.exec();

    query.next();

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
    //else
        //ui->pushButton_aceptar_traspaso->close();
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
        ui_tienda_agregar* tienda_agregar=new ui_tienda_agregar;
        tienda_agregar->set_idEmpresa(get_idEmpresa());
        tienda_agregar->set_ui_tienda_actual(this);
        tienda_agregar->set_caso(b);
        tienda_agregar->setWindowTitle("Tienda");
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

//////////////////// LO ARREGLO ?????'
void ui_tienda::on_imprimir_tienda_clicked()
{
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("productos_tienda.pdf");
    QPainter painter;
    if (! painter.begin(&printer))
        qWarning("failed to open file, is it writable?");


    QImage logo("fondo.png");
    painter.drawImage(10,10,logo);


    //Sacando el nombre de la Tienda
    QSqlQuery query;
    query.prepare("SELECT alias FROM tienda WHERE idtienda=?");
    query.bindValue(0,idTienda);
    query.exec();
    query.next();
    QString n_tienda=query.value(0).toString();

    painter.setFont(QFont("Times New Roman", 30));
    painter.drawText(350,30,"Tienda "+n_tienda);
    painter.setFont(QFont("Times New Roman", 15));
    painter.drawText(800,20,"Fecha: "+QDate::currentDate().toString());
    painter.drawText(800,40,"Hora: "+QTime::currentTime().toString());
    painter.setFont(QFont("Times New Roman", 20));
    painter.drawText(360,70,"Lista de Productos");
    painter.setFont(QFont("Times New Roman", 15));
    painter.drawText(10,120,"N");
    painter.drawText(50,120,"Codigo");
    painter.drawText(130,120,"Vitrina");
    painter.drawText(210,120,"Fila");
    painter.drawText(260,120,"Columna");
    painter.drawText(350,120,"Nivel");
    painter.drawText(420,120,"Descripcion");
    painter.drawText(810,120,"Precio de Venta");
    painter.drawText(950,120,"Stock");
    painter.drawLine(10,130,1000,130);

    //Sacando ids de vitrinas que pertenecen a la tienda
    QSqlQuery query1;
    query1.prepare("SELECT idvitrina, codigo FROM vitrina WHERE idtienda=?");
    query1.bindValue(0,idTienda);
    query1.exec();
    int c=1;
    int tmp=1;

    while(query1.next())
    {
        QString id_vitrina=query1.value(0).toString();
        QString v_codigo= query1.value(1).toString();
        //Sacando id de los productos
        QSqlQuery query3;
        query3.prepare("SELECT idproducto,fila,columna,nivel FROM item_posicion WHERE idvitrina=?");
        query3.bindValue(0,id_vitrina);
        query3.exec();

        while(query3.next())
        {
            QString i_idproducto = query3.value(0).toString();
            int i_fila= query3.value(1).toInt();
            int i_columna= query3.value(2).toInt();
            int i_nivel= query3.value(3).toInt();


            //Sacando lista de productos
            QSqlQuery query2;
            query2.prepare("SELECT codigo, descripcion,stock,precio_venta,accesorios FROM producto WHERE idproducto=?");
            query2.bindValue(0,i_idproducto);
            query2.exec();
            query2.next();

            QString p_codigo = query2.value(0).toString();
            QString p_descripcion= query2.value(1).toString();
            QString p_stock = query2.value(2).toString();
            QString p_precio = query2.value(3).toString();

            painter.drawText(10,120+c*30,QString::number(tmp));
            painter.drawText(50,120+c*30,p_codigo);
            painter.drawText(130,120+c*30,v_codigo);
            painter.drawText(210,120+c*30,QString::number(i_fila));
            painter.drawText(260,120+c*30,QString::number(i_columna));
            painter.drawText(350,120+c*30,QString::number(i_nivel));
            painter.drawText(420,120+c*30,p_descripcion);
            painter.drawText(810,120+c*30,p_precio);
            painter.drawText(950,120+c*30,p_stock);
            painter.drawLine(10,120+c*35,1000,120+c*35);

            c++;
            tmp++;
            if(tmp%20==0)
            {
                printer.newPage();
                c=1;
                painter.setFont(QFont("Times New Roman", 30));
                painter.drawText(350,30,"Tienda "+n_tienda);
                painter.setFont(QFont("Times New Roman", 15));
                painter.drawText(800,20,"Fecha: "+QDate::currentDate().toString());
                painter.drawText(800,40,"Hora: "+QTime::currentTime().toString());
                painter.setFont(QFont("Times New Roman", 20));
                painter.drawText(360,70,"Lista de Productos");
                painter.setFont(QFont("Times New Roman", 15));
                painter.drawText(10,120,"N");
                painter.drawText(50,120,"Codigo");
                painter.drawText(130,120,"Vitrina");
                painter.drawText(210,120,"Fila");
                painter.drawText(260,120,"Columna");
                painter.drawText(350,120,"Nivel");
                painter.drawText(420,120,"Descripcion");
                painter.drawText(810,120,"Precio de Venta");
                painter.drawText(950,120,"Stock");
                painter.drawLine(10,130,1000,130);
            }
        }
    }

    painter.end();

    QTextEdit parent;
    //parent.show();

    QString filename ="productos_tienda.pdf";
    qDebug()<<"Print file name is "<<filename;
    if(!filename.isEmpty()) {
        if(QFileInfo(filename).suffix().isEmpty()) {
            filename.append(".pdf");
        }

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
        dlg->setWindowTitle(QObject::tr("Print Document"));

        if(dlg->exec() == QDialog::Accepted) {
            parent.print(&printer);
        }
        delete dlg;
    }

}


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

void ui_tienda::on_imprimir_vitrina_clicked()
{
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("productos_vitrina.pdf");
    QPainter painter;
    if (! painter.begin(&printer))
        qWarning("failed to open file, is it writable?");


    QImage logo("fondo.png");
    painter.drawImage(10,10,logo);


    //Sacando el nombre de la Tienda
    QSqlQuery query;
    query.prepare("SELECT alias FROM tienda WHERE idtienda=?");
    query.bindValue(0,idTienda);
    query.exec();
    query.next();
    QString n_tienda=query.value(0).toString();


    //Sacando nombre de la Vitrina

    query.prepare("SELECT alias, codigo FROM vitrina WHERE idvitrina=?");
    query.bindValue(0,idVitrina);
    query.exec();
    query.next();
    QString n_vitrina= query.value(0).toString();
    QString c_vitrina= query.value(1).toString();


    painter.setFont(QFont("Times New Roman", 30));
    painter.drawText(350,30,"Tienda "+n_tienda);
    painter.setFont(QFont("Times New Roman", 15));
    painter.drawText(800,20,"Fecha: "+QDate::currentDate().toString());
    painter.drawText(800,40,"Hora: "+QTime::currentTime().toString());
    painter.setFont(QFont("Times New Roman", 20));
    painter.drawText(160,70,"Lista de Productos de la Vitrina "+c_vitrina+":"+n_vitrina);
    painter.setFont(QFont("Times New Roman", 15));
    painter.drawText(10,120,"N");
    painter.drawText(50,120,"Codigo");
    painter.drawText(130,120,"Fila");
    painter.drawText(190,120,"Columna");
    painter.drawText(280,120,"Nivel");
    painter.drawText(350,120,"Descripcion");
    painter.drawText(810,120,"Precio de Venta");
    painter.drawText(950,120,"Stock");
    painter.drawLine(10,130,1000,130);


    int c=1;
    int tmp=1;

    //Sacando id de los productos
    QSqlQuery query3;
    query3.prepare("SELECT idproducto,fila,columna,nivel FROM item_posicion WHERE idvitrina=?");
    query3.bindValue(0,idVitrina);
    query3.exec();
    while(query3.next())
    {
        QString i_idproducto = query3.value(0).toString();
        int i_fila= query3.value(1).toInt();
        int i_columna= query3.value(2).toInt();
        int i_nivel= query3.value(3).toInt();

        //Sacando lista de productos
        QSqlQuery query2;
        query2.prepare("SELECT codigo, descripcion,stock,precio_venta,accesorios FROM producto WHERE idproducto=?");
        query2.bindValue(0,i_idproducto);
        query2.exec();
        query2.next();

        QString p_codigo = query2.value(0).toString();
        QString p_descripcion= query2.value(1).toString();
        QString p_stock = query2.value(2).toString();
        QString p_precio = query2.value(3).toString();
        QString p_accesorios= query2.value(4).toString();


        painter.drawText(10,120+c*30,QString::number(tmp));
        painter.drawText(50,120+c*30,p_codigo);
        painter.drawText(130,120+c*30,QString::number(i_fila));
        painter.drawText(190,120+c*30,QString::number(i_columna));
        painter.drawText(280,120+c*30,QString::number(i_nivel));
        painter.drawText(350,120+c*30,p_descripcion);
        painter.drawText(810,120+c*30,p_precio);
        painter.drawText(950,120+c*30,p_stock);
        painter.drawLine(10,120+c*35,1000,120+c*35);

        c++;
        tmp++;
        if(tmp%20==0)
        {
            printer.newPage();
            c=1;
            painter.setFont(QFont("Times New Roman", 30));
            painter.drawText(350,30,"Tienda "+n_tienda);
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(800,20,"Fecha: "+QDate::currentDate().toString());
            painter.drawText(800,40,"Hora: "+QTime::currentTime().toString());
            painter.setFont(QFont("Times New Roman", 20));
            painter.drawText(160,70,"Lista de Productos de la Vitrina "+c_vitrina+":"+n_vitrina);
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(10,120,"N");
            painter.drawText(50,120,"Codigo");
            painter.drawText(130,120,"Fila");
            painter.drawText(190,120,"Columna");
            painter.drawText(280,120,"Nivel");
            painter.drawText(350,120,"Descripcion");
            painter.drawText(810,120,"Precio de Venta");
            painter.drawText(950,120,"Stock");
            painter.drawLine(10,130,1000,130);
        }


    }

    painter.end();
    QTextEdit parent;

    QString filename ="productos_tienda.pdf";
    qDebug()<<"Print file name is "<<filename;
    if(!filename.isEmpty()) {
        if(QFileInfo(filename).suffix().isEmpty()) {
            filename.append(".pdf");
        }

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
        dlg->setWindowTitle(QObject::tr("Print Document"));

        if(dlg->exec() == QDialog::Accepted) {
            parent.print(&printer);
        }
        delete dlg;
    }

}

void ui_tienda::on_grilla_cellDoubleClicked(int row, int column)
{
    ui_item_posicion* posicion_agregar = new ui_item_posicion;
    posicion_agregar->set_ui_tienda_actual(this);
    if(idItem.isEmpty())
    {
        posicion_agregar->set_caso(true);
        posicion_agregar->setWindowTitle("Nueva Posicion");
        posicion_agregar->set_posicion(row+1,column+1,actual_nivel);

    }else
    {
        posicion_agregar->set_iditem(get_idItem());
        posicion_agregar->set_caso(false);
        posicion_agregar->actualizar();
        posicion_agregar->setWindowTitle("Editar Posicion");
        posicion_agregar->set_posicion(row+1,column+1,actual_nivel);

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
        ui_tienda * tienda_traspaso=new ui_tienda;
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
    if(caso)
    if(idItem.isEmpty())
    {
        if(caso_traspaso)
        {
            int fila=ui->grilla->currentRow()+1;
            int columna=ui->grilla->currentColumn()+1;
            int nivel=actual_nivel;
            QSqlQuery query1;
            query1.prepare("SELECT idproducto, fila ,columna,nivel FROM item_posicion WHERE iditem_posicion=?");
            query1.bindValue(0,idItem_tras);
            query1.exec();
            query1.next();
            QString idpro=query1.value(0).toString();
            int a_fila=query1.value(1).toInt();
            int a_columna=query1.value(2).toInt();
            int a_nivel=query1.value(3).toInt();
            item_posicion *del = new item_posicion(idItem_tras,"",0,0,0,"");
            del->eliminar();

            QSqlQuery query;
            query.prepare("SELECT codigo, descripcion FROM producto WHERE idproducto=?");
            query.bindValue(0,idpro);
            query.exec();
            query.next();
            QString cpro=query.value(0).toString();
            QString dpro=query.value(1).toString();


            query.prepare("SELECT codigo FROM vitrina WHERE idvitrina=?");
            query.bindValue(0,ui_tienda_traspaso->get_idVitrina());
            query.exec();
            query.next();
            QString c_vitrina=query.value(0).toString();



            query.prepare("SELECT alias FROM tienda WHERE idtienda=?");
            query.bindValue(0,ui_tienda_traspaso->get_idTienda());
            query.exec();
            query.next();
            QString t_alias=query.value(0).toString();




            query.prepare("INSERT INTO item_posicion(idproducto,idvitrina,fila,columna,nivel) VALUES(?,?,?,?,?)");
            query.bindValue(0,idpro);
            query.bindValue(1,get_idVitrina());
            query.bindValue(2,fila);
            query.bindValue(3,columna);
            query.bindValue(4,nivel);
            query.exec();
            close();
            ui_tienda_traspaso->limpiar_grilla();
            ui_tienda_traspaso->set_dimension_grilla();
            ui_tienda_traspaso->actualizar_grilla();

            //Generando Guia de Traspaso
            QPrinter printer;
            printer.setOrientation(QPrinter::Landscape);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("Guia_Traspaso.pdf");
            QPainter painter;
            if (! painter.begin(&printer))
                qWarning("failed to open file, is it writable?");


            painter.setFont(QFont("Times New Roman", 25));
            painter.drawText(100,30,"Guia de Remision de Traspaso");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(550,20,"Fecha: "+QDate::currentDate().toString());
            painter.drawText(550,40,"Hora: "+QTime::currentTime().toString());
            painter.setFont(QFont("Times New Roman", 20));


/*
            painter.drawText(10,90,"Usuario:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,120,"Nombre");
            painter.drawText(210,120,"Apellidos");
            painter.drawLine(10,130,680,130);

  */          //painter.drawText(50,120,Sesion::get_Usuario()->get_nombre());




            painter.setFont(QFont("Times New Roman", 20));
            painter.drawText(10,200,"Posicion Antigua del Producto:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,230,"Codigo");
            painter.drawText(130,230,"Tienda");
            painter.drawText(280,230,"Vitrina");
            painter.drawText(350,230,"Fila");
            painter.drawText(390,230,"Columna");
            painter.drawText(480,230,"Nivel");
            painter.drawText(540,230,"Descripcion");

            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,250,cpro);
            painter.drawText(130,250,t_alias);
            painter.drawText(280,250,c_vitrina);
            painter.drawText(350,250,QString::number(a_fila));
            painter.drawText(390,250,QString::number(a_columna));
            painter.drawText(480,250,QString::number(a_nivel));
            painter.drawText(540,250,dpro);



            painter.setFont(QFont("Times New Roman", 20));
            painter.drawText(10,310,"Posicion Nueva del Producto:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,340,"Codigo");
            painter.drawText(130,340,"Tienda");
            painter.drawText(280,340,"Vitrina");
            painter.drawText(350,340,"Fila");
            painter.drawText(390,340,"Columna");
            painter.drawText(480,340,"Nivel");
            painter.drawText(540,340,"Descripcion");
            painter.drawLine(10,350,680,350);




            query.prepare("SELECT codigo FROM vitrina WHERE idvitrina=?");
            query.bindValue(0,get_idVitrina());
            query.exec();
            query.next();
            QString cn_vitrina=query.value(0).toString();



            query.prepare("SELECT alias FROM tienda WHERE idtienda=?");
            query.bindValue(0,get_idTienda());
            query.exec();
            query.next();
            QString tn_alias=query.value(0).toString();

            painter.drawText(50,360,cpro);
            painter.drawText(130,360,tn_alias);
            painter.drawText(280,360,cn_vitrina);
            painter.drawText(350,360,QString::number(fila));
            painter.drawText(390,360,QString::number(columna));
            painter.drawText(480,360,QString::number(nivel));
            painter.drawText(540,360,dpro);

            painter.end();


            QTextEdit parent;

            QString filename ="Guia_Traspaso.pdf";
            qDebug()<<"Print file name is "<<filename;
            if(!filename.isEmpty()) {
                if(QFileInfo(filename).suffix().isEmpty()) {
                    filename.append(".pdf");
                }

                QPrinter printer(QPrinter::HighResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(filename);
                QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
                dlg->setWindowTitle(QObject::tr("Print Document"));

                if(dlg->exec() == QDialog::Accepted) {
                    parent.print(&printer);
                }
                delete dlg;
            }
        }
        else
        {
            int fila=ui->grilla->currentRow()+1;
            int columna=ui->grilla->currentColumn()+1;
            int nivel=actual_nivel;

            QSqlQuery query;
            query.prepare("INSERT INTO item_posicion(idproducto,idvitrina,fila,columna,nivel) VALUES(?,?,?,?,?)");
            query.bindValue(0,idProducto_tras);
            query.bindValue(1,get_idVitrina());
            query.bindValue(2,fila);
            query.bindValue(3,columna);
            query.bindValue(4,nivel);
            query.exec();


            query.prepare("DELETE FROM producto_contenedor WHERE producto_idproducto=?");
            query.bindValue(0,idProducto_tras);
            query.exec();

            query.prepare("INSERT INTO historial_almacen(entidad_1,id_1,entidad_2,id_2,operacion,fecha) VALUES('Producto',?,'Contenedor',?,'quitar',now())");
            query.bindValue(0,idProducto_tras);
            query.bindValue(1,ui_almacen_traspaso->get_currentIdContenedor());
            query.exec();

            close();
            ui_tienda_traspaso->limpiar_grilla();
            ui_tienda_traspaso->set_dimension_grilla();
            ui_tienda_traspaso->actualizar_grilla();


            query.prepare("SELECT codigo, descripcion FROM producto WHERE idproducto=?");
            query.bindValue(0,idProducto_tras);
            query.exec();
            query.next();
            QString cpro=query.value(0).toString();
            QString dpro=query.value(1).toString();


            query.prepare("SELECT codigo FROM vitrina WHERE idvitrina=?");
            query.bindValue(0,ui_tienda_traspaso->get_idVitrina());
            query.exec();
            query.next();
            QString c_vitrina=query.value(0).toString();



            query.prepare("SELECT alias FROM tienda WHERE idtienda=?");
            query.bindValue(0,ui_tienda_traspaso->get_idTienda());
            query.exec();
            query.next();
            QString t_alias=query.value(0).toString();


            query.prepare("SELECT nombre FROM almacen WHERE idalmacen=?");
            query.bindValue(0,ui_almacen_traspaso->get_currentIdAlmacen());
            query.exec();
            query.next();
            QString al_nombre=query.value(0).toString();

            query.prepare("SELECT nombre FROM andamio WHERE idandamio=?");
            query.bindValue(0,ui_almacen_traspaso->get_currentIdAndamio());
            query.exec();
            query.next();
            QString an_nombre=query.value(0).toString();

            query.prepare("SELECT nombre FROM contenedor WHERE idcontenedor=?");
            query.bindValue(0,ui_almacen_traspaso->get_currentIdContenedor());
            query.exec();
            query.next();
            QString c_nombre=query.value(0).toString();


            QPrinter printer;
            printer.setOrientation(QPrinter::Landscape);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("Guia_Traspaso.pdf");
            QPainter painter;
            if (! painter.begin(&printer))
                qWarning("failed to open file, is it writable?");


            painter.setFont(QFont("Times New Roman", 25));
            painter.drawText(100,30,"Guia de Remision de Traspaso");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(550,20,"Fecha: "+QDate::currentDate().toString());
            painter.drawText(550,40,"Hora: "+QTime::currentTime().toString());
            painter.setFont(QFont("Times New Roman", 20));


/*
            painter.drawText(10,90,"Usuario:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,120,"Nombre");
            painter.drawText(210,120,"Apellidos");
            painter.drawLine(10,130,680,130);

            //painter.drawText(50,120,Sesion::get_Usuario()->get_nombre());

*/


            painter.setFont(QFont("Times New Roman", 20));
            painter.drawText(10,200,"Posicion Antigua del Producto:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,230,"Codigo");
            painter.drawText(130,230,"Tienda");
            painter.drawText(250,230,"Almacen");
            painter.drawText(340,230,"Andamio");
            painter.drawText(430,230,"Contenedor");
            painter.drawText(540,230,"Fila");
            painter.drawText(590,230,"Columna");
            painter.drawText(690,230,"Descripcion");
            painter.drawLine(10,240,770,350);


            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,250,cpro);
            painter.drawText(130,250,t_alias);
            painter.drawText(250,250,al_nombre);
            painter.drawText(340,250,an_nombre);
            painter.drawText(430,250,c_nombre);
            painter.drawText(540,250,QString::number(fila));
            painter.drawText(590,250,QString::number(columna));
            painter.drawText(690,250,dpro);



            painter.setFont(QFont("Times New Roman", 20));
            painter.drawText(10,310,"Posicion Nueva del Producto:");
            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,340,"Codigo");
            painter.drawText(130,340,"Tienda");
            painter.drawText(280,340,"Vitrina");
            painter.drawText(350,340,"Fila");
            painter.drawText(390,340,"Columna");
            painter.drawText(480,340,"Nivel");
            painter.drawText(540,340,"Descripcion");
            painter.drawLine(10,350,770,350);

            painter.setFont(QFont("Times New Roman", 15));
            painter.drawText(50,360,cpro);
            painter.drawText(130,360,t_alias);
            painter.drawText(280,360,c_vitrina);
            painter.drawText(350,360,QString::number(fila));
            painter.drawText(390,360,QString::number(columna));
            painter.drawText(480,360,QString::number(nivel));
            painter.drawText(540,360,dpro);



            painter.end();

            QTextEdit parent;
            QString filename ="Guia_Traspaso.pdf";
            qDebug()<<"Print file name is "<<filename;
            if(!filename.isEmpty()) {
                if(QFileInfo(filename).suffix().isEmpty()) {
                    filename.append(".pdf");
                }

                QPrinter printer(QPrinter::HighResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(filename);
                QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
                dlg->setWindowTitle(QObject::tr("Print Document"));

                if(dlg->exec() == QDialog::Accepted) {
                    parent.print(&printer);
                }
                delete dlg;
            }

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
        ui_traspaso_almacen* traspaso_almacen=new ui_traspaso_almacen;
        traspaso_almacen->set_ui_tienda_traspaso(this);
        traspaso_almacen->set_idItem_tras(get_idItem());
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
