#include "ui_configuracion.h"
#include "ui_ui_configuracion.h"
#include "conexionbd.h"
#include <QSqlQuery>
#include <QDebug>
#include "configurador.h"
ui_configuracion::ui_configuracion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_configuracion)
{
    ui->setupUi(this);
    ui->btn_saveConfiguration->setEnabled(false);
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
        ui->btn_saveConfiguration->setEnabled(true);

        currentIdEmpresa = res[5];
        currentIdTienda = res[6];
        QString id_Empresa = (res[5]);
        QString id_Tienda =  (res[6]);
        ui->comboBox_empresa->setCurrentIndex(id_Empresa.toInt(0));
        ui->comboBox_tienda->setCurrentIndex(id_Tienda.toInt(0));

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
