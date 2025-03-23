#define MAX_SIZE 100
#define MAX_LENGTH 1000

typedef struct pair{
  char variable_name[MAX_LENGTH];
  int value;
  struct pair* next;
}pair;

typedef struct Scope{
  pair** symTable;
  struct Scope* parent;
}Scope;

void insertVar(Scope*, char*, int);
void lookup(Scope*, char*);
void createScope(Scope**);
void deleteScope(Scope**);
void processFile(const char *, Scope*);
