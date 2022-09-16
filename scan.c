/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.2";

int const DB_SIZE = 20;

struct person
{
    int nummer;
    int  geburtsjahr;
    int todesjahr;
    char vorname[10];
    char nachname[10];
    char M_vorname[10];
    char M_nachname[10];
    char V_vorname[10];
    char V_nachname[10];
    char Partner[10];
    char Kind_1[10];
    char Kind_2[10];
    char Kind_3[10];
};
typedef struct person person_t;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t database[DB_SIZE];
    while(fscanf(filepointer,
                 "%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
                 &database[zaehler].nummer,
		 &database[zaehler].geburtsjahr,
		 &database[zaehler].todesjahr,
                 database[zaehler].vorname,
                 database[zaehler].nachname,
                 database[zaehler].M_vorname,
		 database[zaehler].M_nachname,
		 database[zaehler].V_vorname,
		 database[zaehler].V_nachname,
		 database[zaehler].Partner,
		 database[zaehler].Kind_1,
		 database[zaehler].Kind_2,
		 database[zaehler].Kind_3)
          != EOF)
    {
        printf("%d, %d, %d, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s \n",
                database[zaehler].nummer,
		database[zaehler].geburtsjahr,
		database[zaehler].todesjahr,
		database[zaehler].vorname,
		database[zaehler].nachname,
		database[zaehler].M_vorname,
		database[zaehler].M_nachname,
		database[zaehler].V_vorname,
		database[zaehler].V_nachname,
		database[zaehler].Partner,
		database[zaehler].Kind_1,
		database[zaehler].Kind_2,
		database[zaehler].Kind_3);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
