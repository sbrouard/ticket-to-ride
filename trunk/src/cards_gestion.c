#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"
#include "link.h"
#include "concat.h"



int colors(struct Rail *rails, int nb_rails, int ** col){

  int nb_colors = 0;
  size_t max_colors = 1;
  int is_in_colors = 0;
  for (int ind_rail = 0; ind_rail < nb_rails; ind_rail++){
    for (int ind_color = 0; ind_color < nb_colors; ind_color++){
      if (rails[ind_rail].color == (*col)[ind_color]){
	is_in_colors = 1;
	break;
      }
    }
    if (!is_in_colors){
      if (nb_colors >= max_colors){
    *col = realloc(*col, 2*max_colors*sizeof(int));
	max_colors*=2;
      }
      (*col)[nb_colors] = rails[ind_rail].color;
      nb_colors++;
    }
    is_in_colors = 0;
  }
  return nb_colors;
}





void init_card_hands(int nb_players, int nb_starting_cards, int **card_hands, int *colors, int nb_colors){ 
  int color;
  
  for (int player = 0; player < nb_players; player++){
    card_hands[player] = malloc(nb_starting_cards*sizeof(int));
    for (int card = 0; card < nb_starting_cards; card++){
      color = rand() % nb_colors;
      card_hands[player][card]= colors[color];
    }
  }
}





void init_obj_hands(int nb_players, int nb_starting_objs, int  ** obj_hands, struct Objective *objectives,int nb_objs,int *objectives_condition){
  
  int index;
  

  if (nb_players*nb_starting_objs > nb_objs)
    printf("There are not enougth objectives");

  else{

    for (int player = 0; player < nb_players; player++){
      //printf("player %d\n",player);
      obj_hands[player] = malloc(nb_starting_objs*sizeof(int));
      for (int obj = 0; obj < nb_starting_objs; obj++){
	//printf("obj %d\n",obj);
	index = rand() % nb_objs;
	//printf("index : %d\n", index);
	while (objectives_condition[index] != 0){
	  index = rand() % nb_objs;
	  //printf("index : %d\n", index);
	  //printf("drawn : %d\n", objectives[index].drawn);
	}
	objectives_condition[index] = 1;
	obj_hands[player][obj] = index;
      }
    }
  }
}





void init_nb_objs(int nb_players, int nb_starting_objs, int *nb_objs){

  for (int i = 0; i < nb_players; i++)
    nb_objs[i] = nb_starting_objs;

}




void draw_color_card(int player, int nb_players, int **card_hand, 
		     int *nb_cards, int *wagon_cards_modif, int **cards, 
             int nb_colors, int *colors, int colored_game){

  // apply modifs in server
  card_hand[player] = realloc(card_hand[player], (nb_cards[player]+2)*sizeof(int));
  if (colored_game){
    card_hand[player][nb_cards[player]] = colors[rand() % nb_colors];
    card_hand[player][nb_cards[player]+1] = colors[rand() % nb_colors];
  }
  else{
      card_hand[player][nb_cards[player]] = 0;
      card_hand[player][nb_cards[player]+1] = 0;
  }
  nb_cards[player]+=2;

  // give changes to players
  wagon_cards_modif[player] = 2;
  cards[player][0] = card_hand[player][nb_cards[player]-2];
  cards[player][1] = card_hand[player][nb_cards[player]-1];
}



void draw_objectives(int player, int nb_players, int **obj_hands,/*int nb_objs_player,
		     struct Objective *objectives,*/ int nb_objs_total, int *objs_cond,
		     int **new_objs, int nb_objs_drawn_max, int min_objs_to_pick, struct f_player * player_fonctions, int *nb_objs,int * nb_new_objs){
  
  // draw nb_objs_drawn_max random free objs
  
  int *drawn_objs = malloc(nb_objs_drawn_max*sizeof(int));
  for (int i = 0; i < nb_objs_drawn_max; i++){
    int free2 = 0;
    int index;
    while (!free2){
      index = rand() % nb_objs_total;
      if (objs_cond[index] == 0)
        free2 = 1;
    }
    objs_cond[index] = 1;
    drawn_objs[i] = index;
  }
    
    // ask the player to choose which objs he wants
    
    int *T_chosen_objs = player_fonctions[player].choose_objective(nb_objs_drawn_max, drawn_objs, min_objs_to_pick);//array of boolean telling if objs are kept or not
    
    if (are_objs_valid(T_chosen_objs, min_objs_to_pick, nb_objs_drawn_max)){ //test if the number of chosen objectives are between MIN_OBJS_TO_PICK and NB_OBJ_DRAWN_MAX  
      
      // apply modifs in the server and the player
      
      
      
      int nb_chosen_objs = 0;
      for (int i = 0; i < nb_objs_drawn_max; i++){
	if (T_chosen_objs[i]){
	  objs_cond[drawn_objs[i]] = T_chosen_objs[i]; // say which objs aren't avaible anymore
	  nb_chosen_objs++;
	}
      }
      
      nb_objs[player] += nb_chosen_objs;
      obj_hands[player] = realloc(obj_hands[player],nb_objs[player]*sizeof(int *));
      int j = nb_objs[player] - nb_chosen_objs;
      for (int i = 0; i < nb_objs_drawn_max; i++){
	if (T_chosen_objs[i]){
	  obj_hands[player][j] = drawn_objs[i];
	  j++;
	}
	
	nb_new_objs[player] = nb_chosen_objs;
      }
    }
  free(T_chosen_objs);
  free(drawn_objs);
}



void init_first_chosen_objs(int * T_chosen_objs,  int nb_objs_given, int * all_objective_conditions, int all_objs_conditions_size, int * obj_player_hand, int * nb_objs, int * objectives, int *new_obj, int player){
  for (int i=0 ; i<nb_objs_given ; i++){
    if (T_chosen_objs[i]==0){
      all_objective_conditions[obj_player_hand[i]]=0; //puts back the objective in the pile
      obj_player_hand[i]=-1; //suppresses the objective of the hand
      nb_objs[player]--;//modifies the number of objectives      
    }
  }
  for (int i=0 ; i<nb_objs_given ; i++){
    if(obj_player_hand[i]==-1){
      for(int j=nb_objs_given-1 ; j>i ; j--){
	if(obj_player_hand[j]!=-1){
	  obj_player_hand[i]=obj_player_hand[j];
	  obj_player_hand[j]=-1;
	  break;
	}
      }
    }
  }
  for (int i=0 ; i<nb_objs[player] ; i++){
    new_obj[i]=obj_player_hand[i];
  }
  objectives[player]=nb_objs[player]; 
}

