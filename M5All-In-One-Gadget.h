/* インクルードガード */
#pragma once

// button gpio number
#define BTN_A_GPIO 39
#define BTN_B_GPIO 38
#define BTN_C_GPIO 37

// UltraSonic pin
#define ECHO_PIN 5
#define TRIG_PIN 2

// jpg image path
#define TITLE_IMG_PATH "/images/title/title.jpg"

#define MENU_WBGT_IMG_PATH "/images/menu/monitor.jpg"
#define MENU_WBGT_FOCUS_IMG_PATH "/images/menu/monitor_focus.jpg"
#define MENU_MUSIC_IMG_PATH "/images/menu/music.jpg"
#define MENU_MUSIC_FOCUS_IMG_PATH "/images/menu/music_focus.jpg"
#define MENU_MEASURE_IMG_PATH "/images/menu/measure.jpg"
#define MENU_MEASURE_FOCUS_IMG_PATH "/images/menu/measure_focus.jpg"
#define MENU_DATE_IMG_PATH "/images/menu/date.jpg"
#define MENU_DATE_FOCUS_IMG_PATH "/images/menu/date_focus.jpg"

#define WBGT_SAFE_IMG_PATH "/images/wbgt/safe.jpg"
#define WBGT_ATTENTION_IMG_PATH "/images/wbgt/attention.jpg"
#define WBGT_ALERT_IMG_PATH "/images/wbgt/alert.jpg"
#define WBGT_HIGH_ALERT_IMG_PATH "/images/wbgt/high_alert.jpg"
#define WBGT_DANGER_IMG_PATH "/images/wbgt/danger.jpg"
#define WBGT_TEMPERATURE_IMG_PATH "/images/wbgt/temperature.jpg"
#define WBGT_HUMIDITY_IMG_PATH "/images/wbgt/humidity.jpg"
#define WBGT_DEGREE_IMG_PATH "/images/wbgt/degree.jpg"
#define WBGT_PERCENT_IMG_PATH "/images/wbgt/percent.jpg"

#define MUSIC_NOWPLAYING_IMG_PATH "/images/music/nowplaying.jpg"
#define MUSIC_NOWSTOPPING_IMG_PATH "/images/music/nowstopping.jpg"

#define MEASURE_NOTICE_IMG_PATH "/images/measure/measure.jpg"
#define MEASURE_CM_IMG_PATH "/images/measure/cm.jpg"

#define DATE_NOTICE_IMG_PATH "/images/date/notice.jpg"
#define DATE_SLASH_IMG_PATH "/images/date/slash.jpg"
#define DATE_COLON_IMG_PATH "/images/date/colon.jpg"

#define COMMON_BUTTON_BACK_IMG_PATH "/images/common/button/back.jpg"
#define COMMON_BUTTON_DECIDE_IMG_PATH "/images/common/button/decide.jpg"
#define COMMON_BUTTON_DOWN_IMG_PATH "/images/common/button/down.jpg"
#define COMMON_BUTTON_NEXT_IMG_PATH "/images/common/button/next.jpg"
#define COMMON_BUTTON_PLAY_IMG_PATH "/images/common/button/play.jpg"
#define COMMON_BUTTON_STOP_IMG_PATH "/images/common/button/stop.jpg"
#define COMMON_BUTTON_UP_IMG_PATH "/images/common/button/up.jpg"
#define COMMON_BUTTON_FILLWHITE_IMG_PATH "/images/common/button/fillwhite.jpg"

#define COMMON_ORANGE1_IMG_PATH "/images/common/orange_number/1.jpg"
#define COMMON_ORANGE2_IMG_PATH "/images/common/orange_number/2.jpg"
#define COMMON_ORANGE3_IMG_PATH "/images/common/orange_number/3.jpg"
#define COMMON_ORANGE4_IMG_PATH "/images/common/orange_number/4.jpg"
#define COMMON_ORANGE5_IMG_PATH "/images/common/orange_number/5.jpg"
#define COMMON_ORANGE6_IMG_PATH "/images/common/orange_number/6.jpg"
#define COMMON_ORANGE7_IMG_PATH "/images/common/orange_number/7.jpg"
#define COMMON_ORANGE8_IMG_PATH "/images/common/orange_number/8.jpg"
#define COMMON_ORANGE9_IMG_PATH "/images/common/orange_number/9.jpg"
#define COMMON_ORANGE0_IMG_PATH "/images/common/orange_number/0.jpg"
#define COMMON_ORANGEDOT_IMG_PATH "/images/common/orange_number/dot.jpg"
#define COMMON_ORANGEFILLWHITE_IMG_PATH "/images/common/orange_number/fillwhite.jpg"

#define COMMON_BLUE1_IMG_PATH "/images/common/blue_number/1.jpg"
#define COMMON_BLUE2_IMG_PATH "/images/common/blue_number/2.jpg"
#define COMMON_BLUE3_IMG_PATH "/images/common/blue_number/3.jpg"
#define COMMON_BLUE4_IMG_PATH "/images/common/blue_number/4.jpg"
#define COMMON_BLUE5_IMG_PATH "/images/common/blue_number/5.jpg"
#define COMMON_BLUE6_IMG_PATH "/images/common/blue_number/6.jpg"
#define COMMON_BLUE7_IMG_PATH "/images/common/blue_number/7.jpg"
#define COMMON_BLUE8_IMG_PATH "/images/common/blue_number/8.jpg"
#define COMMON_BLUE9_IMG_PATH "/images/common/blue_number/9.jpg"
#define COMMON_BLUE0_IMG_PATH "/images/common/blue_number/0.jpg"
#define COMMON_BLUEDOT_IMG_PATH "/images/common/blue_number/dot.jpg"
#define COMMON_BLUEFILLWHITE_IMG_PATH "/images/common/blue_number/fillwhite.jpg"

// MENU jpg image coordinate
#define MENU_WBGT_X_CRD 0
#define MENU_WBGT_Y_CRD 0
#define MENU_MUSIC_X_CRD 0
#define MENU_MUSIC_Y_CRD 50

// WBGT jpg image coordinate

// Music jpg image coordinate

// Measure jpg image coordinate

// Date jpg image coordinate

typedef enum {
    TITLE,
    MENU,
    WBGT,
    MUSIC_STOP,
    MUSIC_PLAY,
    MEASURE,
    DATE
} State;

typedef enum {
    ENTRY,
    DO,
    EXIT
} Action;

typedef enum {
    MENU_WBGT,
    MENU_MUSIC,
    MENU_MEASURE,
    MENU_DATE
} FocusState;

typedef enum {
    SAFE,
    ATTENTION,
    ALERT,
    HIGH_ALERT,
    DANGER
} WbgtIndex;
