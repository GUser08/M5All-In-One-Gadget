/* インクルードガード */
#pragma once
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>

class MdDateTime // classの定義
{
private: // privateはクラス内からしかアクセスできない
    TinyGPSPlus gps;

public: // publicはどこからでもアクセス可能
    MdDateTime();
    String readDate();
    String readTime();
};
