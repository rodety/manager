#include "ui_cliente_datos.h"
#include "ui_ui_cliente_datos.h"

ui_cliente_datos::ui_cliente_datos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_cliente_datos)
{
    ui->setupUi(this);
    ui->comboBox_tipoDoc->setModel(tipodoc_ident::mostrar());
    ui->lineEdit_nombres->setFocus();
    QDate hoy=QDate::currentDate();
    ui->dateEdit->setMaximumDate(hoy);
}

ui_cliente_datos::~ui_cliente_datos()
{
    delete ui;
}

void ui_cliente_datos::setCliente(persona * p)
{
    cliente_act=*p;
    ui->lineEdit_nombres->setText(p->getNombres());
    ui->lineEdit_primerApellido->setText(p->getPrimerApellido());
    ui->lineEdit_segundoApellido->setText(p->getSegundoApellido());
    ui->comboBox_tipoDoc->setCurrentIndex(p->getIdTipoDocIdent().toInt()-1);///////
    ui->lineEdit_nroDoc->setText(p->getNroDoc());
    ui->lineEdit_correo->setText(p->getCorreo());
    QDate fecha=QDate::fromString(p->getFechaNacimiento(),"yyyy-MM-dd");
    ui->dateEdit->setDate(fecha);
    ui->comboBox_sexo->setCurrentIndex(p->getSexo().toInt());
    ui->lineEdit_direccion->setText(p->getDireccion());
    ui->lineEdit_nacionalidad->setText(p->getNacionalidad());
    ui->lineEdit_telefono->setText(p->getTelefono());
    ui->lineEdit_telefono2->setText(p->getTelefono2());
    ui->celular->setText(p->getCelular());
}

bool ui_cliente_datos::verificaRestriccionesCliente()
{
    QRegExp noNumeros("[a-zA-Z]");
    QRegExp noAlfabeto("[0-9\.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");

    if(ui->lineEdit_nombres->text().contains(noAlfabeto))
    {
        box.setText("Los nombres solo pueden contener letras");
        box.exec();
        ui->lineEdit_nombres->setFocus();
        return false;
    }
    if(ui->lineEdit_nombres->text().size() == 0)
    {
        box.setText("Los nombres son obligatorios");
        box.exec();
        ui->lineEdit_nombres->setFocus();
        return false;
    }
    if(ui->lineEdit_primerApellido->text().contains(noAlfabeto))
    {
        box.setText("El Primer Apellido solo pueden contener letras");
        box.exec();
        ui->lineEdit_primerApellido->setFocus();
        return false;
    }
    if(ui->lineEdit_primerApellido->text().size() == 0)
    {
        box.setText("El Primer Apellido es obligatorio");
        box.exec();
        ui->lineEdit_primerApellido->setFocus();
        return false;
    }
    if(ui->lineEdit_segundoApellido->text().contains(noAlfabeto))
    {
        box.setText("El Segundo Apellido solo pueden contener letras");
        box.exec();
        ui->lineEdit_segundoApellido->setFocus();
        return false;
    }
    int j=0;
    for(int i=0;i<ui->lineEdit_correo->text().size();i++)
        if(ui->lineEdit_correo->text()[i]=='@')
        {
            j++;
        }
    if(j>1)
    {
        box.setText("El Correo esta mal escrito");
        box.exec();
        ui->lineEdit_correo->setFocus();
        return false;
    }
    if(ui->lineEdit_nroDoc->text().contains(noNumeros))
    {
        box.setText("El Documento debe conterner unicamente digitos");
        box.exec();
        ui->lineEdit_nroDoc->setFocus();
        return false;
    }
    if(ui->lineEdit_telefono->text().contains(noNumeros))
    {
        box.setText("El Telefono debe conterner unicamente digitos");
        box.exec();
        ui->lineEdit_telefono->setFocus();
        return false;
    }
    if(ui->lineEdit_telefono->text().size()<6 && ui->lineEdit_telefono->text().size()!=0)
    {
        box.setText("El Telefono debe conterner 6 digitos");
        box.exec();
        ui->lineEdit_telefono->setFocus();
        return false;
    }
    if(ui->lineEdit_telefono2->text().contains(noNumeros))
    {
        box.setText("El Segundo Telefono debe conterner unicamente digitos");
        box.exec();
        ui->lineEdit_telefono2->setFocus();
        return false;
    }
    if(ui->lineEdit_telefono2->text().size()<6 && ui->lineEdit_telefono2->text().size()!=0)
    {
        box.setText("El Segundo Telefono debe conterner 6 digitos");
        box.exec();
        ui->lineEdit_telefono2->setFocus();
        return false;
    }
    if(ui->celular->text().contains(noNumeros))
    {
        box.setText("El Celular no puede contener letras");
        box.exec();
        ui->celular->setFocus();
        return false;
    }
    if((ui->celular->text().size()>9 || ui->celular->text().size()<6) && ui->celular->text().size()!=0)
    {
        box.setText("El Celular debe conterner entre 6 y 9 digitos");
        box.exec();
        ui->celular->setFocus();
        return false;
    }
    return true;
}

void ui_cliente_datos::on_pushButton_Aceptar_clicked()
{
    cliente nuevo_cliente;
    tipodoc_ident documento;
    documento.setNombre(ui->comboBox_tipoDoc->currentText());
    documento.buscar();

    if(!verificaRestriccionesCliente())
        return;

    cliente_act.setNombres(ui->lineEdit_nombres->text());
    cliente_act.setPrimerApellido(ui->lineEdit_primerApellido->text());
    cliente_act.setSegundoApellido(ui->lineEdit_segundoApellido->text());
    cliente_act.setNroDoc(ui->lineEdit_nroDoc->text());
    cliente_act.setDireccion(ui->lineEdit_direccion->text());
    cliente_act.setCorreo(ui->lineEdit_correo->text());
    QString sx;sx=sx.setNum(ui->comboBox_sexo->currentIndex());
    cliente_act.setSexo(sx);
    QString year;year=year.setNum(ui->dateEdit->date().year());
    QString month;month=month.setNum(ui->dateEdit->date().month());
    QString day;day=day.setNum(ui->dateEdit->date().day());
    QString fecha;fecha.append(year);fecha.append("-");fecha.append(month);fecha.append("-");fecha.append(day);
    cliente_act.setFechaNacimiento(fecha);
    cliente_act.setTelefono(ui->lineEdit_telefono->text());
    cliente_act.setTelefono2(ui->lineEdit_telefono2->text());
    cliente_act.setNacionalidad(ui->lineEdit_nacionalidad->text());
    cliente_act.setCelular(ui->celular->text());
    cliente_act.setIdTipoDocIdent(documento.getIdTipoDocIdent());

    if(strcmp(this->windowTitle().toStdString().c_str(),"Nuevo Cliente")==0)
        if(cliente_act.agregar())
        {
            cliente_act.buscar();
            nuevo_cliente.setIdCliente(cliente_act.getIdPersona());
            if(nuevo_cliente.agregar())
            {
                this->close();
                guarde();
            }
        }
    if(strcmp(this->windowTitle().toStdString().c_str(),"Editar Cliente")==0)
        if(cliente_act.actualizar())
        {
            this->close();
            guarde();
        }
}

void ui_cliente_datos::on_pushButton_Cancelar_clicked()
{
    this->close();
}
