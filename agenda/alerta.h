#ifndef ALERTA_H
#define ALERTA_H
#include <objetopersistente.h>

class alerta:ObjetoPersistente
{

private:
    QString idAlerta;
    QString idColaborador;
    QString fecha;
    QString hora;
    QString descripcion;
    QString color;
    QString tipo;
public:
    alerta();
    void setIdAlerta(QString tmp);
    void setIdColaborador(QString tmp);
    void setfecha(QString tmp);
    void sethora(QString tmp);
    void setdescripcion(QString tmp);
    void setcolor(QString tmp);
    void settipo(QString tmp);

    QString getIdAlerta();
    QString getIdColaborador();
    QString getfecha();
    QString gethora();
    QString getdescripcion();
    QString getcolor();
    QString gettipo();



    bool agregar();
    bool actualizar();
    bool eliminar();

    static QSqlQueryModel* mostrar(int);
    bool completar();

    static QSqlQueryModel* buscarAlerta(QString _item);
};

#endif // ALERTA_H
