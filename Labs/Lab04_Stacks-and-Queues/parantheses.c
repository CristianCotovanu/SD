#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){

  /* TODO: Cerinta 3
   * Implementation must use a stack.
   * Do NOT forget to deallocate the memory you use.
   */
  int i;
  Item aux;
  Stack* stack = createStack();

  for(i = 0; i < length; i++) {
    aux = str[i];
    //printf("%c\n", aux);
    if(aux == '(') {
      push(stack, '('); //Add to stack '(' 
    } else if (isStackEmpty(stack) == 0) { // Remove 1 '(' corresponding to ')' 
        pop(stack);                   // if the stack is not empty   
    } else {
        return 0; //If there is no correspondent to '(' that is not balanced
    }
  }

  if(isStackEmpty(stack) == 1) {
      return 1;
  } else {
      return 0;
  }
}


int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
