#include <stdio.h>
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	
	int i;
	
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main(int argc, char **argv){
	
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	
	if( argc!=3 ){
		fprintf(stderr, "Usar: %s BASE_DE_DATOS INSTRUCCION-SQL\n", argv[0]);
		return(1);
	}
	
	rc = sqlite3_open(argv[1], &db);
	
	if( rc ){
		fprintf(stderr, "No puedo abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
	
	rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
	
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error en la consulta SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	sqlite3_close(db);
	return 0;
}
