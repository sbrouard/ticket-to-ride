#include <stdlib.h>
#include <stdio.h>
#include "link.h"
#include "interface.h"

struct Rail const rail_defaut = {-1,-1,-1,-1};


void init_link(struct Link *res){
  res->nbr_way = 0;
  res->tab_rails = malloc(sizeof(struct My_Rail));
  res->tab_rails[0].rail = &rail_defaut;
  res->tab_rails[0].id_player = -1; 
  res->tab_rails[0].id_rail = -1;
}


void modify_link(struct Link * link, struct Rail * rail, int id_rail){
    if (link->nbr_way != 0)
      link->tab_rails = realloc(link->tab_rails,(link->nbr_way+1) * sizeof(struct My_Rail));
    link->nbr_way++;
    link->tab_rails[link->nbr_way - 1].rail = rail;
    link->tab_rails[link->nbr_way - 1].id_player = -1;
    link->tab_rails[link->nbr_way - 1].id_rail = id_rail;
}


void free_link(struct Link * link){
  free(link->tab_rails);
  link->tab_rails = NULL;
}


struct Link ** init_map(int nbr_towns, struct Rail *tab_rails, int size_tab_rails){

    if (nbr_towns < 0)
        return NULL;
    struct Link ** matrix = malloc((nbr_towns+1) * sizeof(struct Link *));
    for(int i=0; i<nbr_towns+1; i++)
      matrix[i] = malloc((nbr_towns+1) * sizeof(struct Link));

    for (int i=0;i<nbr_towns+1;i++)
      for (int j=0;j<nbr_towns+1;j++)
	init_link(&matrix[i][j]);

    int a;
    int b;
    for (int i=0; i<size_tab_rails;i++){
        a=tab_rails[i].town1;
        b=tab_rails[i].town2;
        if (a<b)
            modify_link(&matrix[a][b],&tab_rails[i],i);
        else
            modify_link(&matrix[b][a],&tab_rails[i],i);
    }
    return matrix;
}


void free_map(struct Link ** matrix, int nbr_towns){
  for(int i=0; i<nbr_towns+1; i++){
    for(int j=0;j<nbr_towns+1; j++){
      free_link(&(matrix[i][j]));
    }
    free(matrix[i]);
  } 
  free(matrix);
  matrix=NULL;
}


void set_player_on_rail(struct My_Rail * rail, int id){
    rail->id_player = id;
}


int is_rail_free(struct My_Rail * rail){
    return rail->id_player==0;
}


int who_on_rail(struct My_Rail * rail){
    return rail->id_player;
}



int rail_size(struct My_Rail * rail){
    return rail->rail->length;
}



struct My_Rail * give_my_rail(int id_rail, struct Link **matrix, struct Rail *tab_rails){
  struct Rail rail = tab_rails[id_rail];
  int town1 = rail.town1;
  int town2 = rail.town2;
  struct Link *link;
  struct My_Rail *res=NULL;
  if (town1<town2)
    link = &matrix[town1][town2];
  else
    link = &matrix[town2][town1];
  for(int i=0; i< link->nbr_way; i++){
    if (link->tab_rails[i].id_rail == id_rail){
      res = &(link->tab_rails[i]);
      return res;
    }
  }
  return res;
}
