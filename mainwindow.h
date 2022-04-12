#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


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
    QByteArray Data;
    void saveImage();

signals:
  void downloaded();

public slots:
    void sockReady();
    void sockDisc();


private slots:
    void fileDownloaded(QNetworkReply* pReply);
    void on_pushButton_clicked();

private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
