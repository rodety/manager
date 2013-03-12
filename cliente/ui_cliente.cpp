#include "ui_cliente.h"
#include "ui_ui_cliente.h"
#include <QSqlRecord>
#include <QSqlQueryModel>

ui_cliente::ui_cliente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_cliente)
{
    ui->setupUi(this);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->tableView, SIGNAL (doubleClicked (const QModelIndex & )), this, SLOT (historial_clinico(const QModelIndex & )));
    connect(ui->tableView_2, SIGNAL (doubleClicked (const QModelIndex & )), this, SLOT (medidas_historial(const QModelIndex & )));
    ui->tabWidget->setTabEnabled(1,0);
    ui->tabWidget->setCurrentIndex(0);
    this->listar_clientes();
}

ui_cliente::~ui_cliente()
{
    delete ui;
}

void ui_cliente::listar_clientes()
{
    ui->tableView->setModel(cliente::mostrar());
}

void ui_cliente::listar_historial()
{
    historialClinico historial;
    historial.setIdCliente(clt_his.getIdCliente());
    ui->tableView_2->setModel(historial.mostrar());

    ui->lineEdit_ecd->setText("");
    ui->lineEdit_eci->setText("");
    ui->lineEdit_eld->setText("");
    ui->lineEdit_eli->setText("");
    ui->lineEdit_ccd->setText("");
    ui->lineEdit_cci->setText("");
    ui->lineEdit_cld->setText("");
    ui->lineEdit_cli->setText("");
    ui->lineEdit_ejcd->setText("");
    ui->lineEdit_ejci->setText("");
    ui->lineEdit_ejld->setText("");
    ui->lineEdit_ejli->setText("");
    ui->lineEdit_dcd->setText("");
    ui->lineEdit_dci->setText("");
    ui->lineEdit_dld->setText("");
    ui->lineEdit_dli->setText("");
}

void ui_cliente::historial_clinico(const QModelIndex &model)
{
    int fila=model.row();
    if(fila!=-1)
    {
        persona persona_selec;
        persona_selec.setNombres(ui->tableView->model()->data(ui->tableView->model()->index(fila,0)).toString());
        persona_selec.setPrimerApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,1)).toString());
        persona_selec.setSegundoApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,2)).toString());
        if(persona_selec.buscar())
        {
            clt_his.setIdCliente(persona_selec.getIdPersona());
            if(clt_his.buscar())
            {
                ui->tabWidget->setCurrentIndex(1);
                listar_historial();
            }
        }
    }
}

void ui_cliente::medidas_historial(const QModelIndex &model)
{
    int fila=model.row();
    if(fila!=-1)
    {
        historialClinico historial;
        historial.setDoctor(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,0)).toString());
        historial.setFecha(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,1)).toString());
        historial.setIdCliente(clt_his.getIdCliente());
        if(historial.buscar())
        {
            ui->lineEdit_ecd->setText(historial.getMedidasCercaDerecha().getEsferico());
            ui->lineEdit_eci->setText(historial.getMedidasCercaIzquierda().getEsferico());
            ui->lineEdit_eld->setText(historial.getMedidasLejosDerecha().getEsferico());
            ui->lineEdit_eli->setText(historial.getMedidasLejosIzquierda().getEsferico());
            ui->lineEdit_ccd->setText(historial.getMedidasCercaDerecha().getCilindrico());
            ui->lineEdit_cci->setText(historial.getMedidasCercaIzquierda().getCilindrico());
            ui->lineEdit_cld->setText(historial.getMedidasLejosDerecha().getCilindrico());
            ui->lineEdit_cli->setText(historial.getMedidasLejosIzquierda().getCilindrico());
            ui->lineEdit_ejcd->setText(historial.getMedidasCercaDerecha().getEje());
            ui->lineEdit_ejci->setText(historial.getMedidasCercaIzquierda().getEje());
            ui->lineEdit_ejld->setText(historial.getMedidasLejosDerecha().getEje());
            ui->lineEdit_ejli->setText(historial.getMedidasLejosIzquierda().getEje());
            ui->lineEdit_dcd->setText(historial.getMedidasCercaDerecha().getDistanciaPupilar());
            ui->lineEdit_dci->setText(historial.getMedidasCercaIzquierda().getDistanciaPupilar());
            ui->lineEdit_dld->setText(historial.getMedidasLejosDerecha().getDistanciaPupilar());
            ui->lineEdit_dli->setText(historial.getMedidasLejosIzquierda().getDistanciaPupilar());
        }
    }
}

void ui_cliente::on_tabWidget_currentChanged(int index)
{
    if(index==0)
    {
        ui->tabWidget->setTabEnabled(1,0);
        ui->buscar->setEnabled(1);
        ui->pushButton_buscar->setEnabled(1);
    }
    else
    {
        ui->tabWidget->setTabEnabled(1,1);
        ui->buscar->setEnabled(0);
        ui->pushButton_buscar->setEnabled(0);
    }
}



void ui_cliente::on_pushButton_clicked()
{
    ui_cliente_datos* cliente_agregar=new ui_cliente_datos;
    cliente_agregar->setWindowTitle("Nuevo Cliente");
    cliente_agregar->show();
    connect(cliente_agregar,SIGNAL(guarde()),this,SLOT(listar_clientes()));
}

void ui_cliente::on_pushButton_2_clicked()
{
    int fila=ui->tableView->currentIndex().row();
    if(fila!=-1)
    {
        persona persona_selec;
        persona_selec.setNombres(ui->tableView->model()->data(ui->tableView->model()->index(fila,0)).toString());
        persona_selec.setPrimerApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,1)).toString());
        persona_selec.setSegundoApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,2)).toString());
        if(persona_selec.buscar())
        {
            cliente cliente_selec;
            cliente_selec.setIdCliente(persona_selec.getIdPersona());
            if(cliente_selec.buscar())
            {
                ui_cliente_datos* cliente_actualizar=new ui_cliente_datos;
                cliente_actualizar->setWindowTitle("Editar Cliente");
                cliente_actualizar->setCliente(&persona_selec);
                cliente_actualizar->show();
                connect(cliente_actualizar,SIGNAL(guarde()),this,SLOT(listar_clientes()));
            }
        }
    }
}

void ui_cliente::on_pushButton_3_clicked()
{
    int fila=ui->tableView->currentIndex().row();
    if(fila!=-1)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Question);
        box.setWindowTitle("Advertencia");
        box.setText("Esta seguro de eliminar a este cliente?");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        switch(ret)
        {
            case QMessageBox::Ok:
            {
                persona persona_selec;
                persona_selec.setNombres(ui->tableView->model()->data(ui->tableView->model()->index(fila,0)).toString());
                persona_selec.setPrimerApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,1)).toString());
                persona_selec.setSegundoApellido(ui->tableView->model()->data(ui->tableView->model()->index(fila,2)).toString());
                if(persona_selec.buscar())
                {
                    cliente cliente_selec;
                    cliente_selec.setIdCliente(persona_selec.getIdPersona());
                    if(cliente_selec.buscar())
                    {
                        cliente_selec.eliminar();
                        listar_clientes();
                    }
                }
                break;
            }
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    }
}

void ui_cliente::on_NuevoHistorial_clicked()
{
    ui_historial_clinico* historial=new ui_historial_clinico;
    historial->setWindowTitle("Nuevo Historial");
    historial->setCliente(&clt_his);
    historial->show();
    connect(historial,SIGNAL(guarde()),this,SLOT(listar_historial()));
}

void ui_cliente::on_EditarHistorial_clicked()
{
    int fila=ui->tableView_2->currentIndex().row();
    if(fila!=-1)
    {
        historialClinico historial_selec;
        historial_selec.setIdCliente(clt_his.getIdCliente());
        historial_selec.setDoctor(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,0)).toString());
        historial_selec.setFecha(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,1)).toString());
        if(historial_selec.buscar())
        {
            ui_historial_clinico* historial_cliente=new ui_historial_clinico;
            historial_cliente->setWindowTitle("Editar Historial");
            historial_cliente->setCliente(&clt_his);
            historial_cliente->setHistorial(&historial_selec);
            historial_cliente->show();
            connect(historial_cliente,SIGNAL(guarde()),this,SLOT(listar_historial()));
        }
    }
}

void ui_cliente::on_BorrarHistorial_clicked()
{
    int fila=ui->tableView_2->currentIndex().row();
    if(fila!=-1)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Question);
        box.setWindowTitle("Advertencia");
        box.setText("Esta seguro de eliminar este historial?");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        switch(ret)
        {
            case QMessageBox::Ok:
            {
                historialClinico historial_selec;
                historial_selec.setIdCliente(clt_his.getIdCliente());
                historial_selec.setDoctor(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,0)).toString());
                historial_selec.setFecha(ui->tableView_2->model()->data(ui->tableView_2->model()->index(fila,1)).toString());
                if(historial_selec.buscar())
                {
                    historial_selec.eliminar();
                    listar_historial();
                }
                break;
            }
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    }
}

void ui_cliente::on_pushButton_buscar_clicked()
{
    QString buscar;
    buscar=ui->buscar->text();
    if(ui->tabWidget->currentIndex()==0)
    {
        QSqlQueryModel* model=cliente::buscarCliente(buscar);
        ui->tableView->setModel(model);
    }
    else
    {
        /*historialClinico historial;
        QSqlQueryModel* model=historial.buscarHistorial(buscar);
        ui->tableView_2->setModel(model);*/
    }
}

void ui_cliente::on_pushButton_Informe_clicked()
{
    if(ui->tableView_2->model()->rowCount()<2)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Advertencia");
        box.setText("Deben de existir mas de 2 historiales!!!");
        box.setStandardButtons(QMessageBox::Ok);
        box.setDefaultButton(QMessageBox::Ok);
        box.exec();
    }
    else
    {
        QList<historialClinico>* lista=new QList<historialClinico>;
        for(int i=0;i<ui->tableView_2->model()->rowCount();i++)
        {
            historialClinico h;
            h.setIdCliente(clt_his.getIdCliente());
            h.setDoctor(ui->tableView_2->model()->data(ui->tableView_2->model()->index(i,0)).toString());
            h.setFecha(ui->tableView_2->model()->data(ui->tableView_2->model()->index(i,1)).toString());
            h.buscar();
            lista->append(h);
        }
        ui_medidas_historial* form=new ui_medidas_historial;
        form->setHistoriales(lista);
        form->show();
    }
}
