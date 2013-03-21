#include "ui_tienda_agregar.h"
#include "ui_ui_tienda_agregar.h"

ui_tienda_agregar::ui_tienda_agregar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ui_tienda_agregar)
{
    ui->setupUi(this);
}

ui_tienda_agregar::~ui_tienda_agregar()
{
    delete ui;
}

void ui_tienda_agregar::actualizar()
{
    ui->textAlias->clear();
    ui->textDireccion->clear();
    ui->textPermisoMunicipal->clear();
    ui->textTelefono->clear();

    QSqlQuery query;
    query.prepare("SELECT nombre,direccion,telefono,permisoMunicipal,email FROM Tienda WHERE idTienda=?");
    query.bindValue(0,idTienda);
    query.exec();
    query.next();

    QString  alias= query.value(0).toString();
    QString  direccion= query.value(1).toString();
    QString  telefono= query.value(2).toString();
    QString  permiso= query.value(3).toString();
    QString  email = query.value(4).toString();

    ui->textAlias->insert(alias);
    ui->textDireccion->insert(direccion);
    ui->textPermisoMunicipal->insert(permiso);
    ui->textTelefono->insert(telefono);
    ui->textEmail->insert(email);
}

bool ui_tienda_agregar::validar_tienda()
{
    QRegExp letras   ("[a-zA-Z]");
    QRegExp numeros  ("[0-9]");
    QRegExp simbolos ("[.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");
    QString  alias= ui->textAlias->text();
    QString  telefono= ui->textTelefono->text();
    QSqlQuery query;
    query.prepare("SELECT idTienda FROM Tienda WHERE nombre=?");
    query.bindValue(0,alias);
    query.exec();
    query.next();
    if(ui->textAlias->text()==""||ui->textDireccion->text()=="")
    {
        QMessageBox msgBox;
        msgBox.setText("Complete todos los espacios con *");
        msgBox.exec();
        return false;
    }
    else if(ui->textAlias->text().contains(simbolos))
    {
        box.setText("El Alias de la Tienda solo puede contener letras");
        box.exec();
        ui->textAlias->setFocus();
        return false;
    }
    else if(ui->textDireccion->text().contains(simbolos) )
    {
        box.setText("La dirección solo puede contener letras y números");
        box.exec();
        ui->textDireccion->setFocus();
        return false;
    }
    else if(query.isValid()&&caso==true)
    {
        QMessageBox msgBox;
        msgBox.setText("La tienda ya existe");
        msgBox.exec();
        ui->textAlias->clear();
        return false;
    }
    else if(telefono.contains(letras))
    {
        box.setText("El Telefono debe conterner unicamente digitos");
        box.exec();
        ui->textTelefono->setFocus();
        return false;
    }
    else if(telefono.size()<6 &&telefono.size()!=0)              // 0??????????????????????????????????????????
    {
        box.setText("El Telefono debe conterner entre 6 y 9 digitos");
        box.exec();
        ui->textTelefono->setFocus();
        return false;
    }
    else if((telefono.size()>9 || telefono.size()<6) && telefono.size()!=0)   //?????????????????????????????????'
    {
        box.setText("El Celular debe conterner entre 6 y 9 digitos");
        box.exec();
        ui->textTelefono->setFocus();
        return false;
    }
    else
        return true;
}


void ui_tienda_agregar::on_pushButton_Aceptar_clicked()
{
    QString  nombre = ui->textAlias->text();
    QString  direccion= ui->textDireccion->text();
    QString  telefono = ui->textTelefono->text();
    QString  permiso  = ui->textPermisoMunicipal->text();
    QString  email  = ui->textEmail->text();

    tienda *nueva_tienda;
    QMessageBox *msgBox =new QMessageBox;
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
    msgBox->setWindowTitle("Resultado");
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setButtonText(QMessageBox::Ok,"Aceptar");

    if(validar_tienda())
    {

    if(caso)//nueva tienda
        {
            nueva_tienda = new tienda(0,get_idEmpresa(),nombre,direccion,telefono,permiso,email);
            if(nueva_tienda->agregar())
                msgBox->setText("La Tienda fue creada correctamente.");
            else
                msgBox->setText("La Tienda no se pudo crear.");
        }
    else//actualizar tienda
        {

            nueva_tienda=new tienda(idTienda,idEmpresa,nombre,direccion,telefono,permiso,email);
            nueva_tienda->actualizar();
            msgBox->setText("Datos actualizados correctamente.");
        }
        close();
        emit actualizarParent(idEmpresa);

        msgBox->exec();
    }

}

void ui_tienda_agregar::on_pushButton_Cancelar_clicked()
{
    this->close();
}
