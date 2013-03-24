#include "uiventas.h"
#include "ui_uiventas.h"

uiventas::uiventas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiventas)
{
    ui->setupUi(this);
}

uiventas::~uiventas()
{
    delete ui;
}
