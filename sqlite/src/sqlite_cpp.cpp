#include "../h/sqlite_cpp.h"
#include <stdio.h>
#include <string.h>

sqlite_cpp::sqlite_cpp( char *base ){
	zErrMsg = 0;
	rc = 0;
	printf("\n%s\n",base);
	rc = sqlite3_open(base, &db);
	if( rc ){
		fprintf(stderr, "No puedo abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}

}

int sqlite_cpp::noReg = 0;
char sqlite_cpp::voto[35];

void sqlite_cpp::cerrar_db( ){
	sqlite3_close(db);
}

int sqlite_cpp::callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	
	for(i=0; i<argc; i++){
		printf("%s='%s', ", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	noReg++;
	return 0;
}
int sqlite_cpp::get_voto(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	strcat( voto, argv[2] ? argv[2] : "NULL" );
	return 0;
}

int sqlite_cpp::consultar_voto( char *curp, char *tel, char *res){
	strcpy(voto,"");
	char cmd[65];
	sprintf(cmd, "SELECT * FROM voto WHERE curp='%s' AND tel='%s';", curp, tel);
	rc = sqlite3_exec(db, cmd, get_voto, 0, &zErrMsg);
	if( strcmp( voto, "") == 0 )
		return 1;
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error en la consulta SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	printf("VOTO: %s\n", voto);
	memcpy(res, voto, 3);
	strcpy(voto,"");
	return 0;
}
int sqlite_cpp::consultar_registros(){
	rc = sqlite3_exec(db, "select * from voto;", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error en la consulta SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	int registros = noReg;
	noReg = 0;
	return registros;
}

int sqlite_cpp::consulta_partido( char *partido ){
	char cmd[40];
	sprintf(cmd, "SELECT * FROM voto WHERE PARTIDO = '%s';", partido);
	rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error en la consulta SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	int registros = noReg;
	noReg = 0;
	return registros;
}

int sqlite_cpp::add_voto( char *curp, char *num, char *partido ){
	char cmd[67];
	sprintf(cmd, "INSERT INTO voto VALUES ('%s','%s','%s');", curp, num, partido);
	rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error en la consulta SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	return 0;
}

int sqlite_cpp::ini_transaccion( ){
	rc = sqlite3_exec(db, "BEGIN;", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error al iniciar transaccion SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	return 0;
}

int sqlite_cpp::fin_transaccion( ){
	rc = sqlite3_exec(db, "COMMIT;", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Error al finalizar transaccion SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	return 0;
}

int sqlite_cpp::can_transaccion( ){
	rc = sqlite3_exec(db, "ROLLBACK;", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Erro al cancelar transaccion SQL: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	return 0;
}

int sqlite_cpp::getRC( ){
	return rc;
}
