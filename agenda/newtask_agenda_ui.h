#ifndef NEWTASK_AGENDA_UI_H
#define NEWTASK_AGENDA_UI_H

#include <QWidget>
#include "agenda_ui.h"


namespace Ui {
    class newTask_agenda_ui;
}

class newTask_agenda_ui : public QWidget
{
    Q_OBJECT

public:
    explicit newTask_agenda_ui(QWidget *parent = 0);
    ~newTask_agenda_ui();

    void set_cliked_type(int type);
    void show_data_task_form(QString code);
    void setDate(QDate);
    void enableDate(bool);
    void setTitle(QString);
    void hideButton();
    agenda_ui* parent_ui_form;
    QString dni_task;
    QString code_task;

private slots:
    void on_pushButton_Acept_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_nombre_clicked();
    void on_pushButton_apellido_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_lineEdit_PacienteSearch_returnPressed();
    void on_lineEdit_Name_returnPressed();

private:
    Ui::newTask_agenda_ui *ui;
};

#endif // NEWTASK_AGENDA_UI_H
