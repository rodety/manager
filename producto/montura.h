#ifndef MONTURA_H
#define MONTURA_H

#include <producto/producto.h>

class montura:public producto
{
private:
    forma pForma;
    color pColor;
    tamanio pTamanio;
    calidad pCalidad;
public:
    montura();

    forma getForma();
    color getColor();
    tamanio getTamanio();
    calidad getCalidad();

    void setForma(forma tmp);
    void setColor(color tmp);
    void setTamanio(tamanio tmp);
    void setCalidad(calidad tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();
};

#endif // MONTURA_H
