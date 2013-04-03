#include "newalerta_alerta_ui.h"
#include "ui_newalerta_alerta_ui.h"
#include <QDebug>
#include <QMessageBox>

newalerta_alerta_ui::newalerta_alerta_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newalerta_alerta_ui)
{
    ui->setupUi(this);
    QDate FECHA = QDate::currentDate();
    ui->dateEdit->setDate(FECHA);
}

newalerta_alerta_ui::~newalerta_alerta_ui()
{
    delete ui;
}

void newalerta_alerta_ui::create_alert(QString type)
{
    QMessageBox *msgBox=new QMessageBox;
    int ret;
    QSqlQuery query;


    query.prepare("INSERT INTO e_alerta(fecha,hora,descripcion,color,tipo) VALUES(?,?,?,?,?)");


    query.bindValue(0,ui->dateEdit->text());
    query.bindValue(1,ui->timeEdit->text());
    query.bindValue(2,ui->lineEdit->text());
    query.bindValue(3,"#ffffff");
    query.bindValue(4,type);
    query.exec();

    if(query.numRowsAffected()==1)
    {
        QString info = "Se creo una nueva alerta con éxito.";
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowTitle("Información");
        msgBox->setWindowIcon(QIcon(":/new/add1-.png"));

        msgBox->setText(info);
        msgBox->setStandardButtons(QMessageBox::Save);
        msgBox->setDefaultButton(QMessageBox::Save);
        msgBox->setButtonText(QMessageBox::Save, "Aceptar");

        ret = msgBox->exec();
    }
    else
    {
        QString str_warning = "Ingrese una alerta válida porfavor.";
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowTitle("Advertencia");
        msgBox->setWindowIcon(QIcon(":/new/add1-.png"));

        msgBox->setText(str_warning);
        msgBox->setStandardButtons(QMessageBox::Save);
        msgBox->setDefaultButton(QMessageBox::Save);
        msgBox->setButtonText(QMessageBox::Save, "Aceptar");

        ret = msgBox->exec();
        return;
    }

    qDebug()<<ui->dateEdit->time()<<endl;
    qDebug()<<ui->timeEdit->text()<<endl;
    qDebug()<<ui->lineEdit->text()<<endl;

    this->close();

    if(type == "general")
    {

        parent_ui_form->update_table_alert_day();
    }
    else
    {

        parent_ui_form_agenda->update_table_alerta_personal();

    }
}

void newalerta_alerta_ui::on_pushButton_Acept_clicked()
{
    QString TIPO_ALERTA;

    TIPO_ALERTA = alert_type_var;

   create_alert(TIPO_ALERTA);
}

void newalerta_alerta_ui::on_pushButton_Cancel_clicked()
{
    this->close();
}

void newalerta_alerta_ui::set_clicked_type(int type)
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


void newalerta_alerta_ui::update_new_alerta_form(QString code)
{
    QString CODIGO,DESCRICPCION;
    QDate FECHA;
    QTime HORA;

    CODIGO = code;
    QSqlQuery query;
    query.prepare("SELECT fecha,hora,descripcion FROM e_alerta WHERE alerta_pk="+CODIGO);
    query.exec();
    query.next();
    FECHA = query.value(0).toDate();
    HORA = query.value(1).toTime();
    DESCRICPCION = query.value(2).toString();
    ui->dateEdit->setDate(FECHA);
    ui->timeEdit->setTime(HORA);
    ui->lineEdit->insert(DESCRICPCION);

}

void newalerta_alerta_ui::on_pushButton_Save_clicked()
{
    QString CODIGO,FECHA,HORA,DESCRIPCION;
    QSqlQuery query;
    int ret;
    QMessageBox *msgBox = new QMessageBox;

    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowTitle("Confirmar Guardar");
    msgBox->setWindowIcon(QIcon(":/new/edit.png"));

    msgBox->setText("La alerta seleccionada va a ser modificado.");
    msgBox->setInformativeText("¿Desea guardar los cambios?");
    msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Guardar");
    msgBox->setButtonText(QMessageBox::Discard, "No, guardar");
    msgBox->setButtonText(QMessageBox::Cancel, "Cancelar");
    ret = msgBox->exec();



    switch (ret) {
       case QMessageBox::Save:
           // Save was clicked
            CODIGO = code_var;

            FECHA = ui->dateEdit->text();
            HORA = ui->timeEdit->text();
            DESCRIPCION = ui->lineEdit->text();


            query.prepare("UPDATE e_alerta SET fecha=?,hora=?,descripcion=? WHERE alerta_pk="+code_var);

            query.bindValue(0,FECHA);
            query.bindValue(1,HORA);
            query.bindValue(2,DESCRIPCION);
            query.exec();

            this->close();
            //parent_ui_form->update_table_alert();

            //parent_ui_form = new alertas_ui;
            //parent_ui_form = new alertas_ui;

            if(parent_ui_form_agenda)
            {
                parent_ui_form_agenda->update_table_agenda_form();
                parent_ui_form_agenda->update_table_alerta_personal();

            }
            else
            {
                parent_ui_form->update_table_alert_day();
            }
           break;
       case QMessageBox::Discard:
           // Don't Save was clicked
           this->close();
           break;
       case QMessageBox::Cancel:
           // Cancel was clicked
           break;
       default:
           // should never be reached
           break;
    }


}
