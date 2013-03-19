#include "configurador.h"
#include <QMessageBox>
#include<vector>

using namespace std;
configurador::configurador(QString archivoBD)
{
    conexiondb = new ConexionBD;
    nombreArchivo =  archivoBD;
    leerConfiguracion();
    nameConfig = "config.ini";
}
configurador::~configurador()
{
    delete conexiondb;
}
bool configurador::leerConfiguracion()
{
    QString namefile = nombreArchivo;
    QFile file(namefile);
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    if(!file.isOpen())
    {
      file.open(QIODevice::WriteOnly|QIODevice::Text);
      if(!file.isOpen())
        qDebug()<<"Error archivo de configuración";
      else
      {
          QTextStream out(&file);
              out << "192.168.1.241#optical#root#jose-123#3306#";
              return false;
      }
    }
    QString str_db;
    QTextStream in(&file);
    str_db = in.readLine();
    file.close();
    //qDebug()<<"str_db: "<<str_db<<endl;
    QStringList tokens=str_db.split(QRegExp("[#]"));

    conexiondb->setHost(tokens[0]);
    conexiondb->setName(tokens[1]);
    conexiondb->setUser(tokens[2]);
    conexiondb->setPass(tokens[3]);
    conexiondb->setPort(tokens[4]);
}

bool configurador::actualizarConfiguracion(QString a, QString b, QString c, QString d, QString e)
{
    QFile file(nameConfig);
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    if(!file.isOpen())
    {
        qDebug()<<"Error de apertura de archivo de configuracion"<<endl;
      return false;
    }
    QTextStream out(&file);
    out <<a<<"#"<<b<<"#"<<c<<"#"<<d<<"#"<<e<<"#";
    file.close();
}

bool configurador::conectar_db()
{
    if(conexiondb->connect())
    {       
        return true;
    }
    else
    {       
        return false;
    }

}
