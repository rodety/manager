#-------------------------------------------------
#
# Project created by QtCreator 2013-02-16T12:40:56
#
#-------------------------------------------------


QT      += sql
QT      += network
QT      += gui
QT      += widgets
QT      += printsupport
QT       += core gui

TARGET = opticalManager
TEMPLATE = app
DEFINES += NCREPORT_IMPORT

unix {
    LIBS += -lncreport -Llib -L/usr/local/bin
    LIBS += -lzint
    target.path = /usr/local/bin
}
win32-g++: {
    release: LIBS += nc/libncreport2.a
    debug: LIBS += nc/libncreportd2.a
    target.path = bin
} else {
    win32: LIBS += ncreport2.lib
    target.path = bin
}

INCLUDEPATH += include

SOURCES += main.cpp\
        mainwindow.cpp \
    producto/ui_producto.cpp \
    objetopersistente.cpp \
    producto/producto.cpp \
    producto/montura.cpp \
    producto/estado.cpp \
    producto/marca.cpp \
    producto/forma.cpp \
    producto/color.cpp \
    producto/tamanio.cpp \
    producto/calidad.cpp \
    mycombobox.cpp \
    producto/ui_agregarmontura.cpp \
    producto/luna.cpp \
    producto/diametro.cpp \
    producto/tipoluna.cpp \
    producto/tratamiento.cpp \
    producto/ui_agregarluna.cpp \
    cliente/ui_medidas_historial.cpp \
    cliente/ui_historial_clinico.cpp \
    cliente/ui_cliente_datos.cpp \
    cliente/ui_cliente.cpp \
    cliente/medidashistorial.cpp \
    cliente/historialclinico.cpp \
    cliente/cliente.cpp \
    producto/tipolente.cpp \
    producto/potencia.cpp \
    producto/curvabase.cpp \
    producto/tiempouso.cpp \
    producto/material.cpp \
    producto/lentecontacto.cpp \
    producto/ui_agregarlente.cpp \
    producto/talla.cpp \
    producto/otros.cpp \
    producto/ui_agregarotros.cpp \
    extras/etiqueta.cpp \
    extras/trabajosextras.cpp \
    extras/ui_trabajosextras.cpp \
    vitrina/vitrina.cpp \
    vitrina/ui_vitrina_agregar.cpp \
    vitrina/ui_traspaso_almacen.cpp \
    vitrina/ui_tienda.cpp \
    vitrina/ui_andamio_datos.cpp \
    vitrina/ui_almacen.cpp \
    vitrina/tienda.cpp \
#    vitrina/forma.cpp \
    vitrina/empresa.cpp \
    vitrina/ui_item_posicion.cpp \
    vitrina/item_posicion.cpp \
    vitrina/andamio.cpp \
    vitrina/ui_almacen_datos.cpp \
    vitrina/ui_contenedor_datos.cpp \
    vitrina/almacen.cpp \
    vitrina/contenedor.cpp \
    vitrina/ui_tienda_agregar.cpp \
    configuracion/usuariosform.cpp \
    configuracion/usuario.cpp \
    configuracion/ui_login.cpp \
    configuracion/ui_cambiarpassdialog.cpp \
    configuracion/sesion.cpp \
    configuracion/dialoglogin.cpp \
    configuracion/dialogbuscarusuarios.cpp \
    configuracion/configurador.cpp \
    configuracion/conexionbd.cpp \
    vitrina/ui_agregar_empresa.cpp \
    configuracion/ui_configuracion.cpp \
    configuracion/tusuario.cpp \
    cliente/documento.cpp \
    reporte/ui_reporte.cpp \
    venta/uiventas.cpp \
    producto/tipootros.cpp \
    compra/ui_cant_item.cpp \
    compra/ui_datos_compras.cpp \
    compra/compras.cpp \
    compra/ui_proveedores.cpp \
    compra/ui_datos_proveedor.cpp \
    compra/proveedor.cpp \
    compra/compra.cpp \
    producto/genero.cpp \
    agenda/newalerta_alerta_ui.cpp \
    agenda/funciones.cpp \
    agenda/agenda_ui.cpp \
    agenda/alerta.cpp

HEADERS  += mainwindow.h \
    configuracion/configprogram.h \
    producto/ui_producto.h \
    objetopersistente.h \
    producto/producto.h \
    producto/montura.h \
    producto/estado.h \
    producto/marca.h \
    producto/forma.h \
    producto/color.h \
    producto/tamanio.h \
    producto/calidad.h \
    mycombobox.h \
    producto/ui_agregarmontura.h \
    producto/luna.h \
    producto/diametro.h \
    producto/tipoluna.h \
    producto/tratamiento.h \
    producto/ui_agregarluna.h \
    cliente/ui_medidas_historial.h \
    cliente/ui_historial_clinico.h \
    cliente/ui_cliente_datos.h \
    cliente/ui_cliente.h \
    cliente/medidashistorial.h \
    cliente/historialclinico.h \
    cliente/cliente.h \
    producto/tipolente.h \
    producto/potencia.h \
    producto/curvabase.h \
    producto/tiempouso.h \
    producto/material.h \
    producto/lentecontacto.h \
    producto/ui_agregarlente.h \
    producto/talla.h \
    producto/otros.h \
    producto/ui_agregarotros.h \
    extras/etiqueta.h \
    extras/trabajosextras.h \
    extras/ui_trabajosextras.h \
    vitrina/vitrina.h \
    vitrina/ui_traspaso_almacen.h \
    vitrina/ui_tienda_agregar.h \
    vitrina/ui_tienda.h \
    vitrina/ui_andamio_datos.h \
    vitrina/ui_almacen.h \
    vitrina/tienda.h \
    vitrina/empresa.h \
    vitrina/ui_vitrina_agregar.h \
    vitrina/ui_item_posicion.h \
    vitrina/item_posicion.h \
    vitrina/andamio.h \
    vitrina/ui_almacen_datos.h \
    vitrina/ui_contenedor_datos.h \
    vitrina/almacen.h \
    vitrina/contenedor.h \
    vitrina/ui_ui_almacen_datos.h \
    configuracion/usuariosform.h \
    configuracion/usuario.h \
    configuracion/ui_login.h \
    configuracion/ui_cambiarpassdialog.h \
    configuracion/sesion.h \
    configuracion/dialoglogin.h \
    configuracion/dialogbuscarusuarios.h \
    configuracion/configurador.h \
    configuracion/conexionbd.h \
    vitrina/ui_agregar_empresa.h \
    configuracion/ui_configuracion.h \
    configuracion/tusuario.h \
    cliente/documento.h \
    reporte/ui_reporte.h \
    venta/uiventas.h \
    producto/tipootros.h \
    compra/ui_cant_item.h \
    compra/ui_datos_compras.h \
    compra/compras.h \
    compra/ui_proveedores.h \
    compra/ui_datos_proveedor.h \
    compra/proveedor.h \
    compra/compra.h \
    producto/genero.h \
    agenda/newalerta_alerta_ui.h \
    agenda/funciones.h \
    agenda/agenda_ui.h \
    agenda/alerta.h

FORMS    += mainwindow.ui \
    producto/ui_producto.ui \
    producto/ui_agregarmontura.ui \
    producto/ui_agregarluna.ui \
    cliente/ui_medidas_historial.ui \
    cliente/ui_historial_clinico.ui \
    cliente/ui_cliente_datos.ui \
    cliente/ui_cliente.ui \
    producto/ui_agregarlente.ui \
    producto/ui_agregarotros.ui \
    extras/ui_trabajosextras.ui \
    vitrina/ui_vitrina_agregar.ui \
    vitrina/ui_traspaso_almacen.ui \
    vitrina/ui_tienda.ui \
    vitrina/ui_andamio_datos.ui \
    vitrina/ui_almacen.ui \
    vitrina/ui_item_posicion.ui \
    vitrina/ui_contenedor_datos.ui \
    vitrina/ui_tienda_agregar.ui \
    configuracion/usuariosform.ui \
    configuracion/ui_login.ui \
    configuracion/ui_cambiarpassdialog.ui \
    configuracion/dialoglogin.ui \
    configuracion/dialogbuscarusuarios.ui \
    vitrina/ui_agregar_empresa.ui \
    configuracion/ui_configuracion.ui \
    reporte/ui_reporte.ui \
    venta/uiventas.ui \
    compra/ui_cant_item.ui \
    compra/ui_datos_compras.ui \
    compra/compras.ui \
    compra/ui_proveedores.ui \
    compra/ui_datos_proveedor.ui \
    agenda/newalerta_alerta_ui.ui \
    agenda/agenda_ui.ui

RESOURCES += \
    Icons/Icons.qrc \





OTHER_FILES += \
    configuracion/config.ini
