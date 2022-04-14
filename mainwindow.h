#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "filedownloader.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QByteArray downloadedData() const;
    QTcpSocket* socket;
    QByteArrayList Data;

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void loadImage();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QList<FileDownloader *> list;
    QList<QPixmap> listPix;
    FileDownloader * m_pImgCtrl;
    QStringList ls;
    Ui::MainWindow *ui;
    qsizetype currentImageIndex = 0;
};

#endif // MAINWINDOW_H
