#ifndef UIVENTAS_H
#define UIVENTAS_H

#include <QWidget>
#include <cliente/ui_cliente.h>
#include <producto/ui_producto.h>
#include <configuracion/tusuario.h>

namespace Ui {
class uiventas;
}

class uiventas : public QWidget
{
    Q_OBJECT
    
public:
    explicit uiventas(QWidget *parent = 0);
    ~uiventas();

private slots:
    void on_pushButton_buscarCliente_clicked();
    void recojeCliente(QString,QString,QString);
    void on_pushButton_buscarProducto_clicked();
    void recojeProducto(QString,QString,QString,QString,int);

private:
    Ui::uiventas *ui;
    int count_row;
};

#endif // UIVENTAS_H
