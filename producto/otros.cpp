#include "otros.h"

otros::otros()
{
}

color otros::getColor()
{
    return pColor;
}
talla otros::getTalla()
{
    return pTalla;
}
calidad otros::getCalidad()
{
    return pCalidad;
}


void otros::setColor(color tmp)
{
    pColor=tmp;
}
void otros::setTalla(talla tmp)
{
    pTalla=tmp;
}
void otros::setCalidad(calidad tmp)
{
    pCalidad=tmp;
}

bool otros::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Producto(codigo,descripcion,precioCompra,precioVenta,precioDescuento,accesorios,stock,observaciones,Estado_idEstado,Marca_idMarca) VALUES(?,?,?,?,?,?,?,?,?,?)");//falta colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,accesorios);
    query.bindValue(6,stock);
    query.bindValue(7,observaciones);
    query.bindValue(8,pEstado.getIdEstado());
    query.bindValue(9,pMarca.getIdMarca());
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
        query.prepare("INSERT INTO Otros(Producto_idProducto,Color_idColor,Talla_idTalla,Calidad_idCalidad) VALUES(?,?,?,?)");
        query.bindValue(0,idProducto);
        query.bindValue(1,pColor.getIdColor());
        query.bindValue(2,pTalla.getIdTalla());
        query.bindValue(3,pCalidad.getIdCalidad());
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}
bool otros::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE Producto SET codigo=?,descripcion=?,precioCompra=?,precioVenta=?,precioDescuento=?,accesorios=?,stock=?,observaciones=?,Estado_idEstado=?,Marca_idMarca=? WHERE idProducto=?");//falta colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,accesorios);
    query.bindValue(6,stock);
    query.bindValue(7,observaciones);
    query.bindValue(8,pEstado.getIdEstado());
    query.bindValue(9,pMarca.getIdMarca());
    query.bindValue(10,idProducto);
    if(query.exec())
    {
        query.clear();
        query.prepare("UPDATE Otros SET Color_idColor=?,Talla_idTalla=?,Calidad_idCalidad=? WHERE Producto_idProducto=?");
        query.bindValue(0,pColor.getIdColor());
        query.bindValue(1,pTalla.getIdTalla());
        query.bindValue(2,pCalidad.getIdCalidad());
        query.bindValue(3,idProducto);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}
bool otros::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Otros WHERE Producto_idProducto=?");
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

QSqlQueryModel* otros::mostrar()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT codigo,descripcion,e.nombre as 'Estado',precioCompra,precioVenta,precioDescuento,stock,m.nombre as 'Marca',c.nombre as 'Color',t.nombre as 'Talla',ca.nombre as 'Calidad' FROM Producto p,Otros o,Estado e,Marca m,Color c,Talla t,Calidad ca WHERE p.Estado_idEstado=e.idEstado AND p.Marca_idMarca=m.idMarca AND p.idProducto=o.Producto_idProducto AND o.Color_idColor=c.idColor AND o.Talla_idTalla=t.idTalla AND o.Calidad_idCalidad=ca.idCalidad");
    return model;
}

bool otros::completar()
{
    QSqlQuery query;
    query.prepare("SELECT p.idProducto,p.accesorios,p.observaciones FROM Producto p,Otros o WHERE p.idProducto=o.Producto_idProducto AND p.codigo=? AND p.descripcion=? AND p.precioCompra=? AND p.precioVenta=? AND p.precioDescuento=? AND p.stock=? AND p.Estado_idEstado=? AND p.Marca_idMarca=? AND o.Color_idColor=? AND o.Talla_idTalla=? AND o.Calidad_idCalidad=?");//falta seleccionar colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,stock);
    query.bindValue(6,pEstado.getIdEstado());
    query.bindValue(7,pMarca.getIdMarca());
    query.bindValue(8,pColor.getIdColor());
    query.bindValue(9,pTalla.getIdTalla());
    query.bindValue(10,pCalidad.getIdCalidad());
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            idProducto=query.value(0).toString();
            accesorios=query.value(1).toString();
            observaciones=query.value(2).toString();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
