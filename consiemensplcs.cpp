#include "ConSiemensPlcs.h"
#include "ui_consiemensplcs.h"

ConSiemensPlcs::ConSiemensPlcs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConSiemensPlcs)
{
    ui->setupUi(this);

    siemsPlc = new Plcqtlib();
    timer = new QTimer();
    plcok = false;

    connect(timer, SIGNAL(timeout()), this, SLOT(TimEvent()));
    connect(this,SIGNAL(NetPlcStato(bool)),this,SLOT(PlcOk()));

    timer->start(2000);// update every 2 secends
}

ConSiemensPlcs::~ConSiemensPlcs()
{
    delete ui;
}

void ConSiemensPlcs::Mess(QString msg)
{
    QMessageBox msgBox;
    //msgBox.setText("Not connected Plc");
    msgBox.setText(msg);
    msgBox.exec();
}

void ConSiemensPlcs::PlcOk()
{
    QString msg = "Connect Success!";
    this->Mess(msg);
}

void ConSiemensPlcs::TimEvent()
{
    if(plcok == true){
        float datoint ;
        // try to read data from plc
        datoint = siemsPlc ->getDbReal(1,2);
        //        datoint = siemsPlc->

        qDebug("xxx %f", datoint);
    }else{
        qDebug("plc not connectd!");
    }
}

void ConSiemensPlcs::on_BtConnectPlc_clicked()
{
    QString plcType = "S71200"; // or "S7200"
    QString plcIP = "192.168.0.100";

    int statotcp = siemsPlc->setTcp(plcIP, 102);

    int mpi,rack,slot;
    mpi = 2;    rack = 0;    slot = 0;
    int statoplc = siemsPlc->setPlc(plcType,mpi,rack,slot);

    if ((statotcp == 0) & (statoplc == 0) ){
        plcok = true;
        emit NetPlcStato(plcok);

        QString adr;
        int port;
        port = siemsPlc->getPort();
        adr = "port:" + adr.setNum(port);
        qDebug("%s", qPrintable(adr));
        int sock;
        sock = siemsPlc->getSocketDescriptor();
        adr = "socket:" + adr.setNum(sock);
        qDebug("%s", qPrintable(adr));
        adr = siemsPlc->getError();
        qDebug("%s", qPrintable(adr));
        adr = adr.setNum(statoplc);
        qDebug("%s", qPrintable(adr));

    }else {
        plcok = false;
        QString msg = "Not connected With Plc";
        this->Mess(msg);
    }
}
