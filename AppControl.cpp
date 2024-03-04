#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char *g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char *g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH, 0, 0);
}

// メニュー画面
void AppControl::displayMenuInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, 0, 0);                // 熱中症
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, 0, 50);              // 音楽
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, 0, 100);           // 距離
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, 0, 150);              // 時刻
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, 0, 200);       // ボタン↑
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, 120, 200); // 決定
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, 240, 200);   // ボタン↓
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, 0, 0);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{

    setFocusState(next_state);

    switch (current_state)
    {
    case MENU_WBGT:
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, 0, 0);

        break;

    case MENU_MUSIC:

        mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, 0, 50);

        break;

    case MENU_MEASURE:

        mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, 0, 100);
        break;

    case MENU_DATE:

        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, 0, 150);
        break;
    }

    switch (next_state)
    {

    case MENU_WBGT:

        mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, 0, 0);
        break;

    case MENU_MUSIC:

        mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, 0, 50);
        break;

    case MENU_MEASURE:
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, 0, 100);

        break;

    case MENU_DATE:
        mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, 0, 150);

        break;
    }
}

void AppControl::displayWBGTInit() // 熱中症モニタ初期画面
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    displayTempHumiIndex();
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, 253, 0);
    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, 0, 50);
    mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, 253, 50);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, 186, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, 186, 50);
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, 0, 0);
}

void AppControl::displayTempHumiIndex() // 熱中症モニタの画面に温度・湿度・アラートを描画する
{

    double temperature; // 取得した温度を代入する箱（変数）
    double humidity;    // 取得した湿度を代入する箱（変数）
    WbgtIndex index;    // 取得したアラートを代入する箱（変数）

    mwbgt.init();//温湿度の値をとるために温湿度センサーの初期化
    mwbgt.getWBGT(&temperature, &humidity, &index); // MdWBGTMonitorクラスのgetWBGT関数を呼び出している。引数にアドレスを渡すから変数名の前に「＆」をつける。

    int numnum = (int)(temperature * 10); // intのnumnumの箱をつくって温度の値に*10をして整数にした、キャスト演算子でダブル型→int型にしたnumに代入
    int temp[3];                          // 数字を入れる箱を配列で作成
    temp[0] = (numnum / 100) % 10;        // 100の位を商と余りで求める
    temp[1] = (numnum / 10) % 10;         // 十の位を商と余りで求める
    temp[2] = numnum % 10;                // 余りとして一の位を求める

    int numm = (int)(humidity * 10); // intのnummの箱をつくって湿度の値に*10をして整数にした、キャスト演算子でダブル型→int型にしたnummに代入
    int humi[3];                     // 数字を入れる箱を配列で作成
    humi[0] = (numm / 100) % 10;     // 100の位を商と余りで求める
    humi[1] = (numm / 10) % 10;      // 十の位を商と余りで求める
    humi[2] = numm % 10;             // 余りとして一の位を求める

    mlcd.displayJpgImageCoordinate(g_str_orange[temp[0]], 120, 0); // オレンジの数字を表示させる。百の位
    mlcd.displayJpgImageCoordinate(g_str_orange[temp[1]], 153, 0); // 十の位
    mlcd.displayJpgImageCoordinate(g_str_orange[temp[2]], 220, 0); // 一の位

    mlcd.displayJpgImageCoordinate(g_str_blue[humi[0]], 120, 50); // blueの数字を表示させる。
    mlcd.displayJpgImageCoordinate(g_str_blue[humi[1]], 153, 50);
    mlcd.displayJpgImageCoordinate(g_str_blue[humi[2]], 220, 50);

    if (index == SAFE) // indexにはいている値をもとに画面表示する
    {
        mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, 0, 100);
    }
    else if (index == ATTENTION)
    {
        mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, 0, 100);
    }
    else if (index == ALERT)
    {
        mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, 0, 100);
    }
    else if (index == HIGH_ALERT)
    {
        mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, 0, 100);
    }
    else if (index == DANGER)
    {
        mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, 0, 100);
    }
}

void AppControl::displayMusicInit() // 音楽プレイヤーの初期画面
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    displayMusicStop();
}

void AppControl::displayMusicStop() // 音楽停止画面を描画する
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, 0, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, 240, 200);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
    displayMusicTitle();
}

void AppControl::displayMusicTitle()
{

    mlcd.displayText(mmplay.getTitle(), 10, 120);
}

void AppControl::displayNextMusic()
{
    mlcd.displayText("               ", 0, 120);
    displayMusicTitle();
    mmplay.selectNextMusic();
}

void AppControl::displayMusicPlay()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    displayMusicTitle();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, 0, 200);
}

void AppControl::displayMeasureInit() // 距離測定画面の初期画面を描画　//変わらない画像を作成
{

    mlcd.clearDisplay();        // LCD画面をクリアする
    mlcd.fillBackgroundWhite(); // LCDをに白色の背景を描画する
    displayMeasureDistance();

    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, 240, 100);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, 139, 100);
}

void AppControl::displayMeasureDistance() // 測定した距離を描画する
{

    int num = (int)(mmdist.getDistance() * 10); // intのnumの箱をつくってそれにgetDistanceでとってきた値に*10をして整数にした、キャスト演算子でダブル型→int型にしたnumに代入
    int digit[4];                               // digit＝桁
    digit[0] = num / 1000;                      // 1000の位を求める
    digit[1] = (num / 100) % 10;                // 100の位を商と余りで求める
    digit[2] = (num / 10) % 10;                 // 十の位を商と余りで求める
    digit[3] = num % 10;                        // 余りとして一の位を求める

    if (num > 20 && num < 4500) // num(測定した値をいれている)に2cm(20mm)～450cm(4500)以外の時は更新しないを設定）
    {
        if (digit[1] == 0 && digit[0] == 0) // 条件が多いほうから処理されるため上位に記載。
        {
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 10, 100); // 1000位を0で測定されたら画像を白にする。
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 53, 100); // 100位を0で測定されたら画像を白にする。g_str_blue[digit[1]]を画像白（COMMON_BLUEFILLWHITE_IMG_PATH）で表示
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[2]], 96, 100);
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[3]], 182, 100);
        }
        else if (digit[0] == 0)
        {
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 10, 100); // 1000位を0で測定されたら画像を白にする。
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[1]], 53, 100);
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[2]], 96, 100);
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[3]], 182, 100);
        }
        else
        {
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[0]], 10, 100); // 青の数字を画面に表示させるconst char *g_str_blue[] から配列にはいっている数字を表示する
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[1]], 53, 100);
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[2]], 96, 100);
            mlcd.displayJpgImageCoordinate(g_str_blue[digit[3]], 182, 100);
        }
    }
}

void AppControl::displayDateInit() // 時刻表示のモニタ初期画面
{

    mlcd.clearDisplay();        // LCD画面をクリアする
    mlcd.fillBackgroundWhite(); // LCDをに白色の背景を描画する
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, 0, 0);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, 120, 200);
}

void AppControl::displayDateUpdate() // 現在の日時
{
    mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);
    mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, 0, 0);
}

void AppControl::controlApplication()
{

    mmplay.init();

    while (1)
    {

        switch (getState())
        {
        case TITLE:
            switch (getAction())
            {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                displayTitleInit();
                setStateMachine(TITLE, DO);

                break;

            case DO:
                if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed)
                {
                    setStateMachine(TITLE, EXIT);
                    setBtnAllFlgFalse();
                }

                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);

                break;

            default:
                break;
            }

            break;

        case MENU:

            switch (getAction())
            {
            case ENTRY:
                setFocusState(MENU_WBGT); // メニュー画面における「フォーカスの状態」をWBGTにする。
                displayMenuInit();
                setStateMachine(MENU, DO);
                break;

            case DO:
                switch (getFocusState())
                {
                case MENU_WBGT:
                    if (m_flag_btnA_is_pressed)
                    {
                        focusChangeImg(MENU_WBGT, MENU_DATE);
                    }

                    else if (m_flag_btnB_is_pressed)
                    {
                        setStateMachine(MENU, EXIT);
                    }

                    else if (m_flag_btnC_is_pressed)
                    {

                        focusChangeImg(MENU_WBGT, MENU_MUSIC);
                    }
                    setBtnAllFlgFalse();
                    break;

                case MENU_MUSIC:

                    if (m_flag_btnA_is_pressed)
                    {
                        focusChangeImg(MENU_MUSIC, MENU_WBGT);
                    }

                    else if (m_flag_btnB_is_pressed)
                    {
                        setStateMachine(MENU, EXIT);
                    }

                    else if (m_flag_btnC_is_pressed)
                    {

                        focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                    }
                    setBtnAllFlgFalse();
                    break;

                case MENU_MEASURE:

                    if (m_flag_btnA_is_pressed)
                    {
                        focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                    }

                    else if (m_flag_btnB_is_pressed)
                    {
                        setStateMachine(MENU, EXIT);
                    }

                    else if (m_flag_btnC_is_pressed)
                    {

                        focusChangeImg(MENU_MEASURE, MENU_DATE);
                    }
                    setBtnAllFlgFalse();
                    break;

                case MENU_DATE:

                    if (m_flag_btnA_is_pressed)
                    {
                        focusChangeImg(MENU_DATE, MENU_MEASURE);
                    }

                    else if (m_flag_btnB_is_pressed)
                    {
                        setStateMachine(MENU, EXIT);
                    }

                    else if (m_flag_btnC_is_pressed)
                    {

                        focusChangeImg(MENU_DATE, MENU_WBGT);
                    }
                    setBtnAllFlgFalse();
                    break;
                }
                break;

            case EXIT:

                switch (getFocusState())
                {

                case MENU_WBGT:

                    setStateMachine(WBGT, ENTRY);

                    break;

                case MENU_MUSIC:

                    setStateMachine(MUSIC_STOP, ENTRY);

                    break;

                case MENU_MEASURE:

                    setStateMachine(MEASURE, ENTRY);

                    break;

                case MENU_DATE:

                    setStateMachine(DATE, ENTRY);

                    break;
                default:
                    break;
                }
            }

            break;

        case WBGT:

            switch (getAction())
            {

            case ENTRY:

                displayWBGTInit();
                setStateMachine(WBGT, DO);

                break;

            case DO:

                displayTempHumiIndex();
                delay(100);

                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(WBGT, EXIT);
                    setBtnAllFlgFalse();
                }

                break;

            case EXIT:

                setStateMachine(MENU, ENTRY);

                break;

            default:
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction())
            {
            case ENTRY:
                displayMusicStop();
                displayMusicTitle();
                setStateMachine(MUSIC_STOP, DO);
                break;

            case DO:

                if (m_flag_btnA_is_pressed)
                {
                    setStateMachine(MUSIC_STOP, EXIT);
                }

                else if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MUSIC_STOP, EXIT);
                }

                else if (m_flag_btnC_is_pressed)
                {
                    displayNextMusic();
                    setBtnAllFlgFalse();
                }

                break;

            case EXIT:

                if (m_flag_btnA_is_pressed)
                {
                    setStateMachine(MUSIC_PLAY, ENTRY);
                }

                else if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MENU, ENTRY);
                }
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction())
            {
            case ENTRY:
                displayMusicPlay();
                setStateMachine(MUSIC_PLAY, DO);
                mmplay.prepareMP3();
                break;

            case DO:
                mmplay.playMP3();
                if (m_flag_btnA_is_pressed)
                {
                    setStateMachine(MUSIC_PLAY, EXIT);
                    setBtnAllFlgFalse();
                }
                if (!(mmplay.playMP3()))

                {
                    mmplay.stopMP3();

                    setStateMachine(MUSIC_PLAY, EXIT);
                }

                break;

            case EXIT:

                setStateMachine(MUSIC_STOP, ENTRY);

                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction())
            {
            case ENTRY:
                displayMeasureInit();
                setStateMachine(MEASURE, DO);

                break;

            case DO:

                displayMeasureDistance();
                delay(250);
                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MEASURE, EXIT);
                    setBtnAllFlgFalse();
                }

                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction())
            {
            case ENTRY:
                displayDateInit();
                setStateMachine(DATE, DO);

                break;

            case DO:
                displayDateUpdate();
                delay(100);

                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(DATE, EXIT);
                    setBtnAllFlgFalse();
                }

                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                break;
            default:
                break;
            }

        default:
            break;
        }
    }
}
