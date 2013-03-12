#include "marca.h"

marca::marca()
{
}


QString marca::getIdMarca()
{
    return idMarca;
}
QString marca::getNombre()
{
    return nombre;
}


void marca::setIdMarca(QString tmp)
{
    idMarca=tmp;
}
void marca::setNombre(QString tmp)
{
    nombre=tmp;
}


bool marca::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Marca(nombre) VALUES(?)");
    query.bindValue(0,nombre);
    if(query.exec())
        return true;
    else
        return false;
}
bool marca::actualizar()
{
    return false;
}
bool marca::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Marca WHERE idMarca=?");
    query.bindValue(0,idMarca);
    if(query.exec())
        return true;
    else
        return false;
}

QSqlQueryModel* marca::mostrar()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT nombre FROM Marca");
    return model;
}

bool marca::completar()
{
    QSqlQuery query;
    query.prepare("SELECT idMarca FROM Marca WHERE nombre=?");
    query.bindValue(0,nombre);
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            idMarca=query.value(0).toString();
            return true;
        }
        return false;
    }
    else
        return false;
}
