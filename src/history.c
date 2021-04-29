#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "../include/fort.h"
#include "../include/sqlite3_client.h"
#include "../include/history.h"

#ifndef _HISTORY_
#define _HISTORY_

static ft_table_t *table;
static int vehicles_count = 0;

char hparking_code[20];
unsigned int hvehicle_id;
char hdate_arrivee[30];
char hdate_sortie[30];
unsigned int hvehicle_count;
unsigned int hparking_fees;
char hmatricule[15];
char hclient[160];
char hlibelle_type[100];
unsigned int htarif_heure;
unsigned int htarif_24;
unsigned int hduree;

static int callback_print_vehicles_count_h(void *NotUsed, int argc, char **argv, char **azColName) {
  vehicles_count = atoi(argv[0]);
  if(vehicles_count > 0) {
    table = ft_create_table();
    /* Change border style */
    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "CODE", "MATRICULE", "TYPE", "CLIENT", "ARRIVEE", "SORTIE", "TOTAL FACTURE");
  } else {
    printf("\033[1m Il n'y a rien à afficher.\033[0m\n");
  }
  return 0;
}

static int callback_print_vehicles_h(void *NotUsed, int argc, char **argv, char **azColName) {
//   s.id_vehicule 0, s.date_arrivee 1, s.date_sortie 2, duree 3, v.matricule 4, 
// v.id_type_vehicule 5, v.client 6 , tv.libelle 7, tv.tarif_heure 8, tv.tarif_24_heures 9
// "CODE", "MATRICULE", "TYPE", "CLIENT", "ARRIVEE", "SORTIE", "TOTAL FACTURE"
  strcpy(hdate_arrivee, argv[1]);
  strcpy(hdate_sortie, argv[2]);
  hduree = atoi(argv[3]);
  strcpy(hmatricule, argv[4]);
  strcpy(hclient, argv[6]);
  strcpy(hlibelle_type, argv[7]);
  htarif_heure = atoi(argv[8]);
  htarif_24 = atoi(argv[9]);
  
  if(!hduree && (strcmp(hdate_arrivee, hdate_sortie) != 0)) hduree = 1;
  hparking_fees = ((int)(hduree / 24)) * htarif_24 + ((int)(hduree % 24)) * htarif_heure;

  ft_u8printf_ln(table, "P%s-%s|%s|%s|%s|%s|%s|%c FCFA", argv[5], argv[0], argv[4], argv[7], argv[6], argv[1], argv[2], hparking_fees);
  return 0;
}

void history() {
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;
  con = sqlite3_open(DB_FILE, &dbh);
  if(con) {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
    exit(1);
  }
  char* Query_0 = "SELECT COUNT(*) AS nb FROM stationnements WHERE etat='out';";
  con = sqlite3_exec(dbh, Query_0, callback_print_vehicles_count_h, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }
  char* Query = "SELECT s.id_vehicule, s.date_arrivee, s.date_sortie, CAST((JULIANDAY(s.date_sortie) - JULIANDAY(s.date_arrivee)) * 24 AS INTEGER) as duree, v.matricule, v.id_type_vehicule, v.client, tv.libelle, tv.tarif_heure, tv.tarif_24_heures FROM stationnements s LEFT JOIN vehicules v ON s.id_vehicule=v.id JOIN type_vehicules tv ON v.id_type_vehicule=tv.id WHERE s.etat='out';";
  con = sqlite3_exec(dbh, Query, callback_print_vehicles_h, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }
  if(vehicles_count > 0) {
    ft_set_cell_prop(table, FT_ANY_ROW, 7, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
  }
  sqlite3_close(dbh);
}

#endif
