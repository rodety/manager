#ifndef LUNA_H
#define LUNA_H

#include <producto/producto.h>

class luna:public producto
{
private:
    diametro pDiametro;
    calidad pCalidad;
    tipoLuna pTipoLuna;
    tratamiento pTratamiento;
    QString valorInicial;
    QString valorFinal;
    QString precio;
public:
    luna();

    diametro getDiametro();
    calidad getCalidad();
    tipoLuna getTipoLuna();
    tratamiento getTratamiento();
    QString getValorInicial();
    QString getValorFinal();
    QString getPrecio();

    void setDiametro(diametro tmp);
    void setCalidad(calidad tmp);
    void setTipoLuna(tipoLuna tmp);
    void setTratamiento(tratamiento tmp);
    void setValorInicial(QString tmp);
    void setValorFinal(QString tmp);
    void setPrecio(QString tmp);

    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar();
    bool completar();

    bool verificarPrecio();
};

#endif // LUNA_H
