#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
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

private:
    FileDownloader* m_pImgCtrl;
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
