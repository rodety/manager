#ifndef TRABAJOSEXTRAS_H
#define TRABAJOSEXTRAS_H

#include <objetopersistente.h>

class trabajosExtras:public ObjetoPersistente
{
private:
    QString idTrabajosExtras;
    QString descripcion;
    QString precio;
public:
    trabajosExtras();

    QString getIdTrabajosExtras();
    QString getDescripcion();
    QString getPrecio();

    void setIdTrabajosExtras(QString tmp);
    void setDescripcion(QString tmp);
    void setPrecio(QString tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();
};

#endif // TRABAJOSEXTRAS_H
