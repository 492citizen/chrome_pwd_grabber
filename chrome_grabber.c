#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>


char check_file_exists(char *file_path);

char *db_path_chromium = "/home/me/.config/chromium/Default/Login Data";
char *db_path_chrome = "/home/me/testfile"; //".config/google-chrome/Default/Login Data";


FILE *out_file;

int main(void){
	
	printf("Checking installed browsers...\n");
	if(check_file_exists(db_path_chromium)){
		printf("Chromium is installed\n");
	}
	if(check_file_exists(db_path_chrome)){
		printf("Chrome is installed\n");
	}

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

	return 0;

}

/*
 *Get database path (for chrome / chromium / brave)
 */
char check_file_exists(char *file_path){
	printf("Checking File... ");
	printf("Checking database: %s\n", *file_path);
	FILE *file;
	if (file = fopen(*file_path, "r")){ // file exists
		fclose(file);
		return 1;
	}
	// file doesn't exist
	perror("Error");
	printf("Database does not exist.\n");
	return 0;
}
