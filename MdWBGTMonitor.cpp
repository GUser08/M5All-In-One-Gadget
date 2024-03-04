#include "MdWBGTMonitor.h"
#include "DrTHSensor.h" //センサーのヘッダーをインクルード

DrTHSensor dthsen; // DrTHSensorクラスのインスタンス化

void MdWBGTMonitor::init() // MdWBGTMonitorクラスのinit関数の呼び出し（MdWBGTMonitor）クラスの関数を呼び出す関数の前（：：)につける
{
    dthsen.init(); // インスタンス化した「dthsen.」のinitを実行して初期化
}

void MdWBGTMonitor::getWBGT(double *temperature, double *humidity, WbgtIndex *index)
{

    dthsen.getTempHumi(temperature, humidity); // 温度と湿度の値を取得して、temperature（温度）、humidity（湿度）の箱に値をいれる。※閉じカッコを忘れない！！
    // index = 0.68 * 温度[℃] ＋ 0.12 * 湿度[%]
    int calc_index = (int)(0.68 * *temperature + 0.12 * *humidity); // intの箱をつくってキャスト演算子でダブル型→int型のcalc_indexに代入

    if (calc_index < 15)//計算した結果もとに分類わけをしている。
    {
        *index = SAFE;//SAFE～DANGERの値をindexのアドレスに格納（M5All-In-One-Gadget.hよりWbgtIndex の値）
    }

    else if (calc_index < 24)
    {
        *index = ATTENTION;
    }
    else if (calc_index < 27)
    {
        *index = ALERT;
    }

    else if (calc_index < 30)
    {
        *index = HIGH_ALERT;
    }
    else if (calc_index > 31)
    {
        *index = DANGER;
    }
}
