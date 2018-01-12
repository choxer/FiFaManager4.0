#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED
#include "datastruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createTeam(void);
void deleteTeam(void);

void addPlayer(int);
void deletePlayer(void);

void searchPlayer(void);

void listTeams(void);
void listOneTeam(int);
void listOnePlayer(int, int);

void endprog(void);

void freeOnePlayer(TPlayer *Player);
void freeOneTeam(TTeam *Team);

#endif // TEAM_H_INCLUDED
