#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "filedownloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),socket(new QTcpSocket(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    if(qobject_cast<QAbstractSocket*>(sender())) {
        sender()->deleteLater();
    }
}


void MainWindow::sockReady()
{
    FileDownloader * m_pImgCtrl;
    QString s = socket->readAll();
    QStringList ls = s.split("$~");

    for(int i = 0;i < ls.size();i++){
        m_pImgCtrl = new FileDownloader(ls[i],this);
        list.push_back(m_pImgCtrl);
    }

    socket = new QTcpSocket(this);
    connect(m_pImgCtrl, &FileDownloader::downloaded, this, &MainWindow::loadImage);

}


void MainWindow::loadImage()
{
    QPixmap Image;
    Image.loadFromData(list[currentImageIndex % list.size()]->downloadedData());
    ui->label->setPixmap(Image);
}


void MainWindow::on_pushButton_2_clicked()
{
    ++currentImageIndex;
    loadImage();
}




