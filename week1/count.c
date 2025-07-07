#include <string.h>
#include <stdio.h>
#include "include/input_utils.h"


int calc_length(string name);

int main(){
  string name = "EMEKA NWOSU";


  int length = calc_length(name);

  printf("Number of characters in name %s is %i\n", name, length);
}


int calc_length(string name){
  int length = 0;
  while (name[length] != '\0'){
    length++;
  }
  return length;
}

#include <string.h>

int main(){
  char *name[0] = "EMEKA";
  char *name[1] = "NWOSU";

  printf("Initials in name is %s\n",char*);
} 