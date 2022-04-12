#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap;
    QFile file("https://images.pexels.com/photos/674010/pexels-photo-674010.jpeg?auto=compress&cs=tinysrgb&h=750&w=1260");
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
    pixmap.load("https://images.pexels.com/photos/674010/pexels-photo-674010.jpeg?auto=compress&cs=tinysrgb&h=750&w=1260");
    ui->label->setPixmap(pixmap);
    QUrl imageUrl("http: //qt.digia.com/Documents/1/QtLogo.png");
    connect(
     &m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
     this, SLOT (fileDownloaded(QNetworkReply*))
    );

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
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
        Data = socket->readAll();
        QFile file("out.txt");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << Data;
            qDebug() << Data;
            file.close();

    }
}

void MainWindow::fileDownloaded(QNetworkReply* pReply){
 m_DownloadedData = pReply->readAll();
 //emit a signal
 pReply->deleteLater();
 emit downloaded();
}

QByteArray MainWindow::downloadedData() const{
    return m_DownloadedData;
}

void MainWindow::saveImage()
{


}


