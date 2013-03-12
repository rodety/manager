#ifndef CONTENEDOR_H
#define CONTENEDOR_H

#include "objetopersistente.h"

class contenedor:public ObjetoPersistente
{
private:
    QString idContenedor;
    QString idAndamio;
    QString nombre;
    QString descripcion;
    QString pos_fila;
    QString pos_columna;
    QString capacidad;



public:

    contenedor();
    contenedor(QString,QString,QString,QString,QString,QString,QString);

    QString getIdContenedor();
    QString getIdAndamio();
    QString getNombre();
    QString getDescripcion();
    QString getPosFila();
    QString getPosColumna();
    QString getCapacidad();

    void setIdContenedor(QString);
    void setIdAndamio(QString);
    void setNombre(QString);
    void setDescripcion(QString);
    void setPosFila(QString);
    void setPosColumna(QString);
    void setCapacidad(QString);

    bool agregar();
    bool actualizar();
    bool eliminar();
};

#endif // CONTENEDOR_H
