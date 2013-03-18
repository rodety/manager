#include "ui_configuracion.h"
#include "ui_ui_configuracion.h"

ui_configuracion::ui_configuracion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_configuracion)
{
    ui->setupUi(this);
}

ui_configuracion::~ui_configuracion()
{
    delete ui;
}


void ui_configuracion::on_btn_testConexion_clicked()
{
    QString ip = ui->lineEdit_ipdatabase->text();
    //QString port = ui->lineEdit_//
}
