#include "tienda.h"

tienda::tienda()
{
}

tienda::tienda(QString _idtienda, QString _idempresa, QString _alias, QString _direccion, QString _telefono, QString _permisoMunicipal, QString _email)
{
    idTienda=_idtienda;
    idEmpresa=_idempresa;
    alias=_alias;
    direccion=_direccion;
    telefono=_telefono;
    permisoMunicipal=_permisoMunicipal;
    email = _email;
}

bool tienda::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Tienda (Empresa_idEmpresa,nombre,direccion,telefono,permisoMunicipal,email) VALUES (?,?,?,?,?,?)");

    query.bindValue(0,idEmpresa);
    query.bindValue(1,alias);
    query.bindValue(2,direccion);
    query.bindValue(3,telefono);
    query.bindValue(4,permisoMunicipal);
    query.bindValue(5,email);

    if(query.exec())
        return true;
    else
        return false;
    return true;
}

bool tienda::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE Tienda SET Empresa_idEmpresa=?,nombre=?,direccion=?,telefono=?,permisoMunicipal=?,email=? WHERE idTienda=?");

    query.bindValue(0,idEmpresa);
    query.bindValue(1,alias);
    query.bindValue(2,direccion);
    query.bindValue(3,telefono);
    query.bindValue(4,permisoMunicipal);
    query.bindValue(5,idTienda);
    query.bindValue(6,email);

    if(query.exec())
        return true;
    else
        return false;
    return true;
}

bool tienda::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Tienda WHERE idTienda='"+idTienda+"'");

    if(query.exec())
        return true;
    else
        return false;
}

QSqlQueryModel* tienda::mostrar()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select nombre,direccion,telefono,permisoMunicipal from Tienda");
    return model;
}
