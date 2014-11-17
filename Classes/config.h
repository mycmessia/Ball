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
    #define s_main_images_plist     "main_images.plist"
    #define s_main_images           "main_images.png"
    #define s_repeat_images_plist   "repeat_sheet.plist"
    #define s_repeat_images         "repeat_sheet.png"
    
    #define s_background    "background.png"
    #define s_start_btn     "start_btn.png"
    #define s_start_btn_a   "start_btn_active.png"
    #define s_banner        "banner.png"
    #define s_intro_btn     "intro_btn.png"
    #define s_intro_btn_a   "intro_btn_active.png"
    #define s_quit_btn      "quit_btn.png"
    #define s_quit_btn_a    "quit_btn_active.png"
    #define s_setting_btn   "setting_btn.png"
    #define s_setting_btn_a "setting_btn_active.png"
    #define s_rank_btn      "rank_btn.png"
    #define s_rank_btn_a    "rank_btn_active.png"
    #define s_grade_txt     "grade.png"
    #define s_next_txt      "next.png"
    #define s_pause_btn     "pause_btn.png"
    #define s_pause_btn_a   "pause_btn_active.png"
    #define s_board         "game_board.png"
    #define s_board_rect    "board_rect.png"
    #define s_alert_board   "alert_board.png"
    #define s_pause         "pause.png"
    #define s_resume_btn    "resume_btn.png"
    #define s_resume_btn_a  "resume_btn_active.png"
    #define s_restart_btn   "restart_btn.png"
    #define s_restart_btn_a "restart_btn_active.png"
    #define s_go_home_btn   "go_home_btn.png"
    #define s_go_home_btn_a "go_home_btn_active.png"
    
    #define s_blue_ball     "blue_ball.png"
    #define s_yellow_ball   "yellow_ball.png"
    #define s_red_ball      "red_ball.png"
    #define s_green_ball    "green_ball.png"
    
    // audio
    #define s_btn_click     "btn_click.mp3"
    
}

#endif
