#ifndef UI_CONFIGURACION_H
#define UI_CONFIGURACION_H
#include "configurador.h"
#include <QWidget>
#include <map>
using namespace std;
namespace Ui {
class ui_configuracion;
}

class ui_configuracion : public QWidget
{
    Q_OBJECT

public:
    explicit ui_configuracion(QWidget *parent = 0);
    ~ui_configuracion();
public:
    void update_comboBox_Empresa();
    void update_comboBox_Tienda(QString idEmpresa);
    QString get_currentIdEmpresa();
    QString get_currentIdTienda();
    void set_currentIdEmpresa(QString);
    void set_currentIdTienda(QString);

private slots:
    void on_btn_testConexion_clicked();
    void on_comboBox_empresa_currentIndexChanged(const QString &arg1);
    void on_btn_saveConfiguration_clicked();
    void on_comboBox_tienda_currentTextChanged(const QString &arg1);

    void on_comboBox_tienda_currentIndexChanged(const QString &arg1);

    void on_btn_eliminar_ducumento_clicked();

    void on_btn_eliminar_tusuario_clicked();


    void on_btn_eliminar_estado_clicked();

    void on_btn_script_clicked();

    void on_comboBox_Documento_currentIndexChanged(const QString &arg1);

    void on_comboBox_tipoUsuario_currentIndexChanged(const QString &arg1);

    void on_comboBox_estadoProductos_currentIndexChanged(const QString &arg1);

    void on_btnAgregar_empresa_clicked();

private:
    Ui::ui_configuracion *ui;
    void saveConfiguration();
    map<QString,QString> Empresas;
    map<QString,QString> Tiendas;
    QString currentIdEmpresa;
    QString currentIdTienda;
    void loadConfiguration();
    configurador* config;
    std::map<int,QString> res;
    void controlbotones(bool a);

};

#endif // UI_CONFIGURACION_H
