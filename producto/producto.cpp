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
