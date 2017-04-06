#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"
#include "link.h"



int is_last_turn(int * wagons_remaining, int nb_players){
  for (int i = 0; i <nb_players; i++){
    if (wagons_remaining[i] <=2)
      return 1;
  }
  return 0;
}



int are_objs_valid(int * T_chosen_objs, int min_objs_to_pick, int nb_objs_given){//verify the number of objectives the player wants to keep
  int nb_objs=0;
  for (int i=0; i<nb_objs_given; i++){
    if(T_chosen_objs[i]==1)
      nb_objs++;
  }
  return ((nb_objs >= min_objs_to_pick) && (nb_objs <= nb_objs_given));
}




// do the test
int cheat(struct Action action, int nb_players, int player, 
	  int nb_objs_tot, int *nb_objs, struct Rail *rails,
          int nb_rails, int *wagons_remaining, int **card_hands, 
	  int *nb_cards, struct Link **map, int nb_town){

  
  printf("cheat\n");
  int nb_free_objs = nb_objs_tot;
  switch (action.type){
  case DRAW: // draw color cards -> no pb
    printf("draw\n");
    return 0;
    break;



  case BUILD: // build a rail -> rail exist and is free ? enougth wagons ? enought cards of the right color ?
    printf("build\n");
    if (action.rail < 0 || action.rail > nb_rails){ // the rail doesn't exists
      return 1;
        break;
    }
    if (wagons_remaining[player] < rails[action.rail].length){ // the player doesn't have enought wagons
      return 1;
      break;
    }
    int nb_cards_player = 0;
    for (int i = 0; i < nb_cards[player]; i++){
      if (card_hands[player][i] == rails[action.rail].color || card_hands[player][i] == 0)
	nb_cards_player++;
    }

    if (nb_cards_player < rails[action.rail].length){// the player doesn't have enought wagon cards
      return 1;
      break;
    }

    int town1 = rails[action.rail].town1;
    int town2 = rails[action.rail].town2;
    int l,c;
    if (town1 < town2){ // the map is a triangular matrix
      l = town1;
      c = town2;
    }
    else{
      l = town2;
      c = town1;
    }
    
    int nb_way = map[l][c].nbr_way;
    int is_free = 0;
    for (int i = 0; i< nb_way; i++){
      if (map[l][c].tab_rails[i].id_player == -1)
	is_free = 1;
    }
    if (!is_free){
      return 1;
      break;
    }
    return 0;
    break;



  case OBJECTIVE: // draw objectives -> enought objs in the pile ?
    printf("objective\n");
    
    for (int i = 0; i < nb_players; i++){
      nb_free_objs -= nb_objs[i];
      
    if (nb_free_objs <= 2){ // modify the name min
      return 1;
      break;
    }
    return 0;
    break;
    


  default: // this action doesn't exit, so he is cheating
    printf("default\n");
    return 1;
    break;


  }
  
}



  









void apply(int player, struct Action action,int nb_players,int **card_hand,
	   int *nb_cards, int *wagon_cards_modif, int **cards, int nb_colors,
	   int *col, struct Link **map, struct Rail * rails, int *wagons_remaining, int *used_wagons,
       int ** obj_hands, int nb_objs_total, int * objs_cond, int **new_objs, int nb_objs_drawn_max, int min_objs_to_pick, struct f_player * player_fonctions, int *nb_objs, int * nb_new_objs,int colored_game){
  printf("apply");
  switch (action.type){
    
  case DRAW: // draw color card
    
    draw_color_card(player, nb_players, card_hand, nb_cards, wagon_cards_modif, cards, nb_colors, col,colored_game);
    break;
    
  case BUILD: // build a rail

    //build_rail();
    build_rail(player,nb_players,action.rail,card_hand,nb_cards,wagon_cards_modif,
	       cards,map,rails,/*nb_rails,*/wagons_remaining,used_wagons);
    break;
  case OBJECTIVE: // draw objectives

    draw_objectives(player,nb_players,obj_hands,/*nb_objs_player,objectives,*/nb_objs_total,objs_cond,new_objs,nb_objs_drawn_max,min_objs_to_pick, player_fonctions, nb_objs, nb_new_objs);
    break;
    

  default: // Houston ! We've got a problem !
    printf("Cheat function doesn't work !!    type= %d    DRAW= %d BUILD= %d OBJECTIVE= %d\n",action.type, DRAW, BUILD, OBJECTIVE);
    break;
  }
}

