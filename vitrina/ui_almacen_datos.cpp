#include "ui_almacen_datos.h"
#include "ui_ui_almacen_datos.h"
#include "almacen.h"
#include <QMessageBox>

ui_almacen_datos::ui_almacen_datos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_almacen_datos)
{
    ui->setupUi(this);
}

ui_almacen_datos::~ui_almacen_datos()
{
    delete ui;
}

QString ui_almacen_datos::get_idTienda(){return idTienda;}
void ui_almacen_datos::set_idTienda(QString t){idTienda = t;}

ui_almacen* ui_almacen_datos::get_ui_almacen_parent(){return ui_almacen_parent;}
void ui_almacen_datos::set_ui_almacen_parent(ui_almacen* al){ui_almacen_parent = al;}

int ui_almacen_datos::get_behavior(){return behavior;}
void ui_almacen_datos::set_behavior(int b){behavior = b;}

void ui_almacen_datos::update_form()
{
    ui->lineEdit_nombre->clear();
    ui->lineEdit_descripcion->clear();

    QSqlQuery query;
    query.prepare("SELECT nombre,descripcion FROM almacen WHERE idalmacen=?");
    query.bindValue(0,ui_almacen_parent->get_currentIdAlmacen());
    query.exec();
    query.next();

    QString nombre = query.value(0).toString();
    QString descripcion = query.value(1).toString();

    ui->lineEdit_nombre->insert(nombre);
    ui->lineEdit_descripcion->insert(descripcion);

}

void ui_almacen_datos::on_pushButton_cancelar_clicked()
{
    close();
}

void ui_almacen_datos::on_pushButton_aceptar_clicked()
{
    QString nombre = ui->lineEdit_nombre->text();
    QString descripcion = ui->lineEdit_descripcion->text();

    almacen* almacen_data;

    QMessageBox *msgBox =new QMessageBox;
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
    msgBox->setWindowTitle("Resultado");
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setButtonText(QMessageBox::Ok,"Aceptar");

    if(nombre.compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("El nombre de un almacen no puede quedar en blanco!");
        msgBox->exec();
    }
    else
    {
        switch(behavior)
        {
            case 0://New Almacen
                almacen_data = new almacen(0,get_idTienda(),nombre,descripcion);
                almacen_data->agregar();
                msgBox->setText("Almacen creado correctamente.");
                break;

            case 1://Update Almacen
                QString idAlmacen = ui_almacen_parent->get_currentIdAlmacen();
                almacen_data = new almacen(idAlmacen,idTienda,nombre,descripcion);
                //almacen_data = new almacen(idAlmacen,get_idTienda(),nombre,descripcion);
                almacen_data->actualizar();
                msgBox->setText("Datos actualizados correctamente.");
                break;
         }

        close();
        ui_almacen_parent->update_comboBox_Almacen(idTienda);
        //ui_almacen_parent->update_comboBox_Almacen(get_idTienda());

        msgBox->exec();
    }
}


