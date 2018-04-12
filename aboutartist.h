#ifndef ABOUTARTIST_H
#define ABOUTARTIST_H
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include <QtNetwork>


#include <QDialog>

namespace Ui {
class AboutArtist;
}

class AboutArtist : public QDialog
{
    Q_OBJECT

public:
    explicit AboutArtist(QWidget *parent = 0);
    ~AboutArtist();
    void setWebInfo(QString);
    void setSongInfo(QString,QString);

private:
    Ui::AboutArtist *ui;
    QWebView *view;
    QUrl adres;
public slots:
    void LoadPage();

};

#endif // ABOUTARTIST_H
