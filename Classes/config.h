//
//  config.h
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//

#ifndef Ball_config_h
#define Ball_config_h

#define USING_NS_GC using namespace gameConfig

namespace gameConfig {
    
    // layer tag
    static int layerTagCounter = 0;
    
    const int WELCOME_LAYER = layerTagCounter++;
    const int GAME_LAYER = layerTagCounter++;
    const int PAUSE_LAYER = layerTagCounter++;
    
    // images
    #define s_background    "background.png"
    #define s_start_btn     "start_btn"
    #define s_logo          "logo"
    #define s_intro_btn     "intro_btn"
    #define s_quit_btn      "quit_btn"
    #define s_setting_btn   "setting_btn"
    #define s_rank_btn      "rank_btn"
    #define s_grade_txt     "grade"
    #define s_next_txt      "next"
    #define s_pause_btn     "pause_btn"
    #define s_board         "game_board.png"
    #define s_board_rect    "board_rect"
    #define s_alert_board   "alert_board"
    
    // audio
    #define s_btn_click     "btn_click.mp3"
    
}

#endif
