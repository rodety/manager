#include "alerta.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDate>
alerta::alerta()
{
}

void alerta::setIdAlerta(QString tmp){ idAlerta = tmp;}
void alerta::setIdColaborador(QString tmp){idColaborador = tmp;}
void alerta::setfechainicio(QString tmp){fechainicio = tmp;}
void alerta::setfechafin(QString tmp){fechafin = tmp;}
void alerta::sethora(QString tmp){hora = tmp;}
void alerta::setdescripcion(QString tmp){descripcion = tmp;}
void alerta::setcolor(QString tmp){color = tmp;}
void alerta::settipo(QString tmp){tipo = tmp;}

QString alerta::getIdAlerta(){return idAlerta;}
QString alerta::getIdColaborador(){return idColaborador;}
QString alerta::getfecha(){return fechainicio;}
QString alerta::gethora(){return hora;}
QString alerta::getdescripcion(){return descripcion;}
QString alerta::getcolor(){return color;}
QString alerta::gettipo(){return tipo;}



bool alerta::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Alerta(Colaborador_idColaborador,fechaInicio,fechaFin,hora,descripcion,color,tipo) VALUES (?,?,?,?,?,?,?)");
    qDebug()<<"Colaborador "<<idColaborador<<endl ;
    query.bindValue(0,idColaborador);
    query.bindValue(1,fechainicio);
    query.bindValue(2,fechafin);
    query.bindValue(3,hora);
    query.bindValue(4,descripcion);
    query.bindValue(5,color);
    query.bindValue(6,tipo);

    if(query.exec())
        return true;
    else
    {
        QSqlError error(query.lastError());
        QMessageBox::critical(0,"Error permisos",error.text(),0,0);
        return false;
    }
}
bool alerta::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE Alerta SET fechaInicio=?,fechaFin=?,hora=?,descripcion=? WHERE idAlerta=?");
    query.bindValue(0,fechainicio);
    query.bindValue(0,fechafin);
    query.bindValue(1,hora);
    query.bindValue(2,descripcion);        
    query.bindValue(3,idAlerta);

    if(query.exec())
        return true;
    else
    {
        return false;
    }
}
bool alerta::eliminar()
{
    QSqlQuery query;
    //query.prepare("DELETE FROM Alerta")
}

QSqlQueryModel* alerta::mostrar(int t, QDate d)
{
    QSqlQueryModel* model=new QSqlQueryModel;        
    model->setQuery("SELECT hora as 'Hora',descripcion as 'Descripcion' FROM Alerta WHERE tipo ="+QString::number(t)+" AND fechaInicio <='"+d.toString(Qt::ISODate)+" AND fechaFin >='"+d.toString(Qt::ISODate)+"' order by hora");
    return model;
}

bool alerta::completar()
{
    QSqlQuery query;
    query.prepare("SELECT idAlerta FROM Alerta WHERE fechaInicio = ? AND fechaFin = ? AND hora = ? AND descripcion = ?");
    query.bindValue(0,fechainicio);
    query.bindValue(1,fechafin);
    query.bindValue(2,hora);
    query.bindValue(3,descripcion);

    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            idAlerta=query.value(0).toString();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

QSqlQueryModel* alerta::buscarAlerta(QString _item){}
