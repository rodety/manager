#include "configurador.h"
#include <QMessageBox>
#include<vector>

using namespace std;
configurador::configurador(QString archivoBD)
{
    conexiondb = new ConexionBD;
    nombreArchivo =  archivoBD;
    leerConfiguracion();
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
      qDebug()<<"Error archivo de configuración";
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

bool configurador::actualizarConfiguracion()
{
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
