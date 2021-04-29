#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "../include/sqlite3_client.h"
#include "../include/add_vehicule.h"

#ifndef _ADD_VEHICULE_
#define _ADD_VEHICULE_

int count_types = 0;
int last_vehicle_id;
char date_arrivee[21];

int selected_vtype_id, nbre_total_place, places_dispo, mutable;
char selected_vtype_name[160];

static int callback_save_vehicle(void *NotUsed, int argc, char **argv, char **azColName) {
  return 0;
}

static int callback_save_parking(void *NotUsed, int argc, char **argv, char **azColName) {
  return 0;
}

static int callback_list_types(void *NotUsed, int argc, char **argv, char **azColName) {
  // id, libelle, nbre_total_place, places_dispo
  printf("\033[1m\033[34m%s\033[0m. %s\033[0m - Places : %s/%s\n", argv[0], argv[1], argv[3], argv[2]);
  return 0;
}

static int callback_count_types(void *NotUsed, int argc, char **argv, char **azColName) {
  count_types = atoi(argv[0]);
  return 0;
}

static int callback_get_last_vehicle_id(void *NotUsed, int argc, char **argv, char **azColName) {
  last_vehicle_id = atoi(argv[0]);
  return 0;
}

static int callback_get_vtype_state(void *NotUsed, int argc, char **argv, char **azColName) {
  // id, nbre_total_place, places_dispo, mutable
  selected_vtype_id = atoi(argv[0]);
  nbre_total_place = atoi(argv[1]);
  places_dispo = atoi(argv[2]);
  mutable = atoi(argv[3]);
  return 0;
}

static int callback_get_vtype_state_2(void *NotUsed, int argc, char **argv, char **azColName) {
  // id, libelle, nbre_total_place, places_dispo
  selected_vtype_id = atoi(argv[0]);
  strcpy(selected_vtype_name, argv[1]);
  nbre_total_place = atoi(argv[2]);
  places_dispo = atoi(argv[3]);
  return 0;
}


static int _list_types() {
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;

  con = sqlite3_open(DB_FILE, &dbh);
  if(con) {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
    exit(1);
  }
  char* Query = "SELECT COUNT(*) AS nb FROM type_vehicules;";
  con = sqlite3_exec(dbh, Query, callback_count_types, 0, &ErrMsg);
  if( con != SQLITE_OK ){
    fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
    sqlite3_free(ErrMsg);
  }
  if(count_types > 0) {
    char* Query = "SELECT id, libelle, nbre_total_place, places_dispo FROM type_vehicules ORDER BY id ASC;";
    con = sqlite3_exec(dbh, Query, callback_list_types, 0, &ErrMsg);
    if( con != SQLITE_OK ){
      fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
      sqlite3_free(ErrMsg);
    } else {
      return 0;
    }
  } else {
    printf("\033[31mErreur :: Vous devez prédéfinir les Types de Véhicule avant de continuer.\033[0m\n");
  }
  return -1;
}

void add_vehicule() {
  sqlite3 *dbh;
  char *ErrMsg = 0;
  int con;
  char matricule[31];
  char id_type_vehicule[11];
  char client[161];

  printf("Types de Véhicules autorisés : \n");
  if(_list_types() == 0) {
    printf("Entrez le \033[1ml'Identifiant du Type de Véhicule\033[0m : ");
    fgets(id_type_vehicule, 10, stdin);
    clear_buffer();
    printf("Entrez le \033[1mMatricule du Véhicule\033[0m : ");
    fgets(matricule, 31, stdin);
    clear_buffer();
    printf("Entrez le \033[1mNom Complet du Client\033[0m : ");
    fgets(client, 160, stdin);
    clear_buffer();
    printf("Entrez la \033[1mDate d'Arrivée\033[0m (Format: AAAA-MM-JJ HH:min): ");
    fgets(date_arrivee, 20, stdin);
    clear_buffer();

    printf("Date arrivee : %s\n", trim(date_arrivee));

    con = sqlite3_open(DB_FILE, &dbh);
    if(con) {
      fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(dbh));
      exit(1);
    }
    char Query[500];
    sprintf(Query, "INSERT INTO vehicules(id, matricule, id_type_vehicule, client) VALUES(NULL, '%s', '%s', '%s');", trim(matricule), trim(id_type_vehicule), trim(client));
    con = sqlite3_exec(dbh, Query, callback_save_vehicle, 0, &ErrMsg);
    if( con != SQLITE_OK ){
      fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
      sqlite3_free(ErrMsg);
    } else {
      char* Query2 = "SELECT id FROM vehicules ORDER BY id DESC LIMIT 1;";
      con = sqlite3_exec(dbh, Query2, callback_get_last_vehicle_id, 0, &ErrMsg);
      if( con != SQLITE_OK ){
        fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
        sqlite3_free(ErrMsg);
      } else {
        // printf("Last vehicle ID :: %d\n", last_vehicle_id);
        // get v-types attrs
        char Query21[100];
        sprintf(Query21, "SELECT id, nbre_total_place, places_dispo, mutable FROM type_vehicules WHERE id=%s LIMIT 1;", trim(id_type_vehicule));
        con = sqlite3_exec(dbh, Query21, callback_get_vtype_state, 0, &ErrMsg);
        if( con != SQLITE_OK ){
          fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
          sqlite3_free(ErrMsg);
        } else {
          if(places_dispo > 0) {
            char Query3[500];
            sprintf(Query3, "INSERT INTO stationnements(id, id_vehicule, date_arrivee, etat) VALUES(NULL, %d, '%s', 'in');", last_vehicle_id, trim(date_arrivee));
            con = sqlite3_exec(dbh, Query3, callback_save_parking, 0, &ErrMsg);
            if( con != SQLITE_OK ){
              fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
              sqlite3_free(ErrMsg);
            } else {
              char Query211[100];
              sprintf(Query211, "UPDATE type_vehicules SET places_dispo=places_dispo-1 WHERE id=%d LIMIT 1;", selected_vtype_id);
              con = sqlite3_exec(dbh, Query211, callback_save_parking, 0, &ErrMsg);
              if( con != SQLITE_OK ) {
                fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
                sqlite3_free(ErrMsg);
              } else {
                printf("\033[32mLe Véhicule a été enregistré avec succès !\nSon code de Stationnement est \033[1mP%s-%d\033[0m\n", trim(id_type_vehicule), last_vehicle_id);
              }
            }
          } else { // No place left for that type - mutate ?
            printf("Désolé, il n'y a plus de place pour ce type de véhicule.\n");
            if(mutable > 0) {
              sprintf(Query21, "SELECT id, libelle, nbre_total_place, places_dispo FROM type_vehicules WHERE id=%d LIMIT 1;", mutable);
              con = sqlite3_exec(dbh, Query21, callback_get_vtype_state_2, 0, &ErrMsg);
              if( con != SQLITE_OK ){
                fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
                sqlite3_free(ErrMsg);
              } else {
                if(places_dispo > 0) {
                  printf("Cependant, il y a une place disponible en tant que '%s'.\n", selected_vtype_name);
                  printf("Voulez-vous l'occuper ? O/N ");
                  char c, confirm;
                  scanf("%s", &confirm);
                  while (1) {
                    c = getchar();
                    if (c == '\n')
                      break;
                  }
                  if(confirm == 'O' || confirm == 'o') {
                    char Query35[500];
                    printf("Date arrivee : %s\n", trim(date_arrivee));
                    sprintf(Query35, "INSERT INTO stationnements(id, id_vehicule, date_arrivee, etat) VALUES(NULL, %d, '%s', 'in');", last_vehicle_id, trim(date_arrivee));
                    con = sqlite3_exec(dbh, Query35, callback_save_parking, 0, &ErrMsg);
                    if( con != SQLITE_OK ){
                      fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
                      sqlite3_free(ErrMsg);
                    } else {
                      char Query2111[100];
                      sprintf(Query2111, "UPDATE type_vehicules SET places_dispo=places_dispo-1 WHERE id=%d LIMIT 1;", selected_vtype_id);
                      con = sqlite3_exec(dbh, Query2111, callback_save_parking, 0, &ErrMsg);
                      if( con != SQLITE_OK ) {
                        fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
                        sqlite3_free(ErrMsg);
                      }
                      char Query2112[100];
                      sprintf(Query2112, "UPDATE vehicules SET id_type_vehicule=%d WHERE id=%d LIMIT 1;", selected_vtype_id, last_vehicle_id);
                      con = sqlite3_exec(dbh, Query2112, callback_save_parking, 0, &ErrMsg);
                      if( con != SQLITE_OK ) {
                        fprintf(stderr, "\033[31mErreur SQL :: \033[1m%s\033[0m\n", ErrMsg);
                        sqlite3_free(ErrMsg);
                      } else {
                        printf("\033[32mLe Véhicule a été enregistré avec succès !\nSon code de Stationnement est \033[1mP%s-%d\033[0m\n", trim(id_type_vehicule), last_vehicle_id);
                      }
                    }
                  } else {
                    printf("Passez une bonne journée !\n");
                  }
                } // end no place in mutable
              }
            } //end no place in first vtype
          }
        }
        
      }
      // printf("\033[32mLe Véhicule a été enregistré avec succès !\nSon code de Stationnement est \033[1mP%s-%d\033[0m\n", trim(id_type_vehicule), last_vehicle_id);
    }
  }
  sqlite3_close(dbh);
}
#endif
