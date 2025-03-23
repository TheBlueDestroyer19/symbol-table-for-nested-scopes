#include <stdio.h>
#include "template.h"

int main() {
  printf("Enter the name of the file to be executed: ");
  char fname[100]; scanf("%s",fname);
  Scope* currentScope=NULL;
  processFile(fname,currentScope);
}
