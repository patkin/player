#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <string>
#include <QtMultimedia>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QTime>
#include "dialog.h"
#include <QIcon>
#include<songdialog.h>
#include <QMediaMetaData>



#include <QListView>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_checkBox_toggled(bool checked);

    void on_actionOpen_File_triggered();

    void on_listWidget_activated();
    void deleteAction();

    void keyPressEvent ( QKeyEvent * event );

    void durationChanged(qint64 duration);

    void positionChanged(qint64 progress);

    void show_time(quint64 currentInfo);

    void on_songBar_sliderMoved(int position);

    void openMediaFile();

    void on_pushButton_2_clicked();

    void on_actionZapisz_triggered();

    void on_actionWczytaj_triggered();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_dial_valueChanged(int value);

    void updateSong();

    void chanegeVolLCD();

    void chanegeSpeedLCD();

    void changePosUp();

    void changePosDown();

    void loadError();

private:
    Ui::MainWindow *ui;

   QMediaPlayer *player;
   QStringList fileNames;
   QString playlistName;
   QMediaPlaylist *playlist;
   int total, playPauseCounter;
   int defaultVolume;
   quint64 duration;
   Dialog *mydialog;
   SongDialog *mysong;
protected:
    void  closeEvent(QCloseEvent*);

};

#endif // MAINWINDOW_H
