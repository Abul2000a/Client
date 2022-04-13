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
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

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
        QStringList ls = s.split(",");
        qDebug() << ls[0];
        for(int i = 0; i < ls.size();++i){
            QUrl imageUrl(ls[i]);
            m_pImgCtrl = new FileDownloader(imageUrl, this);

            connect(m_pImgCtrl, SIGNAL(downloaded()),SLOT(loadImage()));
        }

    }
}


void MainWindow::loadImage()
{
    QPixmap buttonImage;
    buttonImage.loadFromData(m_pImgCtrl->downloadedData());
    ui->label->setPixmap(buttonImage);
}


