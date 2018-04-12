#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "music.h"
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    total=0;
    mysong= new SongDialog;
    mydialog = new Dialog;
    player = music::getInstance().getPlayer();
    playlist = music::getInstance().getPlaylist();
    ui->pushButton->setText("────────────\n╔═╦╗╔═╗╔╦╗\n║╬║╚╣╬╚╣║║\n║╔╩═╩══╬╗║\n╚╝─────╚═╝");
    duration = 0;
    playPauseCounter = 1;

    player->setVolume(50);
    defaultVolume = ui->dial->value();
    player->setPlaylist(playlist);


   connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
   connect(player, SIGNAL(positionChanged(qint64)), this,SLOT(positionChanged(qint64)));
   connect(ui->pushButton_7,SIGNAL(clicked()),playlist,SLOT(shuffle()));
   connect(player,SIGNAL(metaDataAvailableChanged(bool)),this,SLOT(updateSong()));
   connect(player,SIGNAL(volumeChanged(int)),this,SLOT(chanegeVolLCD()));
   connect(player,SIGNAL(playbackRateChanged(qreal)),this,SLOT(chanegeSpeedLCD()));
   connect(ui->pushButton_5,SIGNAL(clicked()),playlist,SLOT(next()));
   connect(ui->pushButton_6,SIGNAL(clicked()),playlist,SLOT(previous()));
   connect(ui->pushButton_11,SIGNAL(clicked()),mysong,SLOT(show()));
   connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(deleteAction()));
   connect(ui->actionAbout_Us,SIGNAL(triggered()),mydialog,SLOT(show()));
   connect(ui->pushButton_12,SIGNAL(clicked()),this,SLOT(changePosUp()));
   connect(ui->pushButton_13,SIGNAL(clicked()),this,SLOT(changePosDown()));
   connect(playlist,SIGNAL(loadFailed()),this,SLOT(loadError()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   if(!playlist->isEmpty()){
        if(playPauseCounter == 1){
            ui->pushButton->setText("───────╔═╗──\n╔═╦═╗╔╦╣═╬═╗\n║╬║╬╚╣║╠═║╩╣\n║╔╩══╩═╩═╩═╝\n╚╝──────────");
            player->play();
            playPauseCounter = 2;
         }
        else{
            ui->pushButton->setText("────────────\n╔═╦╗╔═╗╔╦╗\n║╬║╚╣╬╚╣║║\n║╔╩═╩══╬╗║\n╚╝─────╚═╝");
            player->pause();
            playPauseCounter =1;
        }
    }else{
        openMediaFile();
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton->setText("────────────\n╔═╦╗╔═╗╔╦╗\n║╬║╚╣╬╚╣║║\n║╔╩═╩══╬╗║\n╚╝─────╚═╝");
    player->stop();
    playPauseCounter = 1;
}


void MainWindow::openMediaFile(){
    fileNames = QFileDialog::getOpenFileNames(this, "Open Song File","","MP3 files (*.mp3)");

    foreach (QString argument, fileNames) {

            QUrl url(argument);
            if (url.isValid()) {
                playlist->addMedia(url);
        }
        ui->listWidget->addItem(url.fileName());

        }
    total = playlist->mediaCount();
}




void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qreal v = value/100;
    player->setPlaybackRate(v);



}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
     player->setVolume(position);
     defaultVolume = position;

     if(ui->checkBox->isChecked()){
         ui->checkBox->setChecked(false);
     }

}



void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked==true)
        player->setVolume(0);
    else
        player->setVolume(defaultVolume);
}

void MainWindow::on_actionOpen_File_triggered()
{
    openMediaFile();
}


void MainWindow::deleteAction(){
    playlist->removeMedia(ui->listWidget->currentRow());
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void MainWindow::on_listWidget_activated()
{
    ui->songBar->setRange(0, player->duration() / 1000);
    playlist->setCurrentIndex(ui->listWidget->currentRow());
    ui->pushButton->setText("───────╔═╗──\n╔═╦═╗╔╦╣═╬═╗\n║╬║╬╚╣║╠═║╩╣\n║╔╩══╩═╩═╩═╝\n╚╝──────────");
    playPauseCounter =2;
    player->play();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        deleteAction();
}


void MainWindow::positionChanged(qint64 progress)
{
        ui->songBar->setValue(progress / 1000);
        show_time(progress/1000);
}


void MainWindow::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    ui->songBar->setMaximum(duration / 1000);
}

void MainWindow::show_time(quint64 currentInfo){

        QString tStr;
            QTime currentTime(0,(currentInfo/60)%60, currentInfo%60);
            QTime totalTime(0,(duration/60)%60, duration%60);
            QString format = "mm:ss";
            tStr = currentTime.toString(format) + " / " + totalTime.toString(format);

        ui->label->setText(tStr);

}


void MainWindow::on_songBar_sliderMoved(int position)
{
    player->setPosition(position*1000);
}

void MainWindow::on_pushButton_2_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    ui->pushButton->setText("────────────\n╔═╦╗╔═╗╔╦╗\n║╬║╚╣╬╚╣║║\n║╔╩═╩══╬╗║\n╚╝─────╚═╝");
    player->stop();
    playPauseCounter = 1;
}


void MainWindow::on_actionZapisz_triggered()
{
    playlistName=QFileDialog::getSaveFileName(this,"Lista odtwarznia- zapisz jako","/nowaplaylista","Plik m3u (*.m3u)");
    if(!playlistName.isEmpty()){

        if(!playlist->save(QUrl::fromLocalFile(playlistName),"m3u")){
            QMessageBox::information(this,tr("Error"),"Save error, try again");
        }

        }
    //playlist->save("d/",".m3u");

    //QUrl playlistUrl(playlistName);
   // playlist->save(playlistUrl,0);
}

void MainWindow::on_actionWczytaj_triggered()
{
    playlistName = QFileDialog::getOpenFileName(this, "Otworz playliste","","MP3 playlist files (*.m3u)");
    if(!playlistName.isNull()){
        playlist->clear();
        playlist->load(QUrl::fromLocalFile(playlistName),"*.m3u");
        ui->listWidget->clear();
        for(int i=0;i<playlist->mediaCount();i++){
          ui->listWidget->addItem(playlist->media(i).canonicalUrl().fileName());
        }
    }

}

void MainWindow::on_pushButton_7_clicked()
{
   ui->listWidget->clear();
   for(int i=0;i<playlist->mediaCount();i++){
     ui->listWidget->addItem(playlist->media(i).canonicalUrl().fileName());
   }

}

void MainWindow::on_pushButton_8_clicked()
{
    if(playlist->playbackMode()==0){
        playlist->setPlaybackMode(playlist->CurrentItemInLoop);
        ui->label_4->setText("Song in Loop");
    }
    else{
        playlist->setPlaybackMode(playlist->CurrentItemOnce);
        ui->label_4->setText("Song play Once");
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(playlist->playbackMode()==2){
        playlist->setPlaybackMode(playlist->Loop);
        ui->label_4->setText("Playlist in Loop");
    }
    else{
        playlist->setPlaybackMode(playlist->Sequential);
        ui->label_4->setText("Playlist Sequential");
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    playlist->setPlaybackMode(playlist->Random);
    ui->label_4->setText("Play Song Random");

}


void MainWindow::on_dial_valueChanged(int value)
{
    player->setVolume(value);
    defaultVolume = value;

    if(ui->checkBox->isChecked()){
        ui->checkBox->setChecked(false);
    }
}

void MainWindow::updateSong(){
    mysong->setInfo2(playlist->currentMedia().canonicalUrl().fileName(),playlist->currentMedia().canonicalUrl().toLocalFile(),player->metaData("AudioBitRate").toString(),player->metaData("AudioCodec").toString(),player->metaData("ChannelCount").toString(),player->metaData("SampleRate").toString());
    mysong->setInfo(player->metaData("Author").toString(),player->metaData("Title").toString(),player->metaData("AlbumTitle").toString(),player->metaData("Year").toString(),player->metaData("TrackNumber").toString(),player->metaData("Genre").toString(),player->metaData("Duration").toString());
    ui->label_2->setText(player->metaData("Author").toString());
    ui->label_3->setText(player->metaData("Title").toString());

    qDebug()<<"update done ";
}

void MainWindow::chanegeVolLCD(){
    ui->label_4->setText("Volumne: "+QString::number(player->volume())+"%");

}

void   MainWindow::closeEvent(QCloseEvent*)
{
    qApp->quit();
}

void MainWindow::changePosUp(){
    int tempIndex=ui->listWidget->currentRow();
    if(tempIndex>0){
        QMediaContent tempMedia=playlist->media(tempIndex);
        playlist->removeMedia(tempIndex);
        playlist->insertMedia(tempIndex-1,tempMedia);

        ui->listWidget->clear();
        for(int i=0;i<playlist->mediaCount();i++){
          ui->listWidget->addItem(playlist->media(i).canonicalUrl().fileName());
        }
    }
}

void MainWindow::changePosDown(){
    int tempIndex=ui->listWidget->currentRow();
    if((tempIndex<(playlist->mediaCount()-1))&&(tempIndex!=-1)){
        QMediaContent tempMedia=playlist->media(tempIndex);
        playlist->removeMedia(tempIndex);
        playlist->insertMedia(tempIndex+1,tempMedia);

        ui->listWidget->clear();
        for(int i=0;i<playlist->mediaCount();i++){
          ui->listWidget->addItem(playlist->media(i).canonicalUrl().fileName());
        }
    }
}

void MainWindow::chanegeSpeedLCD(){
    ui->label_4->setText("Song Speed: "+QString::number(player->playbackRate())+"x");

}

void MainWindow::loadError(){
    QMessageBox::information(this,tr("Error"),"Load error, try again");
}
