#ifndef MARCA_H
#define MARCA_H

#include <objetopersistente.h>

class marca:public ObjetoPersistente
{
private:
    QString idMarca;
    QString nombre;
public:
    marca();

    QString getIdMarca();
    QString getNombre();

    void setIdMarca(QString tmp);
    void setNombre(QString tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();
};

#endif // MARCA_H
