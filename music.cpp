#include "music.h"

music::music()
{
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
}

music::~music()
{

}

QMediaPlayer* music::getPlayer(){
    return player;
}

QMediaPlaylist* music::getPlaylist(){
    return playlist;
}
