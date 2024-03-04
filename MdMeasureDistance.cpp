#include "MdMeasureDistance.h"
#include <Arduino.h>
#include "DrUltraSonic.h"        //作った（DrUltraSonic）呼び出すためのヘッダーファイルをインクルード
#include "M5All-In-One-Gadget.h" //作った(ECHO_PIN, TRIG_PIN)呼び出すためのヘッダーファイルをインクルード

DrUltraSonic drul = DrUltraSonic(ECHO_PIN, TRIG_PIN); // インスタンスの初期化。引数ECHO_PIN5, TRIG_PIN2渡す

double MdMeasureDistance::getDistance()//戻り値はダブル型、MdMeasureDistanceクラスの変数名はgetDistance引数はなし
{
    double distance = 0;

    distance = drul.measureReturnTime() * 340 * (0.000001) * 0.5 * 100; //measureReturnTime超音波が返ってくるまでの時間の取得。関数呼び出し

    return distance;//戻り値はdistanceを返す。
}