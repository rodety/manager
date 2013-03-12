#ifndef TIENDA_H
#define TIENDA_H
#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QDate>
#include <QTime>
#include <objetopersistente.h>
#include <QSqlQueryModel>
using namespace std;
class tienda:public ObjetoPersistente
{
    private:
        QString idTienda;
        QString idEmpresa;
        QString alias;
        QString direccion;
        QString telefono;
        QString permisoMunicipal;
        QString email;

    public:
        tienda();
        tienda(QString,QString,QString,QString,QString,QString,QString);

        QString getIdTienda()  { return idTienda; }
        QString getIdEmpresa() { return idEmpresa; }
        QString getAlias()     { return alias; }
        QString getDireccion() { return direccion; }
        QString getTelefono()  { return telefono; }
        QString getPermisoMunicipal() { return permisoMunicipal; }
        QString getEmail()     { return email; }

        void setIdTienda(QString tmp)   { idTienda=tmp; }
        void setIdEmpresa(QString tmp)  { idEmpresa=tmp; }
        void setAlias(QString tmp)      { alias=tmp; }
        void setDireccion(QString tmp)  { direccion=tmp; }
        void setTelefono(QString tmp)   { telefono=tmp; }
        void setPermisoMunicipal(QString tmp)  { permisoMunicipal=tmp; }
        void setEmail(QString tmp)      { email=tmp; }

        bool validar(QString,QString);

        static QSqlQueryModel* mostrar();
        bool agregar();
        bool actualizar();
        bool eliminar();
};

#endif // TIENDA_H
