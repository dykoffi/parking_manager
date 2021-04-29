/**
 * @version 1.0
 * @file include/add_vehicule.h
 * @brief Prototypes des fonctions d'enregistrements
 * 
 * Prototypes des fonctions du src/add_vehicule.c
 **/

#include <sqlite3.h>
#include "sqlite3_client.h"

int count_types;
int last_vehicle_id;

/**
 * Callback exécutée à la requête d'ajout
 * @fn callback_save_vehicle(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_save_vehicle(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête d'inscription du stationnement
 * @fn static int callback_save_parking(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_save_parking(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de liste des types de vehicule
 * @fn static int callback_list_types(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_list_types(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de comptage des types de vehicule
 * @fn static int callback_count_types(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_count_types(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Callback exécutée à la requête de recuperation du dernier vehicule ajoute
 * @fn static int callback_get_last_vehicle_id(void *NotUsed, int argc, char **argv, char **azColName)
 * @param NotUsed void * 
 * @param int argc 
 * @param argv char**
 * @param azColName char**
 * @return int 0
 **/
static int callback_get_last_vehicle_id(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * Recupere et affiche les types de vehicule predefini
 * @fn static int _list_types()
 * @param void
 * @return void
 **/
static int _list_types(void);

/**
 * Demande et enregistre en BDD les informations d'un nouveau vehicule arrivant
 * @fn static int _list_types()
 * @param void
 * @return void
 **/
void add_vehicule();

