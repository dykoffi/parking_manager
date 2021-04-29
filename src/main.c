/**
 * @file src/main.c 
 * @brief Le point d'entrée de l'application
 * 
 * Contient la définition de la fonction principale, gère la logique de toute l'application 
 * et les interactions avec l'utilisateur.
 * 
 * @author Edy koffi
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../include/main.h"
#include "../include/add_type_vehicule.h"
#include "../include/add_vehicule.h"
#include "../include/fort.h"
#include "../include/list_types.h"
#include "../include/list_vehicules.h"
#include "../include/sqlite3.h"
#include "../include/unpark_vehicule.h"
#include "../include/history.h"

int print_menu(void)
{
  printf("\nBIENVENUE\n");
  printf("\nMENU\n\n");
  printf("\t\033[1;35mVEHICULES\033[0m\n\
          \033[1;34m1\033[0m. Enregistrer un Stationnement\n\
          \033[1;34m2\033[0m. Historique des Véhicules\n");
  printf("\t\033[1;35mTYPES DE VEHICULES\033[0m\n\
          \033[1;34m3\033[0m. Ajouter un Type de Véhicules\n\
          \033[1;34m4\033[0m. Lister les Types de Véhicules\n");
  printf("\t\033[1;35mSTATIONNEMENTS\033[0m\n\
          \033[1;34m5\033[0m. Sortir un Véhicule\n\
          \033[1;34m6\033[0m. Historique\n");
  return 0;
}

int main(int argc, char *argv[])
{
  char choice[15], continuer = 'O';
  int ichoice, c;
  do
  {
    print_menu();
    do
    {
      printf("Votre choix : ");
      scanf("%s", choice);
      while (1)
      {
        c = getchar();
        if (c == '\n')
          break;
      }
      ichoice = atoi(choice);
      if (strcmp(trim(choice), "quitter") == 0 || strcmp(trim(choice), "Quitter") == 0)
      {
        continuer = 'N';
        printf("Sortie de l'application...\n");
        sleep(1);
        exit(0);
      }
      else if (!(ichoice >= 1 && ichoice <= 13))
      {
        printf("\033[31mErreur :: \033[1mChoix non disponible\033[0m\n");
      }
    } while (!(ichoice >= 1 && ichoice <= 13));

    if (continuer == 'O' || continuer == 'o')
    {
      switch (ichoice)
      {
      case 1:
        printf("Ajout d'un Véhicule : \n");
        add_vehicule();
        break;
      case 2:
        printf("Liste des Véhicules : \n");
        list_vehicles();
        break;
      case 3:
        printf("Ajout d'un Type de Véhicules : \n");
        add_type();
        break;
      case 4:
        printf("Liste des Types de Véhicule : \n");
        list_types();
        break;
      case 5:
        printf("Sortie de Véhicule : \n");
        unpark_vehicle();
        break;
      case 6:
        printf("Historique des Paiements :\n");
        list_vehicles();
        break;
      case 7:
        printf("Test de la connexion à la BDD : \n");
        connect();
        break;
      }
    }
    printf("Voulez-vous faire autre chose ? (O/N) ");
    scanf("%c", &continuer);
    while (1)
    {
      c = getchar();
      if (c == '\n')
        break;
    }
  } while (continuer == 'O' || continuer == 'o');

  printf("Sortie ...\n");
  sleep(1);
  exit(0);
}