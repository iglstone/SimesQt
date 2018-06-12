#ifndef CONSIEMENSPLCS_H
#define CONSIEMENSPLCS_H

#include <QDialog>
#include <QMessageBox>
#include "plcqtlib.h"
#include <QDebug>
#include <QTimer>

namespace Ui {
class ConSiemensPlcs;
}

class ConSiemensPlcs : public QDialog
{
    Q_OBJECT

public:
    explicit ConSiemensPlcs(QWidget *parent = 0);
    ~ConSiemensPlcs();

signals:
    void NetPlcStato(bool);

private slots:
    void on_BtConnectPlc_clicked();
    void PlcOk();
    void TimEvent();
    int i;

private:
    Ui::ConSiemensPlcs *ui;
    bool plcok;
    QTimer *timer;
    Plcqtlib *siemsPlc;

    void Mess(QString msg);

};

#endif // CONSIEMENSPLCS_H
