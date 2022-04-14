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

private slots:
    void sockReady();
    void sockDisc();
    void loadImage();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    QTcpSocket* socket;
    QList<FileDownloader *> list;
    qsizetype currentImageIndex = 0;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
