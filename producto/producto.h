#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <objetopersistente.h>

#include <producto/estado.h>
#include <producto/marca.h>
#include <producto/forma.h>
#include <producto/color.h>
#include <producto/tamanio.h>
#include <producto/calidad.h>
#include <producto/diametro.h>
#include <producto/tipoluna.h>
#include <producto/tratamiento.h>
#include <producto/tipolente.h>
#include <producto/potencia.h>
#include <producto/curvabase.h>
#include <producto/tiempouso.h>
#include <producto/material.h>
#include <producto/talla.h>

class producto:public ObjetoPersistente
{
protected:
    QString idProducto;
    QString codigo;
    QString descripcion;
    QString precioCompra;
    QString precioVenta;
    QString precioDescuento;
    QString accesorios;
    QString stock;
    QString observaciones;
    estado pEstado;
    marca pMarca;
    int cantidadVitrina;
    int cantidadAlmacen;

    //colaborador
public:
    producto();

    QString getIdProducto();
    QString getCodigo();
    QString getDescripcion();
    QString getPrecioCompra();
    QString getPrecioVenta();
    QString getPrecioDescuento();
    QString getAccesorios();
    QString getStock();
    QString getObservaciones();
    estado getEstado();
    marca getMarca();
    //getColaborador

    void setIdProducto(QString tmp);
    void setCodigo(QString tmp);
    void setDescripcion(QString tmp);
    void setPrecioCompra(QString tmp);
    void setPrecioVenta(QString tmp);
    void setPrecioDescuento(QString tmp);
    void setAccesorios(QString tmp);
    void setStock(QString tmp);
    void setObservaciones(QString tmp);
    void setEstado(estado tmp);
    void setMarca(marca tmp);
    void addToVitrina();
    void addToAlmacen(int tmp=1);
    void almacenToVitrina();    //se debe de borrar si es que cantidadAlmacen llega a 0
    void vitrinaToAlmacen();
    //setColaborador
};

#endif // PRODUCTO_H
