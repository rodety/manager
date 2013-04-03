#include "newtask_agenda_ui.h"
#include "ui_newtask_agenda_ui.h"
#include <QSqlQuery>
#include <QDebug>
#include "funciones.h"
#include <QMessageBox>

newTask_agenda_ui::newTask_agenda_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTask_agenda_ui)
{
    ui->setupUi(this);
    QDate FECHA = QDate::currentDate();
    ui->dateEdit->setDate(FECHA);
    //ui->pushButton_Query->setVisible(0);

    ui->tableWidget->setColumnWidth(0, 245);
    ui->tableWidget->setColumnWidth(1, 90);
    ui->tableWidget->setColumnWidth(2, 95);
    ui->tableWidget->setColumnWidth(3, 95);

}

newTask_agenda_ui::~newTask_agenda_ui()
{
    delete ui;
}

void newTask_agenda_ui::on_pushButton_Acept_clicked()
{
    //#################REVISAR CUANDO LISTA DE PERSONAL ESTA VACIA
    QSqlQuery query;
    QMessageBox *msgBox=new QMessageBox;
    int ret;

    query.prepare("INSERT INTO e_agenda(dni_pk,nombre,fecha,hora,descripcion,ficha,color,telefono) VALUES(?,?,?,?,?,?,?,?)");
    query.bindValue(0,dni_task);
    query.bindValue(1,ui->lineEdit_Name->text());
    query.bindValue(2,ui->dateEdit->text());
    query.bindValue(3,ui->timeEdit->text());
    query.bindValue(4,ui->lineEdit_Descripcion->text());
    query.bindValue(5,ui->lineEdit_historiaClinica->text());
    query.bindValue(6,"#ffffff");
    query.bindValue(7,ui->lineEdit_Telefono->text());


    //######AGREGAR FICHA- - - > TERMINAR PACIENTE Y REGRESAR

    query.exec();

    if(query.numRowsAffected()==1)
    {       
        this->close();
        parent_ui_form->update_table_alerta_personal();
    }
    else
    {
        QString str_warning = "No se pudo crear la nueva tarea";
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowTitle("Advertencia");
        msgBox->setWindowIcon(QIcon(":/new/file_add.png"));

        msgBox->setText(str_warning);
        msgBox->setStandardButtons(QMessageBox::Save);
        msgBox->setDefaultButton(QMessageBox::Save);
        msgBox->setButtonText(QMessageBox::Save, "Aceptar");

        ret = msgBox->exec();
        return;
    }
    this->parent_ui_form->update_table_agenda_form();

}

void newTask_agenda_ui::on_pushButton_Save_clicked()
{
    QString DNI,CODE;

    DNI = dni_task;
    CODE = code_task;

    QSqlQuery query;

    QMessageBox *msgBox = new QMessageBox;
    int ret;

    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowTitle("Confirmar Guardar");
    msgBox->setWindowIcon(QIcon(":/new/application.png"));

    msgBox->setText("Los datos de la tarea van a ser modificados.");
    msgBox->setInformativeText("¿Desea guardar los cambios?");
    msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Guardar");
    msgBox->setButtonText(QMessageBox::Discard, "No, guardar");
    msgBox->setButtonText(QMessageBox::Cancel, "Cancelar");
    ret = msgBox->exec();

    switch(ret)
    {
    case QMessageBox::Save:

        query.prepare("UPDATE e_agenda SET nombre=?,fecha=?,hora=?,descripcion=?,ficha=?,telefono=? WHERE agenda_pk="+CODE);
        query.bindValue(0,ui->lineEdit_Name->text());
        query.bindValue(1,ui->dateEdit->text());
        query.bindValue(2,ui->timeEdit->text());
        query.bindValue(3,ui->lineEdit_Descripcion->text());
        query.bindValue(4,ui->lineEdit_historiaClinica->text());
        query.bindValue(5,ui->lineEdit_Telefono->text());
        query.exec();

        if(parent_ui_form)
            parent_ui_form->update_table_agenda_form();
        this->close();

        break;
    case QMessageBox::Discard:
        this->close();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }

}

void newTask_agenda_ui::on_pushButton_Cancel_clicked()
{
    this->close();
}

//PARA HABILITAR BOTONOS ACEPTAR; GUARDAR; CANCELAR
void newTask_agenda_ui::set_cliked_type(int type)
{
    switch(type)
    {
        case 0:
            ui->pushButton_Acept->setDisabled(1);
            ui->pushButton_Save->setDisabled(1);
            break;

        case 1:
            ui->pushButton_Acept->setDisabled(1);
            break;
        case 2:
            ui->pushButton_Save->setDisabled(1);
            break;
    }
}



void newTask_agenda_ui::show_data_task_form(QString code)
{
    QString CODIGO,FECHA,NOMBRE,DESCRIPCION,HISTORIA_CLINICA,TELEFONO;
    QTime HORA;

    CODIGO = code;

    QSqlQuery query;
    query.prepare("SELECT fecha,hora,nombre,descripcion,ficha,telefono FROM e_agenda WHERE agenda_pk="+CODIGO);
    query.exec();
    query.next();

    FECHA = query.value(0).toString();
    HORA = query.value(1).toTime();
    NOMBRE = query.value(2).toString();
    DESCRIPCION =query.value(3).toString();
    HISTORIA_CLINICA = query.value(4).toString();
    TELEFONO = query.value(5).toString();


    ui->lineEdit_Name->insert(NOMBRE);
    ui->lineEdit_Descripcion->insert(DESCRIPCION);
    ui->lineEdit_historiaClinica->insert(HISTORIA_CLINICA);
    ui->dateEdit->setDate(toDate(FECHA));
    ui->lineEdit_Telefono->insert(TELEFONO);
    ui->timeEdit->setTime(HORA);
}

void newTask_agenda_ui::on_pushButton_nombre_clicked()
{
    QString DNI,NOMBRE,HISTORIA_CLINICA;
    //DNI = ui->lineEdit_Dni->text();
    NOMBRE = ui->lineEdit_PacienteSearch->text();
    QSqlQuery query;



    query.exec();
    query.next();

    NOMBRE = query.value(0).toString()+" "+query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString();

    query.prepare("SELECT historia_clinica_pk FROM e_historia_clinica WHERE dni_pk="+DNI);
    query.exec();
    query.next();

    HISTORIA_CLINICA = query.value(0).toString();

}

void newTask_agenda_ui::on_pushButton_apellido_clicked()
{
    //------------CLEAR TABLE---------------------------------
        for (int i=ui->tableWidget->rowCount()-1; i >= 0; --i)
            ui->tableWidget->removeRow(i);
        ui->tableWidget->setSortingEnabled(0);
        //--------------VAR---------------------------------------------
        QSqlQuery query_paciente,query_dni,query_historial,query_tmp;
        QString str_search,APELLIDO_PATERNO,NOMBRE_RESULT,DNI_RESULT,HISTORIA_CLINICA;
        QString telefono, celular;
        int COUNT = 0;

        //-------------GET VALUES TO SEARCH -----------------------------------------
        str_search = ui->lineEdit_PacienteSearch->text();

        qDebug()<<"str_search: "<<str_search<<endl;
        //-----------------FIND FOR HISTORIA_CLINICA--------------------------------
        if(ui->comboBox_search->currentIndex()==0&&str_search!="")
        {

        query_historial.prepare("SELECT dni_pk, concat(apellido_paterno, ' ',apellido_materno, ' ',primer_nombre, ' ',segundo_nombre) FROM e_dni WHERE dni_pk = (SELECT dni_pk FROM e_historia_clinica WHERE nick='"+str_search+"')");
        query_historial.exec();


        if(query_historial.next())
        {

                DNI_RESULT = query_historial.value(0).toString();

                NOMBRE_RESULT = query_historial.value(1).toString();

                ui->tableWidget->insertRow(COUNT);


                //ui->tableWidget->setItem(COUNT,0,new QTableWidgetItem(DNI_RESULT));

                ui->tableWidget->setItem(COUNT,0,new QTableWidgetItem(NOMBRE_RESULT));
                ui->tableWidget->setItem(COUNT,1,new QTableWidgetItem(str_search));


        }

        qDebug()<<"DNI_RESULT: "<<DNI_RESULT<<endl;
        query_historial.prepare("SELECT telefono_paciente, celular_paciente FROM e_paciente WHERE dni_pk='"+DNI_RESULT+"';");
        query_historial.exec();
        if(query_historial.next())
        {

            telefono = query_historial.value(0).toString();
            celular = query_historial.value(1).toString();

            qDebug()<<"telefono/celular: "<<telefono+"  "+celular<<endl;
            ui->tableWidget->setItem(COUNT, 2, new QTableWidgetItem(telefono));
            ui->tableWidget->setItem(COUNT, 3, new QTableWidgetItem(celular));
        }


        }
        //-------------------------FIND FOR DNI----------------------------------------
        if(ui->comboBox_search->currentIndex()==2&&str_search!="")
        {
            bool b=false;
            str_search.toInt(&b);

            if(b)
            {
                qDebug()<<"Conversion sucess"<<endl;
                int n=str_search.toInt();
                if(n<=0)
                {
                    b=false;

                }
            }
            if(b)
            {
                query_dni.prepare("SELECT concat(apellido_paterno, ' ',apellido_materno, ' ',primer_nombre, ' ',segundo_nombre) FROM e_dni WHERE dni_pk='"+str_search+"'");
                query_dni.exec();



                if(query_dni.next())
                {
                    qDebug()<<"Query sucess"<<endl;

                    NOMBRE_RESULT = query_dni.value(0).toString();

                    ui->tableWidget->insertRow(COUNT);

                    //ui->tableWidget->setItem(COUNT,0,new QTableWidgetItem(DNI_RESULT));
                    ui->tableWidget->setItem(COUNT,0,new QTableWidgetItem(NOMBRE_RESULT));


                }
                query_dni.prepare("SELECT nick FROM e_historia_clinica WHERE dni_pk='"+str_search+"'");
                query_dni.exec();
                if(query_dni.next())
                {
                    ui->tableWidget->setItem(COUNT,1,new QTableWidgetItem(query_dni.value(0).toString()));
                }
                query_dni.prepare("SELECT telefono_paciente, celular_paciente FROM e_paciente WHERE dni_pk='"+str_search+"'");
                query_dni.exec();
                if(query_dni.next())
                {
                    qDebug()<<"tele/cel: "<<query_dni.value(0).toString()+"  "+query_dni.value(1).toString()<<endl;
                    ui->tableWidget->setItem(COUNT,2,new QTableWidgetItem(query_dni.value(0).toString()));
                    ui->tableWidget->setItem(COUNT,3,new QTableWidgetItem(query_dni.value(1).toString()));
                }

            }
        }
        //----------------FIND FOR APELLIDO_PATERNO------------------------------------------------
        if(ui->comboBox_search->currentIndex()==1&&str_search!="")
        {
        if(str_search=="")
                return;
        //query_paciente.prepare("CREATE VIEW dniHistoriaPaciente AS{SELECT concat(d.apellido_paterno, ' ',d.apellido_materno, ' ',d.primer_nombre, ' ',d.segundo_nombre) FROM e_dni d, LEFT JOIN e_historia_clinica h ON d.dni_pk=h.dni_pk LEFT JOIN e_paciente p ON d.dni_pk=p.dni_pk   WHERE concat(d.apellido_paterno, ' ', d.apellido_materno, ' ', d.primer_nombre, ' ', d.segundo_nombre) LIKE \""+str_search+"%\""+" &&d. dni_pk = ANY (SELECT dni_pk FROM e_persona WHERE tipo='Paciente')};");
        query_paciente.prepare("SELECT concat(d.apellido_paterno, ' ',d.apellido_materno, ' ',d.primer_nombre, ' ',d.segundo_nombre), h.nick, p.telefono_paciente, p.celular_paciente FROM e_dni d LEFT JOIN e_historia_clinica h ON d.dni_pk=h.dni_pk LEFT JOIN e_paciente p ON d.dni_pk=p.dni_pk WHERE concat(d.apellido_paterno, ' ', d.apellido_materno, ' ', d.primer_nombre, ' ', d.segundo_nombre) LIKE \""+str_search+"%\""+" && d.dni_pk = ANY (SELECT dni_pk FROM e_persona WHERE tipo='Paciente')");
        query_paciente.exec();


                while(query_paciente.next())
                {


                    //DNI_RESULT = query_paciente.value(0).toString();

                    NOMBRE_RESULT = query_paciente.value(0).toString();

                    ui->tableWidget->insertRow(COUNT);


                    ui->tableWidget->setItem(COUNT,0,new QTableWidgetItem(NOMBRE_RESULT));
                    ui->tableWidget->setItem(COUNT,1,new QTableWidgetItem(query_paciente.value(1).toString()));
                    ui->tableWidget->setItem(COUNT,2,new QTableWidgetItem(query_paciente.value(2).toString()));
                    ui->tableWidget->setItem(COUNT,3,new QTableWidgetItem(query_paciente.value(3).toString()));
                    COUNT++;
                }


        }
        ui->tableWidget->setSortingEnabled(1);
}


void newTask_agenda_ui::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int FILA = item->row();
    const QString NOMBRE = ui->tableWidget->item(FILA,0)->text();
    const QString HISTORIA_CLINICA = ui->tableWidget->item(FILA,1)->text();
    const QString TELEFONO_CELULAR = ui->tableWidget->item(FILA,2)->text()+" - "+ui->tableWidget->item(FILA,3)->text();

    ui->lineEdit_Name->clear();
    ui->lineEdit_Name->insert(NOMBRE);

    ui->lineEdit_historiaClinica->clear();
    ui->lineEdit_historiaClinica->insert(HISTORIA_CLINICA);

    ui->lineEdit_Telefono->clear();
    ui->lineEdit_Telefono->insert(TELEFONO_CELULAR);
    ui->lineEdit_Descripcion->setFocus();
}

void newTask_agenda_ui::on_lineEdit_PacienteSearch_returnPressed()
{
    ui->pushButton_apellido->click();

}
void newTask_agenda_ui::setDate(QDate date)
{
    ui->dateEdit->setDate(date);
}

void newTask_agenda_ui::on_lineEdit_Name_returnPressed()
{
    ui->lineEdit_Telefono->setFocus();
}
void newTask_agenda_ui::enableDate(bool val)
{
    ui->dateEdit->setEnabled(val);
}

void newTask_agenda_ui::setTitle(QString val)
{
    this->setWindowTitle(val);
}

void newTask_agenda_ui::hideButton()
{
    ui->label_8->hide();
    ui->comboBox_search->hide();
    ui->lineEdit_PacienteSearch->hide();
    ui->pushButton_apellido->hide();
    ui->tableWidget->hide();
    ui->pushButton_Acept->hide();
    ui->pushButton_Save->hide();
    this->resize(481,100);
}
