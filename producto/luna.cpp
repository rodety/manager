#include "luna.h"

luna::luna()
{
}

diametro luna::getDiametro()
{
    return pDiametro;
}
calidad luna::getCalidad()
{
    return pCalidad;
}
tipoLuna luna::getTipoLuna()
{
    return pTipoLuna;
}
tratamiento luna::getTratamiento()
{
    return pTratamiento;
}
QString luna::getValorInicial()
{
    return valorInicial;
}
QString luna::getValorFinal()
{
    return valorFinal;
}
QString luna::getPrecio()
{
    return precio;
}


void luna::setDiametro(diametro tmp)
{
    pDiametro=tmp;
}
void luna::setCalidad(calidad tmp)
{
    pCalidad=tmp;
}
void luna::setTipoLuna(tipoLuna tmp)
{
    pTipoLuna=tmp;
}
void luna::setTratamiento(tratamiento tmp)
{
    pTratamiento=tmp;
}
void luna::setValorInicial(QString tmp)
{
    valorInicial=tmp;
}
void luna::setValorFinal(QString tmp)
{
    valorFinal=tmp;
}
void luna::setPrecio(QString tmp)
{
    precio=tmp;
}

bool luna::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Producto(descripcion,precioCompra,precioVenta,precioDescuento,stock,observaciones,Estado_idEstado) VALUES(?,?,?,?,?,?,?)");//falta colaborador
    query.bindValue(0,descripcion);
    query.bindValue(1,precioCompra);
    query.bindValue(2,precioVenta);
    query.bindValue(3,precioDescuento);
    query.bindValue(4,stock);
    query.bindValue(5,observaciones);
    query.bindValue(6,pEstado.getIdEstado());
    if(query.exec())
    {
        query.clear();
        query.prepare("SELECT @@identity AS id;");
        query.exec();
        if(query.size()!=0)
        {
            query.first();
            idProducto=query.value(0).toString();
        }
        query.clear();
        query.prepare("INSERT INTO Luna(Producto_idProducto,Diametro_idDiametro,Calidad_idCalidad,TipoLuna_idTipoLuna,Tratamiento_idTratamiento,valorInicial,valorFinal,precio) VALUES(?,?,?,?,?,?,?,?)");
        query.bindValue(0,idProducto);
        query.bindValue(1,pDiametro.getIdDiametro());
        query.bindValue(2,pCalidad.getIdCalidad());
        query.bindValue(3,pTipoLuna.getIdTipoLuna());
        query.bindValue(4,pTratamiento.getIdTratamiento());
        query.bindValue(5,valorInicial);
        query.bindValue(6,valorFinal);
        query.bindValue(7,precio);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool luna::actualizar()
{
    Sesion* s=Sesion::getSesion();
    QSqlQuery query;
    query.prepare("UPDATE Producto SET descripcion=?,precioCompra=?,precioVenta=?,precioDescuento=?,stock=?,observaciones=?,Estado_idEstado=?,idColaborador=? WHERE idProducto=?");
    query.bindValue(0,descripcion);
    query.bindValue(1,precioCompra);
    query.bindValue(2,precioVenta);
    query.bindValue(3,precioDescuento);
    query.bindValue(4,stock);
    query.bindValue(5,observaciones);
    query.bindValue(6,pEstado.getIdEstado());
    query.bindValue(7,s->getIdColaborador());
    query.bindValue(8,idProducto);
    if(query.exec())
    {
        query.clear();
        query.prepare("UPDATE Luna SET Diametro_idDiametro=?,Calidad_idCalidad=?,TipoLuna_idTipoLuna=?,Tratamiento_idTratamiento=?,valorInicial=?,valorFinal=?,precio=? WHERE Producto_idProducto=?");
        query.bindValue(0,pDiametro.getIdDiametro());
        query.bindValue(1,pCalidad.getIdCalidad());
        query.bindValue(2,pTipoLuna.getIdTipoLuna());
        query.bindValue(3,pTratamiento.getIdTratamiento());
        query.bindValue(4,valorInicial);
        query.bindValue(5,valorFinal);
        query.bindValue(6,precio);
        query.bindValue(7,idProducto);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool luna::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Luna WHERE Producto_idProducto=?");
    query.bindValue(0,idProducto);
    if(query.exec())
    {
        query.clear();
        query.prepare("DELETE FROM Producto WHERE idProducto=?");
        query.bindValue(0,idProducto);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

QSqlQueryModel* luna::mostrar()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT descripcion,e.nombre as 'Estado',precioCompra,precioVenta,precioDescuento,stock,d.valor as 'Diametro',c.nombre as 'Calidad',tl.nombre as 'Tipo de Luna',t.nombre as 'Tratamiento',l.valorInicial,l.valorFinal,l.precio FROM Producto p,Estado e,Luna l,Diametro d,Calidad c,TipoLuna tl,Tratamiento t WHERE p.Estado_idEstado=e.idEstado AND p.idProducto=l.Producto_idProducto AND l.Diametro_idDiametro=d.idDiametro AND l.Calidad_idCalidad=c.idCalidad AND l.TipoLuna_idTipoLuna=tl.idTipoLuna AND l.Tratamiento_idTratamiento=t.idTratamiento");
    return model;
}

bool luna::completar()
{
    QSqlQuery query;
    query.prepare("SELECT p.idProducto,p.observaciones FROM Producto p,Luna l WHERE p.idProducto=l.Producto_idProducto AND p.descripcion=? AND p.precioCompra=? AND p.precioVenta=? AND p.precioDescuento=? AND p.stock=? AND p.Estado_idEstado=? AND l.Diametro_idDiametro=? AND l.Calidad_idCalidad=? AND l.TipoLuna_idTipoLuna=? AND l.Tratamiento_idTratamiento=? AND l.valorInicial=? AND l.valorFinal=?  AND l.precio=?");//falta seleccionar colaborador
    query.bindValue(0,descripcion);
    query.bindValue(1,precioCompra);
    query.bindValue(2,precioVenta);
    query.bindValue(3,precioDescuento);
    query.bindValue(4,stock);
    query.bindValue(5,pEstado.getIdEstado());
    query.bindValue(6,pDiametro.getIdDiametro());
    query.bindValue(7,pCalidad.getIdCalidad());
    query.bindValue(8,pTipoLuna.getIdTipoLuna());
    query.bindValue(9,pTratamiento.getIdTratamiento());
    query.bindValue(10,valorInicial);
    query.bindValue(11,valorFinal);
    query.bindValue(12,precio);
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            idProducto=query.value(0).toString();
            observaciones=query.value(1).toString();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
#include <QSqlError>
bool luna::verificarPrecio()
{
    QSqlQuery query;
    //query.prepare("SELECT p.precioCompra,p.precioVenta,p.precioDescuento FROM Producto p,Luna l,Diametro d,Calidad c,TipoLuna tl,Tratamiento t WHERE p.idProducto=l.Producto_idProducto AND l.Diametro_idDiametro=d.idDiametro AND l.Calidad_idCalidad=c.idCalidad AND l.TipoLuna_idTipoLuna=tl.idTipoLuna AND l.Tratamiento_idTratamiento=t.idTratamiento AND d.valor=? AND c.nombre=? AND tl.nombre=? AND t.nombre=? AND l.valorInicial=? AND l.valorFinal=? AND l.precio=1");
    query.prepare("SELECT p.precioCompra,p.precioVenta,p.precioDescuento FROM Producto p,Luna l WHERE p.idProducto=l.Producto_idProducto AND l.Diametro_idDiametro=? AND l.Calidad_idCalidad=? AND l.TipoLuna_idTipoLuna=? AND l.Tratamiento_idTratamiento=? AND l.valorInicial=? AND l.valorFinal=? AND l.precio=1");
    query.bindValue(0,pDiametro.getIdDiametro());
    query.bindValue(1,pCalidad.getIdCalidad());
    query.bindValue(2,pTipoLuna.getIdTipoLuna());
    query.bindValue(3,pTratamiento.getIdTratamiento());
    query.bindValue(4,valorInicial);
    query.bindValue(5,valorFinal);
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            precioCompra=query.value(0).toString();
            precioVenta=query.value(1).toString();
            precioDescuento=query.value(2).toString();
            precio="0";
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
