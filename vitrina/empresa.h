#ifndef EMPRESA_H
#define EMPRESA_H

#include <objetopersistente.h>
#include <QSqlQueryModel>

class empresa:public ObjetoPersistente
{
    private:
        QString id;
        QString ruc;
        QString razonSocial;
        QString domilicioFiscal;
        QString telefono;

    public:
        empresa();
        empresa(QString idEmpresa,QString ruc,QString raz_social,QString domicilio,QString telefono);
        QString getId();
        QString getRuc();
        QString getrazonSocial();
        QString getDomilicioFiscal();
        QString getTelefono();

        void setId(QString);
        void setRuc(QString);
        void setRazonSocial(QString);
        void setDomicilioFiscal(QString);
        void setTelefono(QString);
        bool agregar();
        bool actualizar();
        bool eliminar();


};

#endif // EMPRESA_H
