#ifndef ALERTAS_UI_H
#define ALERTAS_UI_H

#include <QWidget>
#include "newalerta_alerta_ui.h"
#include <QTableWidget>
#include "funciones.h"

namespace Ui {
    class alertas_ui;
}

class alertas_ui : public QWidget
{
    Q_OBJECT

public:
    explicit alertas_ui(QWidget *parent = 0);
    ~alertas_ui();

    void update_table_alert();
    void set_access_level(int access);

    void update_table_alert_day();

private:
    Ui::alertas_ui *ui;

private slots:


private slots:
    void on_newAlert_alerta_clicked();
    void on_editar_alerta_clicked();
    void on_verAlerta_clicked();
    void on_pushButton_showAll_clicked();
    void on_tableWidget_AlertList_itemClicked(QTableWidgetItem *item);
    void on_eliminar_alerta_clicked();
    void on_dateEdit_dateChanged(const QDate &date);

    void on_pushButton_Alert_changeColor_clicked();
    void on_dateEdit_editingFinished();
};

#endif // ALERTAS_UI_H
