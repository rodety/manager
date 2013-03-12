#ifndef CALIDAD_H
#define CALIDAD_H

#include <objetopersistente.h>

class calidad:public ObjetoPersistente
{
private:
    QString idCalidad;
    QString nombre;
public:
    calidad();

    QString getIdCalidad();
    QString getNombre();

    void setIdCalidad(QString tmp);
    void setNombre(QString tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();
};

#endif // CALIDAD_H
