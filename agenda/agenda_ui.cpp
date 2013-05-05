#include "agenda_ui.h"
#include "ui_agenda_ui.h"

#include <QSqlQuery>
#include <QDebug>
#include <QColorDialog>
#include <QMessageBox>
#include <configuracion/sesion.h>
#include <configuracion/usuario.h>
#include <agenda/alerta.h>
#include <vitrina/tienda.h>
agenda_ui::agenda_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::agenda_ui)
{
    ui->setupUi(this);
    fecha = QDate::currentDate();
    ui->calendarWidget->setSelectedDate(fecha);
    actualizar_combo_tienda();
    actualizar_tiempo(fecha);
    ui->tableView_Alert_General->setColumnWidth(1,357);
    ui->tableView_Alert_Personal->setColumnWidth(1,357);


}


agenda_ui::~agenda_ui()
{
    delete ui;
}


void agenda_ui::on_pushButton_AlertaGeneral_changeColor_clicked()
{
    //setColorRow(ui->tableWidget_Alert,FILA,COLOR_VALUE);
}

void agenda_ui::on_pushButton_Alert_Personales_add_clicked()
{
    newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;
    NEW_ALERTA_FORM->set_type_alert(1);
    //NEW_ALERTA_FORM->parent_ui_form_agenda = this;
    NEW_ALERTA_FORM->show();
}

void agenda_ui::on_dateEdit_Alerta_Personales_dateChanged(const QDate &date)
{
    update_table_alerta_personal();
}

void agenda_ui::update_table_alerta_personal()
{

}

void agenda_ui::on_pushButton_show_SelectAlert_Personales_4_clicked()
{
    update_table_alerta_personal();
}

void agenda_ui::on_pushButton_Alert_Personales_edit_clicked()
{

}

void agenda_ui::on_pushButton_Alert_Personales_remove_clicked()
{
}


void agenda_ui::on_pushButton_agenda_changeColor_clicked()
{
    /*if(!ui->tablaView_Agend->currentItem())
        return;
    QString AGENDA_CODE;
    QSqlQuery query;
    //AGENDA_CODE = ui->lineEdit_codigo->text();
    QColor dfault = ui->tablaView_Agend->currentItem()->backgroundColor();
    QColorDialog *palette = new QColorDialog();
    palette->setCurrentColor(dfault);
    palette->exec();
    QColor color(palette->currentColor());
    QString COLOR_VALUE = color.name();
    int FILA = ui->tablaView_Agend->currentItem()->row();
    setColorRow(ui->tablaView_Agend,FILA,COLOR_VALUE);
    query.prepare("UPDATE e_agenda SET color=? WHERE agenda_pk="+AGENDA_CODE);
    query.bindValue(0,COLOR_VALUE);
    query.exec();*/
}

void agenda_ui::on_pushButton_update_Agenda_clicked()
{

    //on_dateEdit_Agenda_dateChanged(QDate::currentDate());
}


void agenda_ui::on_calendarWidget_clicked(const QDate &date)
{
    actualizar_tiempo(date);
}



void agenda_ui::on_tablaView_Agend_doubleClicked(const QModelIndex &index)
{
    int FILA = index.row();
    QString CODIGO;
    //CODIGO = ui->tablaView_Agend->item(FILA,5)->text();
    //ui->lineEdit_codigo->clear();
    //ui->lineEdit_codigo->insert(CODIGO);

}
void agenda_ui::on_pushButton_Alert_General_add_clicked()
{
    newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;    
    NEW_ALERTA_FORM->set_type_alert(0); //Configurando Tipo de alerta 0 Alerta General 1 alerta Personal
    NEW_ALERTA_FORM->set_comportaminto(0);
    connect(NEW_ALERTA_FORM,SIGNAL(updateChange()),this,SLOT(updateTable_Alert_General()));
    NEW_ALERTA_FORM->show();
}
void agenda_ui::updateTable_Alert_General()
{
    ui->tableView_Alert_General->setModel(alerta::mostrar(0,fecha));
}

void agenda_ui::updateTable_Alert_Personal()
{
    ui->tableView_Alert_Personal->setModel(alerta::mostrar(1,fecha));
}

void agenda_ui::actualizar_combo_tienda()
{
    ui->comboBox_tienda->clear();

    QSqlQuery query;
    query.prepare("SELECT idTienda,nombre FROM Tienda");
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

void agenda_ui::on_pushButton_Alert_General_edit_clicked()
{
    int fila=ui->tableView_Alert_General->currentIndex().row();
    if(fila!=-1)
    {
        alerta actual_alerta;
        actual_alerta.sethora(ui->tableView_Alert_General->model()->data(ui->tableView_Alert_General->model()->index(fila,0)).toString());
        actual_alerta.setdescripcion(ui->tableView_Alert_General->model()->data(ui->tableView_Alert_General->model()->index(fila,1)).toString());
        actual_alerta.setfecha(fecha.toString(Qt::ISODate));
        actual_alerta.completar();

        newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;
        NEW_ALERTA_FORM->set_type_alert(0); //Configurando Tipo de alerta 0 Alerta General 1 alerta Personal
        NEW_ALERTA_FORM->set_alerta(actual_alerta);
        NEW_ALERTA_FORM->set_comportaminto(1);//Comportamiento 1 edita 0 Nuevo

        connect(NEW_ALERTA_FORM,SIGNAL(updateChange()),this,SLOT(updateTable_Alert_General()));
        NEW_ALERTA_FORM->show();
    }

}
void agenda_ui::actualizar_tiempo(const QDate &date)
{
    fecha = date;
    updateTable_Alert_General();
    updateTable_Alert_Personal();
}

void agenda_ui::on_tableView_Alert_General_doubleClicked(const QModelIndex &index)
{
    int fila = index.row();
    QString hora = ui->tableView_Alert_General->model()->data(ui->tableView_Alert_General->model()->index(fila,0)).toString();
    QString detalles = ui->tableView_Alert_General->model()->data(ui->tableView_Alert_General->model()->index(fila,1)).toString();
    QString str_warning = hora +"  "+ detalles;
    QMessageBox *msgBox=new QMessageBox;
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowTitle("Detalles");
    msgBox->setWindowIcon(QIcon(":/new/add1-.png"));

    msgBox->setText(str_warning);
    msgBox->setStandardButtons(QMessageBox::Save);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Aceptar");
    msgBox->exec();
}
