#include "ui_configuracion.h"
#include "ui_ui_configuracion.h"
#include "configuracion/configurador.h"
#include <QSqlQuery>
#include <QDebug>
ui_configuracion::ui_configuracion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_configuracion)
{
    ui->setupUi(this);
    ui->btn_saveConfiguration->setEnabled(false);
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

    configurador* config = new configurador("config.ini");
    config->actualizarConfiguracion(ip,db,user,pass,port);
    if(config->conectar_db())
    {
        ui->label_result->setText("Conexion exitosa");
        update_comboBox_Empresa();
        ui->btn_saveConfiguration->setEnabled(true);
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
    QString igv = ui->lineEdit_IGV->text();
    QString serie = ui->lineEdit_boleta->text();
    QSqlQuery query;
    query.prepare("INSERT INTO Configuracion (Tienda_idTienda,igv,serieBoleta) VALUES (?,?,?)");
    qDebug()<<currentIdTienda<<igv<<serie<<endl;
    query.bindValue(0,currentIdTienda);
    query.bindValue(1,igv);
    query.bindValue(2,serie);
    if(!query.exec())
    {
        query.prepare("UPDATE Configuracion SET (igv,serieBoleta) VALUES (?,?) WHERE (Tienda_idTienda = ?)");

        query.bindValue(0,igv);
        query.bindValue(1,serie);
        query.bindValue(2,currentIdTienda);
        query.exec();
    }

}
