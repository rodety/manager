#include "ui_agregarluna.h"
#include "ui_ui_agregarluna.h"

ui_agregarLuna::ui_agregarLuna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_agregarLuna)
{
    ui->setupUi(this);

    ui->comboBox_diametro->setTipo("diametro");
    ui->comboBox_diametro->ActualizarItems(diametro::mostrar());
    ui->comboBox_calidad->setTipo("calidad");
    ui->comboBox_calidad->ActualizarItems(calidad::mostrar());
    ui->comboBox_tipoLuna->setTipo("tipoLuna");
    ui->comboBox_tipoLuna->ActualizarItems(tipoLuna::mostrar());
    ui->comboBox_tratamiento->setTipo("tratamiento");
    ui->comboBox_tratamiento->ActualizarItems(tratamiento::mostrar());
    ui->comboBox_estado->setTipo("estado");
    ui->comboBox_estado->ActualizarItems(estado::mostrar());
    modo=0;

    ui->label_estado->hide();
    ui->comboBox_estado->hide();
    ui->pushButton_xEstado->hide();
    ui->label_precio->hide();
    ui->checkBox_precio->hide();
}

ui_agregarLuna::~ui_agregarLuna()
{
    delete ui;
}

void ui_agregarLuna::setModo(bool m)
{
    modo=m;
}

void ui_agregarLuna::setLuna(luna *l)
{
    pLuna=*l;
    ui->lineEdit_descripcion->setText(pLuna.getDescripcion());
    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
    ui->spinBox_stock->setValue(pLuna.getStock().toInt());
    ui->lineEdit_observaciones->setText(pLuna.getObservaciones());
    ui->comboBox_estado->buscarValor(pLuna.getEstado().getNombre());
    ui->checkBox_precio->setChecked(pLuna.getPrecio().toInt());
    ui->comboBox_diametro->buscarValor(pLuna.getDiametro().getValor());
    ui->comboBox_calidad->buscarValor(pLuna.getCalidad().getNombre());
    ui->comboBox_tipoLuna->buscarValor(pLuna.getTipoLuna().getNombre());
    ui->comboBox_tratamiento->buscarValor(pLuna.getTratamiento().getNombre());
    ui->lineEdit_vInicial->setText(pLuna.getValorInicial());
    ui->lineEdit_vFinal->setText(pLuna.getValorFinal());
    if(pLuna.getPrecio().toInt()==1)
    {
        ui->label_precio->show();
        ui->checkBox_precio->show();
    }
    else
    {
        if(verificarSelecciones())
        {
            if(pLuna.verificarPrecio())
            {
                ui->label_precio->hide();
                ui->checkBox_precio->hide();
            }
            else
            {
                ui->label_precio->show();
                ui->checkBox_precio->show();
            }
        }
    }
    ui->label_estado->show();
    ui->comboBox_estado->show();
    ui->pushButton_xEstado->show();
}

bool ui_agregarLuna::verificarRestricciones()
{
    QRegExp noNumeros("[a-zA-Z]");
    QRegExp noAlfabeto("[0-9\.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");

    if(ui->lineEdit_precioCompra->text().contains(noNumeros))
    {
        box.setText("El Precio de Compra solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioCompra->setFocus();
        return false;
    }
    if(ui->lineEdit_precioCompra->text().size() == 0)
    {
        box.setText("El Precio de Compra es obligatorio");
        box.exec();
        ui->lineEdit_precioCompra->setFocus();
        return false;
    }
    if(ui->lineEdit_precioVenta->text().contains(noNumeros))
    {
        box.setText("El Precio de Venta solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioVenta->setFocus();
        return false;
    }
    if(ui->lineEdit_precioVenta->text().size() == 0)
    {
        box.setText("El Precio de Venta es obligatorio");
        box.exec();
        ui->lineEdit_precioVenta->setFocus();
        return false;
    }
    if(ui->lineEdit_precioDescuento->text().contains(noNumeros))
    {
        box.setText("El Precio de Descuento solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioDescuento->setFocus();
        return false;
    }
    if(ui->lineEdit_precioDescuento->text().size() == 0)
    {
        box.setText("El Precio de Descuento es obligatorio");
        box.exec();
        ui->lineEdit_precioDescuento->setFocus();
        return false;
    }
    if(modo==1)
        if(!ui->comboBox_estado->selecciono())
        {
            box.setText("Seleccione algun Estado");
            box.exec();
            ui->comboBox_estado->setFocus();
            return false;
        }
    if(!ui->comboBox_diametro->selecciono())
    {
        box.setText("Seleccione algun Diametro");
        box.exec();
        ui->comboBox_diametro->setFocus();
        return false;
    }
    if(!ui->comboBox_calidad->selecciono())
    {
        box.setText("Seleccione alguna Calidad");
        box.exec();
        ui->comboBox_calidad->setFocus();
        return false;
    }
    if(!ui->comboBox_tipoLuna->selecciono())
    {
        box.setText("Seleccione algun Tipo de Luna");
        box.exec();
        ui->comboBox_tipoLuna->setFocus();
        return false;
    }
    if(!ui->comboBox_tratamiento->selecciono())
    {
        box.setText("Seleccione algun tratamiento");
        box.exec();
        ui->comboBox_tratamiento->setFocus();
        return false;
    }
    if(ui->lineEdit_vInicial->text().contains(noNumeros))
    {
        box.setText("El Valor Inicial solo puede contener numeros");
        box.exec();
        ui->lineEdit_vInicial->setFocus();
        return false;
    }
    if(ui->lineEdit_vInicial->text().size() == 0)
    {
        box.setText("El Valor Inicial es obligatorio");
        box.exec();
        ui->lineEdit_vInicial->setFocus();
        return false;
    }
    if(ui->lineEdit_vFinal->text().contains(noNumeros))
    {
        box.setText("El Valor Final solo puede contener numeros");
        box.exec();
        ui->lineEdit_vFinal->setFocus();
        return false;
    }
    if(ui->lineEdit_vFinal->text().size() == 0)
    {
        box.setText("El Valor Final es obligatorio");
        box.exec();
        ui->lineEdit_vFinal->setFocus();
        return false;
    }
    return true;
}

void ui_agregarLuna::on_pushButton_aceptar_clicked()
{
    if(!verificarRestricciones())
        return;
    pLuna.setDescripcion(ui->lineEdit_descripcion->text());
    pLuna.setPrecioCompra(ui->lineEdit_precioCompra->text());
    pLuna.setPrecioVenta(ui->lineEdit_precioVenta->text());
    pLuna.setPrecioDescuento(ui->lineEdit_precioDescuento->text());
    pLuna.setStock(ui->spinBox_stock->text());
    pLuna.setObservaciones(ui->lineEdit_observaciones->text());
    estado pEstado;pEstado.setNombre(ui->comboBox_estado->currentText());pEstado.completar();
    //colaborador
    diametro pDiametro;pDiametro.setValor(ui->comboBox_diametro->currentText());pDiametro.completar();
    calidad pCalidad;pCalidad.setNombre(ui->comboBox_calidad->currentText());pCalidad.completar();
    tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->comboBox_tipoLuna->currentText());pTipoLuna.completar();
    tratamiento pTratamiento;pTratamiento.setNombre(ui->comboBox_tratamiento->currentText());pTratamiento.completar();
    pLuna.setValorInicial(ui->lineEdit_vInicial->text());
    pLuna.setValorFinal(ui->lineEdit_vFinal->text());
    if(ui->checkBox_precio->isChecked())
        pLuna.setPrecio("1");
    else
        pLuna.setPrecio("0");
    pLuna.setEstado(pEstado);
    //colaborador
    pLuna.setDiametro(pDiametro);
    pLuna.setCalidad(pCalidad);
    pLuna.setTipoLuna(pTipoLuna);
    pLuna.setTratamiento(pTratamiento);
    if(modo==0)//agrego
    {
        pEstado.setNombre("activo");pEstado.completar();
        pLuna.setEstado(pEstado);
        if(pLuna.agregar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El producto no se pudo agregar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
    else//actualizo
    {
        if(pLuna.actualizar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El producto no se pudo actualizar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
}


void ui_agregarLuna::on_pushButton_xDiametro_clicked()
{
    ui->comboBox_diametro->eliminar();
}

void ui_agregarLuna::on_pushButton_xCalidad_clicked()
{
    ui->comboBox_calidad->eliminar();
}

void ui_agregarLuna::on_pushButton_xTipoLuna_clicked()
{
    ui->comboBox_tipoLuna->eliminar();
}

void ui_agregarLuna::on_pushButton_xTratamiento_clicked()
{
    ui->comboBox_tratamiento->eliminar();
}

void ui_agregarLuna::on_pushButton_xEstado_clicked()
{
    ui->comboBox_estado->eliminar();
}

bool ui_agregarLuna::verificarSelecciones()
{
    if(ui->comboBox_diametro->selecciono())
        if(ui->comboBox_calidad->selecciono())
            if(ui->comboBox_tipoLuna->selecciono())
                if(ui->comboBox_tratamiento->selecciono())
                {
                    diametro pDiametro;pDiametro.setValor(ui->comboBox_diametro->currentText());pDiametro.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->comboBox_calidad->currentText());pCalidad.completar();
                    tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->comboBox_tipoLuna->currentText());pTipoLuna.completar();
                    tratamiento pTratamiento;pTratamiento.setNombre(ui->comboBox_tratamiento->currentText());pTratamiento.completar();
                    pLuna.setDiametro(pDiametro);
                    pLuna.setCalidad(pCalidad);
                    pLuna.setTipoLuna(pTipoLuna);
                    pLuna.setTratamiento(pTratamiento);
                    pLuna.setValorInicial(ui->lineEdit_vInicial->text());
                    pLuna.setValorFinal(ui->lineEdit_vFinal->text());
                    ui->label_precio->show();
                    ui->checkBox_precio->show();
                    return true;
                }
                else
                    return false;
            else
                return false;
        else
            return false;
    else
        return false;
}

void ui_agregarLuna::on_comboBox_diametro_currentIndexChanged(int index)
{
    if(modo==1 && pLuna.getPrecio().toInt()==1)
        return;
    else
        if(ui->comboBox_diametro->selecciono())
        {
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
        }
}

void ui_agregarLuna::on_comboBox_calidad_currentIndexChanged(int index)
{
    if(modo==1 && pLuna.getPrecio().toInt()==1)
        return;
    else
        if(ui->comboBox_calidad->selecciono())
        {
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
        }
}

void ui_agregarLuna::on_comboBox_tipoLuna_currentIndexChanged(int index)
{
    if(modo==1 && pLuna.getPrecio().toInt()==1)
        return;
    else
        if(ui->comboBox_tipoLuna->selecciono())
        {
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
        }
}

void ui_agregarLuna::on_comboBox_tratamiento_currentIndexChanged(int index)
{
    if(modo==1 && pLuna.getPrecio().toInt()==1)
        return;
    else
        if(ui->comboBox_tratamiento->selecciono())
        {
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
        }
}

void ui_agregarLuna::on_lineEdit_vInicial_editingFinished()
{
    QRegExp noNumeros("[a-zA-Z]");
    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");
    if(ui->lineEdit_vInicial->text().contains(noNumeros))
    {
        box.setText("El Valor Inicial solo puede contener numeros");
        box.exec();
        ui->lineEdit_vInicial->setText("");
        ui->lineEdit_vInicial->setFocus();
        return;
    }
    else
    {
        if(modo==1 && pLuna.getPrecio().toInt()==1)
            return;
        else
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
    }
}

void ui_agregarLuna::on_lineEdit_vFinal_editingFinished()
{
    QRegExp noNumeros("[a-zA-Z]");
    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");
    if(ui->lineEdit_vFinal->text().contains(noNumeros))
    {
        box.setText("El Valor Final solo puede contener numeros");
        box.exec();
        ui->lineEdit_vFinal->setText("");
        ui->lineEdit_vFinal->setFocus();
        return;
    }
    else
    {
        if(modo==1 && pLuna.getPrecio().toInt()==1)
            return;
        else
            if(verificarSelecciones())
            {
                if(pLuna.verificarPrecio())
                {
                    ui->checkBox_precio->setChecked(0);
                    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
                    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
                    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
                    ui->label_precio->hide();
                    ui->checkBox_precio->hide();
                }
            }
    }
}
