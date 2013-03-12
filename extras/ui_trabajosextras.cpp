#include "ui_trabajosextras.h"
#include "ui_ui_trabajosextras.h"

ui_trabajosExtras::ui_trabajosExtras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_trabajosExtras)
{
    ui->setupUi(this);
    modo=0;
}

ui_trabajosExtras::~ui_trabajosExtras()
{
    delete ui;
}

void ui_trabajosExtras::setModo(bool m)
{
    modo=m;
}
void ui_trabajosExtras::setTrabajosExtras(trabajosExtras *t)
{
    pTrabajosExtras=*t;
    ui->lineEdit_descripcion->setText(pTrabajosExtras.getDescripcion());
    ui->lineEdit_precio->setText(pTrabajosExtras.getPrecio());
}

bool ui_trabajosExtras::verificarRestricciones()
{
    QRegExp noNumeros("[a-zA-Z]");
    QRegExp noAlfabeto("[0-9\.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");

    if(ui->lineEdit_descripcion->text().size() == 0)
    {
        box.setText("La Descripcion es obligatoria");
        box.exec();
        ui->lineEdit_descripcion->setFocus();
        return false;
    }
    if(ui->lineEdit_precio->text().contains(noNumeros))
    {
        box.setText("El Precio solo puede contener numeros");
        box.exec();
        ui->lineEdit_precio->setFocus();
        return false;
    }
    if(ui->lineEdit_precio->text().size() == 0)
    {
        box.setText("El Precio es obligatorio");
        box.exec();
        ui->lineEdit_precio->setFocus();
        return false;
    }
    return true;
}

void ui_trabajosExtras::on_pushButton_agregar_clicked()
{
    if(!verificarRestricciones())
        return;
    pTrabajosExtras.setDescripcion(ui->lineEdit_descripcion->text());
    pTrabajosExtras.setPrecio(ui->lineEdit_precio->text());
    if(modo==0)//agrego
    {
        if(pTrabajosExtras.agregar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El Trabajo Extra no se pudo agregar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
    else//actualizo
    {
        if(pTrabajosExtras.actualizar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El Trabajo Extra no se pudo actualizar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
}
