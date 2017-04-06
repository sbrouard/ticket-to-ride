#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"

//#include "interface.h"
//#include "server.h"

int test_get_map_info(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  if (map_info.nb_towns == 2 && map_info.nb_links == 1 && map_info.nb_objs == 1 && map_info.nb_w_player == 10)
    return 1;
  return 0;
  
}



int test_file2rails(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective objs[map_info.nb_objs];
  file2rails(rails, map_info.nb_links, objs, map_info.nb_objs, "tests_file.txt");
  if (rails[0].town1 == 1 && rails[0].town2 == 2 && rails[0].length == 6 && rails[0].color == 42){
    return 1;
  }
  return 0;
}


int main(){
  printf("test of get_map_info ... ");
  if (test_get_map_info())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  printf("test of file2rails ... ");
  if (test_file2rails())
    printf("PASSED\n");
  else
  printf("FAILED\n");

  return 0;
}
