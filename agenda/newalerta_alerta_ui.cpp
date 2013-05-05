#include "newalerta_alerta_ui.h"
#include "ui_newalerta_alerta_ui.h"
#include <QDebug>
#include <QMessageBox>
#include <agenda/alerta.h>
#include <configuracion/sesion.h>

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
    if(comportamiento == 0)
    {
        alerta nueva;
        nueva.setfecha(ui->dateEdit->text());
        nueva.sethora(ui->timeEdit->text());
        nueva.setdescripcion(ui->lineEdit->text());
        nueva.setcolor("#ffffff");
        nueva.settipo(QString::number(type_alert));
        Sesion* s=Sesion::getSesion();
        nueva.setIdColaborador(QString::number(s->getIdColaborador()));

        if(nueva.agregar()==true)
        {
            /*QString info = "Se creo una nueva alerta con éxito.";
            msgBox->setIcon(QMessageBox::Information);
            msgBox->setWindowTitle("Información");
            msgBox->setWindowIcon(QIcon(":/new/add1-.png"));

            msgBox->setText(info);
            msgBox->setStandardButtons(QMessageBox::Save);
            msgBox->setDefaultButton(QMessageBox::Save);
            msgBox->setButtonText(QMessageBox::Save, "Aceptar");

            ret = msgBox->exec();*/
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
    }
    if(comportamiento == 1)
    {
        alerta_actual.setfecha(ui->dateEdit->date().toString(Qt::ISODate));
        alerta_actual.sethora(ui->timeEdit->time().toString());
        alerta_actual.setdescripcion(ui->lineEdit->text());

        if(alerta_actual.actualizar()==true)
        {
            /*QString info = "Se actualizo alerta con éxito.";
            msgBox->setIcon(QMessageBox::Information);
            msgBox->setWindowTitle("Información");
            msgBox->setWindowIcon(QIcon(":/new/add1-.png"));

            msgBox->setText(info);
            msgBox->setStandardButtons(QMessageBox::Save);
            msgBox->setDefaultButton(QMessageBox::Save);
            msgBox->setButtonText(QMessageBox::Save, "Aceptar");

            ret = msgBox->exec();*/
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

    }

    this->close();
    emit updateChange();
}

void newalerta_alerta_ui::on_pushButton_Acept_clicked()
{
   QString TIPO_ALERTA;
   //TIPO DE ALERTA 0 ALERTA GENERA 1 ALERTA PERSONAL
   TIPO_ALERTA = alert_type_var;
   create_alert(TIPO_ALERTA);
}

void newalerta_alerta_ui::on_pushButton_Cancel_clicked()
{
    this->close();
}


void newalerta_alerta_ui::set_type_alert(int type)
{
    type_alert = type;
}
void newalerta_alerta_ui::set_alerta(alerta a)
{
    alerta_actual = a;
    //ui->dateEdit->setDate(QDate::fromString(a.getfecha()));
    ui->dateEdit->setDate(QDate::fromString(a.getfecha(),Qt::ISODate));
    ui->timeEdit->setTime(QTime::fromString(a.gethora()));
    ui->lineEdit->setText(a.getdescripcion());

}
void newalerta_alerta_ui::set_comportaminto(int c)
{
    // 0 NUEVA ALERTA 1 EDITAR ALERTA
    comportamiento = c;
}
