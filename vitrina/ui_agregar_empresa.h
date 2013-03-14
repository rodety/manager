#ifndef UI_AGREGAR_EMPRESA_H
#define UI_AGREGAR_EMPRESA_H

#include <QWidget>
#include "ui_tienda.h"

namespace Ui {
class ui_agregar_empresa;
}

class ui_agregar_empresa : public QWidget
{
    Q_OBJECT
private:
    QString idEmpresa;
    ui_tienda* ui_empresa_parent;
    int behavior;
public:
    void set_idEmpresa(QString idEmpresa);
    QString get_idEmpresa();

    void set_ui_empresa_parent(ui_tienda* parent);
    ui_tienda* get_ui_empresa_parent();

    int get_behavior();
    void set_behavior(int);
    void update_form();

    
public:
    explicit ui_agregar_empresa(QWidget *parent = 0);
    ~ui_agregar_empresa();
    
private slots:
    void on_pushButton_accept_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ui_agregar_empresa *ui;
};

#endif // UI_AGREGAR_EMPRESA_H
