#include "mycombobox.h"

MyComboBox::MyComboBox(QWidget* parent):QComboBox(parent)
{
    icono_agregar=new QIcon(":/Icons/1349716383_monotone_plus_add_round.png");
    this->connect(this,SIGNAL(activated(int)),this,SLOT(nuevo()));
}

void MyComboBox::setTipo(QString tmp)
{
    tipo=tmp;
}

void MyComboBox::buscarValor(QString tmp)
{
    for(int i=0;i<this->count();i++)
    {
        if(this->itemText(i)==tmp)
        {
            this->setCurrentIndex(i);
            return;
        }
    }
}

bool MyComboBox::selecciono()
{
    if(this->currentIndex()==0)
        return false;
    if(this->currentIndex()==this->count()-1)
        return false;
    else
        return true;
}

void MyComboBox::ActualizarItems(QSqlQueryModel *model)
{
    this->clear();

    this->addItem("---Seleccione---");
    for(int i=0;i<model->rowCount();i++)
        this->addItem(model->record(i).value(0).toString());
    this->addItem(*icono_agregar,"...Nuevo...");
}

void MyComboBox::nuevo()
{
    if(this->currentText()=="...Nuevo..."&& this->currentIndex()==this->count()-1)
    {
        this->setEditable(true);
        this->connect(this->lineEdit(),SIGNAL(editingFinished()),this,SLOT(agregar()));
        this->setEditText("");
    }
}

void MyComboBox::agregar()
{
    this->setEditable(false);
    if(tipo=="estado")
    {
        estado pEstado;
        pEstado.setNombre(this->itemText(this->count()-1));
        pEstado.agregar();
        ActualizarItems(estado::mostrar());
    }
    if(tipo=="marca")
    {
        marca pMarca;
        pMarca.setNombre(this->itemText(this->count()-1));
        pMarca.agregar();
        ActualizarItems(marca::mostrar());
    }
    if(tipo=="forma")
    {
        forma pForma;
        pForma.setNombre(this->itemText(this->count()-1));
        pForma.agregar();
        ActualizarItems(forma::mostrar());
    }
    if(tipo=="color")
    {
        color pColor;
        pColor.setNombre(this->itemText(this->count()-1));
        pColor.agregar();
        ActualizarItems(color::mostrar());
    }
    if(tipo=="tamanio")
    {
        tamanio pTamanio;
        pTamanio.setNombre(this->itemText(this->count()-1));
        pTamanio.agregar();
        ActualizarItems(tamanio::mostrar());
    }
    if(tipo=="calidad")
    {
        calidad pCalidad;
        pCalidad.setNombre(this->itemText(this->count()-1));
        pCalidad.agregar();
        ActualizarItems(calidad::mostrar());
    }
    if(tipo=="diametro")
    {
        diametro pDiametro;
        pDiametro.setValor(this->itemText(this->count()-1));
        pDiametro.agregar();
        ActualizarItems(diametro::mostrar());
    }
    if(tipo=="tipoLuna")
    {
        tipoLuna pTipoLuna;
        pTipoLuna.setNombre(this->itemText(this->count()-1));
        pTipoLuna.agregar();
        ActualizarItems(tipoLuna::mostrar());
    }
    if(tipo=="tratamiento")
    {
        tratamiento pTratamiento;
        pTratamiento.setNombre(this->itemText(this->count()-1));
        pTratamiento.agregar();
        ActualizarItems(tratamiento::mostrar());
    }
    if(tipo=="tipoLente")
    {
        tipoLente pTipoLente;
        pTipoLente.setNombre(this->itemText(this->count()-1));
        pTipoLente.agregar();
        ActualizarItems(tipoLente::mostrar());
    }
    if(tipo=="potencia")
    {
        potencia pPotencia;
        pPotencia.setNombre(this->itemText(this->count()-1));
        pPotencia.agregar();
        ActualizarItems(potencia::mostrar());
    }
    if(tipo=="curvaBase")
    {
        curvaBase pCurvaBase;
        pCurvaBase.setValor(this->itemText(this->count()-1));
        pCurvaBase.agregar();
        ActualizarItems(curvaBase::mostrar());
    }
    if(tipo=="tiempoUso")
    {
        tiempoUso pTiempoUso;
        pTiempoUso.setValor(this->itemText(this->count()-1));
        pTiempoUso.agregar();
        ActualizarItems(tiempoUso::mostrar());
    }
    if(tipo=="material")
    {
        material pMaterial;
        pMaterial.setNombre(this->itemText(this->count()-1));
        pMaterial.agregar();
        ActualizarItems(material::mostrar());
    }
    if(tipo=="talla")
    {
        talla pTalla;
        pTalla.setNombre(this->itemText(this->count()-1));
        pTalla.agregar();
        ActualizarItems(talla::mostrar());
    }
    if(tipo=="tusuario")
    {
        tusuario pTusuario;
        pTusuario.setNombre(this->itemText(this->count()-1));
        pTusuario.agregar();
        ActualizarItems(tusuario::mostrar());
    }
    if(tipo=="documento")
    {
        documento pDocumento;
        pDocumento.setNombre(this->itemText(this->count()-1));
        pDocumento.agregar();
        ActualizarItems(documento::mostrar());
    }
    if(tipo=="tipoOtros")
    {
        tipoOtros pTipo;
        pTipo.setNombre(this->itemText(this->count()-1));
        pTipo.agregar();
        ActualizarItems(tipoOtros::mostrar());
    }
    if(tipo=="genero")
    {
        genero pGenero;
        pGenero.setNombre(this->itemText(this->count()-1));
        pGenero.agregar();
        ActualizarItems(genero::mostrar());
    }

    this->setCurrentIndex(this->count()-2);
}

void MyComboBox::eliminar()
{
    if(!selecciono())
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Seleccione");
        box.setText("Seleccione un Dato para Eliminar!");
        box.setStandardButtons(QMessageBox::Ok);
        box.setDefaultButton(QMessageBox::Ok);
        box.exec();
        return;
    }
    bool error=false;
    if(tipo=="estado")
    {
        estado pEstado;
        pEstado.setNombre(this->currentText());
        pEstado.completar();
        if(pEstado.eliminar())
            ActualizarItems(estado::mostrar());
        else
            error=true;
    }
    if(tipo=="marca")
    {
        marca pMarca;
        pMarca.setNombre(this->currentText());
        pMarca.completar();
        if(pMarca.eliminar())
            ActualizarItems(marca::mostrar());
        else
            error=true;
    }
    if(tipo=="forma")
    {
        forma pForma;
        pForma.setNombre(this->currentText());
        pForma.completar();
        if(pForma.eliminar())
            ActualizarItems(forma::mostrar());
        else
            error=true;
    }
    if(tipo=="color")
    {
        color pColor;
        pColor.setNombre(this->currentText());
        pColor.completar();
        if(pColor.eliminar())
            ActualizarItems(color::mostrar());
        else
            error=true;
    }
    if(tipo=="tamanio")
    {
        tamanio pTamanio;
        pTamanio.setNombre(this->currentText());
        pTamanio.completar();
        if(pTamanio.eliminar())
            ActualizarItems(tamanio::mostrar());
        else
            error=true;
    }
    if(tipo=="calidad")
    {
        calidad pCalidad;
        pCalidad.setNombre(this->currentText());
        pCalidad.completar();
        if(pCalidad.eliminar())
            ActualizarItems(calidad::mostrar());
        else
            error=true;
    }
    if(tipo=="diametro")
    {
        diametro pDiametro;
        pDiametro.setValor(this->currentText());
        pDiametro.completar();
        if(pDiametro.eliminar())
            ActualizarItems(diametro::mostrar());
        else
            error=true;
    }
    if(tipo=="tipoLuna")
    {
        tipoLuna pTipoLuna;
        pTipoLuna.setNombre(this->currentText());
        pTipoLuna.completar();
        if(pTipoLuna.eliminar())
            ActualizarItems(tipoLuna::mostrar());
        else
            error=true;
    }
    if(tipo=="tratamiento")
    {
        tratamiento pTratamiento;
        pTratamiento.setNombre(this->currentText());
        pTratamiento.completar();
        if(pTratamiento.eliminar())
            ActualizarItems(tratamiento::mostrar());
        else
            error=true;
    }
    if(tipo=="tipoLente")
    {
        tipoLente pTipoLente;
        pTipoLente.setNombre(this->currentText());
        pTipoLente.completar();
        if(pTipoLente.eliminar())
            ActualizarItems(tipoLente::mostrar());
        else
            error=true;
    }
    if(tipo=="potencia")
    {
        potencia pPotencia;
        pPotencia.setNombre(this->currentText());
        pPotencia.completar();
        if(pPotencia.eliminar())
            ActualizarItems(potencia::mostrar());
        else
            error=true;
    }
    if(tipo=="curvaBase")
    {
        curvaBase pCurvaBase;
        pCurvaBase.setValor(this->currentText());
        pCurvaBase.completar();
        if(pCurvaBase.eliminar())
            ActualizarItems(curvaBase::mostrar());
        else
            error=true;
    }
    if(tipo=="tiempoUso")
    {
        tiempoUso pTiempoUso;
        pTiempoUso.setValor(this->currentText());
        pTiempoUso.completar();
        if(pTiempoUso.eliminar())
            ActualizarItems(tiempoUso::mostrar());
        else
            error=true;
    }
    if(tipo=="material")
    {
        material pMaterial;
        pMaterial.setNombre(this->currentText());
        pMaterial.completar();
        if(pMaterial.eliminar())
            ActualizarItems(material::mostrar());
        else
            error=true;
    }
    if(tipo=="talla")
    {
        talla pTalla;
        pTalla.setNombre(this->currentText());
        pTalla.completar();
        if(pTalla.eliminar())
            ActualizarItems(talla::mostrar());
        else
            error=true;
    }
    if(tipo=="tusuario")
    {
        tusuario ptuauario;
        ptuauario.setNombre(this->currentText());
        ptuauario.completar();
        if(ptuauario.eliminar())
            ActualizarItems(tusuario::mostrar());
        else
            error=true;
    }
    if(tipo=="documento")
    {
        documento pDocumento;
        pDocumento.setNombre(this->currentText());
        pDocumento.completar();
        if(pDocumento.eliminar())
            ActualizarItems(documento::mostrar());
        else
            error=true;
    }
    if(tipo=="tipoOtros")
    {
        tipoOtros pTipo;
        pTipo.setNombre(this->currentText());
        pTipo.completar();
        if(pTipo.eliminar())
            ActualizarItems(tipoOtros::mostrar());
        else
            error=true;
    }
    if(tipo=="genero")
    {
        genero pGenero;
        pGenero.setNombre(this->currentText());
        pGenero.completar();
        if(pGenero.eliminar())
            ActualizarItems(genero::mostrar());
        else
            error=true;
    }
    if(error)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Error");
        box.setText("El Dato no se pudo eliminar!\n porque esta siendo usado");
        box.setStandardButtons(QMessageBox::Ok);
        box.setDefaultButton(QMessageBox::Ok);
        box.exec();
    }
}
