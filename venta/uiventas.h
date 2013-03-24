#ifndef UIVENTAS_H
#define UIVENTAS_H

#include <QWidget>

namespace Ui {
class uiventas;
}

class uiventas : public QWidget
{
    Q_OBJECT
    
public:
    explicit uiventas(QWidget *parent = 0);
    ~uiventas();
    
private:
    Ui::uiventas *ui;
};

#endif // UIVENTAS_H
