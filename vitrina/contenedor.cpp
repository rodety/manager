#include "contenedor.h"

contenedor::contenedor()
{
}

contenedor::contenedor(QString idC, QString idAn, QString n, QString d, QString f, QString c,QString cap)
{
    idContenedor = idC;
    idAndamio = idAn;
    nombre = n;
    descripcion = d;
    pos_fila = f;
    pos_columna = c;
    capacidad = cap;
}

QString contenedor::getIdContenedor()
{
    return idContenedor;
}

QString contenedor::getIdAndamio()
{
    return idAndamio;
}

QString contenedor::getNombre()
{
    return nombre;
}

QString contenedor::getDescripcion()
{
    return descripcion;
}

QString contenedor::getPosFila()
{
    return pos_fila;

}

QString contenedor::getPosColumna()
{
    return pos_columna;
}

QString contenedor::getCapacidad()
{
    return capacidad;
}

void contenedor::setIdContenedor(QString idC)
{
    idContenedor = idC;
}

void contenedor::setIdAndamio(QString idAn)
{
    idAndamio = idAn;
}

void contenedor::setNombre(QString n)
{
    nombre = n;
}

void contenedor::setDescripcion(QString d)
{
    descripcion = d;
}

void contenedor::setPosFila(QString f)
{
    pos_fila = f;
}

void contenedor::setPosColumna(QString c)
{
    pos_columna = c;
}

void contenedor::setCapacidad(QString cap)
{
    capacidad = cap;
}

bool contenedor::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO contenedor(idandamio,nombre,descripcion,pos_fila,pos_columna,capacidad) VALUES(?,?,?,?,?,?)");
    query.bindValue(0,idAndamio);
    query.bindValue(1,nombre);
    query.bindValue(2,descripcion);
    query.bindValue(3,pos_fila);
    query.bindValue(4,pos_columna);
    query.bindValue(5,capacidad);

    if(query.exec())
        return true;
    else
        return false;
}

bool contenedor::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE contenedor SET idandamio=?,nombre=?,descripcion=?,pos_fila=?,pos_columna=?,capacidad=? WHERE idcontenedor=?");
    query.bindValue(0,idAndamio);
    query.bindValue(1,nombre);
    query.bindValue(2,descripcion);
    query.bindValue(3,pos_fila);
    query.bindValue(4,pos_columna);
    query.bindValue(5,capacidad);
    query.bindValue(6,idContenedor);

    if(query.exec())
        return true;
    else
        return false;


}

bool contenedor::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM contenedor WHERE idcontenedor='"+idContenedor+"'");

    if(query.exec())
        return true;
    else
        return false;
}



