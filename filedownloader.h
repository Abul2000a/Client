#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>

class QNetworkReply;
class QNetworkRequest;

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    FileDownloader(){}
    explicit FileDownloader(QUrl imageUrl, QObject *parent = nullptr);
    QByteArray downloadedData() const;

signals:
    void downloaded();

private slots:
    void fileDownloaded(QNetworkReply* pReply);
private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
};

#endif // FILEDOWNLOADER_H
