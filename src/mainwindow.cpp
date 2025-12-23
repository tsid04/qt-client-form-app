#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QTcpSocket();
    port=12345;
    ip=QHostAddress("127.0.0.1");
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::timerCall);
    timer->setInterval(200);


    for (int i=0; i<100; ++i)
    {
      x.append ( 3*M_PI*(i/100.0) ); // x goes from 0 to 1
      y.append ( cos(x[i]) ); // let's plot a quadratic function
      counter++;
    }
    // create graph and assign data to it:
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("time (s)");
    ui->plot->yAxis->setLabel("cos(x)");
    // set axes ranges, so we see allvoid data:
    ui->plot->xAxis->setRange(-3, 10);
    ui->plot->yAxis->setRange(-1.5, 1.5);

    ui->plot->replot();

}

void MainWindow::timerCall(){

    x.append ( 3*M_PI*(counter/100.0) ); // x goes from 0 to 1
    y.append ( cos(x[100]) ); // let's plot a quadratic function
    x.removeFirst();
    y.removeFirst();
    ui->plot->graph(0)->setData(x, y);
    ui->plot->xAxis->setRange(3*M_PI*(counter/100.0)-3, 3*M_PI*(counter/100.0));

    ui->plot->replot();

    counter++;

}


MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::on_ServerConnect_clicked()
{
    if (client->state() == QAbstractSocket::ConnectedState) {
        client->disconnectFromHost();
    }

    else {
        client->connectToHost(ip, port);
    }

}

void MainWindow::on_SendsMessage_clicked()
{
    QByteArray ba = "taqwa";
    client->write(ba);
}

void MainWindow::on_btnPlotDiagram_clicked()
{
    if (timer->isActive()) {
        timer->stop();
    }

    else {
        timer->start();
    }
}

