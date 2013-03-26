#include "ui_agregarotros.h"
#include "ui_ui_agregarotros.h"

ui_agregarOtros::ui_agregarOtros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_agregarOtros)
{
    ui->setupUi(this);

    ui->comboBox_marca->setTipo("marca");
    ui->comboBox_marca->ActualizarItems(marca::mostrar());
    ui->comboBox_talla->setTipo("talla");
    ui->comboBox_talla->ActualizarItems(talla::mostrar());
    ui->comboBox_calidad->setTipo("calidad");
    ui->comboBox_calidad->ActualizarItems(calidad::mostrar());
    ui->comboBox_color->setTipo("color");
    ui->comboBox_color->ActualizarItems(color::mostrar());
    ui->comboBox_estado->setTipo("estado");
    ui->comboBox_estado->ActualizarItems(estado::mostrar());
    ui->comboBox_tipo->setTipo("tipoOtros");
    ui->comboBox_tipo->ActualizarItems(tipoOtros::mostrar());
    modo=0;
    ui->label_estado->hide();
    ui->comboBox_estado->hide();
    ui->pushButton_xestado->hide();
}

ui_agregarOtros::~ui_agregarOtros()
{
    delete ui;
}

void ui_agregarOtros::setModo(bool m)
{
    modo=m;
}

void ui_agregarOtros::setOtros(otros* o)
{
    pOtros=*o;
    ui->lineEdit_codigo->setText(pOtros.getCodigo());
    ui->lineEdit_descripcion->setText(pOtros.getDescripcion());
    ui->lineEdit_precioCompra->setText(pOtros.getPrecioCompra());
    ui->lineEdit_precioVenta->setText(pOtros.getPrecioVenta());
    ui->lineEdit_precioDescuento->setText(pOtros.getPrecioDescuento());
    ui->lineEdit_accesorios->setText(pOtros.getAccesorios());
    ui->spinBox_stock->setValue(pOtros.getStock().toInt());
    ui->lineEdit_observaciones->setText(pOtros.getObservaciones());
    ui->comboBox_estado->buscarValor(pOtros.getEstado().getNombre());
    ui->comboBox_marca->buscarValor(pOtros.getMarca().getNombre());
    ui->comboBox_color->buscarValor(pOtros.getColor().getNombre());
    ui->comboBox_talla->buscarValor(pOtros.getTalla().getNombre());
    ui->comboBox_calidad->buscarValor(pOtros.getCalidad().getNombre());
    ui->comboBox_tipo->buscarValor(pOtros.getTipoOtros().getNombre());
    ui->label_estado->show();
    ui->comboBox_estado->show();
    ui->pushButton_xestado->show();
}

bool ui_agregarOtros::verificarRestricciones()
{
    QRegExp noNumeros("[a-zA-Z]");
    QRegExp noAlfabeto("[0-9\.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");

    if(ui->lineEdit_codigo->text().size() == 0)
    {
        box.setText("El Codigo es obligatorio");
        box.exec();
        ui->lineEdit_codigo->setFocus();
        return false;
    }
    if(ui->lineEdit_descripcion->text().size() == 0)
    {
        box.setText("La Descripcion es obligatoria");
        box.exec();
        ui->lineEdit_descripcion->setFocus();
        return false;
    }
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
    if(!ui->comboBox_marca->selecciono())
    {
        box.setText("Seleccione alguna Marca");
        box.exec();
        ui->comboBox_marca->setFocus();
        return false;
    }
    if(!ui->comboBox_calidad->selecciono())
    {
        box.setText("Seleccione alguna Calidad");
        box.exec();
        ui->comboBox_calidad->setFocus();
        return false;
    }
    if(!ui->comboBox_color->selecciono())
    {
        box.setText("Seleccione algun Color");
        box.exec();
        ui->comboBox_color->setFocus();
        return false;
    }
    if(!ui->comboBox_talla->selecciono())
    {
        box.setText("Seleccione alguna Talla o la opcion No Tiene");
        box.exec();
        ui->comboBox_talla->setFocus();
        return false;
    }
    if(!ui->comboBox_tipo->selecciono())
    {
        box.setText("Seleccione algun Tipo");
        box.exec();
        ui->comboBox_tipo->setFocus();
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
    return true;
}

void ui_agregarOtros::on_pushButton_agregar_clicked()
{
    if(!verificarRestricciones())
        return;
    pOtros.setCodigo(ui->lineEdit_codigo->text());
    pOtros.setDescripcion(ui->lineEdit_descripcion->text());
    pOtros.setPrecioCompra(ui->lineEdit_precioCompra->text());
    pOtros.setPrecioVenta(ui->lineEdit_precioVenta->text());
    pOtros.setPrecioDescuento(ui->lineEdit_precioDescuento->text());
    pOtros.setAccesorios(ui->lineEdit_accesorios->text());
    pOtros.setStock(ui->spinBox_stock->text());
    pOtros.setObservaciones(ui->lineEdit_observaciones->text());
    estado pEstado;pEstado.setNombre(ui->comboBox_estado->currentText());pEstado.completar();
    marca pMarca;pMarca.setNombre(ui->comboBox_marca->currentText());pMarca.completar();
    //colaborador
    color pColor;pColor.setNombre(ui->comboBox_color->currentText());pColor.completar();
    talla pTalla;pTalla.setNombre(ui->comboBox_talla->currentText());pTalla.completar();
    calidad pCalidad;pCalidad.setNombre(ui->comboBox_calidad->currentText());pCalidad.completar();
    tipoOtros pTipoOtros;pTipoOtros.setNombre(ui->comboBox_tipo->currentText());pTipoOtros.completar();
    pOtros.setEstado(pEstado);
    pOtros.setMarca(pMarca);
    //colaborador
    pOtros.setColor(pColor);
    pOtros.setTalla(pTalla);
    pOtros.setCalidad(pCalidad);
    pOtros.setTipoOtros(pTipoOtros);
    if(modo==0)//agrego
    {
        pEstado.setNombre("activo");pEstado.completar();
        pOtros.setEstado(pEstado);
        if(pOtros.agregar())
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
        if(pOtros.actualizar())
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

void ui_agregarOtros::on_pushButton_xmarca_clicked()
{
    ui->comboBox_marca->eliminar();
}

void ui_agregarOtros::on_pushButton_xcalidad_clicked()
{
    ui->comboBox_calidad->eliminar();
}

void ui_agregarOtros::on_pushButton_xcolor_clicked()
{
    ui->comboBox_color->eliminar();
}

void ui_agregarOtros::on_pushButton_xestado_clicked()
{
    ui->comboBox_estado->eliminar();
}

void ui_agregarOtros::on_pushButton_xtalla_clicked()
{
    ui->comboBox_talla->eliminar();
}

void ui_agregarOtros::on_pushButton_xtipo_clicked()
{
    ui->comboBox_tipo->eliminar();
}


