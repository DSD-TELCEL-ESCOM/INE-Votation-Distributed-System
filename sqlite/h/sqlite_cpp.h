#include "../sqlite-3.2.2/sqlite3.h"

class sqlite_cpp{
	public:
		sqlite_cpp( char *base );
		void cerrar_db( void );
		int consultar_registros( void );
		int consultar_voto( char *curp, char *tel, char *res );
		int consulta_partido( char *partido );
		int add_voto( char *curp, char *num, char *partido );
		int ini_transaccion( void );
		int fin_transaccion( void );
		int can_transaccion( void );
		int getRC( void );
		static int callback(void *NotUsed, int argc, char **argv, char **azColName);
		static int get_voto(void *NotUsed, int argc, char **argv, char **azColName);
	private:
		sqlite3 *db;
		char *zErrMsg;
		int rc;
		static int noReg;
		static char voto[];
};
