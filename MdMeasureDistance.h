/* インクルードガード */
#pragma once
#include <M5Stack.h>

class MdMeasureDistance // classの定義
{
private: // privateはクラス内からしかアクセスできない
public:  // publicはどこからでもアクセス可能
  double getDistance();   
};
