// Naive AI (random choice)

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "player.h"
#include "link.h"
#include "interface.h"
#include "server.h"

static struct Player AI_0;
static struct Link **AI_0_matrix;


// AUXILIARY FUNCTIONS

/*!
 * \brief AI_0_fill_tab_accessible (auxiliary function of the function "objective_realised")
 * \param tab_to_fill is a tabular of size the total number of towns; the function is going to set tab_to_fill[i] at 1 if the town "i" is accessible by the player from the town "current_town".
 * \param current_town is the town from which the function is going to search all towns accessible by the player (if he has set a rails from this town); at the begining: current_town=town1 or town2 of the objective
 * \param id is the identifier of the player.
 */
void AI_0_fill_tab_accessible(int *tab_to_fill, int current_town, int id){ 
  tab_to_fill[current_town] = 1;
  for(int i=0; i<AI_0.nb_rails; i++){
    int town1 = AI_0.rails[i].town1;
    int town2 = AI_0.rails[i].town2;
    struct My_Rail *my_rail = give_my_rail(i,AI_0_matrix,AI_0.rails);
    if(my_rail->id_player == id && town1 == current_town && tab_to_fill[town2]==0)
      AI_0_fill_tab_accessible(tab_to_fill,town2,id);
    if(my_rail->id_player == id && town2 == current_town && tab_to_fill[town1]==0)
      AI_0_fill_tab_accessible(tab_to_fill,town1,id);
  }
}

/*!
 * \brief AI_0_objective_realised
 * \param town1 is the town1 of the objective.
 * \param town2 is the town2 of the objective.
 * \param id is the identifier of a given player.
 * \return Returns 1 if the objective has been realised by the player.
 */
int AI_0_objective_realised(int town1, int town2, int id){
  int towns_accessible_left[AI_0.nb_towns+1];
  int towns_accessible_right[AI_0.nb_towns+1];
  for(int i=1; i<AI_0.nb_towns+1; i++){
    towns_accessible_left[i] = 0;
    towns_accessible_right[i] = 0;
  }
  AI_0_fill_tab_accessible(towns_accessible_left,town1,id);
  AI_0_fill_tab_accessible(towns_accessible_right,town2,id);
  int realised = 0;
  for(int i=1; i<AI_0.nb_towns+1; i++){
    if(towns_accessible_left[i]==1 && towns_accessible_right[i]==1)
      realised = 1;
  } 
  return realised;
} 





// MAIN FUNCTIONS

/*!
 * \brief AI_0_init_player Initialises all the parameters of a struct Player (composed of the general game parameters, and his own informations about the game).
 * \param id is the identifier of the player.
 * \param nb_players is the total number of players in the game.
 * \param nb_towns is the total number of towns in the game.
 * \param nb_rails is the total number of rails in the game.
 * \param rails is the tabular composed of all the rails of the game.
 * \param nb_initial_wagons is the number of wagons that each player has at the begining of the game.
 * \param nb_obj is the total number of objective-cards of the game.
 * \param objs is the tabular composed of all the objective-cards of the game.
 * \return Returns 1 if the initialisation went well; 0 otherwise.
 */
int AI_0_init_player(int id, int nb_players, int nb_towns, int nb_rails, struct Rail *rails, int nb_initial_wagons, int nb_obj, struct Objective *objs){

  // Storage of all the informations
  AI_0.id_player = id;
  AI_0.points = 0;
  AI_0.nb_players = nb_players;
  AI_0.nb_towns = nb_towns;

  AI_0.nb_remaining_wagons = malloc(nb_players*sizeof(int)); 
  for(int i=0; i<nb_players; i++)
    AI_0.nb_remaining_wagons[i] = nb_initial_wagons;


  AI_0.nb_remaining_wagon_cards = malloc(nb_players*sizeof(int));
  for(int i=0; i<nb_players; i++){
    AI_0.nb_remaining_wagon_cards[i] = 0;
  }
  

  AI_0.nb_remaining_objective_cards = malloc(nb_players*sizeof(int));
  for(int i=0; i<nb_players; i++){
    AI_0.nb_remaining_objective_cards[i] = 0;
  }


  AI_0.nb_rails = nb_rails;
  AI_0.rails = malloc(nb_rails*sizeof(struct Rail));
  for(int i=0; i<nb_rails; i++){
    AI_0.rails[i].town1 = rails[i].town1;
    AI_0.rails[i].town2 = rails[i].town2;
    AI_0.rails[i].length = rails[i].length; 
    AI_0.rails[i].color = rails[i].color;
  }


  AI_0.total_nb_obj = nb_obj;
  AI_0.objs = malloc(nb_obj*sizeof(struct Objective));
  for(int i=0; i<nb_obj; i++){
    AI_0.objs[i].town1 = objs[i].town1;
    AI_0.objs[i].town2 = objs[i].town2;
    AI_0.objs[i].points = objs[i].points;
  }


  AI_0.nb_personal_objs = 0;
  AI_0.nb_objs_completed = 0;
  AI_0.personal_objs = malloc(nb_obj*sizeof(int));
  for(int i=0; i<nb_obj; i++)
    AI_0.personal_objs[i] = -1;
  // size of AI_0.personal_objs = total number of objs
  // but has only AI_0.nb_personal_objs

  int *col = malloc(sizeof(int)); //col must be used in the function colors
  AI_0.nb_colors = colors(AI_0.rails, AI_0.nb_rails,&col);
  free(col); //col not usefull so needs to be freed

  AI_0.nb_personal_wagon_cards = 0;
  AI_0.personal_wagon_cards = malloc(AI_0.nb_colors*sizeof(int));
  for(int i=0; i<AI_0.nb_colors; i++)
    AI_0.personal_wagon_cards[i] = 0;


  AI_0.nb_objectives_chosen = 0;
  AI_0.draw_chosen = 0;


  // Initialisation of the personal matrix
  AI_0_matrix = init_map(nb_towns, rails, nb_rails);

  return 1;
}





/*!
 * \brief AI_0_play_turn Calls the player, actualises all the changes that occured since the last time the player was called, and asks the player which action he wants.
 * \param used_wagons is a tabular which length is the number of players (for a given player, the tabular's value is the number of wagons he has set during the last round).
 * \param cards_in_hand is a tabular which length is the number of players (for a given player, the tabular's value is the number of cards that the player has won or lost during the last round: negative if lost).
 * \param objectives is a tabular composed of the number of objectives drawned by each player.
 * \param nb_new_rails is the length of the tabular changes (= the number of rails that the current player has set during the last round).
 * \param changes is the tabular of all the rails that the players have set during the last round.
 * \param new_obj is the tabular of the objectives that the current player has drawned during the last round.
 * \param cards If the action chosen in the last round was "draw": "cards" is the tabular of all the colors (= wagon-cards) drawned. If the action chosen was "build": "cards" is the tabular of all the colors lost (because set).
 * \return Returns the struct Action chosen and completed by the player according to his strategy.
 */

struct Action AI_0_play_turn(int *used_wagons, int *cards_in_hand, int *objectives, int nb_new_rails, struct New_rail *changes, int *new_obj, int *cards){


  // Actualisation of the matrix with the tabular "changes"
  for(int i=0; i<nb_new_rails; i++){
    struct My_Rail *my_rail = give_my_rail(changes[i].rail, AI_0_matrix, AI_0.rails);
    set_player_on_rail(my_rail, changes[i].player);
  }


  // Actualisation of all player's parameters
  for(int i=0; i<AI_0.nb_players; i++){
    AI_0.nb_remaining_wagons[i] -= used_wagons[i];
    AI_0.nb_remaining_wagon_cards[i] += cards_in_hand[i];
    AI_0.nb_remaining_objective_cards[i] += objectives[i];
  }

  // Actualisation of own objectives
  for(int i=0; i<objectives[AI_0.id_player] && AI_0.nb_personal_objs < AI_0.total_nb_obj; i++){
    AI_0.personal_objs[AI_0.nb_personal_objs] = new_obj[i];
    AI_0.nb_personal_objs++;
  }

  // Actualisation of own cards
  if(AI_0.draw_chosen == 1){ // case draw
    for(int i=0; i<cards_in_hand[AI_0.id_player]; i++){
      AI_0.nb_personal_wagon_cards++;
      for(int j=0; j<AI_0.nb_colors; j++){
	if(cards[i]==j)
	  AI_0.personal_wagon_cards[j]++;
      }
    }
  }
  if(cards_in_hand[AI_0.id_player]<0){ // case build
    for(int i=0; i<(0-cards_in_hand[AI_0.id_player]); i++){
      AI_0.nb_personal_wagon_cards--;
      for(int j=0; j<AI_0.nb_colors; j++){
	if(cards[i]==j)
	  AI_0.personal_wagon_cards[j]--;
      }
    }
  }

  // Actualisation of number of own objectives completed
  int number_realised = 0;
  for(int i=0; i<AI_0.nb_personal_objs; i++){
    int town1 = AI_0.objs[AI_0.personal_objs[i]].town1;
    int town2 = AI_0.objs[AI_0.personal_objs[i]].town2;
    int realised = AI_0_objective_realised(town1,town2,AI_0.id_player);
    if(realised)
      number_realised++;
  }
  AI_0.nb_objs_completed = number_realised;


  // Choose a random action
  struct Action res_action={DRAW,0,0,0};
  srand(time(NULL));
  int nb_aleat = rand();
  nb_aleat = nb_aleat%3;


  // Completion of the struct Action (in relation of the action chosen)
  if(nb_aleat==0){
    res_action.type = DRAW; 
    res_action.rail = 0; // unusefull but still initialised
    int color_aleat_1 = rand();
    int color_aleat_2 = rand();

    res_action.color = (color_aleat_1)%(AI_0.nb_colors);
    res_action.color2 = (color_aleat_2)%(AI_0.nb_colors);  

    AI_0.nb_objectives_chosen = 0;
    AI_0.draw_chosen = 1;
  }
  if(nb_aleat==1){
    res_action.type = BUILD; 
    int rail_aleat = rand();
    res_action.rail = (rail_aleat)%(AI_0.nb_rails);
    res_action.color = 0; // unusefull but still initialised
    res_action.color2 = 0; // unusefull but still initialised
    
    AI_0.nb_objectives_chosen = 0;
    AI_0.draw_chosen = 0;
  }
  if(nb_aleat==2){
    res_action.type = OBJECTIVE;
    res_action.rail = 0; // unusefull but still initialised
    res_action.color = 0; // unusefull but still initialised
    res_action.color2 = 0; // unusefull but still initialised

    AI_0.draw_chosen = 0;
    // AI_0.nb_objectives_chosen set in the function AI_O_choose_objective
  }

  return res_action;
}





/*!
 * \brief AI_0_choose_objective
 * \param nb is the number of objectives proposed to the player.
 * \param objs is the tabular of the objectives proposed to the player.
 * \param min is the minimum number of objectives that the player has to chose in the tabular "objs".
 * \return Returns a tabular (in the stack, but instantly registered by the server) indicating which objectives have been chosen.
 */
int *AI_0_choose_objective(int nb, int *objs, int min){ // Picks a random number of objectives
  srand(time(NULL));
  int *tab = malloc(nb * sizeof(int));
  for(int i=0; i<nb; i++)
    tab[i] = rand()%2;

  int k = 0;
  for(int i=0; i<nb; i++){
    if(tab[i]==1)
      k++;
  }

  AI_0.nb_objectives_chosen = k;
  return tab;
}





/*!
 * \brief AI_0_free_player Frees the struct Player of the player.
 * \return Returns 1 if the player has been freed well.
 */
int AI_0_free_player(){
  free(AI_0.nb_remaining_wagons);
  free(AI_0.nb_remaining_wagon_cards);
  free(AI_0.nb_remaining_objective_cards);
  free(AI_0.rails);
  free(AI_0.objs);
  free(AI_0.personal_objs);
  free(AI_0.personal_wagon_cards);
  return 1;
}

