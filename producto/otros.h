#ifndef OTROS_H
#define OTROS_H

#include <producto/producto.h>

class otros:public producto
{
private:
    color pColor;
    talla pTalla;
    calidad pCalidad;
public:
    otros();

    color getColor();
    talla getTalla();
    calidad getCalidad();

    void setColor(color tmp);
    void setTalla(talla tmp);
    void setCalidad(calidad tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();
};

#endif // OTROS_H
