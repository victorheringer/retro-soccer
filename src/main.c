#include <gb/gb.h>
#include <gb/bgb_emu.h>
#include <stdlib.h>
#include <stdio.h>
#include "../res/map-tiles.h"
#include "../res/room-map.h"
#include "../res/sprites.h"
#include "../res/splash-data.h"
#include "../res/splash-map.h"
#include "../res/backyard.h"
#include "../res/backyard-tiles.h"

char BUFFER[100];
uint8_t FRAME_COUNTER = 1;
uint8_t BACKGROUND_SCROLL = 0;

enum { TRAINER_NUMBER = 0, CAT_NUMBER = 1 } SPRITES_NUMBER;
enum { IDLE = 0, WALKING_LEFT = 1, WALKING_RIGHT = 2 } SPRITE_STATE;
enum { UNDEFINED = 255 } HELPERS;

typedef struct Sprite {
  uint8_t x;
  uint8_t y;
  uint8_t ref;
  uint8_t state;
  uint8_t animate_frame_position;
  uint8_t idle_anim[3][4];
  uint8_t walk_right_anim[3][4];
  uint8_t walk_up_anim[3][4];
} Sprite;

struct Sprite CAT = {
  65, 125, CAT_NUMBER, IDLE, UNDEFINED,
  { {50, 51, 52, 53}, {50, 54, 52, 53}, {50, 55, 52, 53} },
  { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} },
  { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }
};

struct Sprite TRAINER = {
  40, 120, TRAINER_NUMBER, IDLE, UNDEFINED,
  { {26, 27, 28, 29}, {26, 27, 28, 29}, {26, 27, 28, 29} },
  { {42,43,44,45}, {46,47,48,49}, {42,43,44,45} },
  { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }
};

void printn(int number) {
  BGB_MESSAGE_FMT(BUFFER, "DEBUG: %d", number);
}

void handleFrames() {  

  if(FRAME_COUNTER == 61) {
    FRAME_COUNTER = 1;
  }

  FRAME_COUNTER++;
}

void handleBackgroundScroll() {  
  BACKGROUND_SCROLL++;

  if(BACKGROUND_SCROLL == 8) {
    BACKGROUND_SCROLL = 0;
  }
}

void load_splash_screen() {
  set_bkg_data(0, 141, SplashData);
  set_bkg_tiles(0,0, 20, 18, SplashMap);

  SHOW_BKG;
  waitpad(J_START);
  HIDE_BKG;
}

void load_main_room() {
  set_bkg_data(0, 127, MapTiles);
  set_bkg_tiles(0,0, 27, 23, Room);

  SHOW_BKG;
}

void load_backyard() {
  set_bkg_data(0, 47, BackyardTiles);
  set_bkg_tiles(0,0, 20, 18, Backyard);

  SHOW_BKG;
}

void load_sprites() {
  set_sprite_data(26, 41, Sprites);

  SHOW_SPRITES;
}

void init_cat(uint8_t sprite_anim) {
  uint8_t sprite_position = CAT.ref * 4;
  uint8_t delta_x = 0;
  uint8_t delta_y = 0;

  if(sprite_anim > 2) {
    return;
  }

  for(uint8_t i = 0; i < 4; i++) {

    delta_x = i == 2 || i == 3 ? 8 : 0;
    delta_y = i == 1 || i == 3 ? 8 : 0;

    set_sprite_tile(sprite_position + i, CAT.idle_anim[sprite_anim][i]);
    move_sprite(sprite_position + i, CAT.x + delta_x, CAT.y + delta_y);
  }

}

void init_trainer(uint8_t sprite_anim) {
  uint8_t sprite_position = TRAINER.ref * 4;
  uint8_t delta_x = 0;
  uint8_t delta_y = 0;

  for(uint8_t i = 0; i < 4; i++) {

    delta_x = i == 2 || i == 3 ? 8 : 0;
    delta_y = i == 1 || i == 3 ? 8 : 0;

    set_sprite_tile(sprite_position + i, TRAINER.idle_anim[sprite_anim][i]);
    move_sprite(sprite_position + i, TRAINER.x + delta_x, TRAINER.y + delta_y);
  }
}

void animate_walk_trainer() {
  uint8_t stop_animation_position = 0;

  if(TRAINER.animate_frame_position == UNDEFINED) {
    return;
  }

  if(TRAINER.state == WALKING_RIGHT) {

    if(BACKGROUND_SCROLL < 8 && FRAME_COUNTER % 5) {
      scroll_bkg(1 ,0);
      handleBackgroundScroll();
    }

    if(FRAME_COUNTER % 15 == 0) { 
      
      set_sprite_tile(0, TRAINER.walk_right_anim[TRAINER.animate_frame_position][0]);
      set_sprite_tile(1, TRAINER.walk_right_anim[TRAINER.animate_frame_position][1]);
      set_sprite_tile(2, TRAINER.walk_right_anim[TRAINER.animate_frame_position][2]);
      set_sprite_tile(3, TRAINER.walk_right_anim[TRAINER.animate_frame_position][3]);

      TRAINER.animate_frame_position = TRAINER.animate_frame_position + 1;

      stop_animation_position = sizeof(TRAINER.walk_right_anim)/4 - 1;
      printn(FRAME_COUNTER);

      if(TRAINER.animate_frame_position == stop_animation_position) {
        TRAINER.animate_frame_position = UNDEFINED;
        TRAINER.state = IDLE;
      }
    }
  }

}

void walk_trainer() {
  uint8_t key = joypad();

  if(TRAINER.state == IDLE) {
    switch(key) {
      case J_LEFT: {
        TRAINER.state = WALKING_LEFT;
        TRAINER.animate_frame_position = 0;
        break;
      }
      case J_RIGHT : {
        TRAINER.state = WALKING_RIGHT;
        TRAINER.animate_frame_position = 0;
        break;
      }
    }
  }
  
  animate_walk_trainer();
} 

void main(void) {

  load_splash_screen();

  DISPLAY_ON;

  load_backyard();
  load_sprites();

  init_trainer(0);
  
  
  while(1) {
    handleFrames();

    init_cat(FRAME_COUNTER / 20);  
    walk_trainer();
  
    wait_vbl_done();
  }
}