#ifndef COMPRA_H
#define COMPRA_H
#include <QString>
class compra
{
public:
    compra();
    void setDatosProveedor(QString a,QString b,QString c,QString d);
    QString getidProveedor(){return idProveedor;}
    QString getruc(){return ruc;}
    QString getrazonSocial(){return razonSocial;}
    QString getDireccion(){return Direccion;}
private:
    QString idProveedor;
    QString ruc;
    QString razonSocial;
    QString Direccion;

};

#endif // COMPRA_H
