/**
 * @version 1.0
 * @file include/add_type_vehicule.h
 * @brief Prototypes des fonctions d'enregistrements
 * 
 * Prototypes des fonctions du src/add_type_vehicule.c
 **/

#include <sqlite3.h>
#include "sqlite3_client.h"

/**
 * @fn static int callback(void *NotUsed, int argc, char **argv, char **azColName)
 * @brief Callback a exexuter a la requete d'eneregistrement en BDD
 * @param void
 * @return int 0
 * @return int 0
 **/
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * @fn void add_type(void)
 * @brief Enregistre un nouveau type de vehicule en base de donnees
 * @param void
 * @return void
 **/
void add_type(void);