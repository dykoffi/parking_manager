/**
 * @version 1.0
 * @file include/sqlite3_client.h 
 * @brief Test de connection et fonctions utiles
 **/

#include <sqlite3.h>

/**
 * @var extern const char* DB_FILE
 * 
 * Le chemin vers le fichier de base de donnees
 **/
extern const char* DB_FILE;

/**
 * @fn void clear_buffer(void)
 * Nettoie le tampon apres un appel `scanf`
 * @param void
 * @return void
 **/
void clear_buffer(void);

/**
 * @fn char *trim(char*)
 * @param str char* 
 * @return char*
 * 
 * Retire les espaces blancs en debut et fin de chaines de caracteres
 * 
 **/
char *trim(char*);

/**
 * @fn sqlite3* connect(void);
 * @param void 
 * @return sqlite3* une instance de connexion SQLite3
 * 
 * Teste la connectivite avec la base de donnees et affiche une alerte sur l'etat
 * 
 **/
sqlite3* connect(void);
