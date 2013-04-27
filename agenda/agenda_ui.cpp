#include "agenda_ui.h"
#include "ui_agenda_ui.h"
#include "newtask_agenda_ui.h"
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

    const QDate FECHA = QDate::currentDate();
    actualizar_combo_tienda();




}


agenda_ui::~agenda_ui()
{
    delete ui;
}

void agenda_ui::on_pushButton_newTask_clicked()
{

    newTask_agenda_ui *NEW_TASK_FORM = new newTask_agenda_ui;
    NEW_TASK_FORM->set_cliked_type(2);
    //NEW_TASK_FORM->dni_task = ui->comboBox_dni->currentText();
    //NEW_TASK_FORM->setDate(ui->dateEdit_Agenda->date());
    NEW_TASK_FORM->parent_ui_form = this;
    NEW_TASK_FORM->enableDate(false);
    NEW_TASK_FORM->setTitle("Nueva Tarea");
    NEW_TASK_FORM->show();
}

void agenda_ui::on_pushButton_showTask_clicked()
{

}

void agenda_ui::on_pushButton_editTask_clicked()
{

}

void agenda_ui::on_pushButton_deleteTask_clicked()
{

}

void agenda_ui::on_pushButton_showAll_clicked()
{

}

void agenda_ui::show_personal_combox()
{


}

void agenda_ui::on_comboBox_Names_currentIndexChanged(int index)
{

}

void agenda_ui::on_dateEdit_Agenda_dateChanged(const QDate &date)
{


}

void agenda_ui::on_tablaView_Agend_itemClicked(QTableWidgetItem *item)
{

}



void agenda_ui::on_dateEdit_Alerta_dateChanged(const QDate &date)
{

}

void agenda_ui::on_comboBox_dni_currentIndexChanged(const QString &arg1)
{

}

void agenda_ui::on_pushButton_showSelect_clicked()
{

}

void agenda_ui::set_access_level(int access)
{


}

void agenda_ui::on_pushButton_show_SelectAlert_clicked()
{

}

void agenda_ui::update_table_agenda_form()
{


}

void agenda_ui::on_pushButton_Alerta_General_show_clicked()
{
    newalerta_alerta_ui *SHOW_ALERTA_FORM = new newalerta_alerta_ui;
    SHOW_ALERTA_FORM->update_new_alerta_form(this->code_var_alerta_general);
    SHOW_ALERTA_FORM->set_clicked_type(0);
    SHOW_ALERTA_FORM->show();

}


void agenda_ui::on_tableWidget_Alert_itemClicked(QTableWidgetItem *item)
{

}

void agenda_ui::on_pushButton_AlertaGeneral_changeColor_clicked()
{

    //setColorRow(ui->tableWidget_Alert,FILA,COLOR_VALUE);




}

void agenda_ui::on_pushButton_Alert_Personales_add_clicked()
{
    newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;
    NEW_ALERTA_FORM->set_clicked_type(2);
    NEW_ALERTA_FORM->alert_type_var = this->curren_user_code_var;
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


void agenda_ui::on_pushButton_Alert_Personal_changeColor_clicked()
{

}



void agenda_ui::on_tableWidget_Alert_Personales_itemClicked(QTableWidgetItem *item)
{

}

void agenda_ui::on_pushButton_Alert_Personal_show_clicked()
{


}

void agenda_ui::on_pushButton_Alert_Personales_edit_clicked()
{

}

void agenda_ui::on_pushButton_Alert_Personales_remove_clicked()
{


}

void agenda_ui::on_pushButton_show_Agenda_clicked()
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

    on_dateEdit_Agenda_dateChanged(QDate::currentDate());
}

void agenda_ui::on_comboBox_dni_currentIndexChanged(int index)
{

}

void agenda_ui::on_calendarWidget_clicked(const QDate &date)
{
    //ui->dateEdit_Agenda->setDate(date);
}



void agenda_ui::on_tablaView_Agend_doubleClicked(const QModelIndex &index)
{
    int FILA = index.row();
    QString CODIGO;
    //CODIGO = ui->tablaView_Agend->item(FILA,5)->text();
    //ui->lineEdit_codigo->clear();
    //ui->lineEdit_codigo->insert(CODIGO);

    newTask_agenda_ui *EDIT_TASK_FORM = new newTask_agenda_ui;
    EDIT_TASK_FORM->set_cliked_type(1);
    //EDIT_TASK_FORM->code_task = ui->lineEdit_codigo->text();
    //EDIT_TASK_FORM->show_data_task_form(ui->lineEdit_codigo->text());
    EDIT_TASK_FORM->parent_ui_form = this;
    EDIT_TASK_FORM->enableDate(true);
    EDIT_TASK_FORM->setTitle("Editar Tarea");
    EDIT_TASK_FORM->show();
}

void agenda_ui::on_pushButton_printList_clicked()
{

}



void agenda_ui::on_pushButton_Alert_General_add_clicked()
{
    newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;
    NEW_ALERTA_FORM->set_clicked_type(2); //Configurando Comportamiento
    NEW_ALERTA_FORM->set_type_alerta(0); //Configurando Tipo de alerta 0 Alerta General 1 alerta Personal
    Sesion* s=Sesion::getSesion();
    NEW_ALERTA_FORM->alert_type_var = s->getIdColaborador();
    connect(NEW_ALERTA_FORM,SIGNAL(updateChange()),this,SLOT(updateTable_Alert_General()));
    NEW_ALERTA_FORM->show();
}
void agenda_ui::updateTable_Alert_General()
{
    ui->tableView_Alert_General->setModel(alerta::mostrar(0));
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
