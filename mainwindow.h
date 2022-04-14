#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTcpSocket;
class QNetworkReply;
class QNetworkRequest;
class FileDownloader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void sockReady();

private slots:

    void loadImage();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    FileDownloader * m_pImgCtrl = nullptr;
    QTcpSocket* socket;
    QList<FileDownloader *> list;
    qsizetype currentImageIndex = 0;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
