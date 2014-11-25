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
    
    #define image_search_path   "images/"
    #define audio_search_path   "audio/"
    #define font_search_path    "font/"
    
    // images
    #define s_ball_images_plist     "ball_images.plist"
    #define s_ball_images           "ball_images.pvr.ccz"
    
    #define s_background    "background"
    #define s_start_btn     "btn_start"
    #define s_start_btn_a   "btn_start_active"
    #define s_logo          "logo"
    #define s_intro_btn     "btn_intro"
    #define s_intro_btn_a   "btn_intro_active"
    #define s_quit_btn      "btn_quit"
    #define s_quit_btn_a    "btn_quit_active"
    #define s_setting_btn   "btn_setting"
    #define s_setting_btn_a "btn_setting_active"
    #define s_rank_btn      "btn_rank"
    #define s_rank_btn_a    "btn_rank_active"
    #define s_grade_txt     "grade"
    #define s_next_txt      "next"
    #define s_pause_btn     "btn_pause"
    #define s_pause_btn_a   "btn_pause_active"
    #define s_board         "game_board"
    #define s_board_rect    "board_rect"
    #define s_alert_board   "alert_board"
    #define s_pause         "pause"
    #define s_resume_btn    "btn_continue"
    #define s_resume_btn_a  "btn_continue_active"
    #define s_restart_btn   "btn_restart"
    #define s_restart_btn_a "btn_restart_active"
    #define s_go_home_btn   "btn_home"
    #define s_go_home_btn_a "btn_home_active"
    #define s_eye           "eye"
    #define s_sun           "sun"
    
    #define s_blue_ball     "blue_ball"
    #define s_yellow_ball   "yellow_ball"
    #define s_red_ball      "red_ball"
    #define s_green_ball    "green_ball"
    
    // audio
    #define s_btn_click     "btn_click.mp3"
    
    // font
    #define s_number_fnt    "numbers.fnt"
    
}

#endif
