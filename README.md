# Implementation of a Symbol Table to handle Nested Scopes

A compiler records the variable names used in the source program along with its attributes and 
stores it in a data structure called a symbol table. 
I have wriiten a code to support implementation of a symbol table with nested scopes using a hash 
table by maintaining a new symbol table for every scope and linking it with the surrounding scope. 

In order to implement the following functionalities I have also implemented file handling to read sample code and then execute it line by line.

Below are the functionalities that need to be implemented. 
# "begin"
Initialize Scope  - increments the current level and  creates a new symbol 
table for that level. It links the new table to the previous level’s table and 
updates the current level pointer used by lookup and insert functions. 

# "assign <variable_name> <value>"
Insert  the value of variable_name in the current scope  with value

# "print <variable_name>"
Lookup  the value of variable_name in the current scope. If it  does not exist in the current 
scope look it up in the surrounding scope 

# "end"  
Finalyze Scope  changes the current level pointer so  that it points to the table 
for the scope surrounding the current level
