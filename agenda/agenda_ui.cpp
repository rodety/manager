#include "agenda_ui.h"
#include "ui_agenda_ui.h"
#include "newtask_agenda_ui.h"
#include <QSqlQuery>
#include <QDebug>
#include <QColorDialog>
#include <QMessageBox>


agenda_ui::agenda_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::agenda_ui)
{
    ui->setupUi(this);
    show_personal_combox();
    const QDate FECHA = QDate::currentDate();
    //ui->dateEdit_Alerta_Personales->setDate(FECHA);
    //update_table_alerta_personal();
    //ui->dateEdit_Alerta->setDate(FECHA);
    //ui->dateEdit_Agenda->setDate(FECHA);
    //----------- ocultando objetos ----
    //ui->comboBox_dni->hide();
    //ui->lineEdit_codigo->hide();
    ui->dateEdit_Agenda->setEnabled(false);

    ui->tableWidget_Alert->setColumnWidth(0,80);
    ui->tableWidget_Alert->setColumnWidth(1,290);
    ui->tableWidget_Alert->setColumnWidth(2,80);
    ui->tableWidget_Alert_Personales->setColumnWidth(0,80);
    ui->tableWidget_Alert_Personales->setColumnWidth(1,290);
    ui->tableWidget_Alert_Personales->setColumnWidth(2,80);

    ui->tablaView_Agend->setColumnWidth(0,80);
    ui->tablaView_Agend->setColumnWidth(1,80);
    ui->tablaView_Agend->setColumnWidth(2,207);
    ui->tablaView_Agend->setColumnWidth(3,207);
    ui->tablaView_Agend->setColumnWidth(4,80);
    ui->tablaView_Agend->setColumnWidth(5,50);
    ui->tablaView_Agend->setColumnWidth(6,180);
    ui->pushButton_show_Agenda->hide();

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
    NEW_TASK_FORM->setDate(ui->dateEdit_Agenda->date());
    NEW_TASK_FORM->parent_ui_form = this;
    NEW_TASK_FORM->enableDate(false);
    NEW_TASK_FORM->setTitle("Nueva Tarea");
    NEW_TASK_FORM->show();
}

void agenda_ui::on_pushButton_showTask_clicked()
{
    newTask_agenda_ui *SHOW_TASK_FORM = new newTask_agenda_ui;
    SHOW_TASK_FORM->set_cliked_type(0);
    //SHOW_TASK_FORM->show_data_task_form(ui->lineEdit_codigo->text());
    //SHOW_TASK_FORM->dni_task = ui->comboBox_dni->currentText(); // dni perteneciente al dueño de la agenda;
    //SHOW_TASK_FORM->code_task = ui->lineEdit_codigo->text();
    SHOW_TASK_FORM->enableDate(false);
    SHOW_TASK_FORM->hideButton();
    SHOW_TASK_FORM->setTitle("Ver Tarea");
    SHOW_TASK_FORM->show();
}

void agenda_ui::on_pushButton_editTask_clicked()
{
    newTask_agenda_ui *EDIT_TASK_FORM = new newTask_agenda_ui;
    EDIT_TASK_FORM->set_cliked_type(1);
    //EDIT_TASK_FORM->code_task = ui->lineEdit_codigo->text();
    //EDIT_TASK_FORM->show_data_task_form(ui->lineEdit_codigo->text());
    EDIT_TASK_FORM->parent_ui_form = this;
    EDIT_TASK_FORM->enableDate(true);
    EDIT_TASK_FORM->setTitle("Editar Tarea");
    EDIT_TASK_FORM->show();
}

void agenda_ui::on_pushButton_deleteTask_clicked()
{
    //########"############################## DELETE THE DATABASE

    QString CODIGO_TAREA;

    //CODIGO_TAREA = ui->lineEdit_codigo->text();

    QSqlQuery query;

    int ret;
    QMessageBox *msgBox = new QMessageBox;

    QString str_warning = "¿Esta seguro que desea eliminar esa alerta?.";
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowTitle("Confirmar Eliminar");
    msgBox->setWindowIcon(QIcon(":/new/file_delete.png"));

    msgBox->setText(str_warning);
    msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Elimniar");
    msgBox->setButtonText(QMessageBox::Discard, "No, gracias");
    ret = msgBox->exec();

    switch(ret)
    {
    case QMessageBox::Save:
        query.prepare("DELETE FROM e_agenda WHERE agenda_pk="+CODIGO_TAREA);
        query.exec();
        query.next();

        this->on_pushButton_showSelect_clicked();
        break;
    case QMessageBox::Discard:
        break;
    default:
        break;
    }

}

void agenda_ui::on_pushButton_showAll_clicked()
{
    QString FECHA,HORA,NOMBRE,DESCRIPCION,FICHA,CODIGO,COLOR,TELEFONO,TODAY;
    int COUNT;
    TODAY =  ui->dateEdit_Agenda->text();

    for (int i=ui->tablaView_Agend->rowCount()-1; i >= 0; --i)
        ui->tablaView_Agend->removeRow(i);

    ui->tablaView_Agend->setSortingEnabled(0);
    COUNT = 0;

    QSqlQuery query;
    query.prepare("SELECT * FROM e_agenda where fecha ='"+TODAY+"'");

    query.exec();

    while(query.next())
    {
        CODIGO = query.value(0).toString();
        NOMBRE = query.value(2).toString();
        FECHA = query.value(3).toString();
        HORA = query.value(4).toString();
        DESCRIPCION = query.value(5).toString();
        FICHA = query.value(6).toString();
        COLOR = query.value(7).toString();
        TELEFONO = query.value(8).toString();

        ui->tablaView_Agend->insertRow(COUNT);
        ui->tablaView_Agend->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tablaView_Agend->setItem(COUNT,1,new QTableWidgetItem(HORA                                                                  ));
        ui->tablaView_Agend->setItem(COUNT,2,new QTableWidgetItem(NOMBRE));
        ui->tablaView_Agend->setItem(COUNT,3,new QTableWidgetItem(DESCRIPCION));
        ui->tablaView_Agend->setItem(COUNT,4,new QTableWidgetItem(FICHA));
        ui->tablaView_Agend->setItem(COUNT,5,new QTableWidgetItem(CODIGO));
        ui->tablaView_Agend->setItem(COUNT,6,new QTableWidgetItem(TELEFONO));
        setColorRow(ui->tablaView_Agend,COUNT,COLOR);


        COUNT++;
    }

    ui->tablaView_Agend->setSortingEnabled(1);
    //######################################MAKE FUNCTION TO SHOW ALL TASK
}

void agenda_ui::show_personal_combox()
{
    QSqlQuery query,query_dni;
    QString DNI,APELLIDOS_NOMBRES;
    query.prepare("SELECT *FROM e_persona WHERE tipo!=\"Paciente\"");
    query.exec();

    while(query.next())
    {

        DNI = query.value(0).toString();

        query_dni.prepare("SELECT apellido_paterno,apellido_materno,primer_nombre,segundo_nombre FROM e_dni WHERE dni_pk="+DNI);
        query_dni.exec();

        while(query_dni.next())
        {
            APELLIDOS_NOMBRES = query_dni.value(0).toString()+" "+query_dni.value(1).toString()+", "+query_dni.value(2).toString()+" "+query_dni.value(3).toString();
        }
        //ui->comboBox_Names->addItem(APELLIDOS_NOMBRES);
        //ui->comboBox_dni->addItem(DNI);
    }


}

void agenda_ui::on_comboBox_Names_currentIndexChanged(int index)
{
    //ui->comboBox_dni->setCurrentIndex(index);
}

void agenda_ui::on_dateEdit_Agenda_dateChanged(const QDate &date)
{
    QString FECHA,HORA,NOMBRE,FICHA,CODIGO,DESCRIPCION,FECHA_CONSULTA,DNI_CONSULTA,COLOR,TELEFONO;
    int COUNT;

    //DNI_CONSULTA = ui->comboBox_dni->currentText();
    FECHA_CONSULTA = ui->dateEdit_Agenda->text();
    COUNT = 0;

    for (int i=ui->tablaView_Agend->rowCount()-1; i >= 0; --i)
        ui->tablaView_Agend->removeRow(i);

    ui->tablaView_Agend->setSortingEnabled(0);
    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;

    query.prepare("SELECT fecha,hora,nombre,descripcion,ficha,agenda_pk,color,telefono FROM e_agenda WHERE Fecha='"+FECHA_CONSULTA+"' and dni_pk="+DNI_CONSULTA);
    query.exec();

    while(query.next())
    {
        FECHA = query.value(0).toString();
        HORA = query.value(1).toString();
        NOMBRE = query.value(2).toString();
        DESCRIPCION = query.value(3).toString();
        FICHA = query.value(4).toString();
        CODIGO = query.value(5).toString();
        COLOR = query.value(6).toString();
        TELEFONO = query.value(7).toString();

        ui->tablaView_Agend->insertRow(COUNT);

        ui->tablaView_Agend->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tablaView_Agend->setItem(COUNT,1,new QTableWidgetItem(HORA));
        ui->tablaView_Agend->setItem(COUNT,2,new QTableWidgetItem(NOMBRE));
        ui->tablaView_Agend->setItem(COUNT,3,new QTableWidgetItem(DESCRIPCION));
        ui->tablaView_Agend->setItem(COUNT,4,new QTableWidgetItem(FICHA));
        ui->tablaView_Agend->setItem(COUNT,5,new QTableWidgetItem(CODIGO));
        ui->tablaView_Agend->setItem(COUNT,6,new QTableWidgetItem(TELEFONO));
        setColorRow(ui->tablaView_Agend,COUNT,COLOR);


        COUNT++;
     }
    ui->tablaView_Agend->setSortingEnabled(1);

}

void agenda_ui::on_tablaView_Agend_itemClicked(QTableWidgetItem *item)
{
    int FILA = item->row();
    QString CODIGO;
    CODIGO = ui->tablaView_Agend->item(FILA,5)->text();
    //ui->lineEdit_codigo->clear();
    //ui->lineEdit_codigo->insert(CODIGO);
}



void agenda_ui::on_dateEdit_Alerta_dateChanged(const QDate &date)
{
    QString HORA,DESCRIPCION,FECHA_CONSULTA,CODE_ALERTA_GENERAL,COLOR;

    int COUNT;


    //FECHA_CONSULTA = ui->dateEdit_Alerta->text();
    COUNT = 0;

    for (int i=ui->tableWidget_Alert->rowCount()-1; i >= 0; --i)
        ui->tableWidget_Alert->removeRow(i);

    ui->tableWidget_Alert->setSortingEnabled(0);
    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;

    query.prepare("SELECT hora,descripcion,color,alerta_pk FROM e_alerta WHERE fecha='"+FECHA_CONSULTA+"' and tipo='general'");
    query.exec();

    while(query.next())
    {
        HORA = query.value(0).toString();
        DESCRIPCION = query.value(1).toString();
        COLOR = query.value(2).toString();
        CODE_ALERTA_GENERAL = query.value(3).toString();



        ui->tableWidget_Alert->insertRow(COUNT);

        ui->tableWidget_Alert->setItem(COUNT,0,new QTableWidgetItem(HORA));
        ui->tableWidget_Alert->setItem(COUNT,1,new QTableWidgetItem(DESCRIPCION));
        ui->tableWidget_Alert->setItem(COUNT,2, new QTableWidgetItem(CODE_ALERTA_GENERAL));
        setColorRow(ui->tableWidget_Alert,COUNT,COLOR);

        COUNT++;
    }
    ui->tableWidget_Alert->setSortingEnabled(1);

    //this->code_var_alerta_general = CODE_ALERTA_GENERAL;

}

void agenda_ui::on_comboBox_dni_currentIndexChanged(const QString &arg1)
{
    QString FECHA,HORA,NOMBRE,FICHA,CODIGO,DESCRIPCION,FECHA_CONSULTA,DNI_CONSULTA,COLOR,TELEFONO;
    int COUNT;

    ui->tablaView_Agend->setSortingEnabled(0);
    //DNI_CONSULTA = ui->comboBox_dni->currentText();
    FECHA_CONSULTA = ui->dateEdit_Agenda->text();
    COUNT = 0;

    for (int i=ui->tablaView_Agend->rowCount()-1; i >= 0; --i)
        ui->tablaView_Agend->removeRow(i);


    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;
    qDebug()<<"DNI  TO COMPARE :  "+DNI_CONSULTA<<endl;

    query.prepare("SELECT fecha,hora,nombre,descripcion,ficha,agenda_pk,color,telefono FROM e_agenda WHERE fecha='"+FECHA_CONSULTA+"' and dni_pk="+DNI_CONSULTA);
    query.exec();

    while(query.next())
    {
        FECHA = query.value(0).toString();
        HORA = query.value(1).toString();
        NOMBRE = query.value(2).toString();
        DESCRIPCION = query.value(3).toString();
        FICHA = query.value(4).toString();
        CODIGO = query.value(5).toString();
        COLOR = query.value(6).toString();
        TELEFONO = query.value(7).toString();

        ui->tablaView_Agend->insertRow(COUNT);

        ui->tablaView_Agend->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tablaView_Agend->setItem(COUNT,1,new QTableWidgetItem(HORA));
        ui->tablaView_Agend->setItem(COUNT,2,new QTableWidgetItem(NOMBRE));
        ui->tablaView_Agend->setItem(COUNT,3,new QTableWidgetItem(DESCRIPCION));
        ui->tablaView_Agend->setItem(COUNT,4,new QTableWidgetItem(FICHA));
        ui->tablaView_Agend->setItem(COUNT,5,new QTableWidgetItem(CODIGO));
        ui->tablaView_Agend->setItem(COUNT,6,new QTableWidgetItem(TELEFONO));
        setColorRow(ui->tablaView_Agend,COUNT,COLOR);

        COUNT++;
     }
    ui->tablaView_Agend->setSortingEnabled(1);
}

void agenda_ui::on_pushButton_showSelect_clicked()
{
    ui->tablaView_Agend->setSortingEnabled(0);

    QString FECHA,HORA,NOMBRE,FICHA,CODIGO,DESCRIPCION,FECHA_CONSULTA,DNI_CONSULTA,COLOR,TELEFONO;
    int COUNT;

    //DNI_CONSULTA = ui->comboBox_dni->currentText();
    FECHA_CONSULTA = ui->dateEdit_Agenda->text();
    COUNT = 0;

    for (int i=ui->tablaView_Agend->rowCount()-1; i >= 0; --i)
        ui->tablaView_Agend->removeRow(i);


    QSqlQuery query;



    query.prepare("SELECT fecha,hora,nombre,descripcion,ficha,agenda_pk,color,telefono FROM e_agenda WHERE fecha='"+FECHA_CONSULTA+"' and dni_pk="+DNI_CONSULTA);
    query.exec();

    while(query.next())
    {
        FECHA = query.value(0).toString();
        HORA = query.value(1).toString();
        NOMBRE = query.value(2).toString();
        DESCRIPCION = query.value(3).toString();
        FICHA = query.value(4).toString();
        CODIGO = query.value(5).toString();
        COLOR = query.value(6).toString();
        TELEFONO = query.value(7).toString();

        ui->tablaView_Agend->insertRow(COUNT);

        ui->tablaView_Agend->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tablaView_Agend->setItem(COUNT,1,new QTableWidgetItem(HORA));
        ui->tablaView_Agend->setItem(COUNT,2,new QTableWidgetItem(NOMBRE));
        ui->tablaView_Agend->setItem(COUNT,3,new QTableWidgetItem(DESCRIPCION));
        ui->tablaView_Agend->setItem(COUNT,4,new QTableWidgetItem(FICHA));
        ui->tablaView_Agend->setItem(COUNT,5,new QTableWidgetItem(CODIGO));
        ui->tablaView_Agend->setItem(COUNT,6,new QTableWidgetItem(TELEFONO));
        setColorRow(ui->tablaView_Agend,COUNT,COLOR);
        COUNT++;
     }
    ui->tablaView_Agend->setSortingEnabled(1);
}

void agenda_ui::set_access_level(int access)
{

    int NIVEL_ACCESO;

    NIVEL_ACCESO= access;

    if(access == 1)
    {
        //ui->pushButton_editTask->hide();
        //ui->pushButton_deleteTask->hide();
        //ui->pushButton_newTask->hide();
        ui->pushButton_AlertaGeneral_changeColor->hide();
        ui->pushButton_agenda_changeColor->hide();
    }
}

void agenda_ui::on_pushButton_show_SelectAlert_clicked()
{
    QString HORA,DESCRIPCION,FECHA_CONSULTA,CODIGO_ALERTA,COLOR;
    int COUNT;


    //FECHA_CONSULTA = ui->dateEdit_Alerta->text();
    COUNT = 0;

    for (int i=ui->tableWidget_Alert->rowCount()-1; i >= 0; --i)
        ui->tableWidget_Alert->removeRow(i);

    ui->tableWidget_Alert->setSortingEnabled(0);
    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;

    query.prepare("SELECT hora,descripcion,alerta_pk,color FROM e_alerta WHERE fecha='"+FECHA_CONSULTA+"' and tipo='general'");
    query.exec();

    while(query.next())
    {
        HORA = query.value(0).toString();
        DESCRIPCION = query.value(1).toString();
        CODIGO_ALERTA = query.value(2).toString();
        COLOR = query.value(3).toString();

        ui->tableWidget_Alert->insertRow(COUNT);

        ui->tableWidget_Alert->setItem(COUNT,0,new QTableWidgetItem(HORA));
        ui->tableWidget_Alert->setItem(COUNT,1,new QTableWidgetItem(DESCRIPCION));
        ui->tableWidget_Alert->setItem(COUNT,2,new QTableWidgetItem(CODIGO_ALERTA));
        setColorRow(ui->tableWidget_Alert,COUNT,COLOR);

        COUNT++;
    }
    ui->tableWidget_Alert->setSortingEnabled(1);
}

void agenda_ui::update_table_agenda_form()
{

    this->on_pushButton_showSelect_clicked();
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
    QString CURRENT_CODE_ALERT_GENERAL;
     int FILA;

     FILA = item->row();

     CURRENT_CODE_ALERT_GENERAL = ui->tableWidget_Alert->item(FILA,2)->text();
     this->code_var_alerta_general = CURRENT_CODE_ALERT_GENERAL;
    qDebug()<<"CODIGO ALERTA GENERAL : "<<code_var_alerta_general<<endl;
}

void agenda_ui::on_pushButton_AlertaGeneral_changeColor_clicked()
{
    if(!ui->tableWidget_Alert->currentItem())
        return;

    QString ALERTA_CODE;
    QSqlQuery query;

    ALERTA_CODE = code_var_alerta_general;

    QColor dfault = ui->tableWidget_Alert->currentItem()->backgroundColor();
    QColorDialog *palette = new QColorDialog();
    palette->setCurrentColor(dfault);
    palette->exec();


    QColor color(palette->currentColor());
    QString COLOR_VALUE = color.name();

    int FILA = ui->tableWidget_Alert->currentItem()->row();

    setColorRow(ui->tableWidget_Alert,FILA,COLOR_VALUE);


    query.prepare("UPDATE e_alerta SET color=? WHERE alerta_pk="+ALERTA_CODE);
    query.bindValue(0,COLOR_VALUE);
    query.exec();

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
    qDebug()<<"update_table_alerta_personal"<<endl;
    QString HORA,DESCRIPCION,FECHA_CONSULTA,CODE_ALERTA_GENERAL,COLOR,CODIGO_USUARIO;

    int COUNT;

    CODIGO_USUARIO = curren_user_code_var;
//    FECHA_CONSULTA = ui->dateEdit_Alerta_Personales->text();
    COUNT = 0;

    for (int i=ui->tableWidget_Alert_Personales->rowCount()-1; i >= 0; --i)
        ui->tableWidget_Alert_Personales->removeRow(i);

    ui->tableWidget_Alert_Personales->setSortingEnabled(0);
    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;
    qDebug()<<"CURREN USER CODE  :  "+CODIGO_USUARIO<<endl;

    query.prepare("SELECT hora,descripcion,color,alerta_pk FROM e_alerta WHERE fecha='"+FECHA_CONSULTA+"' and tipo='"+CODIGO_USUARIO+"'");
    query.exec();
    qDebug()<<"SELECT AGENDA"<<endl;

    while(query.next())
    {
        HORA = query.value(0).toString();
        DESCRIPCION = query.value(1).toString();
        COLOR = query.value(2).toString();
        CODE_ALERTA_GENERAL = query.value(3).toString();
        qDebug()<<"insert item"<<endl;


        ui->tableWidget_Alert_Personales->insertRow(COUNT);

        ui->tableWidget_Alert_Personales->setItem(COUNT,0,new QTableWidgetItem(HORA));
        ui->tableWidget_Alert_Personales->setItem(COUNT,1,new QTableWidgetItem(DESCRIPCION));
        ui->tableWidget_Alert_Personales->setItem(COUNT,2, new QTableWidgetItem(CODE_ALERTA_GENERAL));
        setColorRow(ui->tableWidget_Alert_Personales,COUNT,COLOR);

        COUNT++;
    }
    ui->tableWidget_Alert_Personales->setSortingEnabled(1);
}

void agenda_ui::on_pushButton_show_SelectAlert_Personales_4_clicked()
{
    update_table_alerta_personal();
}


void agenda_ui::on_pushButton_Alert_Personal_changeColor_clicked()
{
    if(!ui->tableWidget_Alert_Personales->currentItem())
        return;

    QString ALERTA_CODE;
    QSqlQuery query;

    ALERTA_CODE = code_var_alerta_personal;

    QColor dfault = ui->tableWidget_Alert_Personales->currentItem()->backgroundColor();
    QColorDialog *palette = new QColorDialog();
    palette->setCurrentColor(dfault);
    palette->exec();


    QColor color(palette->currentColor());
    QString COLOR_VALUE = color.name();

    int FILA = ui->tableWidget_Alert_Personales->currentItem()->row();
    setColorRow(ui->tableWidget_Alert_Personales,FILA,COLOR_VALUE);
    query.prepare("UPDATE e_alerta SET color=? WHERE alerta_pk="+ALERTA_CODE);
    query.bindValue(0,COLOR_VALUE);
    query.exec();
}



void agenda_ui::on_tableWidget_Alert_Personales_itemClicked(QTableWidgetItem *item)
{
    QString CURRENT_CODE_ALERT_PERSONAL;
     int FILA;

     FILA = item->row();

     CURRENT_CODE_ALERT_PERSONAL = ui->tableWidget_Alert_Personales->item(FILA,2)->text();
     this->code_var_alerta_personal = CURRENT_CODE_ALERT_PERSONAL;

}

void agenda_ui::on_pushButton_Alert_Personal_show_clicked()
{
    newalerta_alerta_ui *SHOW_ALERTA_FORM = new newalerta_alerta_ui;
    SHOW_ALERTA_FORM->update_new_alerta_form(this->code_var_alerta_personal);
    SHOW_ALERTA_FORM->set_clicked_type(0);
    SHOW_ALERTA_FORM->show();

}

void agenda_ui::on_pushButton_Alert_Personales_edit_clicked()
{
    newalerta_alerta_ui *EDIT_ALERT_FORM = new newalerta_alerta_ui;
    //EDIT_ALERT_FORM->parent_ui_form_agenda = this;
    EDIT_ALERT_FORM->code_var = code_var_alerta_personal;
    EDIT_ALERT_FORM->update_new_alerta_form(code_var_alerta_personal);

    EDIT_ALERT_FORM->alert_type_var = "personal";

    EDIT_ALERT_FORM->set_clicked_type(1);
    EDIT_ALERT_FORM->show();    
}

void agenda_ui::on_pushButton_Alert_Personales_remove_clicked()
{
    QString CODIGO;

    CODIGO = code_var_alerta_personal;

    QSqlQuery query;


    int ret;
    QMessageBox *msgBox = new QMessageBox;

    QString str_warning = "¿Esta seguro que desea eliminar esa alerta?.";
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowTitle("Confirmar Eliminar");
    msgBox->setWindowIcon(QIcon(":/new/trash.png"));

    msgBox->setText(str_warning);
    msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Elimniar");
    msgBox->setButtonText(QMessageBox::Discard, "No, gracias");
    ret = msgBox->exec();

    switch(ret)
    {
    case QMessageBox::Save:

        query.prepare("DELETE FROM e_alerta WHERE alerta_pk="+CODIGO);

        query.exec();
        update_table_alerta_personal();        
        break;
    case QMessageBox::Discard:

        break;

    default:
        break;
    }

}

void agenda_ui::on_pushButton_show_Agenda_clicked()
{
    newTask_agenda_ui *SHOW_TASK_FORM = new newTask_agenda_ui;
    SHOW_TASK_FORM->set_cliked_type(0);
    //SHOW_TASK_FORM->show_data_task_form(ui->lineEdit_codigo->text());
    //SHOW_TASK_FORM->dni_task = ui->comboBox_dni->currentText(); // dni perteneciente al dueño de la agenda;
    //SHOW_TASK_FORM->code_task = ui->lineEdit_codigo->text();
    SHOW_TASK_FORM->show();
}

void agenda_ui::on_pushButton_agenda_changeColor_clicked()
{
    if(!ui->tablaView_Agend->currentItem())
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
    query.exec();
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
    ui->dateEdit_Agenda->setDate(date);
}



void agenda_ui::on_tablaView_Agend_doubleClicked(const QModelIndex &index)
{
    int FILA = index.row();
    QString CODIGO;
    CODIGO = ui->tablaView_Agend->item(FILA,5)->text();
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


