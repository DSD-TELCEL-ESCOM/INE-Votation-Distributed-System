#include <iostream>
#include "../h/sqlite_cpp.h"
using namespace std;

int main(){
	sqlite_cpp *sqlite = new sqlite_cpp("dbs/elecciones.db");
	cout << "Total de registros: " <<  sqlite->consultar_registros() << endl;
	cout << "- - - - -- - - - -- - - - -- - - - - - - - -- - - - - -" << endl;
	cout << "Total votos para JAZ: " << sqlite->consulta_partido("JAZ") << endl;
	cout << "- - - - -- - - - -- - - - -- - - - - - - - -- - - - - -" << endl;
	char aux[40];
	if( sqlite->consultar_voto("a11efdtygvsrfetgfd","1111345367", aux) == 0 )
		cout << "El wachin voto por: " << aux << endl;
	else
		cout << "No hay registro con esa curp y telefono..." << endl;
	sqlite->cerrar_db();
	return 0;
}
