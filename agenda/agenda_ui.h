#ifndef AGENDA_UI_H
#define AGENDA_UI_H

#include <QWidget>
#include <QTableWidget>
#include "funciones.h"
#include "newalerta_alerta_ui.h"
//hello
namespace Ui {
    class agenda_ui;
}

class agenda_ui : public QWidget
{
    Q_OBJECT

public:
    explicit agenda_ui(QWidget *parent = 0);
    ~agenda_ui();

    void show_personal_combox();
    void set_access_level(int access);
    int access_user_type;
    void update_table_agenda_form();
    void update_table_alerta_personal();
    QString curren_user_code_var;
    QString code_var_alerta_general;
    QString code_var_alerta_personal;

private:
    Ui::agenda_ui *ui;

private slots:
    void on_pushButton_newTask_clicked();
    void on_pushButton_showTask_clicked();
    void on_pushButton_editTask_clicked();
    void on_pushButton_deleteTask_clicked();
    void on_pushButton_showAll_clicked();
    void on_comboBox_Names_currentIndexChanged(int index);
    void on_dateEdit_Agenda_dateChanged(const QDate &date);
    void on_tablaView_Agend_itemClicked(QTableWidgetItem *item);

    void on_dateEdit_Alerta_dateChanged(const QDate &date);

    void on_comboBox_dni_currentIndexChanged(const QString &arg1);
    void on_pushButton_showSelect_clicked();
    void on_pushButton_show_SelectAlert_clicked();
    void on_pushButton_Alerta_General_show_clicked();

    void on_tableWidget_Alert_itemClicked(QTableWidgetItem *item);
    void on_pushButton_AlertaGeneral_changeColor_clicked();
    void on_pushButton_Alert_Personales_add_clicked();

    void on_dateEdit_Alerta_Personales_dateChanged(const QDate &date);
    void on_pushButton_show_SelectAlert_Personales_4_clicked();
    void on_pushButton_Alert_Personal_changeColor_clicked();

    void on_tableWidget_Alert_Personales_itemClicked(QTableWidgetItem *item);
    void on_pushButton_Alert_Personal_show_clicked();
    void on_pushButton_Alert_Personales_edit_clicked();
    void on_pushButton_Alert_Personales_remove_clicked();
    void on_pushButton_show_Agenda_clicked();
    void on_pushButton_agenda_changeColor_clicked();
    void on_pushButton_update_Agenda_clicked();
    void on_comboBox_dni_currentIndexChanged(int index);

    void on_calendarWidget_clicked(const QDate &date);

    void on_tablaView_Agend_doubleClicked(const QModelIndex &index);
    void on_pushButton_printList_clicked();

    void on_pushButton_Alert_General_add_clicked();
};

#endif // AGENDA_UI_H

