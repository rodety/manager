#include "empresa.h"

empresa::empresa()
{
}
empresa::empresa(QString idEmpresa, QString ruc, QString raz_social, QString domicilio, QString telefono)
{
    id = idEmpresa;
    this->ruc = ruc;
    razonSocial = raz_social;
    domilicioFiscal = domicilio;
    this->telefono = telefono;
}

QString empresa::getId()
{
    return id;
}

QString empresa::getRuc()
{
    return ruc;
}

QString empresa::getrazonSocial()
{
    return razonSocial;
}

QString empresa::getDomilicioFiscal()
{
    return domilicioFiscal;
}

QString empresa::getTelefono()
{
    return telefono;
}

void empresa::setId(QString tmp)
{
    id = tmp;
}
void empresa::setRuc(QString tmp)
{
    ruc=tmp;
}

void empresa::setRazonSocial(QString tmp)
{
    razonSocial=tmp;
}

void empresa::setDomicilioFiscal(QString tmp)
{
    domilicioFiscal=tmp;
}


void empresa::setTelefono(QString tmp)
{
    telefono=tmp;
}

bool empresa::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO empresa(ruc,raz_social,domicilio_fiscal,telefono) VALUES(?,?,?,?)");
    query.bindValue(0,ruc);
    query.bindValue(1,razonSocial);
    query.bindValue(2,domilicioFiscal);
    query.bindValue(3,telefono);

    if(query.exec())
        return true;
    else
        return false;
}
bool empresa::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE empresa SET ruc=?,raz_social=?,domicilio_fiscal=?,telefono=? where idempresa=?");
    query.bindValue(0,ruc);
    query.bindValue(1,razonSocial);
    query.bindValue(2,domilicioFiscal);
    query.bindValue(3,telefono);
    query.bindValue(4,id);

    if(query.exec())
        return true;
    else
        return false;
}
bool empresa::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM empresa WHERE idempresa='"+id+"'");

    if(query.exec())
        return true;
    else
        return false;
}
