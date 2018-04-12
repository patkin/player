#include "songdialog.h"
#include "ui_songdialog.h"

SongDialog::SongDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SongDialog)
{
    ui->setupUi(this);
    aboutA=new AboutArtist;
    aboutB=new AboutArtist;
    connect(ui->pushButton,SIGNAL(clicked()),aboutA,SLOT(LoadPage()));
    connect(ui->pushButton,SIGNAL(clicked()),aboutA,SLOT(show()));
    connect(ui->pushButton_2,SIGNAL(clicked()),aboutB,SLOT(LoadPage()));
    connect(ui->pushButton_2,SIGNAL(clicked()),aboutB,SLOT(show()));
}

SongDialog::~SongDialog()
{
    delete ui;
}

void SongDialog::setInfo (QString author,QString title,QString album,QString year,QString number,QString category, QString duration){
ui->listWidget->clear();
ui->listWidget->addItem("Autor: "+author);
ui->listWidget->addItem("Tytuł: "+title);
ui->listWidget->addItem("Album: "+album);
ui->listWidget->addItem("Kategoria: "+category);
ui->listWidget->addItem("Rok produkcji: "+year);
ui->listWidget->addItem("Numer na albumie: "+number);
ui->listWidget->addItem("Czas trwania: "+duration+"ms");
if(!author.isEmpty()){
    aboutA->setWebInfo(author);
}
    aboutB->setSongInfo(author,title);
}

void SongDialog::setInfo2 (QString name,QString url,QString bit,QString codec,QString canal,QString rate){
ui->listWidget_2->clear();
ui->listWidget_2->addItem("Nazwa pliku: "+name);
ui->listWidget_2->addItem("Ścieżka: "+url);
ui->listWidget_2->addItem("Bit Rate: "+bit);
ui->listWidget_2->addItem("Sample Rate: "+rate);
ui->listWidget_2->addItem("Kodek: "+codec);
ui->listWidget_2->addItem("Kanały: "+canal);
}

