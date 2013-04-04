#ifndef UI_CLIENTE_H
#define UI_CLIENTE_H

#include <QWidget>
#include <cliente/ui_historial_clinico.h>
#include <cliente/ui_cliente_datos.h>
#include <cliente/ui_medidas_historial.h>
#include <QList>

namespace Ui {
class ui_cliente;
}

class ui_cliente : public QWidget
{
    Q_OBJECT
    
public:
    explicit ui_cliente(QWidget *parent = 0);
    ~ui_cliente();
    
private slots:
    void listar_clientes();
    void listar_historial();
    void historial_clinico(const QModelIndex &);
    void medidas_historial(const QModelIndex &);
    void enviar_cliente(const QModelIndex &);
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_NuevoHistorial_clicked();
    void on_EditarHistorial_clicked();
    void on_BorrarHistorial_clicked();

    void on_pushButton_buscar_clicked();
    void on_pushButton_Informe_clicked();

public slots:
    void setComportamiento(int a);
signals:
    void sentCliente(QString,QString,QString);
private:
    Ui::ui_cliente *ui;
    cliente clt_his;
    int comportamiento;
};

#endif // UI_CLIENTE_H
