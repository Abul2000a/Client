#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "filedownloader.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    socket(new QTcpSocket(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::sockReady);
}


MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
    clearList();
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost(ui->lineEdit->text(),5555);
}


void MainWindow::clearList(){
    for(int i = 0; i < list.size(); i++){
        if(list[i] != nullptr){
            delete list[i];
            list[i]=nullptr;
        }
    }
        list.clear();
}


void MainWindow::sockReady()
{
    clearList();
    FileDownloader * m_pImgCtrl = nullptr;
    ui->lineEdit->setText("Connected Press Next");
    QString readSocket = socket->readAll();
    readSocket.remove('\n');
    QStringList splitedUrls = readSocket.split("...", Qt::SkipEmptyParts);
    for(int i = 0; i < splitedUrls.size(); i++){
        m_pImgCtrl = new FileDownloader(splitedUrls[i]);

        list.push_back(m_pImgCtrl);

    }

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




