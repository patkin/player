#include "aboutartist.h"
#include "ui_aboutartist.h"

AboutArtist::AboutArtist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutArtist)
{
    ui->setupUi(this);

}

AboutArtist::~AboutArtist()
{
    delete ui;
}

void AboutArtist::setWebInfo(QString search){
    adres=QUrl("http://m.lastfm.pl/music/"+search);
}
void AboutArtist::setSongInfo(QString name,QString title){
    adres=QUrl("http://www.tekstowo.pl/drukuj,"+name.replace(" ","_")+","+title.replace(" ","_")+".html");
}

void AboutArtist::LoadPage(){
    ui->webView->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->webView->load(adres);

}

