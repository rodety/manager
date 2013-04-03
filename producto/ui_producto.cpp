#include "ui_producto.h"
#include "ui_ui_producto.h"
#include <QPrinter>
#include <QPainter>
#include <QPixmap>
#include <QInputDialog>

#include <iostream> using namespace std;

ui_producto::ui_producto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_producto)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    posicion=0;
    cambiarModeloLuna();

    /// #etiquetas/////////
    system("mkdir -p etiquetas");
    system("mkdir -p etiquetas/imagenes");
    act=-1;
    pag=0;


    connect(ui->tableView_etiquetas, SIGNAL(doubleClicked(const QModelIndex & )), this, SLOT(eliminar_etiqueta(const QModelIndex &)));

}


ui_producto::~ui_producto()
{
    delete ui;
}

void ui_producto::cambiarModeloLuna()
{
    ui->tableView_productos->setModel(luna::mostrar());
}
void ui_producto::cambiarModeloMontura()
{
    ui->tableView_productos->setModel(montura::mostrar());
}
void ui_producto::cambiarModeloLenteContacto()
{
    ui->tableView_productos->setModel(lenteContacto::mostrar());
}
void ui_producto::cambiarModeloOtros()
{
    ui->tableView_productos->setModel(otros::mostrar());
}
void ui_producto::cambiarModeloTrabajosExtras()
{
    ui->tableView_productos->setModel(trabajosExtras::mostrar());
}

void ui_producto::on_comboBox_tipoProducto_currentIndexChanged(int index)
{
    posicion=index;
    if(posicion==0)
        cambiarModeloLuna();
    if(posicion==1)
        cambiarModeloMontura();
    if(posicion==2)
        cambiarModeloLenteContacto();
    if(posicion==3)
        cambiarModeloOtros();
    if(posicion==4)
        cambiarModeloTrabajosExtras();
}

void ui_producto::on_pushButton_agregar_2_clicked()
{
    if(posicion==0)
    {
        ui_agregarLuna* form=new ui_agregarLuna;
        form->setWindowTitle("Nueva Luna");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLuna()));
    }
    if(posicion==1)
    {
        ui_agregarMontura* form=new ui_agregarMontura;
        form->setWindowTitle("Nueva Montura");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloMontura()));
    }
    if(posicion==2)
    {
        ui_agregarLente* form=new ui_agregarLente;
        form->setWindowTitle("Nuevo Lente de Contacto");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLenteContacto()));
    }
    if(posicion==3)
    {
        ui_agregarOtros* form=new ui_agregarOtros;
        form->setWindowTitle("Nuevo Producto");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloOtros()));
    }
    if(posicion==4)
    {
        ui_trabajosExtras* form=new ui_trabajosExtras;
        form->setWindowTitle("Nuevo Trabajo Extra");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloTrabajosExtras()));
    }
}

void ui_producto::on_pushButton_editar_clicked()
{
    int fila=ui->tableView_productos->currentIndex().row();
    if(fila!=-1)
    {
        if(posicion==0)
        {
            luna productoActual;
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());pDiametro.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pCalidad.completar();
            tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pTipoLuna.completar();
            tratamiento pTratamiento;pTratamiento.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTratamiento.completar();
            productoActual.setValorInicial(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
            productoActual.setValorFinal(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
            productoActual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());
            productoActual.setEstado(pEstado);
            productoActual.setDiametro(pDiametro);
            productoActual.setCalidad(pCalidad);
            productoActual.setTipoLuna(pTipoLuna);
            productoActual.setTratamiento(pTratamiento);
            productoActual.completar();

            ui_agregarLuna* form=new ui_agregarLuna;
            form->setModo(true);
            form->setLuna(&productoActual);
            form->setWindowTitle("Editar Luna");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLuna()));
        }
        if(posicion==1)
        {
            montura productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            forma pForma;pForma.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pForma.completar();
            color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pColor.completar();
            tamanio pTamanio;pTamanio.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTamanio.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pCalidad.completar();
            genero pGenero;pGenero.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pGenero.completar();

            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setForma(pForma);
            productoActual.setColor(pColor);
            productoActual.setTamanio(pTamanio);
            productoActual.setCalidad(pCalidad);
            productoActual.setGenero(pGenero);
            productoActual.completar();

            ui_agregarMontura* form=new ui_agregarMontura;
            form->setModo(true);
            form->setMontura(&productoActual);
            form->setWindowTitle("Editar Montura");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloMontura()));
        }
        if(posicion==2)
        {
            lenteContacto productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            productoActual.setPresentacion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());
            productoActual.setTinteVisibilidad(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());
            productoActual.setContenidoAcuoso(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
            productoActual.setDiseno(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
            tipoLente pTipoLente;pTipoLente.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pTipoLente.completar();
            potencia pPotencia;pPotencia.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());pPotencia.completar();
            curvaBase pCurvaBase;pCurvaBase.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());pCurvaBase.completar();
            diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());pDiametro.completar();
            tiempoUso pTiempoUso;pTiempoUso.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,16)).toString());pTiempoUso.completar();
            material pMaterial;pMaterial.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,17)).toString());pMaterial.completar();
            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setTipoLente(pTipoLente);
            productoActual.setPotencia(pPotencia);
            productoActual.setCurvaBase(pCurvaBase);
            productoActual.setDiametro(pDiametro);
            productoActual.setTiempoUso(pTiempoUso);
            productoActual.setMaterial(pMaterial);
            productoActual.completar();

            ui_agregarLente* form=new ui_agregarLente;
            form->setModo(true);
            form->setLenteContacto(&productoActual);
            form->setWindowTitle("Editar Lente de Contacto");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLenteContacto()));
        }
        if(posicion==3)
        {
            otros productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pColor.completar();
            talla pTalla;pTalla.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTalla.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pCalidad.completar();
            tipoOtros pTipoOtros;pTipoOtros.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pTipoOtros.completar();
            genero pGenero;pGenero.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pGenero.completar();

            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setColor(pColor);
            productoActual.setTalla(pTalla);
            productoActual.setCalidad(pCalidad);
            productoActual.setTipoOtros(pTipoOtros);
            productoActual.setGenero(pGenero);
            productoActual.completar();


            ui_agregarOtros* form=new ui_agregarOtros;
            form->setModo(true);
            form->setOtros(&productoActual);
            form->setWindowTitle("Editar Producto");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloOtros()));
        }
        if(posicion==4)
        {
            trabajosExtras actual;
            actual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            actual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            actual.completar();

            ui_trabajosExtras* form=new ui_trabajosExtras;
            form->setModo(true);
            form->setTrabajosExtras(&actual);
            form->setWindowTitle("Editar Trabajo Extra");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloTrabajosExtras()));
        }
    }
}

void ui_producto::on_pushButton_eliminar_clicked()
{
    int fila=ui->tableView_productos->currentIndex().row();
    if(fila!=-1)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Question);
        box.setWindowTitle("Advertencia");
        box.setText("Esta seguro de eliminar este producto?");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        switch(ret)
        {
            case QMessageBox::Ok:
            {
                if(posicion==0)
                {
                    luna productoActual;
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());pDiametro.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pCalidad.completar();
                    tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pTipoLuna.completar();
                    tratamiento pTratamiento;pTratamiento.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTratamiento.completar();
                    productoActual.setValorInicial(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
                    productoActual.setValorFinal(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
                    productoActual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());

                    productoActual.setEstado(pEstado);
                    productoActual.setDiametro(pDiametro);
                    productoActual.setCalidad(pCalidad);
                    productoActual.setTipoLuna(pTipoLuna);
                    productoActual.setTratamiento(pTratamiento);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloLuna();
                }
                if(posicion==1)
                {
                    montura productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    forma pForma;pForma.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pForma.completar();
                    color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pColor.completar();
                    tamanio pTamanio;pTamanio.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTamanio.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pCalidad.completar();
                    genero pGenero;pGenero.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pGenero.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setForma(pForma);
                    productoActual.setColor(pColor);
                    productoActual.setTamanio(pTamanio);
                    productoActual.setCalidad(pCalidad);
                    productoActual.setGenero(pGenero);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloMontura();
                }
                if(posicion==2)
                {
                    lenteContacto productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    productoActual.setPresentacion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());
                    productoActual.setTinteVisibilidad(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());
                    productoActual.setContenidoAcuoso(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
                    productoActual.setDiseno(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
                    tipoLente pTipoLente;pTipoLente.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pTipoLente.completar();
                    potencia pPotencia;pPotencia.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());pPotencia.completar();
                    curvaBase pCurvaBase;pCurvaBase.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());pCurvaBase.completar();
                    diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());pDiametro.completar();
                    tiempoUso pTiempoUso;pTiempoUso.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,16)).toString());pTiempoUso.completar();
                    material pMaterial;pMaterial.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,17)).toString());pMaterial.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setTipoLente(pTipoLente);
                    productoActual.setPotencia(pPotencia);
                    productoActual.setCurvaBase(pCurvaBase);
                    productoActual.setDiametro(pDiametro);
                    productoActual.setTiempoUso(pTiempoUso);
                    productoActual.setMaterial(pMaterial);                    
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloLenteContacto();
                }
                if(posicion==3)
                {
                    otros productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pColor.completar();
                    talla pTalla;pTalla.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTalla.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pCalidad.completar();
                    tipoOtros pTipoOtros;pTipoOtros.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pTipoOtros.completar();
                    genero pGenero;pGenero.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pGenero.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setColor(pColor);
                    productoActual.setTalla(pTalla);
                    productoActual.setCalidad(pCalidad);
                    productoActual.setTipoOtros(pTipoOtros);
                    productoActual.setGenero(pGenero);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloOtros();
                }
                if(posicion==4)
                {
                    trabajosExtras actual;
                    actual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    actual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    actual.completar();

                    actual.eliminar();
                    cambiarModeloTrabajosExtras();
                }
            }
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    }
}


/// #etiquetas ////////////////////////////////////////

void ui_producto::agregar_etiqueta(const QModelIndex &model)
{
    if(posicion==0)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Advertencia");
        box.setText("Las Lunas no se pueden etiquetar!");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }
    if(posicion==4)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Advertencia");
        box.setText("Los Trabajos Extras no se pueden etiquetar!");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }
    int fila=model.row();
    if(fila!=-1)
    {
        etiqueta t;
        QString codigo,color,calidad,precio;
        codigo=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString();
        for(int i=0;i<etiquetas.size();i++)
            if(etiquetas[i].getCodigo()==codigo)
            {
                QMessageBox box;
                box.setIcon(QMessageBox::Question);
                box.setWindowTitle("Advertencia");
                box.setText("Ya existe este producto!\nDesea etiquetarlo de igual manera?");
                box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                box.setDefaultButton(QMessageBox::Ok);
                int ret=box.exec();
                switch(ret)
                {
                    case QMessageBox::Ok:
                        break;
                    case QMessageBox::Cancel:
                        return;
                    default:
                        break;
                }
                break;
            }
        if(codigo.size()==0)
            return;
        if(posicion==1)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        }
        if(posicion==2)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();//tinte visibilidad
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString();//marca
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        }
        if(posicion==3)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString();
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        }
        t.setCodigo(codigo);
        t.setColor(color);
        t.setCalidad(calidad);
        t.setPrecio(precio);
        t.buscarUbicacion();
        etiquetas.append(t);
        ui->tableView_etiquetas->insertRow(ui->tableView_etiquetas->rowCount());
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,0,new QTableWidgetItem(codigo));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,1,new QTableWidgetItem(color));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,2,new QTableWidgetItem(calidad));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,4,new QTableWidgetItem(precio));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,3,new QTableWidgetItem(t.getUbicacion()));
    }
}

void ui_producto::eliminar_etiqueta(const QModelIndex &model)
{
    int fila=model.row();
    ui->tableView_etiquetas->removeRow(fila);
    etiquetas.removeAt(fila);
}

void ui_producto::on_pushButton_previsualizar_clicked()
{
    for(int i=0;i<etiquetas.size();i++)
        etiquetas[i].etiquetar();
    QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
    pm.fill(Qt::white);
    QPainter p;
    //QFont font("times",16);
    QFont font("times",12);
    p.begin(&pm);
    p.setFont(font);

    int j=0;
    int k=0;
    pag=0;
    QString num;

    for(int i=0;i<etiquetas.size();i++)
    {
        QImage tmp("etiquetas/imagenes/"+etiquetas[i].getCodigo()+".png");
        //QImage imagen=tmp.scaledToHeight(60);
        QImage imagen=tmp.scaledToHeight(80);
        /*p.drawImage((200*k)+60,(100*j)+30,imagen);
        p.drawText((200*k)+60,(100*j)+105,etiquetas[i].getColor());
        p.drawText((200*k)+130,(100*j)+105,etiquetas[i].getCalidad());
        p.drawText((200*k)+60,(100*j)+121,etiquetas[i].getUbicacion());
        p.drawText((200*k)+130,(100*j)+121,"S/."+etiquetas[i].getPrecio());*/
        p.drawImage((500*k)+220,(100*j)+30,imagen);
        p.drawText((500*k)+440,(100*j)+46,etiquetas[i].getCodigo());
        p.drawText((500*k)+440,(100*j)+62,etiquetas[i].getColor());
        p.drawText((500*k)+510,(100*j)+62,etiquetas[i].getCalidad());
        p.drawText((500*k)+440,(100*j)+78,etiquetas[i].getUbicacion());
        p.drawText((500*k)+510,(100*j)+78,"S/."+etiquetas[i].getPrecio());

        if(k==1)
        {
            k=-1;
            j++;
        }
        k++;
        if(j==17 || (i+1)==etiquetas.size())
        {
            j=0;
            pm.save("etiquetas/"+num.setNum(pag)+".png");
            pm.fill(Qt::white);
            pag++;
        }
    }

    if(pag!=0)
    {
        ui->lineEdit_pag->setText("1/"+num.setNum(pag));
        this->act=0;
        ui->pushButton_siguiente->setEnabled(1);
        if(this->act==0)
            ui->pushButton_anterior->setDisabled(1);
        if(this->act+1==pag)
            ui->pushButton_siguiente->setDisabled(1);
        QImage act("etiquetas/0.png");
        p.drawImage(0,0,act);
    }
    else
    {
        ui->lineEdit_pag->setText("0/0");
        ui->pushButton_anterior->setDisabled(1);
        ui->pushButton_anterior->setDisabled(1);
        pm.fill(Qt::white);
    }
    ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));
}

void ui_producto::on_pushButton_imprimir_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFileName("etiquetas.pdf");
    QPainter painter;
    if (! painter.begin(&printer))
        qWarning("failed to open file, is it writable?");
    QImage act("etiquetas/0.png");
    act=act.scaledToWidth(9000);
    painter.drawImage(0,0,act);
    painter.end();
    QTextEdit parent;
    QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
    dlg->setWindowTitle(QObject::tr("Print Document"));

    if(dlg->exec() == QDialog::Accepted) {
        parent.print(&printer);
    }
    delete dlg;
}

void ui_producto::on_pushButton_anterior_clicked()
{
    if(pag!=0 && act>0)
    {
        QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
        pm.fill(Qt::white);
        QPainter p;
        p.begin(&pm);
        QString num;
        QImage act("etiquetas/"+num.setNum(--this->act)+".png");
        ui->lineEdit_pag->setText(num.setNum(this->act+1)+"/"+num.setNum(pag));
        p.drawImage(0,0,act);
        ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));

        ui->pushButton_siguiente->setEnabled(1);
        if(this->act==0)
            ui->pushButton_anterior->setDisabled(1);
    }
}

void ui_producto::on_pushButton_siguiente_clicked()
{
    if(pag!=0 && (act+1)<pag)
    {
        QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
        pm.fill(Qt::white);
        QPainter p;
        p.begin(&pm);
        QString num;
        QImage act("etiquetas/"+num.setNum(++this->act)+".png");
        ui->lineEdit_pag->setText(num.setNum(this->act+1)+"/"+num.setNum(pag));
        p.drawImage(0,0,act);
        ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));

        ui->pushButton_anterior->setEnabled(1);
        if(this->act+1==pag)
            ui->pushButton_siguiente->setDisabled(1);
    }
}

void ui_producto::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        ui->lineEdit_buscar->setDisabled(1);
        ui->pushButton_buscar->setDisabled(1);
        ui->pushButton_busquedaAvanzada->setDisabled(1);
    }
    else
    {
        ui->lineEdit_buscar->setEnabled(1);
        ui->pushButton_buscar->setEnabled(1);
        ui->pushButton_busquedaAvanzada->setEnabled(1);
    }
}


void ui_producto::on_btnToVitrina_clicked()
{
    int index=ui->comboBox_tipoProducto->currentIndex();
    if(index<1 || index>3)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Advertencia");
        box.setText("EL tipo de luna actual no se puede transferir a una Vitrina");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }
    if(ui->tableView_productos->currentIndex().row() <0)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Advertencia");
        box.setText("Seleccione el producto que desea mover");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }
    int row=ui->tableView_productos->currentIndex().row();
    QModelIndex ind=ui->tableView_productos->model()->index(row,0);
    QString cod=ui->tableView_productos->model()->data(ind).toString(), idProducto;

    QSqlQuery query;
    query.prepare("SELECT idProducto FROM Producto WHERE codigo =?");
    query.bindValue(0,cod);
    query.exec();   query.next();
    idProducto=query.value(0).toString();

    ui_tienda* tienda= new ui_tienda;
//    tienda->set_idItem_tras(idProducto);
    tienda->set_idTraspaso(idProducto);
    tienda->set_traspaso(true);
    tienda->habilitar_botones();
    tienda->enableButtonAceptar();
    tienda->show();
}

void ui_producto::on_btnToAlmacen_clicked()
{


}


void ui_producto::setComportamiento(int a)
{
    comportamiento = a;
    //0 Comportamiento de etiquetas 1 comportamiento ventas
    if(a == 0)
    {
        connect(ui->tableView_productos, SIGNAL (doubleClicked (const QModelIndex & )), this, SLOT (agregar_etiqueta(const QModelIndex & )));
    }
    if(a == 1)
    {
        connect(ui->tableView_productos, SIGNAL (doubleClicked (const QModelIndex & )), this, SLOT (enviar_producto(const QModelIndex & )));
    }
}


void ui_producto::enviar_producto(const QModelIndex & model)
{
    QString codigo,descripcion,precioCompra,descuento,tipoLuna,tratamiento,valorInicial,ValorFinal,marca,forma,color,tamano,calidad,presentacion,
            tinte,contacuoso,diseno,tipoLente,potencia,curva,diametro,tiempouso,material,genero, mtalla,mtipo;
    int fila =0;
    codigo=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString();

    if(codigo.size()==0)
        return;
    if(posicion==1)
    {
        descripcion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString();
        precioCompra=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        descuento=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString();
        tipoLuna=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
        tratamiento=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
        valorInicial=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
        ValorFinal=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
        descripcion+= " " +tipoLuna+" "+tratamiento+" "+valorInicial+" "+ValorFinal;
    }

    if(posicion==2)
    {
        descripcion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString();
        precioCompra=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        descuento=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString();

        marca=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString();
        forma=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
        color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();
        tamano=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
        calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString();
        genero=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString();
        descripcion+= " " +marca+" "+forma+" "+color+" "+tamano+" "+calidad+" "+genero;
    }
    if(posicion==3)
    {
        descripcion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString();
        precioCompra=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        descuento=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString();

        marca=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString();
        presentacion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
        tinte=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();
        contacuoso=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
        diseno=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString();
        tipoLente=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString();
        potencia=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString();
        curva=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString();
        diametro=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,16)).toString();
        tiempouso=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,17)).toString();
        material=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,18)).toString();
        descripcion+= " " +marca+" "+presentacion+" "+tinte+" "+contacuoso+" "+diseno+" "+tipoLente+" "+potencia+
                " "+curva+" "+diametro+" "+tiempouso+" "+material;

    }
    if(posicion==4)
    {
        descripcion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString();
        precioCompra=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString();
        descuento=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString();

        marca=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString();
        color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
        mtalla=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();
        calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
        mtipo=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString();
        genero=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString();

        descripcion+= " " +marca+" "+color+" "+mtalla+" "+calidad+" "+mtipo+" "+genero;
    }
    if(posicion==5)
    {
        descripcion=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString();
        precioCompra=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString();
    }
    bool ok;
    int cant = QInputDialog::getInt(this,tr("Ingrese Cantidad"),tr("Cantidad"),1,0,1000,1,&ok);
    if(ok)
        emit sentProductoCompra(codigo,descripcion,precioCompra,cant);
}

