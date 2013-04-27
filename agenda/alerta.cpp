#include "alerta.h"
#include <QSqlQuery>
alerta::alerta()
{
}

void alerta::setIdAlerta(QString tmp){ idAlerta = tmp;}
void alerta::setIdColaborador(QString tmp){idColaborador = tmp;}
void alerta::setfecha(QString tmp){fecha = tmp;}
void alerta::sethora(QString tmp){hora = tmp;}
void alerta::setdescripcion(QString tmp){descripcion = tmp;}
void alerta::setcolor(QString tmp){color = tmp;}
void alerta::settipo(QString tmp){tipo = tmp;}

QString alerta::getIdAlerta(){return idAlerta;}
QString alerta::getIdColaborador(){return idColaborador;}
QString alerta::getfecha(){return fecha;}
QString alerta::gethora(){return hora;}
QString alerta::getdescripcion(){return descripcion;}
QString alerta::getcolor(){return color;}
QString alerta::gettipo(){return tipo;}



bool alerta::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Alerta(fecha,hora,descripcion,color,tipo,Colaborador_idColaborador) VALUES (?,?,?,?,?,?)");
    query.bindValue(0,fecha);
    query.bindValue(1,hora);
    query.bindValue(2,descripcion);
    query.bindValue(3,color);
    query.bindValue(4,tipo);
    query.bindValue(5,idColaborador);
    if(query.exec())
        return true;
    else
        return false;


}
bool alerta::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE Alerta SET fecha=?,hora=?,descripcion=?,color=?,Colaborador_idColaborador? WHERE idAlerta=?");
    query.bindValue(0,fecha);
    query.bindValue(1,hora);
    query.bindValue(2,descripcion);
    query.bindValue(3,color);
    query.bindValue(4,idColaborador);
    query.bindValue(5,idAlerta);

    if(query.exec())
        return true;
    else
        return false;
}
bool alerta::eliminar()
{
    QSqlQuery query;
    //query.prepare("DELETE FROM Alerta")
}

QSqlQueryModel* alerta::mostrar(int t)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    if(t = 0)
    {

        model->setQuery("SELECT nombre as 'Documento',numeroDocumento as 'Numero de Documento',nombres as 'Nombres',primer_apellido as 'Apellido Paterno',segundo_apellido as 'Apellido Materno',telefono as 'Telefono',movil as 'Celular' FROM Cliente,Documento WHERE idDocumento=Documento_idDocumento1");
        return model;
    }
    else
    {
        model->setQuery("SELECT nombre as 'Documento',numeroDocumento as 'Numero de Documento',nombres as 'Nombres',primer_apellido as 'Apellido Paterno',segundo_apellido as 'Apellido Materno',telefono as 'Telefono',movil as 'Celular' FROM Cliente,Documento WHERE idDocumento=Documento_idDocumento1");
        return model;
    }

}

bool alerta::completar(){
    return false;
}

QSqlQueryModel* alerta::buscarAlerta(QString _item){}
