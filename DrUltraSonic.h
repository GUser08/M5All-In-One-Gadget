/* インクルードガード */
#pragma once


class DrUltraSonic // classの定義
{
private: // privateはクラス内からしかアクセスできない
    int m_echo_pin;
    int m_trig_pin;

public: // publicはどこからでもアクセス可能
    DrUltraSonic(int echo_pin, int trig_pin);
    double measureReturnTime();
};



