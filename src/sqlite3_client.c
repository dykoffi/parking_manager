#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <ctype.h>
#include "../include/sqlite3_client.h"

#ifndef _SQLITE3_CLIENT_
#define _SQLITE3_CLIENT_

const char* DB_FILE = "/home/nightwalker/Class/C_Adv/park-man/Database.db";

void clear_buffer() {
  int c;
  // while (1) {
  //   c = getchar();
  //   if (c == '\n')
  //     break;
  // }
}

char *trim(char *str) {
  char *end;
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;
  if(*str == 0)  // All spaces?
  return str;
  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  // Write new null terminator character
  end[1] = '\0';
  return str;
}

sqlite3* connect() {
  sqlite3	*conn;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open(DB_FILE, &conn);

  if(rc) {
    fprintf(stderr, "\033[31mErreur SQLite3 :: \033[1m%s\033[0m\n", sqlite3_errmsg(conn));
    exit(1);
  } else {
    fprintf(stdout, "\033[32m\033[1m[OK] La connexion à la base de données a bien été établie.\033[0m\n");
    return conn;
  }
  sqlite3_close(conn);
}
#endif
