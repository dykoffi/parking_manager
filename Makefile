.SILENT: app main add_type_vehicule add_vehicule fort list_types list_vehicules sqlite3_client unpark_vehicule history

app: main add_type_vehicule add_vehicule fort list_types list_vehicules sqlite3_client unpark_vehicule history
	gcc -o app "./tests/main.o" "./tests/add_type_vehicule.o" "./tests/add_vehicule.o" "./tests/fort.o" "./tests/list_types.o" "./tests/list_vehicules.o" "./tests/sqlite3_client.o" "./tests/unpark_vehicule.o" "./tests/history.o" -lsqlite3 -lm;\
	rm ./tests/*.o;\
	echo "Terminé !"

sqlite3_client:
	gcc -o "./tests/sqlite3_client.o" -c "./src/sqlite3_client.c" -lsqlite3

add_type_vehicule:
	gcc -o "./tests/add_type_vehicule.o" -c "./src/add_type_vehicule.c" -lsqlite3

add_vehicule:
	gcc -o "./tests/add_vehicule.o" -c "./src/add_vehicule.c" -lsqlite3

fort:
	gcc -o "./tests/fort.o" -c "./src/fort.c" -lsqlite3

list_types:
	gcc -o "./tests/list_types.o" -c "./src/list_types.c" -lsqlite3

list_vehicules:
	gcc -o "./tests/list_vehicules.o" -c "./src/list_vehicules.c" -lsqlite3

unpark_vehicule:
	gcc -o "./tests/unpark_vehicule.o" -c "./src/unpark_vehicule.c" -lsqlite3

history:
	gcc -o "./tests/history.o" -c "./src/history.c" -lsqlite3
main:
	(ls "./tests/main.o" >> /dev/null 2>&1 && rm ./tests/*.o) || echo "Compilation en cours..."
	gcc -o "./tests/main.o" -c "./src/main.c" -lsqlite3
