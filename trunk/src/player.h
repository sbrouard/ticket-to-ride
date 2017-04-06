#ifndef PLAYER_H
#define PLAYER_H

struct Player{
  int id_player;
  int points;
  int nb_players; 
  int nb_towns; // Total number of towns
  int nb_colors; // Total number of colors

  int *nb_remaining_wagons; // Remaining wagons for each player
  int *nb_remaining_wagon_cards; // Remaining wagon-cards for each player
  int *nb_remaining_objective_cards; // Remainging objective-cards for each player

  int nb_rails; // Total number of rails
  struct Rail *rails; // Initial tabular of all rails

  int total_nb_obj;
  struct Objective *objs; // Tabular of all the objectives

  int nb_personal_objs;
  int nb_objs_completed;
  int *personal_objs; // Tabular of indices (of the players's objectives)
  
  int nb_personal_wagon_cards;
  int *personal_wagon_cards; // Tabular indices=colors ; number=number of this color

  int nb_objectives_chosen; // Number of objectives chosen in the last round
  int draw_chosen; // 1 if the action chosen is to draw (piocher)
};


#endif


