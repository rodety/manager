#include "alertas_ui.h"
#include "ui_alertas_ui.h"
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QDate>
#include <QDateTime>
#include <QColorDialog>
#include <QMessageBox>

alertas_ui::alertas_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertas_ui)
{
    ui->setupUi(this);

    QDate FECHA = QDate::currentDate();
    ui->dateEdit->setDate(FECHA);
    //update_table_alert();

    ui->tableWidget_AlertList->setColumnWidth(0, 90);
    ui->tableWidget_AlertList->setColumnWidth(1, 90);
    ui->tableWidget_AlertList->setColumnWidth(2, 990);
    ui->tableWidget_AlertList->setColumnWidth(3, 90);
    ui->lineEdit_code->setReadOnly(true);
}

alertas_ui::~alertas_ui()
{
    delete ui;
}

void alertas_ui::on_verAlerta_clicked()
{
    newalerta_alerta_ui *SHOW_ALERTA_FORM = new newalerta_alerta_ui;
    SHOW_ALERTA_FORM->update_new_alerta_form(ui->lineEdit_code->text());
    SHOW_ALERTA_FORM->set_clicked_type(0);
    SHOW_ALERTA_FORM->show();
}

void alertas_ui::on_editar_alerta_clicked()
{
    newalerta_alerta_ui *EDIT_ALERT_FORM = new newalerta_alerta_ui;
    EDIT_ALERT_FORM->setWindowTitle("Editar alerta");
    EDIT_ALERT_FORM->update_new_alerta_form(ui->lineEdit_code->text());
    EDIT_ALERT_FORM->code_var = ui->lineEdit_code->text();
    EDIT_ALERT_FORM->set_clicked_type(1);
    EDIT_ALERT_FORM->parent_ui_form =this;
    EDIT_ALERT_FORM->parent_ui_form_agenda = NULL;
    EDIT_ALERT_FORM->show();
}

void alertas_ui::on_newAlert_alerta_clicked()
{
    newalerta_alerta_ui* NEW_ALERTA_FORM = new newalerta_alerta_ui;
    NEW_ALERTA_FORM->setWindowTitle("Nueva alerta");
    NEW_ALERTA_FORM->set_clicked_type(2);
    NEW_ALERTA_FORM->parent_ui_form = this;
    NEW_ALERTA_FORM->alert_type_var = "general";
    NEW_ALERTA_FORM->show();
}

void alertas_ui::update_table_alert()
{

    qDebug()<<"update_table_alert()"<<endl;


    for (int i=ui->tableWidget_AlertList->rowCount()-1; i >= 0; --i)
        ui->tableWidget_AlertList->removeRow(i);
    ui->tableWidget_AlertList->setSortingEnabled(0);

    QString FECHA,HORA,DESCRIPCION,CODIGO,COLOR;
    int COUNT;

    COUNT = 0;

    QSqlQuery query;
    query.prepare("SELECT *FROM e_alerta WHERE tipo='general'");
    query.exec();

    while(query.next())
    {

        CODIGO = query.value(0).toString();
        FECHA = query.value(1).toString();
        HORA = query.value(2).toString();
        DESCRIPCION = query.value(3).toString();
        COLOR = query.value(4).toString();

        qDebug()<<"ESTADO UPDATE TABLE : "<<COLOR<<endl;

        ui->tableWidget_AlertList->insertRow(COUNT);
        ui->tableWidget_AlertList->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tableWidget_AlertList->setItem(COUNT,1,new QTableWidgetItem(HORA));
        ui->tableWidget_AlertList->setItem(COUNT,2,new QTableWidgetItem(DESCRIPCION));
        ui->tableWidget_AlertList->setItem(COUNT,3,new QTableWidgetItem(CODIGO));
        setColorRow(ui->tableWidget_AlertList,COUNT,COLOR);

        qDebug()<<DESCRIPCION<<endl;

        COUNT++;

    }
    ui->tableWidget_AlertList->setSortingEnabled(1);

}

void alertas_ui::on_pushButton_showAll_clicked()
{
    update_table_alert();
}



void alertas_ui::on_tableWidget_AlertList_itemClicked(QTableWidgetItem *item)
{
    QString CODIGO;
    int FILA;

    FILA = item->row();
    CODIGO = ui->tableWidget_AlertList->item(FILA,3)->text();

    ui->lineEdit_code->clear();
    ui->lineEdit_code->insert(CODIGO);

}

void alertas_ui::on_eliminar_alerta_clicked()
{
    if(ui->lineEdit_code->text()=="")
        return;
    QString CODIGO;
    QSqlQuery query;
    int ret;
    QMessageBox *msgBox = new QMessageBox;

    QString str_warning = "¿Esta seguro que desea eliminar esa alerta?.";
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowTitle("Confirmar Eliminar");
    msgBox->setWindowIcon(QIcon(":/new/close.png"));

    msgBox->setText(str_warning);
    msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox->setDefaultButton(QMessageBox::Save);
    msgBox->setButtonText(QMessageBox::Save, "Elimniar");
    msgBox->setButtonText(QMessageBox::Discard, "No, gracias");
    ret = msgBox->exec();
    switch(ret)
    {
    case QMessageBox::Save:
        CODIGO = ui->lineEdit_code->text();

        query.prepare("DELETE FROM e_alerta WHERE alerta_pk="+CODIGO);

        query.exec();

        this->update_table_alert();
        break;
    case QMessageBox::Discard:

        break;

    default:
        break;
    }
}

void alertas_ui::on_dateEdit_dateChanged(const QDate &date)
{
    QString FECHA,HORA,DESCRIPCION,CODIGO,FECHA_CONSULTA,COLOR;
    int COUNT;

    FECHA_CONSULTA = ui->dateEdit->text();
    COUNT = 0;
    ui->tableWidget_AlertList->setSortingEnabled(0);
    for (int i=ui->tableWidget_AlertList->rowCount()-1; i >= 0; --i)
        ui->tableWidget_AlertList->removeRow(i);


    QSqlQuery query;

    qDebug()<<"FECHA TO COMPARE :  "+FECHA_CONSULTA<<endl;

    query.prepare("SELECT fecha,hora,descripcion,alerta_pk,color FROM e_alerta WHERE fecha='"+FECHA_CONSULTA+"' and tipo='general'");
    query.exec();

    while(query.next())
    {
        FECHA = query.value(0).toString();
        HORA = query.value(1).toString();
        DESCRIPCION = query.value(2).toString();
        CODIGO = query.value(3).toString();
        COLOR = query.value(4).toString();


        ui->tableWidget_AlertList->insertRow(COUNT);

        ui->tableWidget_AlertList->setItem(COUNT,0,new QTableWidgetItem(FECHA));
        ui->tableWidget_AlertList->setItem(COUNT,1,new QTableWidgetItem(HORA                                                                  ));
        ui->tableWidget_AlertList->setItem(COUNT,2,new QTableWidgetItem(DESCRIPCION));
        ui->tableWidget_AlertList->setItem(COUNT,3,new QTableWidgetItem(CODIGO));
        setColorRow(ui->tableWidget_AlertList,COUNT,COLOR);

        COUNT++;
     }
    ui->tableWidget_AlertList->setSortingEnabled(1);
}

void alertas_ui::set_access_level(int access)
{

    int NIVEL_ACCESO;

    NIVEL_ACCESO= access;

    if(access == 1)
    {
        ui->editar_alerta->hide();
        ui->newAlert_alerta->hide();
        ui->eliminar_alerta->hide();
        ui->pushButton_Alert_changeColor->hide();
    }
}

void alertas_ui::update_table_alert_day()
{
    const QDate date = ui->dateEdit->date();
    on_dateEdit_dateChanged(date);
}

void alertas_ui::on_pushButton_Alert_changeColor_clicked()
{
    if(!ui->tableWidget_AlertList->currentItem())
        return;
    else
        if(ui->tableWidget_AlertList->currentItem()->text()=="")
            return;

    QString ALERTA_CODE;
    QSqlQuery query;


    ALERTA_CODE = ui->lineEdit_code->text();


    QColor dfault = ui->tableWidget_AlertList->currentItem()->backgroundColor();
    QColorDialog *palette = new QColorDialog();
    palette->setCurrentColor(dfault);
    palette->exec();


    QColor color(palette->currentColor());
    QString COLOR_VALUE = color.name();

    int FILA = ui->tableWidget_AlertList->currentItem()->row();

    setColorRow(ui->tableWidget_AlertList,FILA,COLOR_VALUE);


    query.prepare("UPDATE e_alerta SET color=? WHERE alerta_pk="+ALERTA_CODE);
    query.bindValue(0,COLOR_VALUE);
    query.exec();



    qDebug()<<color.rgb()<<" "<<COLOR_VALUE<<endl;
}

void alertas_ui::on_dateEdit_editingFinished()
{

}
