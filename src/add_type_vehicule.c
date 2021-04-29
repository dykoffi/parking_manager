#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "../include/sqlite3_client.h"
#include "../include/add_type_vehicule.h"

#ifndef _ADD_TYPE_VEHICULE_
#define _ADD_TYPE_VEHICULE_

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  return 0;
}

void add_type() {
  char libelle[101];
  char nbre_total_place[12];
  char tarif_heure[12];
  char tarif_24_heures[12];
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;

  printf("Entrez le \033[1mLibellé du Type\033[0m : ");
  fgets(libelle, 100, stdin);
  clear_buffer();
  printf("Entrez le \033[1mNombre Total de Places\033[0m : ");
  fgets(nbre_total_place, 11, stdin);
  clear_buffer();
  printf("Entrez le \033[1mTarif par Heure\033[0m : ");
  fgets(tarif_heure, 11, stdin);
  clear_buffer();
  printf("Entrez le \033[1mTarif 24 Heures\033[0m : ");
  fgets(tarif_24_heures, 11, stdin);
  clear_buffer();

  con = sqlite3_open(DB_FILE, &dbh);
  if(con) {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
    exit(1);
  }
  char Query[500];
  sprintf(Query, "INSERT INTO type_vehicules(id, libelle, nbre_total_place, places_dispo, tarif_heure, tarif_24_heures) VALUES(NULL, '%s', '%s', '%s', '%s', '%s');", trim(libelle), trim(nbre_total_place), trim(nbre_total_place), trim(tarif_heure), trim(tarif_24_heures));
  con = sqlite3_exec(dbh, Query, callback, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  } else {
    fprintf(stdout, "\033[32mLe Type de Véhicule a bien été enregistré !\033[0m\n");
  }
  sqlite3_close(dbh);
}
#endif
