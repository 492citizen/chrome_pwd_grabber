#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>

// *** F U N C T I O N   P R O T O T Y P E S ***
char check_file_exists(char *file_path);

// *** D B   P A T H S ***
char db_path_chromium[] = "/home/me/.config/chromium/Default/Login Data";
char db_path_chrome[] = "/home/me/.config/google-chrome/Default/Login Data";

char *get_user_stmt = "SELECT username_value FROM logins;"; // fetches usernames from logins table
char *get_pass_stmt = "SELECT password_value FROM logins;"; // fetches passwords from logins table

FILE *out_file;

static int user_callback(void *NotUsed, int argc, char **argv, char **azColName){
	for(int i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

static int pass_callback(void *NotUsed, int argc, char **argv, char **azColName){
	for(int i = 0; i<argc; i++){
		printf("Undecoded: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;

}

int main(void){

	char *zErrMsg = 0;

	printf("Checking installed browsers...\n");
	if(check_file_exists(&db_path_chromium)){
		printf("Chromium is installed\n");
	}
	if(check_file_exists(&db_path_chrome)){
		printf("Chrome is installed\n");
	}

	// create db handle
	sqlite3 *db_chromium;

	// make sql statement
	sqlite3_stmt *res;

	int status = sqlite3_open(db_path_chromium, &db_chromium);

	if (status != SQLITE_OK){
		printf("Error opening database\n");
	}
	else{
		printf("Database successfully opened\n");
	}

	printf("SQL open status: %i\n", status);


	// compile a SQL statement and put it in 4th parameter
	status = sqlite3_exec(db_chromium, get_user_stmt, user_callback, 0, &zErrMsg);
	status = sqlite3_exec(db_chromium, get_pass_stmt, pass_callback, 0, &zErrMsg);

	printf("SQL statement status: %i\n", status);

	return 0;

}

/*
 *Get database path (for chrome / chromium / brave)
 */
char check_file_exists(char *file_path){
	FILE *file;
	if (file = fopen(file_path, "r")){ // file exists
		fclose(file);
		return 1;
	}
	// file doesn't exist
	return 0;
}
