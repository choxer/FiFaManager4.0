#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TEAM.H"
#include "tools.h"
#include "datetime.h"
#include "menu.h"
#include "datastruct.h"
#include "sort.h"
#include "database.h"

int TeamCounter = 0;     //Deklaration von globalen variabeln,
TTeam Teams[MAXTEAM];

//---------------------Funktionen-----------------------------------------//

void createTeam(void){

    clearScreen();
    printf("Erfassung einer neuen Mannschaft\n");
    printline('-',strlen("Erfassung einer neuen Mannschaft"));


    if(TeamCounter >= MAXTEAM)
    {
        return;
        printf("MAXTEAM wurde überschritten\n");
    }
    printf("Teamcounter: %i\n", TeamCounter);

        //Teamname
        void *ptrTest = (Teams+TeamCounter)->Teamn;
        ptrTest = calloc(25, sizeof(char));
        do{} while( !getText("Teamname: ", 25, &((Teams+TeamCounter)->Teamn), 0 ) );

        //trainername
        void *ptrTest2 = (Teams+TeamCounter)->Coach;
        ptrTest2 = calloc(25, sizeof(char));
        do{} while( !getText("Trainername: ", 25, &((Teams+TeamCounter)->Coach), 1 ) );

    do
    {
            addPlayer(1);       //1 für nicht nachfragen ob der spieler einem bestehendem team hinzugefügt werden soll
            printf("Teamcounter: %i\n", TeamCounter);
            printf("Anzahl d. Spieler: %i\n", Teams[TeamCounter].AnzPlayer);

    } while( askYesorNo("Wollen sie noch einen Spieler anlegen?") );
    TeamCounter++;
}

void deleteTeam(void)
{
    printf("deleteTeam\n");
}

void addPlayer(int hinzu)
{
    clearScreen();
    //MenuTitel
    printf("Erfassung eines neuen Spielers\n");
    printline('-',strlen("Erfassung eines neuen Spielers"));

    if(hinzu == 0)
    {
        if(askYesorNo("Wollen Sie einem bestehendem Team einen Spieler hinzufuegen?"))
        {
            TMTitel ArrMTeams[TeamCounter];
            char MenuT[] = {"Angelegte Teams"};
            int i;

            for( i = 0; i < TeamCounter; i++)
            {
                strcpy(ArrMTeams[i].MTitel, (Teams+i)->Teamn);
            }
            int TC = ( getmenu(MenuT,ArrMTeams,TeamCounter) );

            int AnzPlayer = (Teams+TC)->AnzPlayer;
            if( AnzPlayer >= MAXPLAYER)
            {
                printf("Dieses Team ist voll..\n");
            }
            else
            {
                //Spielername
                getText("Spielername: ",30, &( (((Teams+TC)->Player)+AnzPlayer)->Playern), 0 );
                //Birthday
                do{}while(!getDate("Geburtstag: ",0, TC , AnzPlayer));
                //Trikonummer
                getNumber("Trikotnummer: ",1,&((((Teams+TC)->Player)+AnzPlayer)->Trikotn),0,99);
                //Goals
                getNumber("Goals: ",1,&((((Teams+TC)->Player)+AnzPlayer)->Goals),0,99);

                ((Teams+TC)->AnzPlayer)++;
            }
        }
        else
        {
            createTeam();
        }

    }
    else
    {
        int AnzPlayer = (Teams+TeamCounter)->AnzPlayer;

        //Spielername
        getText("Spielername: ",30, &( (((Teams+TeamCounter)->Player)+AnzPlayer)->Playern),0);
        //Birthday
        getDate("Geburtstag: ",0, TeamCounter , AnzPlayer);
        //Trikonummer
        getNumber("Trikotnummer: ",1,&((((Teams+TeamCounter)->Player)+AnzPlayer)->Trikotn),0,99);
        //Goals
        getNumber("Goals: ",1,&((((Teams+TeamCounter)->Player)+AnzPlayer)->Goals),0,999);

        ((Teams+TeamCounter)->AnzPlayer)++;
    }

}

void deletePlayer(void)
{
    printf("deletePlayer\n");
}

void searchPlayer(void)
{
    printf("searchPlayer\n");
}



void listTeams(void)
{
    int i = 0;
    clearScreen();

    for( i = 0; i < TeamCounter; i++)
    {
        listOneTeam(i);
    }
}

void listOneTeam(int TC)
{
    int j = 0;
    printf("------------------->Team: %i\n",TC+1);
    printf("Team: %s\n", (Teams+TC)->Teamn );

    if( ((Teams+TC)->Coach) )
        printf("Trainer         : %s\n", (Teams+TC)->Coach);
    else
        printf("Trainer         :   \n");

    printf("Anzahl Spieler  : %i\n", (Teams+TC)->AnzPlayer);

    for( j = 0; j < ((Teams+TC)->AnzPlayer); j++)
    {
        listOnePlayer(j, TC);
    }

}

void listOnePlayer(int PC, int TC)
{
    printf("  ------------------->Player: %i\n",PC+1);

    //Spielername
    printf("  Spielername: %s\n",(((Teams+TC)->Player)+PC)->Playern);

    //Birthday
    printf("  Birthday: %i.%i.%i\n" ,((((Teams+TC)->Player)+PC)->Birthday)->Day
                                    ,((((Teams+TC)->Player)+PC)->Birthday)->Month
                                    ,((((Teams+TC)->Player)+PC)->Birthday)->Year  );

    //Trikonummer
    printf("  TrikotNr: %i\n",(((Teams+TC)->Player)+PC)->Trikotn );

    //Goals
    printf("  Goals: %i\n",(((Teams+TC)->Player)+PC)->Goals);

}


void freeOnePlayer(TPlayer *Player)
{
    free(Player->Playern);
    free(Player->Birthday);
}

void freeOneTeam(TTeam *Team)
{
    int i;

    free(Team->Teamn);
    free(Team->Coach);
    for (i = 0; i < Team->AnzPlayer; i++)
        freeOnePlayer(Team->Player + i);
}

void endprog(void)
{
    if( askYesorNo("Wollen Sie Ihre Werte speichern?"))
    {
        FILE *Datei2= fopen("save2.txt", "w");
        if(Datei2)
        {
            save(Datei2);
        }
        else
        {
            printf("ERROR: datei2 konnte nicht geoffnet werden\n");
            return;
        }
        fclose(Datei2);

        printf("Werte wurden gespeichert\n");
    }
    int i;
    for(i = 0; i < TeamCounter; i++)
    {
        freeOneTeam(Teams + i);
    }
    printf("Programmende\n");
}

