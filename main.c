#include <gb/gb.h>
#include <gb/console.h>
#include <stdlib.h> 
#include <stdio.h>
#include <gb/font.h>
#include "lib/consts.h"
#include "lib/constants.c"
#include "lib/helpers.c"
#include "lib/state.c"

typedef enum {false, true} bool;
typedef enum {g,m,a} Position;
typedef enum {Gentle, Careful, Neutral, Chaotic, Evil} Behavior;

typedef struct Player {
  char* name;
  uint8_t power;

} Player;

typedef struct Team {
  char* name;
  struct Player *players[18];
} Team;

struct Player* set_player(char* name, uint8_t power) {
  struct Player *player;
  player = (struct Player*) malloc(sizeof(struct Player));
  
  player->name = name;
  player->power = power;

  return player;
}

struct Team* set_team(char* name, struct Player *player) {
  struct Team *team;
  team = (struct Team*) malloc(sizeof(struct Team));

  team->name = name;
  team->players[0] = player;

  return team;
}

enum ROUTES render_intro_screen() { 
  printf("                    ");
  printf(" ------------------ ");
  printf(" |  RETRO SOCCER  | ");
  printf(" ------------------ ");
  blank_lines(4);
  printf("      > START       ");
  blank_lines(1);
  printf("        ABOUT       ");
  blank_lines(3);
  printf(" By Victor Heringer ");
  blank_lines(1);
  printf("   Version 1.0.0    ");

  waitpad(J_START);
  waitpadup();

  return TEAM_SELECTION_SCREEN;
}

enum ROUTES render_game_screen() {
  struct Player *player;
  struct Team *team;

  player = set_player("Enel", 3);
  team = set_team("Bragantino", player);

  printf("%s  \n", team->name);
  printf("--------------------");
  printf("%s %d              ", team->players[0]->name, team->players[0]->power);
  printf("--------------------");
  printf("%s %d ", player->name, player->power);
  waitpad(J_START);
  waitpadup();

  return INTRO_SCREEN;
}

enum ROUTES render_team_selection_screen() {
  int ANIMATION_FRAME_TIME = 3;

  for(int i = 0; i < ANIMATION_FRAME_TIME; i++) {
    blank_lines(1);
    printf("%s /", " SELECIONANDO");
    clear_screen();
    blank_lines(1);
    printf("%s |", " SELECIONANDO");
    clear_screen();
    blank_lines(1);
    printf("%s \\", " SELECIONANDO");
    clear_screen();
  }

  blank_lines(1);
  printf(" PARABENS!          ");
  blank_lines(2);
  printf(" Voce ira gerenciar ");
  blank_lines(2);
  printf(" TIME         VASCO ");
  printf(" ------------------ ");
  printf(" DIVISAO          4 ");
  printf(" ------------------ ");
  printf(" JOGADORES       14 ");
  printf(" ------------------ ");
  printf(" CAIXA       R$ 20k ");
  blank_lines(2);
  printf(" -- press  start -- ");

  waitpad(J_START);
  waitpadup();

  return NEW_GAME_SCREEN;
}

enum ROUTES router(enum ROUTES route) {

  switch(route) {
    case INTRO_SCREEN: {
      return render_intro_screen(); 
    }
    case NEW_GAME_SCREEN: {
      return render_game_screen(); 
    }
    case TEAM_SELECTION_SCREEN: {
      return render_team_selection_screen();
    }
    default: {
      return INTRO_SCREEN;
    }
  }
}

void main() {
  enum ROUTES route = INTRO_SCREEN;

  while(1) {
    route = router(route);
    //scrollable_pad_list();
    //printf("END");
    //waitpadup();
  }
}