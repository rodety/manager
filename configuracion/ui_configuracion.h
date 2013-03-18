#ifndef UI_CONFIGURACION_H
#define UI_CONFIGURACION_H

#include <QWidget>

namespace Ui {
class ui_configuracion;
}

class ui_configuracion : public QWidget
{
    Q_OBJECT
    
public:
    explicit ui_configuracion(QWidget *parent = 0);
    ~ui_configuracion();
    
private:
    Ui::ui_configuracion *ui;
};

#endif // UI_CONFIGURACION_H
