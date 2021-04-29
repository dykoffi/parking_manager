#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "../include/fort.h"
#include "../include/sqlite3_client.h"
#include "../include/list_vehicules.h"

#ifndef _LIST_VEHICULES_
#define _LIST_VEHICULES_

static ft_table_t *table;
static int vehicles_count = 0;

static int callback_print_vehicles_count(void *NotUsed, int argc, char **argv, char **azColName) {
  vehicles_count = atoi(argv[0]);
  if(vehicles_count > 0) {
    table = ft_create_table();
    /* Change border style */
    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "ID", "MATRICULE", "TYPE", "CLIENT", "ARRIVEE", "SORTIE");
  } else {
    printf("\033[1m Il n'y a aucun Véhicule pour le moment.\033[0m\n");
  }
  return 0;
}

static int callback_print_vehicles(void *NotUsed, int argc, char **argv, char **azColName) {
  // s.id_vehicule, s.date_arrivee, s.date_sortie, v.matricule, v.id_type_vehicule, v.client, tv.libelle, tv.tarif_heure, tv.tarif_24_heures
  ft_u8printf_ln(table, "%s|%s|%s|%s|%s|%s", argv[0], argv[3], argv[6], argv[5], argv[1], argv[2]);
  return 0;
}

void list_vehicles() {
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;
  con = sqlite3_open(DB_FILE, &dbh);
  if(con) {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
    exit(1);
  }
  char* Query_0 = "SELECT COUNT(*) AS nb FROM stationnements;";
  con = sqlite3_exec(dbh, Query_0, callback_print_vehicles_count, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }
  char* Query = "SELECT s.id_vehicule, s.date_arrivee, s.date_sortie, v.matricule, v.id_type_vehicule, v.client, tv.libelle, tv.tarif_heure, tv.tarif_24_heures FROM stationnements s LEFT JOIN vehicules v ON s.id_vehicule=v.id JOIN type_vehicules tv ON v.id_type_vehicule=tv.id;";
  con = sqlite3_exec(dbh, Query, callback_print_vehicles, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }
  if(vehicles_count > 0) {
    ft_set_cell_prop(table, FT_ANY_ROW, 6, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
  }
  sqlite3_close(dbh);
}

#endif
