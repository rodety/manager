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
