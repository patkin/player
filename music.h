#ifndef MUSIC_H
#define MUSIC_H
#include <QtMultimedia>
#include <QMediaPlaylist>

class music
{
private:
            music();
            music(const music &);
            music& operator=(const music&);
            ~music();
            QMediaPlayer *player;
            QMediaPlaylist *playlist;
public:
            static music& getInstance()
                    {
                      static music instance;
                      return instance;
                    }
            QMediaPlayer* getPlayer();
            QMediaPlaylist* getPlaylist();

};

#endif // MUSIC_H
