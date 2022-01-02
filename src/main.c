#include <gb/gb.h>
#include <gb/bgb_emu.h>
#include <stdlib.h>
#include <stdio.h>
#include "../res/map-tiles.h"
#include "../res/room-map.h"
#include "../res/sprites.h"
#include "../res/splash-data.h"
#include "../res/splash-map.h"

int FRAME_COUNTER = 0;

enum { TRAINER_NUMBER = 0, CAT_NUMBER = 1 } SPRITES_NUMBER;

typedef struct Sprite {
  uint8_t x;
  uint8_t y;
  uint8_t ref;
  uint8_t idle_anim[3][4];
  uint8_t walk_right_anim[2][4];
  uint8_t walk_up_anim[3][4];
} Sprite;

void handleFrames() {  
  FRAME_COUNTER++;

  if(FRAME_COUNTER == 60) {
    FRAME_COUNTER = 0;
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

void load_sprites() {
  set_sprite_data(26, 41, Sprites);

  SHOW_SPRITES;
}

struct Sprite CAT = {
  65, 125, CAT_NUMBER, 
  { {50, 51, 52, 53}, {50, 54, 52, 53}, {50, 55, 52, 53} },
  { {0,0,0,0}, {0,0,0,0} },
  { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }
};

void init_cat(uint8_t sprite_anim) {
  uint8_t sprite_position = CAT.ref * 4;
  uint8_t delta_x = 0;
  uint8_t delta_y = 0;

  for(uint8_t i = 0; i < 4; i++) {

    delta_x = i == 2 || i == 3 ? 8 : 0;
    delta_y = i == 1 || i == 3 ? 8 : 0;

    set_sprite_tile(sprite_position + i, CAT.idle_anim[sprite_anim][i]);
    move_sprite(sprite_position + i, CAT.x + delta_x, CAT.y + delta_y);
  }
}

void main(void) {

  load_splash_screen();

  DISPLAY_ON;

  load_main_room();
  load_sprites();
  
  
  while(1) {
    handleFrames();

    init_cat(FRAME_COUNTER / 20);
    wait_vbl_done();
  }
}