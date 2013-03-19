#ifndef CONFIGURADOR_H
#define CONFIGURADOR_H
#include <QString>
#include <fstream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "conexionbd.h"
#include<QWidget>
class configurador:QWidget
{
public:
    configurador(QString);
    ~configurador();

    bool actualizarConfiguracion(QString,QString,QString,QString,QString);
    bool conectar_db();
private:
    bool leerConfiguracion();
    QString nombreArchivo;
    ConexionBD *conexiondb;
    QString nameConfig;
};

#endif // CONFIGURADOR_H
