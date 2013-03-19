#include "producto.h"

producto::producto()
{
    cantidadVitrina=0;
    cantidadAlmacen=0;
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

void producto::addToVitrina(int tmp)
{
    QSqlQuery query;
    query.prepare("SELECT cantidadVitrina FROM Producto WHERE idProducto=?");
    query.bindValue(0,idProducto);
    query.exec();
    cantidadVitrina=query.value(0).toInt() + tmp;

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
    query.exec();
    cantidadAlmacen=query.value(0).toInt() + tmp;

    query.prepare("UPDATE Producto SET cantidadAlmacen=? WHERE idProducto=?");
    query.bindValue(0,cantidadAlmacen);
    query.bindValue(1,idProducto);
    query.exec();
}

void producto::almacenToVitrina()
{
    cantidadAlmacen--;
    cantidadVitrina++;
    QSqlQuery query;
    query.prepare("UPDATE Producto SET cantidadVitrina=? WHERE idProducto=?");
    query.bindValue(0,cantidadVitrina);
    query.bindValue(1,idProducto);
    query.exec();
    //cantidadVitrina

    query.prepare("UPDATE Producto SET cantidadAlmacen=? WHERE idProducto=?");
    query.bindValue(0,cantidadAlmacen);
    query.bindValue(1,idProducto);
    query.exec();
}

//setColaborador
