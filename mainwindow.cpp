#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtWidgets/QMainWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::sockDisc);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1",5555);
}


void MainWindow::sockDisc()
{
    socket->deleteLater();
}


void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        QString s = socket->readAll();
        ls = s.split(",");
        for(int i = 0;i < ls.size();i++){
            m_pImgCtrl = new FileDownloader(ls[i],this);
            list.push_back(m_pImgCtrl);
        }

    }

    connect(m_pImgCtrl, &FileDownloader::downloaded, this, &MainWindow::loadImage);

}


void MainWindow::loadImage()
{
    QPixmap buttonImage;
    buttonImage.loadFromData(list[currentImageIndex % list.size()]->downloadedData());
    ui->label->setPixmap(buttonImage);
}


void MainWindow::on_pushButton_2_clicked()
{
    ++currentImageIndex;
    loadImage();
    return;
}




