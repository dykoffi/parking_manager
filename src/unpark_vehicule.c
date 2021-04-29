#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <time.h>
#include "../include/sqlite3_client.h"
#include "../include/unpark_vehicule.h"

#ifndef _UNPARK_VEHICLE_
#define _UNPARK_VEHICLE_

char parking_code[20];
unsigned int vehicle_id;
char date_arrivee[30];
char date_sortie[30];
unsigned int vehicle_count;
unsigned int parking_fees;
char matricule[15];
char client[160];
char libelle_type[100];
unsigned int tarif_heure;
unsigned int tarif_24;
unsigned int duree;

static int callback_unpark(void *NotUsed, int argc, char **argv, char **azColName)
{
  return 0;
}

static int callback_count_vehicle(void *NotUsed, int argc, char **argv, char **azColName)
{
  vehicle_count = atoi(argv[0]);
  return 0;
}

static int callback_get_parked_vehicle(void *NotUsed, int argc, char **argv, char **azColName)
{
  strcpy(date_arrivee, argv[1]);
  strcpy(date_sortie, argv[2]);
  duree = atoi(argv[3]);
  strcpy(matricule, argv[4]);
  strcpy(client, argv[6]);
  strcpy(libelle_type, argv[7]);
  tarif_heure = atoi(argv[8]);
  tarif_24 = atoi(argv[9]);

  return 0;
}

void unpark_vehicle()
{
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;

  printf("Entrez le \033[1mCode de Stationnement\033[0m : ");
  fgets(parking_code, 20, stdin);
  clear_buffer();
  strcpy(parking_code, trim(parking_code));
  char *p = strtok(parking_code, "-");
  vehicle_id = 0;
  while (p != NULL)
  {
    vehicle_id = atoi(p);
    p = strtok(NULL, "-");
  }
  con = sqlite3_open(DB_FILE, &dbh);
  if (con)
  {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
    exit(1);
  }

  // Check if the vehicle is [in]
  char Query0[100];
  sprintf(Query0, "SELECT COUNT(*) AS nb FROM stationnements WHERE id_vehicule=%d AND etat='in';", vehicle_id);
  con = sqlite3_exec(dbh, Query0, callback_count_vehicle, 0, &ErrMsg);
  if (con != SQLITE_OK)
  {
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }

  if (vehicle_count != 1)
  {
    printf("\033[1;31mDésolé, ce Véhicule n'est pas en Stationnement.\033[0m\n");
  }
  else
  {
    // Get the vehicle and compute parking fees
    char Query[500];
    sprintf(Query, "SELECT s.id_vehicule, s.date_arrivee, DATETIME('now') as date_sortie, CAST((JULIANDAY(DATETIME('now')) - JULIANDAY(s.date_arrivee)) * 24 AS INTEGER) as duree, v.matricule, v.id_type_vehicule, v.client, tv.libelle, tv.tarif_heure, tv.tarif_24_heures FROM stationnements s LEFT JOIN vehicules v ON s.id_vehicule=v.id JOIN type_vehicules tv ON v.id_type_vehicule=tv.id WHERE s.id_vehicule=%d LIMIT 1;", vehicle_id);

    con = sqlite3_exec(dbh, Query, callback_get_parked_vehicle, 0, &ErrMsg);
    if (con != SQLITE_OK)
    {
      fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
      sqlite3_free(ErrMsg);
    }
    else
    {
      if (!duree && (strcmp(date_arrivee, date_sortie) != 0))
        duree = 1;
      parking_fees = ((int)(duree / 24)) * tarif_24 + ((int)(duree % 24)) * tarif_heure;
      printf("\nVOTRE FACTURE\n");
      printf("Code de Stationnement :\t%s-%d\n", parking_code, vehicle_id);
      printf("Client :\t%s\n", client);
      printf("Matricule Vehicule :\t%s\n", matricule);
      printf("Type de Vehicule :\t%s\n", libelle_type);
      printf("Date Arrivee :\t%s\n", date_arrivee);
      printf("Date Sortie :\t%s\n", date_sortie);
      printf("Duree :\t%d heures\n", duree);
      printf("Tarif Heure :\t%d FCFA\n", tarif_heure);
      if (duree >= 24)
        printf("Tarif 24 Heures :\t%d FCFA\n", tarif_24);
      printf("TOTAL FACTURE :\t%d FCFA\n", parking_fees);
      printf("\n");
      char c, proceed = 'N';
      printf("Confirmez-vous la sortie de ce Véhicule ? O/N ");
      scanf("%c", &proceed);
      while (1)
      {
        c = getchar();
        if (c == '\n')
          break;
      }
      if (proceed == 'O' || proceed == 'o')
      {
        char Query1[100];
        sprintf(Query1, "UPDATE stationnements SET date_sortie='%s', etat='out' WHERE id_vehicule=%d;", date_sortie, vehicle_id);
        con = sqlite3_exec(dbh, Query1, callback_unpark, 0, &ErrMsg);
        if (con != SQLITE_OK)
        {
          fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
          sqlite3_free(ErrMsg);
        }
        else
        {
          char Query211[100];
          sprintf(Query211, "UPDATE type_vehicules SET places_dispo=places_dispo-1 WHERE libelle='%s' LIMIT 1;", libelle_type);
          con = sqlite3_exec(dbh, Query211, callback_unpark, 0, &ErrMsg);
          if (con != SQLITE_OK)
          {
            fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
            sqlite3_free(ErrMsg);
          }
          printf("\033[32mLe Véhicule a bien été sorti !\033[0m\n");
        }
      }
      else
      {
        printf("Vous avez annulé !\n");
      }
    }
  }

  sqlite3_close(dbh);
}
#endif
