/**
 * @version 1.0
 * @file include/history.h
 * @brief Prototypes des fonctions d'affichage d'historique
 * 
 * Prototypes des fonctions du src/history.c
 **/
#include <stdlib.h>
#include "fort.h"
#include <sqlite3.h>

static ft_table_t *table;
static int vehicles_count;

// variables
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

/**
 * Callback exécutée à la requête de comptage des vehicules
 * @fn static int callback_print_vehicles_count_h(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_print_vehicles_count_h(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de recuperation d'un vehicule
 * @fn static int callback_print_vehicles_h(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_print_vehicles_h(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Recuperer et affiche l'historique des vehicules qui sont sortis du parking
 * @fn void history();
 * @param void
 * @return void
 **/
void history();
