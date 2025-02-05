#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "pages.h"
#include "menus.h"

long long generateUniqueId();
int addaccount();
int verifyaccount(long long int acc_num, const char *passwd);
void removeNewline(char *str);
void file();
void clrscr();

typedef struct{
	long long acc_num;
	char name[50];
	long long aadhar_no;
	char DOB[11];
	long long mob_no;
	char passwd[100];
	}Account;

#define MAX_LINE_LENGTH 256
#define MAX_LENGTH 100

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
long long generateUniqueId() {
    srand(time(NULL));  

    long long newId;
    int exists;

    do {
        newId = (rand() % 9000000000LL) + 1000000000LL;  // Generate a 10-digit ID
        exists = 0;

        FILE *file = fopen("Signup.csv", "r");
        if (file == NULL) {
            perror("Error opening file");
            break;  // If file doesn't exist, consider ID unique
        }

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            long long fileId;
            sscanf(line, "%lld", &fileId);  // Read the ID from the line
            if (fileId == newId) {
                exists = 1;  // ID exists
                break;
            }
        }

        fclose(file);
        if (exists) {
            generateUniqueId();
        }
    } while (exists);

    return newId;
}


int addaccount()
{
	FILE *file;
	file=fopen("Signup.csv","a");

	if(file == NULL){
		printf("Error: Couldn't open the file");
		return 0;
	}

	Account customer;
	printf("Name: \n");
	scanf("%s",&customer.name);

	

	printf("Aadhar number: \n");
	scanf("%lld",&customer.aadhar_no);

	printf("Date of Birth[yyyy-mm-dd]: ");
	scanf("%s",customer.DOB);

	printf("Mobile number: ");
	scanf("%lld",&customer.mob_no);	
	getchar();

	printf("Password: ");
	fgets(customer.passwd,sizeof(customer.passwd),stdin);
	removeNewline(customer.passwd);
	
	customer.acc_num=generateUniqueId();
	//printf("%lld,%s,%s,%lld,%lld,%s\n",customer.acc_num,customer.name,customer.DOB,customer.aadhar_no,customer.mob_no,customer.passwd);
	fprintf(file,"%lld,%s,%s,%lld,%lld,%s\n",customer.acc_num,customer.name,customer.DOB,customer.aadhar_no,customer.mob_no,customer.passwd);

	fclose(file);
	return 1;

}




int verifyaccount(long long acc_num, const char *passwd) {
    FILE *file;
    file = fopen("Signup.csv", "r");  // Open the file in read mode

    if (file == NULL) {
        printf("Error: Couldn't open the file\n");
        return 0;
    }

    char line[256];
    // Skip the header line
    //fgets(line, sizeof(line), file);

    long long acc_no;
    char name[256],pass[256];
    int DOB,adhaar,phno;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Corrected sscanf format
        if (sscanf(line, "%lld,%255[^,],%d,%d,%d,%255s", &acc_no, name, &DOB, &adhaar, &phno, pass) == 6) {
            if (acc_no == acc_num) {
                fclose(file);  // Ensure file is closed before returning
                if (strcmp(pass, passwd) == 0) {
                    return 1;  // Account and password match
                }
                return 0;  // Password does not match
            }
        }
    }
    return 0;

    fclose(file);
    // Account or password didn't match
}


void clear_screen() {
    system("clear");
}
#endif