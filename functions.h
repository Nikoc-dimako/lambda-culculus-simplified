#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "list.h"

using namespace std;

List* num_Lambda(string s);
List* free_variables(string str);
List* reserved_variables(string str);
List* get_touches(List* L1, List* L2);
string renameString(string str,string s1,string s2);
string cutString(string str);
bool isOneVariable(string str);
string get_head(string str);
int get_body_position(string str);

string remove_outer_parenthesis(string sentence);	
string get_type(string str);

string alpha_redex(string sentence,string var_to_rename);
string beta_redex(string s1,string s2,bool flag=true,string head="");
string heta_redex(string);

string normalize(string lambda);
