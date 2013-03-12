#include "ui_almacen.h"
#include "ui_ui_almacen.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "ui_almacen_datos.h"
#include "ui_andamio_datos.h"
#include "ui_contenedor_datos.h"

#include "almacen.h"
#include "andamio.h"
#include "contenedor.h"

#include "ncreport.h"
#include "ncreportoutput.h"
#include "ncreportpreviewoutput.h"
#include "ncreportpreviewwindow.h"
#include <QFileDialog>

ui_almacen::ui_almacen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_almacen)
{
    ui->setupUi(this);

    update_comboBox_Empresa();
}

ui_almacen::~ui_almacen()
{
    delete ui;
}

QString ui_almacen::get_currentIdEmpresa(){return currentIdEmpresa;}
QString ui_almacen::get_currentIdTienda(){return currentIdTienda;}
QString ui_almacen::get_currentIdAlmacen(){return currentIdAlmacen;}
QString ui_almacen::get_currentIdAndamio(){return currentIdAndamio;}
QString ui_almacen::get_currentIdContenedor(){return currentIdContenedor;}

void ui_almacen::set_currentIdEmpresa(QString e){currentIdEmpresa = e;}
void ui_almacen::set_currentIdTienda(QString t){currentIdTienda = t;}
void ui_almacen::set_currentIdAlmacen(QString al){currentIdAlmacen = al;}
void ui_almacen::set_currentIdAndamio(QString an){currentIdAndamio = an;}
void ui_almacen::set_currentIdContenedor(QString c){currentIdContenedor = c;}

void ui_almacen::update_comboBox_Empresa()
{
    ui->comboBox_Empresa->clear();

    QSqlQuery query;
    query.prepare("SELECT idempresa,raz_social FROM empresa");
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idempresa = query.value(0).toString();
        QString raz_social = query.value(1).toString();

        Empresas[raz_social] = idempresa;
        ui->comboBox_Empresa->insertItem(c,raz_social);

        c++;
    }
}

void ui_almacen::update_comboBox_Tienda(QString idEmpresa)
{
    ui->comboBox_Tienda->clear();

    QSqlQuery query;
    query.prepare("SELECT idtienda,alias FROM tienda WHERE idempresa=?");
    query.bindValue(0,idEmpresa);
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idtienda = query.value(0).toString();
        QString alias = query.value(1).toString();

        Tiendas[alias] = idtienda;

        ui->comboBox_Tienda->insertItem(c,alias);

        c++;
    }
}

void ui_almacen::update_comboBox_Almacen(QString idTienda)
{
    qDebug()<<"Tienda: "<<idTienda;
    ui->comboBox_Almacen->clear();

    QSqlQuery query;
    query.prepare("SELECT idalmacen,nombre FROM almacen WHERE idtienda=?");
    query.bindValue(0,idTienda);
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idalmacen = query.value(0).toString();
        QString nombre = query.value(1).toString();
        qDebug()<<idalmacen<<" - "<<nombre;
        Almacenes[nombre] = idalmacen;

        ui->comboBox_Almacen->insertItem(c,nombre);
        c++;
    }

}
void ui_almacen::update_comboBox_Andamio(QString idAlmacen)
{
    ui->comboBox_Andamio->clear();

    QSqlQuery query;
    query.prepare("SELECT idandamio,nombre FROM andamio WHERE idalmacen=?");
    query.bindValue(0,idAlmacen);
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idandamio = query.value(0).toString();
        QString nombre = query.value(1).toString();

        Andamios[nombre] = idandamio;

        ui->comboBox_Andamio->insertItem(c,nombre);

        c++;
    }
}

void ui_almacen::clear_widget_Contenedores()
{
    for(int i=ui->tableWidget_griContenedores->rowCount()-1; i>=0;--i)
        ui->tableWidget_griContenedores->removeRow(i);
    for(int i=ui->tableWidget_griContenedores->columnCount()-1;i>=0;--i)
        ui->tableWidget_griContenedores->removeColumn(i);
}

void ui_almacen::set_dimension_widget_Contenedores()
{
    clear_widget_Contenedores();

    QSqlQuery query;
    query.prepare("SELECT fila,columna FROM andamio WHERE idandamio=?");
    query.bindValue(0,currentIdAndamio);
    query.exec();

    query.next();

    int fila = query.value(0).toInt();
    int columna = query.value(1).toInt();

    for(int i = 0;i<columna;i++)
        ui->tableWidget_griContenedores->insertColumn(i);
    for(int i = 0;i<fila;i++)
        ui->tableWidget_griContenedores->insertRow(i);

}

void ui_almacen::update_widget_Contenedores()
{
    Contenedor.clear();
    QSqlQuery query;
    query.prepare("SELECT nombre,descripcion,pos_fila,pos_columna,idcontenedor FROM contenedor WHERE idandamio=?");
    query.bindValue(0,currentIdAndamio);
    query.exec();

    while(query.next())
    {
        QString nombre = query.value(0).toString();
        QString descripcion = query.value(1).toString();
        int pos_fila = query.value(2).toInt();
        int pos_columna = query.value(3).toInt();
        QString idcontenedor = query.value(4).toString();

        QString key = QString::number(pos_fila)+"-"+QString::number(pos_columna);
        Contenedor[key] = idcontenedor;

        ui->tableWidget_griContenedores->setItem(pos_fila-1,pos_columna-1,new QTableWidgetItem(nombre));
    }
}

void ui_almacen::on_comboBox_Empresa_currentIndexChanged(const QString &arg1)
{
    set_currentIdEmpresa(Empresas[arg1]);
    update_comboBox_Tienda(get_currentIdEmpresa());
}

void ui_almacen::on_comboBox_Tienda_currentIndexChanged(const QString &arg1)
{
    set_currentIdTienda(Tiendas[arg1]);
    update_comboBox_Almacen(get_currentIdTienda());
}

void ui_almacen::on_comboBox_Almacen_currentIndexChanged(const QString &arg1)
{
    set_currentIdAlmacen(Almacenes[arg1]);
    update_comboBox_Andamio(get_currentIdAlmacen());
}

void ui_almacen::on_comboBox_Andamio_currentIndexChanged(const QString &arg1)
{
    set_currentIdAndamio(Andamios[arg1]);

    set_dimension_widget_Contenedores();
    update_widget_Contenedores();

}

void ui_almacen::on_pushButton_addAlmacen_clicked()
{
    if(get_currentIdTienda().compare("")==0)
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
        ui_almacen_datos *new_almacen_form =  new ui_almacen_datos;
        new_almacen_form->set_idTienda(get_currentIdTienda());
        new_almacen_form->set_ui_almacen_parent(this);
        new_almacen_form->set_behavior(0);
        new_almacen_form->setWindowTitle("Nuevo Almacen");
        new_almacen_form->show();
    }
}

void ui_almacen::on_pushButton_editAlmacen_clicked()
{
    if(get_currentIdAlmacen().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Almacen válido!");
        msgBox->exec();
    }
    else
    {
        ui_almacen_datos *edit_almacen_form = new ui_almacen_datos;
        edit_almacen_form->set_idTienda(get_currentIdTienda());
        edit_almacen_form->set_ui_almacen_parent(this);
        edit_almacen_form->set_behavior(1);
        edit_almacen_form->update_form();
        edit_almacen_form->setWindowTitle("Editar Almacen");
        edit_almacen_form->show();
    }
}

void ui_almacen::on_pushButton_deleteAlmacen_clicked()
{
    if(get_currentIdAlmacen().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse un Almacen válido!");
        msgBox->exec();
    }
    else
    {
        almacen *any_almacen = new almacen(get_currentIdAlmacen(),"","","");

        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmar");
        msgBox->setText("Desea eliminar el almacen?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        switch(ret)
        {
            case QMessageBox::Ok:

                any_almacen->eliminar();
                update_comboBox_Almacen(currentIdTienda);
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

void ui_almacen::on_pushButton_addAndamio_clicked()
{
    if(get_currentIdAlmacen().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse un Almacen válido!");
        msgBox->exec();
    }
    else
    {
        ui_andamio_datos* new_andamio_form = new ui_andamio_datos;
        new_andamio_form->set_idAlmacen(get_currentIdAlmacen());
        new_andamio_form->set_ui_almacen_parent(this);
        new_andamio_form->set_behavior(0);
        new_andamio_form->setWindowTitle("Nuevo Andamio");
        new_andamio_form->show();
    }
}


void ui_almacen::on_pushButton_editAndamio_clicked()
{
    if(get_currentIdAndamio().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse un Andamio válido!");
        msgBox->exec();
    }
    else
    {
        ui_andamio_datos* edit_andamio_form = new ui_andamio_datos;
        edit_andamio_form->set_idAlmacen(get_currentIdAlmacen());
        edit_andamio_form->set_ui_almacen_parent(this);
        edit_andamio_form->set_behavior(1);
        edit_andamio_form->update_form();
        edit_andamio_form->setWindowTitle("Editar Andamio");
        edit_andamio_form->show();
    }
}

void ui_almacen::on_pushButton_deleteAndamio_clicked()
{
    if(get_currentIdAndamio().compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse un Andamio válido!");
        msgBox->exec();
    }
    else
    {
        andamio *any_andamio = new andamio(get_currentIdAndamio(),"","","","","");

        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Confirmar");
        msgBox->setText("Desea eliminar el andamio?");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setButtonText(QMessageBox::Cancel,"Cancelar");

        int ret = msgBox->exec();

        switch(ret)
        {
            case QMessageBox::Ok:
                any_andamio->eliminar();
                update_comboBox_Andamio(currentIdAndamio);
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

void ui_almacen::on_tableWidget_griContenedores_cellDoubleClicked(int row, int column)
{
    /*QString fila = QString::number(ui->tableWidget_griContenedores->currentRow()+1);
    QString columna = QString::number(ui->tableWidget_griContenedores->currentColumn()+1);*/
    QString fila = QString::number(row+1);
    QString columna = QString::number(column+1);
    QString pos = fila+"-"+columna;
    set_currentIdContenedor(Contenedor[pos]);

    ui_contenedor_datos* contenedor_form = new ui_contenedor_datos;
    contenedor_form->set_ui_almacen_parent(this);

    if(currentIdContenedor.isEmpty())
    {
        contenedor_form->set_behavior(0);
        contenedor_form->setWindowTitle("Nuevo Contenedor");
        contenedor_form->set_spinBox_fila(row+1);
        contenedor_form->set_spinBox_columna(column+1);

    }
    else
    {
        contenedor_form->set_idContenedor(currentIdContenedor);
        contenedor_form->set_behavior(1);
        contenedor_form->update_form();
        contenedor_form->setWindowTitle("Editar Contenedor");
    }

    contenedor_form->show();
}

void ui_almacen::on_tableWidget_griContenedores_itemSelectionChanged()
{

}

void ui_almacen::on_botonGenerarReporte_clicked()
{
    NCReport *report = new NCReport();
    report->setReportFile( "ReporteContenedores.ncr" );
    //report->runReportToPDF( "reporteContenedoresProductos.pdf" );

    NCReportOutput *output=0;

    output = new NCReportPreviewOutput();
    output->setAutoDelete( FALSE );
    report->setOutput( output );


    /*QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF File"),
    "report.pdf", tr("Pdf files (*.pdf)"));
    if ( fileName.isEmpty() )
        delete report;*/


    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    report->runReport();
    //report->runReportToPreview();
    bool error = report->hasError();
    QString err = report->lastErrorMsg();
    QApplication::restoreOverrideCursor();

    if ( error )
        QMessageBox::information( 0, "Riport error", err );
    else
    {
            //-----------------------------
            // PRINT PREVIEW
            //-----------------------------
            NCReportPreviewWindow *pv = new NCReportPreviewWindow();
            pv->setReport( report );
            pv->setOutput( (NCReportPreviewOutput*)output );
            pv->setWindowModality(Qt::ApplicationModal );
            pv->setAttribute( Qt::WA_DeleteOnClose );
            pv->show();
    }

}
