#ifndef NEWALERTA_ALERTA_UI_H
#define NEWALERTA_ALERTA_UI_H

#include <QSqlQuery>
#include <QWidget>


class alertas_ui;
class agenda_ui;

namespace Ui {
    class newalerta_alerta_ui;
}

class newalerta_alerta_ui : public QWidget
{
    Q_OBJECT

public:
    explicit newalerta_alerta_ui(QWidget *parent = 0);
    ~newalerta_alerta_ui();
    void set_clicked_type(int type);
    void update_new_alerta_form(QString code);
    QString code_var;
    QString alert_type_var;    
    void create_alert(QString type);
    void set_type_alerta(int t){type_alert = t;}


private slots:
    void on_pushButton_Acept_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Save_clicked();
public slots:
signals:
    void updateChange();



private:
    Ui::newalerta_alerta_ui *ui;
    int type_alert;
};

#endif // NEWALERTA_ALERTA_UI_H
