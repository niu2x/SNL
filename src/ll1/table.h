#ifndef __my_table
#define __my_table

#include "NT.h"
#include "../snl/token.h"
#include <map>

extern std::map<TokenType, int> table[100];
void init_table();
#endif