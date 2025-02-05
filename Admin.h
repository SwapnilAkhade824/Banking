#ifndef TEMP_H
#define TEMP_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
long long generateUniqueId();
int addaccount();
int verifyaccount(long long acc_num, char *passwd);
void removeNewline(char *str);
#endif