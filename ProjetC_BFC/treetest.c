#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <err.h>
#include "mylib/mylib.h"


struct fichier
{
	 char *path;
     char *nom;
	 struct fichier *suivant;
};


// commande: ./load "chemin" "nom_fichier"
int main(int nbarg, char *arg[])
{
    struct fichier *liste = NULL;
    
    if (nbarg ==3)
    {
            printf("loading\n");
            liste = load(arg[1], liste);
            printf("loading complete\n");
            printf("search\n\n");
            search(liste, arg[2]);
            printf("search complete\n");
    }
    else printf("Nombre d'arguments invalide\n");
    
    free(liste);
    
    return 0;
}
