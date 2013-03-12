#ifndef UI_CONTENEDOR_DATOS_H
#define UI_CONTENEDOR_DATOS_H

#include <QWidget>
#include "ui_almacen.h"

namespace Ui {
class ui_contenedor_datos;
}

class ui_contenedor_datos : public QWidget
{
    Q_OBJECT
private:

    QString idContenedor;
    ui_almacen* ui_almacen_parent;
    int behavior;


public:

    QString get_idContenedor();
    void set_idContenedor(QString);

    ui_almacen* get_ui_almacen_parent();
    void set_ui_almacen_parent(ui_almacen*);

    int get_behavior();
    void set_behavior(int);

    void set_spinBox_fila(int);
    void set_spinBox_columna(int);

    void clear_widget_list_productos();
    void uptate_widget_list_productos();
    void update_form();


public:
    explicit ui_contenedor_datos(QWidget *parent = 0);
    ~ui_contenedor_datos();
    
private slots:
    void on_pushButton_salir_clicked();

    void on_pushButton_addProducto_clicked();

    void on_pushButton_saveContenedor_clicked();

    void on_pushButton_deleteContenedor_clicked();

    void on_pushButton_deleteProducto_clicked();

    void on_traspaso_clicked();

private:
    Ui::ui_contenedor_datos *ui;
};

#endif // UI_CONTENEDOR_DATOS_H
