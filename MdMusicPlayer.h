/* インクルードガード */
#pragma once

#include <M5Stack.h>

class MdMusicPlayer // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void init();
    char* getTitle();
    void selectNextMusic();
    void prepareMP3();
    bool isRunningMP3();
    bool playMP3();
    void stopMP3();
};
