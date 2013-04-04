#include "producto.h"

producto::producto()
{
}

QString producto::getIdProducto()
{
    return idProducto;
}
QString producto::getCodigo()
{
    return codigo;
}
QString producto::getDescripcion()
{
    return descripcion;
}
QString producto::getPrecioCompra()
{
    return precioCompra;
}
QString producto::getPrecioVenta()
{
    return precioVenta;
}
QString producto::getPrecioDescuento()
{
    return precioDescuento;
}
QString producto::getAccesorios()
{
    return accesorios;
}
QString producto::getStock()
{
    return stock;
}
QString producto::getObservaciones()
{
    return observaciones;
}
estado producto::getEstado()
{
    return pEstado;
}
marca producto::getMarca()
{
    return pMarca;
}
//getColaborador

void producto::setIdProducto(QString tmp)
{
    idProducto=tmp;
}
void producto::setCodigo(QString tmp)
{
    codigo=tmp;
}
void producto::setDescripcion(QString tmp)
{
    descripcion=tmp;
}
void producto::setPrecioCompra(QString tmp)
{
    precioCompra=tmp;
}
void producto::setPrecioVenta(QString tmp)
{
    precioVenta=tmp;
}
void producto::setPrecioDescuento(QString tmp)
{
    precioDescuento=tmp;
}
void producto::setAccesorios(QString tmp)
{
    accesorios=tmp;
}
void producto::setStock(QString tmp)
{
    stock=tmp;
}
void producto::setObservaciones(QString tmp)
{
    observaciones=tmp;
}
void producto::setEstado(estado tmp)
{
    pEstado=tmp;
}
void producto::setMarca(marca tmp)
{
    pMarca=tmp;
}
//setColaborador

void producto::addToVitrina()
{
    QSqlQuery query;
    query.prepare("SELECT cantidadVitrina FROM Producto WHERE idProducto=?");
    query.bindValue(0,idProducto);
    query.exec();   query.next();
    cantidadVitrina= query.value(0).toInt()+ 1;

    query.prepare("UPDATE Producto SET cantidadVitrina=? WHERE idProducto=?");
    query.bindValue(0,cantidadVitrina);
    query.bindValue(1,idProducto);
    query.exec();
}

void producto::addToAlmacen(int tmp)
{
    QSqlQuery query;
    query.prepare("SELECT cantidadAlmacen FROM Producto WHERE idProducto=?");
    query.bindValue(0,idProducto);
    query.exec();   query.next();
    cantidadAlmacen=query.value(0).toInt() + tmp;

    query.prepare("UPDATE Producto SET cantidadAlmacen=? WHERE idProducto=?");
    query.bindValue(0,cantidadAlmacen);
    query.bindValue(1,idProducto);
    query.exec();
}

void producto::vitrinaToAlmacen()
{
    QSqlQuery query;
    query.prepare("SELECT cantidadVitrina, cantidadAlmacen FROM Producto WHERE idProducto=?");
    query.bindValue(0,idProducto);
    query.exec();   query.next();

    cantidadAlmacen=query.value(0).toInt() + 1;
    cantidadVitrina=query.value(1).toInt() - 1;

    query.prepare("UPDATE Producto SET cantidadVitrina=?, cantidadAlmacen=? WHERE idProducto=?");
    query.bindValue(0,cantidadVitrina);
    query.bindValue(1,cantidadAlmacen);
    query.bindValue(2,idProducto);
    query.exec();
}

void producto::almacenToVitrina()
{
    QSqlQuery query;
    query.prepare("SELECT cantidadVitrina, cantidadAlmacen FROM Producto WHERE idProducto=?");
    query.bindValue(0,idProducto);
    query.exec();   query.next();

    cantidadAlmacen=query.value(0).toInt() - 1;
    cantidadVitrina=query.value(1).toInt() + 1;

    query.prepare("UPDATE Producto SET cantidadVitrina=?, cantidadAlmacen=? WHERE idProducto=?");
    query.bindValue(0,cantidadVitrina);
    query.bindValue(1,cantidadAlmacen);
    query.bindValue(2,idProducto);
    query.exec();

    if(cantidadAlmacen==0)
    {
        query.prepare("DELETE FROM Contenedor_has_Producto WHERE idProducto=?");
        query.bindValue(0,idProducto);
        query.exec();
    }
}
