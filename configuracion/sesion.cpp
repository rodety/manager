#include "sesion.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <vector>
#include <QMessageBox>

Sesion* Sesion::mp_instance = 0;
int Sesion::intentos = 0;
bool Sesion::sleep = false;
QTime Sesion::tiempoBloqueo = QTime();

int Sesion::numMinIntentos = 0;
int Sesion::numMaxIntentos = 0;
int Sesion::tiempoEspera = 0;
int Sesion::idEmpresa = 0;
int Sesion::idTienda = 0;
double Sesion::impuesto = 0;

Sesion::Sesion(Usuario * usr)
{
    s_user = usr;
    s_time.start();
}

/**
 *@brief Configura los parámetros de incio de sesion.
 *@param nminI numero minimo de intentos despues de los cuales se bloquera el inicio de sesion
 *@param nmaxI numero maximo de intentos despues de el cual se deshablitara la cuenta.
 *@param tEspera tiempo en msecs que se bloqueara el inicio de sesion
 */
void Sesion::Configurar(int nminI,int nmaxI,int tEspera)
{
    numMinIntentos = nminI;
    numMaxIntentos = nmaxI;
    tiempoEspera = tEspera;
}

/**
 * @brief Verifica si el usuario y el pass son correctos en la base de datos para iniciar sesion si no retorna false
 * @param user Nombre de usuario
 * @param pass Contraseña de usuario
 * @return Codigo de estado de intento de incio de sesion
 */
int Sesion::Iniciar(QString user, QString pass)
{
    if(sleep&&tiempoBloqueo.elapsed()<tiempoEspera) ///<Si el incio de sesion esta dentro de el tiempo de bloqueo
        return Sesion::SleepTime;                   ///<Retorna bloqueo
    QSqlQuery q;
    bool ok = q.exec("select * from Colaborador where usuario = '"+user+"'and contrasena = MD5('"+pass+"')"); ///<Verifica si el usuario y el pass estan registrados
    if(!ok) qDebug()<<q.lastError().text();
    if(!q.next())                                   ///<Si no se producen resultados
    {
        intentos ++;                                ///<Se aumenta el numero de intentos;
        if(intentos >= numMaxIntentos)              ///<Si el numero de intentos paso el numero maximo de intentos
        {
            if(q.exec("call deshabilitarUsr("+user+")")) ///<se deshabilita la cuenta
                return Sesion::UsuarioDeshabilitado;
        }
        else if(!(intentos%numMinIntentos))         ///<Si se ha alcanzado el numero minimo de intentos
        {
            sleep = true;                           ///<se bloquea el incio de sesion
            tiempoBloqueo.restart();                ///<se inicia la cuenta de tiempo
            return Sesion::SleepTime;
        }
        return Sesion::PassUsrWrong;
    }
    QSqlRecord rec = q.record();
    if(!rec.value("habilitado").toBool())   ///<se verifica si el usuario esta deshabilitado
        return Sesion::UsuarioDeshabilitado;

    Usuario * usr = new Usuario(rec.value("idcolaborador").toInt(),
                                rec.value("idtipo_colaborador").toInt(),
                                rec.value("nombre_usuario").toString(),
                                rec.value("nombre").toString(),
                                rec.value("primer_apellido").toString(),
                                rec.value("segundo_apellido").toString());
    mp_instance = new Sesion(usr);
    intentos = 0;
    if(rec.value("reset_pass").toBool())    ///<se verifica si se requiere cambio de contraseña
        return Sesion::ResetPass;
    return Sesion::inicioOK;
}

/**
 * @brief Obtiene la sesion iniciada
 * @return Puntero a la session
 */
Sesion * Sesion::getSesion()
{
    return mp_instance;
}

std::map<int,bool> Sesion::get_Permisos()
{
    std::map<int,bool> res;
    QSqlQuery q("select habilitado,FuncionModulo_idFuncionModulo from Permiso where Colaborador_Persona_idPersona = "+QString::number(s_user->get_id())+" order by FuncionModulo_idFuncionModulo");
    if(!q.exec())
        QMessageBox::critical(0,"Error permisos",q.lastError().text(),0,0);
    while(q.next())
    {
        res[q.value(1).toInt()] = (q.value(0).toBool());
    }
    return res;
}

QPair<int,int> Sesion::getUbicacion()
{
    QPair<int,int> a;
    a.first = idEmpresa;
    a.second = idTienda;

}

void Sesion::setUbicacion(int a, int b)
{
    idEmpresa = a;
    idTienda = b;
    QSqlQuery query;
    query.prepare("SELECT igv FROM Configuracion WHERE Tienda_idTienda =?");
    query.bindValue(0,idTienda);
    if(query.exec())
    {
        impuesto = query.value(0).toString().toDouble();
    }
    else
    {
        impuesto = 0;
        QMessageBox::critical(0,"Error igv",query.lastError().text(),0,0);
    }
}

