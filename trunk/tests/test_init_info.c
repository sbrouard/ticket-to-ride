#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"


int test_max_rail_length(){
  struct Map_info map_info = get_map_info("tests_file.txt");

  struct Rail rails[map_info.nb_links];
  struct Objective objectives[map_info.nb_objs];
  file2rails(rails,map_info.nb_links,objectives,map_info.nb_objs,"tests_file.txt");

  int max = max_rail_length(rails, map_info.nb_links);

  return (max == 6);
}

int test_init_wagons(){
  int nb_players=4;
  int nb_w_player=45;
  int  w[nb_players];
  init_wagons(w, nb_players, nb_w_player);
  for(int i=0; i<nb_players;i++){
    if (w[i]!=nb_w_player){
      return 0;
    }
  }
  return 1;
}

void test_init_turn_info_free(int **new_obj, int ** cards, int nb_players){
  for (int i=0; i<nb_players; i++){
    free(new_obj[i]);
    free(cards[i]);
  }
  free(new_obj);
  free(cards);
}


int test_init_turn_informations(){
  int nb_players=4;
  int nb_starting_cards=4;
  int nb_obj_drawn_max=5;
  int max_rail_length=6;
  int used_wagons[nb_players];
  int cards_in_hands[nb_players];
  int objectives[nb_players];
  struct New_rail changes[nb_players];
  
  //int new_obj[nb_players][nb_obj_drawn_max];
  //int cards[nb_players][max_rail_length];
  int **new_obj;
  int **cards;
  new_obj = malloc(sizeof(int*)*nb_players);
  cards =  malloc(sizeof(int*)*nb_players);
  for (int i=0; i<nb_players; i++){
    new_obj[i]=malloc(sizeof(int)*nb_obj_drawn_max);
    cards[i]=malloc(sizeof(int)*max_rail_length);
      }


  init_turn_informations(used_wagons, cards_in_hands, objectives, changes, new_obj, cards, nb_players, nb_starting_cards, nb_obj_drawn_max, max_rail_length);

  for(int i=0; i<nb_players;i++){
    if (used_wagons[i] != 0 || cards_in_hands[i]!=nb_starting_cards || objectives[i]!=0 || changes[i].rail!=-1 || changes[i].player!=-1){
      test_init_turn_info_free(new_obj,cards, nb_players);
      return 0;
    }
  }
  for(int i=0 ; i<nb_players ; i++){
    for (int j=0 ; j<nb_obj_drawn_max ; j++){
      if (new_obj[i][j]!=-1){
	test_init_turn_info_free(new_obj,cards, nb_players);
	return 0;
      }
    }
    for (int j=0; j<max_rail_length; j++){
      if (cards[i][j]!=-1){
	test_init_turn_info_free(new_obj,cards, nb_players);
	return 0;
      }
    }

  }
  test_init_turn_info_free(new_obj,cards, nb_players);
  return 1;
}



int main(){

  printf("Test of max_rail_length ... ");
  if (test_max_rail_length())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  printf("Test of init_wagons ... ");
  if (test_init_wagons())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  printf("Test of init_turn_informations ... ");
  if (test_init_turn_informations())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  return 0;
}
