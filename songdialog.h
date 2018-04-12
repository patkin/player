#ifndef SONGDIALOG_H
#define SONGDIALOG_H

#include <QDialog>
#include<aboutartist.h>

namespace Ui {
class SongDialog;
}

class SongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SongDialog(QWidget *parent = 0);
    ~SongDialog();
    void setInfo(QString,QString,QString,QString,QString,QString,QString);
    void setInfo2(QString,QString,QString,QString,QString,QString);

private:
    Ui::SongDialog *ui;
    AboutArtist *aboutA;
    AboutArtist *aboutB;
};

#endif // SONGDIALOG_H
