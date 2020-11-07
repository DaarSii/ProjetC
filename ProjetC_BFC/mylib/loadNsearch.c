
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <err.h>

struct fichier
{
	 char *path;
     char *nom;
	 struct fichier *suivant;
};

struct fichier* add_in(struct  fichier *liste, struct fichier *new)
{
    //
    if (liste ==NULL)
    {
        liste = new;
    }
    
    else 
    {
        new->suivant=liste;
        
    }
    return new;
}



struct fichier *load(char *repertoire, struct fichier *liste)
{
    
    struct dirent *dirent;

    DIR *rep = opendir(repertoire);
    if (rep==NULL)
    {
        warn("fail opendir on %s", repertoire);
    }
    dirent = readdir(rep);
    while(dirent != NULL)
    {
        if (!strcmp(dirent->d_name, ".") || !strcmp(dirent->d_name, ".."))
        {
            dirent = readdir(rep);
            continue;
        }
        struct fichier *new = malloc(sizeof(struct fichier));
        new->path =repertoire;
        new->nom =dirent->d_name;
        new->suivant = NULL;
        liste = add_in(liste, new);
        
        if (dirent ->d_type == 4)
        {
            char *newpath = malloc(sizeof(repertoire)+1+sizeof(dirent->d_name)+1);
            newpath[0] = '\0';
            newpath = strcat(newpath, repertoire);
            newpath = strcat(newpath, "/");
            newpath = strcat(newpath, dirent->d_name);
            liste = load(newpath, liste);
        }
        dirent = readdir(rep);
    }
    closedir(rep);
    return liste;
}




void search(struct fichier *liste, char *fichierCherche)
{
    int trouve=0;
    if (liste == NULL)
    {
         warn("fail searching: list empty");
    }

    struct fichier *actuel = liste;

    while (actuel != NULL)
    {
        if (!strcmp(actuel->nom, fichierCherche))
        {
            printf("%s -> %s \n\n", actuel->nom, actuel->path);
            trouve=1;
        }
        
        actuel = actuel->suivant;
    }
    if (trouve==0)
        printf("Non trouvé\n\n");
}
