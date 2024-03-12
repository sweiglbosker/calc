#ifndef _BACKEND_H
#define _BACKEND_H

#include "parser.h"

void PrintParseTree(ParseTree *);
long evalE(ParseTree *t);
long evalE2(ParseTree *t);
long evalE3(ParseTree *t);
long evalER(long a, ParseTree *t);
long evalE2R(long a, ParseTree *t);

#endif
