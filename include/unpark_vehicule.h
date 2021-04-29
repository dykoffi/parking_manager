/**
 * @version 1.0
 * @file include/unpark_vehicule.h
 * @brief Prototypes des fonctions de sortie de vehicule
 * 
 * Prototypes des fonctions du src/unpark_vehicule.c
 **/

#include <sqlite3.h>
#include "sqlite3_client.h"

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

/**
 * Callback exécutée à la requête de sortie de vehicules
 * @fn static int callback_unpark(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_unpark(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de comptage de vehicule
 * @fn static int callback_count_vehicle(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_count_vehicle(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de recuperation de vehicule vehicule
 * @fn static int callback_get_parked_vehicle(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_get_parked_vehicle(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Sort un vehicule du parking avec facture
 * @fn void unpark_vehicle(void)
 * @param void
 * @return void
 **/
void unpark_vehicle(void);
