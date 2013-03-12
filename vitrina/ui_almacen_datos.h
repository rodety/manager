#ifndef UI_ALMACEN_DATOS_H
#define UI_ALMACEN_DATOS_H

#include <QWidget>
#include <vitrina/ui_almacen.h>

namespace Ui {
class ui_almacen_datos;
}

class ui_almacen_datos : public QWidget
{
    Q_OBJECT
private:

    QString idTienda;
    ui_almacen *ui_almacen_parent;
    int behavior;

public:

    QString get_idTienda();
    void set_idTienda(QString);

    ui_almacen* get_ui_almacen_parent();
    void set_ui_almacen_parent(ui_almacen*);

    int get_behavior();
    void set_behavior(int);

    void update_form();

public:
    explicit ui_almacen_datos(QWidget *parent = 0);
    ~ui_almacen_datos();
    
private slots:
    void on_pushButton_cancelar_clicked();

    void on_pushButton_aceptar_clicked();

private:
    Ui::ui_almacen_datos *ui;
};

#endif // UI_ALMACEN_DATOS_H
