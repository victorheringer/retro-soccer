#include <gb/gb.h>
#include "../res/map-tiles.h"
#include "../res/room.h"
#include "../res/sprites.h"

typedef struct {
  int x;
  int y;
  int flip;
} Trainer;

Trainer trainer = { 40, 120, 0 };

void moveTrainer() {
  move_sprite(0, trainer.x, trainer.y);  
  move_sprite(1, trainer.x, trainer.y + 8);
  move_sprite(2, trainer.x + 8, trainer.y);
  move_sprite(3, trainer.x + 8, trainer.y + 8);
}

void animateWalkRight() {

  set_sprite_tile(0, 42);
  set_sprite_tile(1, 43);
  set_sprite_tile(2, 44);
  set_sprite_tile(3, 45);

  trainer.x = trainer.x + 4;
  moveTrainer();
  delay(150);

  set_sprite_tile(0, 46);
  set_sprite_tile(1, 47);
  set_sprite_tile(2, 48);
  set_sprite_tile(3, 49);

  set_sprite_tile(0, 42);
  set_sprite_tile(1, 43);
  set_sprite_tile(2, 44);
  set_sprite_tile(3, 45);

  trainer.x = trainer.x + 4;
  moveTrainer();
  delay(150);

  set_sprite_tile(0, 46);
  set_sprite_tile(1, 47);
  set_sprite_tile(2, 48);
  set_sprite_tile(3, 49);

  //trainer.x = trainer.x + 8;
  //moveTrainer();
  //delay(150);
}

void animateWalkLeft() {
  set_sprite_tile(0, 44);
  set_sprite_tile(1, 45);
  set_sprite_tile(2, 42);
  set_sprite_tile(3, 43);

  if(!trainer.flip) {
    trainer.flip = 1;
    set_sprite_prop(0, S_FLIPX);
    set_sprite_prop(1, S_FLIPX);
    set_sprite_prop(2, S_FLIPX);
    set_sprite_prop(3, S_FLIPX);
  }

  trainer.x = trainer.x -8 ;
  moveTrainer();
  delay(200);
  set_sprite_tile(0, 48);
  set_sprite_tile(1, 49);
  set_sprite_tile(2, 46);
  set_sprite_tile(3, 47);

  delay(200);
}

void walk() {
  uint8_t key;
  key = waitpad(J_UP | J_DOWN | J_LEFT | J_RIGHT);

  switch(key) {
    case J_UP : {
      trainer.y = trainer.y - 5;
      moveTrainer();
      delay(200);
      break;
    }
    case J_DOWN : {
      trainer.y = trainer.y + 5;
      moveTrainer();
      delay(200);
      break;
    }
    case J_LEFT: {
      animateWalkLeft();  
      break;
    }
    case J_RIGHT : {
      animateWalkRight();
      break;
    }
  }
}

void main(void) {

  set_sprite_data(26, 24, Sprites);
  set_bkg_data(0, 44, MapTiles);
  set_bkg_tiles(0,0, 32, 32, Room);

  set_sprite_tile(0, 26);
  set_sprite_tile(1, 27);
  set_sprite_tile(2, 28);
  set_sprite_tile(3, 29);
  moveTrainer();

  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;

  while(1) {
    walk();
  }
}