#ifndef UI_CONFIGURACION_H
#define UI_CONFIGURACION_H

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


private:
    Ui::ui_configuracion *ui;
    void saveConfiguration();
    map<QString,QString> Empresas;
    map<QString,QString> Tiendas;
    QString currentIdEmpresa;
    QString currentIdTienda;
};

#endif // UI_CONFIGURACION_H
