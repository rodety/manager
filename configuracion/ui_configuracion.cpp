#include "ui_configuracion.h"
#include "ui_ui_configuracion.h"
#include "conexionbd.h"
#include <QSqlQuery>
#include <QDebug>
#include "configurador.h"
#include <configuracion/tusuario.h>
#include <producto/estado.h>
#include <vitrina/ui_agregar_empresa.h>
ui_configuracion::ui_configuracion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_configuracion)
{
    ui->setupUi(this);
    controlbotones(false);
    config = new configurador("config.ini");
    if(config->leerConfiguracion())
    {
        res = config->getConfig();
        loadConfiguration();

    }
    else
    {
        qDebug()<<"No logro abrir el fichero"<<endl;

    }

    ui->comboBox_tipoUsuario->setTipo("tusuario");
    ui->comboBox_Documento->setTipo("documento");
    ui->comboBox_estadoProductos->setTipo("estado");
}

ui_configuracion::~ui_configuracion()
{
    delete ui;
}


void ui_configuracion::on_btn_testConexion_clicked()
{
    QString ip = ui->lineEdit_ipdatabase->text();
    QString db = ui->lineEdit_nameDatabase->text();
    QString user = ui->lineEdit_userDatabase->text();
    QString pass = ui->lineEdit_passwordUser->text();
    QString port = ui->lineEdit_portDatabase->text();

    config->actualizarConfiguracion(ip,db,user,pass,port);
    if(config->conectar_db())
    {
        ui->label_result->setText("Conexion exitosa");
        update_comboBox_Empresa();
        controlbotones(true);

        currentIdEmpresa = res[5];
        currentIdTienda = res[6];
        QString id_Empresa = (res[5]);
        QString id_Tienda =  (res[6]);
        ui->comboBox_empresa->setCurrentIndex(id_Empresa.toInt(0));
        ui->comboBox_tienda->setCurrentIndex(id_Tienda.toInt(0));
        ui->comboBox_tipoUsuario->ActualizarItems(tusuario::mostrar());
        ui->comboBox_Documento->ActualizarItems(documento::mostrar());
        ui->comboBox_estadoProductos->ActualizarItems(estado::mostrar());

    }
    else
        ui->label_result->setText("No se logro conectar con la base de datos");
}


void ui_configuracion::update_comboBox_Empresa()
{
    ui->comboBox_empresa->clear();

    QSqlQuery query;
    query.prepare("SELECT idEmpresa,razonSocial FROM Empresa");
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idempresa = query.value(0).toString();
        QString raz_social = query.value(1).toString();

        Empresas[raz_social] = idempresa;
        ui->comboBox_empresa->insertItem(c++,raz_social);
    }

}

void ui_configuracion::update_comboBox_Tienda(QString idEmpresa)
{
    ui->comboBox_tienda->clear();

    QSqlQuery query;
    query.prepare("SELECT idTienda,nombre FROM Tienda WHERE Empresa_idEmpresa=?");
    query.bindValue(0,idEmpresa);
    query.exec();

    int c = 0;

    while(query.next())
    {
        QString idtienda = query.value(0).toString();
        QString alias = query.value(1).toString();
        Tiendas[alias] = idtienda;
        ui->comboBox_tienda->insertItem(c++,alias);
    }
}



void ui_configuracion::on_comboBox_empresa_currentIndexChanged(const QString &arg1)
{
    set_currentIdEmpresa(Empresas[arg1]);
    update_comboBox_Tienda(get_currentIdEmpresa());
}

QString ui_configuracion::get_currentIdEmpresa(){return currentIdEmpresa;}
QString ui_configuracion::get_currentIdTienda(){return currentIdTienda;}

void ui_configuracion::set_currentIdEmpresa(QString e){currentIdEmpresa = e;}
void ui_configuracion::set_currentIdTienda(QString t){currentIdTienda = t;}

void ui_configuracion::saveConfiguration()
{
    QSqlQuery query;
    query.prepare("INSERT Configuracion idTienda,nombre FROM Tienda WHERE Empresa_idEmpresa=?");

}

void ui_configuracion::on_btn_saveConfiguration_clicked()
{
    set_currentIdEmpresa(Empresas[ui->comboBox_empresa->currentText()]);
    set_currentIdTienda(Tiendas[ui->comboBox_tienda->currentText()]);

    QString igv = ui->lineEdit_IGV->text();
    QString serie = ui->lineEdit_boleta->text();
    QSqlQuery query;
    query.prepare("SELECT idConfiguracion FROM Configuracion WHERE Tienda_idTienda = ?");
    query.bindValue(0,currentIdTienda);
    query.exec();
    qDebug()<<currentIdTienda<<igv<<serie<<endl;
    if(query.next())
    {
        QString id = query.value(0).toString();
        query.prepare("UPDATE Configuracion SET igv = ?,serieBoleta = ? WHERE (idConfiguracion = ?)");
        query.bindValue(0,igv);
        query.bindValue(1,serie);
        query.bindValue(2,id);
    }
    else
    {        
        query.prepare("INSERT INTO Configuracion (Tienda_idTienda,igv,serieBoleta) VALUES (?,?,?)");
        query.bindValue(0,currentIdTienda);
        query.bindValue(1,igv);
        query.bindValue(2,serie);
    }
    query.exec();

    QString ip = ui->lineEdit_ipdatabase->text();
    QString db = ui->lineEdit_nameDatabase->text();
    QString user = ui->lineEdit_userDatabase->text();
    QString pass = ui->lineEdit_passwordUser->text();
    QString port = ui->lineEdit_portDatabase->text();
    config->guardarConfiguracion(ip,db,user,pass,port,currentIdEmpresa,currentIdTienda);
}

void ui_configuracion::loadConfiguration()
{

    ui->lineEdit_ipdatabase->setText(res[0]);
    ui->lineEdit_nameDatabase->setText(res[1]);
    ui->lineEdit_userDatabase->setText(res[2]);
    ui->lineEdit_passwordUser->setText(res[3]);
    ui->lineEdit_portDatabase->setText(res[4]);

}

void ui_configuracion::on_comboBox_tienda_currentTextChanged(const QString &arg1)
{
    set_currentIdTienda(Tiendas[arg1]);
}

void ui_configuracion::on_comboBox_tienda_currentIndexChanged(const QString &arg1)
{
    set_currentIdTienda(Tiendas[arg1]);
    QSqlQuery query;
    query.prepare("SELECT igv,serieBoleta FROM Configuracion WHERE (Tienda_idTienda = ?)");
    query.bindValue(0,currentIdTienda);
    query.exec();
    query.next();
    ui->lineEdit_IGV->setText(query.value(0).toString());
    ui->lineEdit_boleta->setText(query.value(1).toString());
}

void ui_configuracion::on_btn_eliminar_ducumento_clicked()
{
    ui->comboBox_Documento->eliminar();
}

void ui_configuracion::on_btn_eliminar_tusuario_clicked()
{
    ui->comboBox_tipoUsuario->eliminar();
}

void ui_configuracion::on_btn_eliminar_estado_clicked()
{
    ui->comboBox_estadoProductos->eliminar();
}

void ui_configuracion::on_btn_script_clicked()
{

    //Inicializando Base de datos con tablas necesarias
    QSqlQuery query;
    query.exec("INSERT INTO `Modulo` VALUES (1,'Modulo General','Para Pruebas')");
    query.exec("INSERT INTO `Colaborador` VALUES ('-','-','-',1,'admin',1,1,'123456778','',1,'1993-05-15','34235463','','354354','354354',0,'','63a9f0ea7bb98050796b649e85481845',1)");
    query.exec("INSERT INTO `Permiso` VALUES (1,1,1,1,'2013-03-02'),(2,1,2,1,'2013-03-02'),(3,1,3,1,'2013-03-02'),(4,1,4,1,'2013-03-02'),(5,1,5,1,'2013-03-02'),(6,1,6,1,'2013-03-02'),(7,1,7,1,'2013-03-02'),(8,1,8,1,'2013-03-02'),(9,1,9,1,'2013-03-02')");
    query.exec("INSERT INTO `FuncionModulo` VALUES (1,1,'Producto','pro'),(2,1,'Usuario','usu'),(3,1,'Cliente','cli'),(4,1,'Vitrina','vit'),(5,1,'Almacen','alm'),(6,1,'Compras','comp'),(7,1,'Reportes','rep'),(8,1,'Ventas','ven'),(9,1,'Configuracion','con')");
    query.exec("INSERT INTO `Documento` VALUES (1,'documento nacional de identidad','DNI'),(2,'carnet de extrangeria','CE'),(3,'pasaporte','PP')");
    query.exec("INSERT INTO `SiNo` VALUES (0,'No','F'),(1,'Si','M')");
    query.exec("INSERT INTO `TipoColaborador` VALUES (1,'Administrador'),(2,'Ventas')");
    query.exec("INSERT INTO `Estado` (nombre) VALUES ('activo'),('inactivo')");
}

void ui_configuracion::on_comboBox_Documento_currentIndexChanged(const QString &arg1)
{

}

void ui_configuracion::on_comboBox_tipoUsuario_currentIndexChanged(const QString &arg1)
{

}

void ui_configuracion::on_comboBox_estadoProductos_currentIndexChanged(const QString &arg1)
{

}

void ui_configuracion::on_btnAgregar_empresa_clicked()
{
    add_empresa = new ui_agregar_empresa;
    connect(add_empresa,SIGNAL(actualizarParent()),this,SLOT(update_comboBox_Empresa()));
    add_empresa->set_behavior(1);
    add_empresa->setWindowTitle("Agregar Empresa");
    add_empresa->show();

}

void ui_configuracion::controlbotones(bool a)
{
    ui->btn_saveConfiguration->setEnabled(a);
    ui->btn_eliminar_ducumento->setEnabled(a);
    ui->btn_eliminar_estado->setEnabled(a);
    ui->btn_eliminar_tusuario->setEnabled(a);
    ui->btnAgregar_empresa->setEnabled(a);
    ui->btnAgregar_Tienda->setEnabled(a);
    ui->btn_backup->setEnabled(a);
    ui->btn_script->setEnabled(a);
}

void ui_configuracion::on_btnAgregar_Tienda_clicked()
{


    if(currentIdEmpresa.compare("")==0)
    {
        QMessageBox *msgBox =new QMessageBox;
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setWindowIcon(QIcon(":/Icons/abiword.png"));
        msgBox->setWindowTitle("Información");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setButtonText(QMessageBox::Ok,"Aceptar");
        msgBox->setText("Debe seleccionarse una Empresa válida!");
        msgBox->exec();
    }
    else
    {

        tienda_agregar = new ui_tienda_agregar;
        connect(tienda_agregar,SIGNAL(actualizarParent(QString)),this,SLOT(update_comboBox_Tienda(QString)));
        tienda_agregar->set_idEmpresa(currentIdEmpresa);
        tienda_agregar->set_idTienda(currentIdTienda);
        tienda_agregar->set_caso(1);
        tienda_agregar->setWindowTitle("Agregar Tienda");
        tienda_agregar->show();
    }

}
