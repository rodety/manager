#include <QApplication>
#include "mainwindow.h"
#include "configuracion/ui_login.h"
#include "configuracion/conexionbd.h"
#include "configuracion/sesion.h"
#include "configuracion/configurador.h"
#include "configuracion/dialoglogin.h"
#include "configuracion/ui_configuracion.h"

#include <QMessageBox>
#include <QTextCodec>
#include <QSplashScreen>
#include <QTimer>
#include <QSqlError>
#include <QDebug>

int main(int argc,char *argv[])
{

    QApplication a (argc,argv);


    if(a.arguments().contains("--without-login"))
    {
      MainWindow *MAIN_WINDOW;
      MAIN_WINDOW = new MainWindow;
      MAIN_WINDOW->showMaximized();
      return a.exec();
    }

    QTextCodec* linuxCodec=QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForTr(linuxCodec);
    //QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);




    QPixmap pix(":/Icons/splash.png");
    pix = pix.scaled(800,450);
    QSplashScreen splash(pix);
    splash.show();
    splash.showMessage("Cargando Modulos",Qt::AlignLeft,Qt::white);
    configurador config("config.ini");
    if(config.conectar_db())
    {        
        Sesion::Configurar(3,10,6000);
        DialogLogin * log = new DialogLogin;
        log->exec();        
        if(log->getOk())
        {     
            MainWindow *MAIN_WINDOW;
            MAIN_WINDOW = new MainWindow;
            MAIN_WINDOW->showMaximized();
        }
        splash.close();
        delete log;
    }
    else
    {
        ui_configuracion *form = new ui_configuracion;
        form->show();
    }

    return a.exec();
}
