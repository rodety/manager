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

    bool actualizarConfiguracion();
    bool conectar_db();
private:
    bool leerConfiguracion();
    QString nombreArchivo;
    ConexionBD *conexiondb;

};

#endif // CONFIGURADOR_H
