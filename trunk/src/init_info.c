#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"
#include "link.h"

void init_all_objective_conditions(int *all_objectives_conditions, int nb_objs){
  for(int i=0; i<nb_objs; i++)
    all_objectives_conditions[i]=0;
}



int max_rail_length(struct Rail *rails, int nb_rails){ //make the test
  int length_max = -1;
  for (int i = 0; i < nb_rails; i++){
    int length = rails[i].length;
    if (length > length_max)
      length_max = length;
  }
  return length_max;
}

void init_wagons(int * wagons_remaining, int nb_players, int nb_w_player){
  for(int i=0; i<nb_players; i++){
    wagons_remaining[i]=nb_w_player;
  }
}

void init_turn_informations(int * used_wagons, int * cards_in_hands, int * objectives, struct New_rail * changes, int * new_obj[], int * cards[], int nb_players,int nb_starting_cards, int nb_obj_drawn_max, int max_rail_length,int ** card_hands){
  for(int i=0; i<nb_players;i++){
    used_wagons[i]=0;
    cards_in_hands[i]=nb_starting_cards;
    objectives[i]=0;
    changes[i].rail=-1;
    changes[i].player=-1;
    for (int j=0; j<(nb_obj_drawn_max);j++){
      new_obj[i][j]=-1;
    }
    for (int j=0; j<max_rail_length; j++){
      if (j<nb_starting_cards)
        cards[i][j]=card_hands[i][j];
      else
        cards[i][j]=-1;
    }

  }


}
