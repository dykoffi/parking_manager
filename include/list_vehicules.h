/**
 * @version 1.0
 * @file include/list_vehicules.h
 * @brief Prototypes des fonctions qui affichent la liste des vehicules
 * 
 * Prototypes des fonctions du src/list_vehicules.c
 **/

#include <sqlite3.h>
#include "sqlite3_client.h"
#include "fort.h"

static ft_table_t *table;
static int vehicles_count;

/**
 * Callback exécutée à la requête de comptage des vehicules
 * @fn static int callback_print_vehicles_count(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_print_vehicles_count(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête d'obtention des vehicules
 * @fn static int callback_print_vehicles(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_print_vehicles(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * @fn void list_vehicles()
 * @brief Affiche la liste des vehicules
 * @param void
 * @return void
 **/
void list_vehicles();