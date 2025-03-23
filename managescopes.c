#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "template.h"

void initializeScope(Scope* newScope) { //Initialize a scope
  (newScope)->parent=NULL;
  (newScope)->symTable=(pair**)malloc(sizeof(pair*)*MAX_SIZE);
  for(int i=0;i<MAX_SIZE;i++) newScope->symTable[i]=NULL;
}
int hash(char *str) {
  int index=0, prime=31;
  while(*str) {
    index=(index*prime + *str)%MAX_SIZE;
    str++;
  }
  return index;
}

void insertVar(Scope* currScope, char* v_name, int val) { //Creating new variables using "assign"
  int i=hash(v_name);
  pair* temp=(currScope)->symTable[i];
  while(temp && temp->next && strcmp(temp->variable_name,v_name)) temp=temp->next;

  if(temp && !strcmp(temp->variable_name,v_name)) temp->value=val;
  else {
    pair* new_var=(pair*)malloc(sizeof(pair));
    strcpy(new_var->variable_name,v_name);
    new_var->value=val;
    new_var->next=NULL;

    if(!temp) currScope->symTable[i]=new_var;
    else temp->next=new_var;
  }
}
int search(Scope* currScope, char* v_name, int *val) {
  int i=hash(v_name);
  pair* temp=currScope->symTable[i];
  while(temp && temp->next && strcmp(temp->variable_name,v_name)) temp=temp->next;
  if(temp && !strcmp(temp->variable_name,v_name)) {
    *val=temp->value;
    return 1;
  }
  else return 0;
}
void lookup(Scope* currScope, char* v_name) { //Lookup value using "print"
  Scope* temp=currScope; int val;
  while(temp && !search(temp,v_name,&val)) temp=temp->parent;
  if(!temp) printf("Error: Variable %s not defined!\nProcess exitted with return status 1!!",v_name);
  else printf("%d\n",val);
} 
void createScope(Scope** parent) { //Creating new scope using "begin"
  Scope* child=(Scope*)malloc(sizeof(Scope));
  initializeScope(child);
  child->parent=*parent;
  *parent=child;
}
void deleteScope(Scope** currScope) { //Ending a scope using "end"
  Scope* temp=*currScope;
  (*currScope)=(*currScope)->parent;
  for(int i=0;i<MAX_SIZE;i++) {
    pair* head=temp->symTable[i];
    while(head) {
      pair* temp=head;
      head=head->next;
      free(temp);
    }
  }
  free(temp->symTable);
  free(temp);
}
