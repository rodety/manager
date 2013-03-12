#ifndef UI_TIENDA_AGREGAR_H
#define UI_TIENDA_AGREGAR_H

#include <QDialog>
#include <vitrina/ui_tienda.h>

namespace Ui {
class ui_tienda_agregar;
}

class ui_tienda_agregar : public QDialog
{
    Q_OBJECT
private:
    bool caso;
    QString idEmpresa;
    ui_tienda * ui_tienda_actual;

public:
    bool get_caso(){return caso;}
    QString get_idEmpresa(){return idEmpresa;}
    ui_tienda* get_ui_tienda_actual(){return ui_tienda_actual;}

    void set_caso(bool tmp){caso=tmp;}
    void set_idEmpresa(QString tmp){idEmpresa=tmp;}
    void set_ui_tienda_actual(ui_tienda* tmp){ui_tienda_actual=tmp;}
    void actualizar();
    bool validar_tienda();

public:
    explicit ui_tienda_agregar(QWidget *parent = 0);
    ~ui_tienda_agregar();
    
private slots:
    void on_pushButton_Aceptar_clicked();

    void on_pushButton_Cancelar_clicked();

private:
    Ui::ui_tienda_agregar *ui;
};

#endif // UI_TIENDA_AGREGAR_H
