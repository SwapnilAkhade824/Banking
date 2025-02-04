#include "Admin.h"

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
	file=fopen("Signup.csv","w");

	if(file == NULL){
		printf("Error: Couldn't open the file");
		return 0;
	}

	Account customer;
	fprintf(file,"Acc_no,Name,DOB,Aadhar_no,Mobile_no,Password\n");
	printf("Name: ");
	fgets(customer.name,sizeof(customer.name),stdin);
	removeNewline(customer.name);
	

	printf("Aadhar number: ");
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


int verifyaccount()
{
	FILE *file;
	file=fopen("Signup.csv","r");
	if(file == NULL){
		printf("Error: Couldn't open the file");
		return 0;
	}
	long long acc_num;
	char line[256],passwd[100];
    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
       char *token = strtok(line, ","); 
        if (token == NULL) continue;
        long long file_acc_num = atoll(token); 

        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ","); 
        token = strtok(NULL, ","); 
        token = strtok(NULL, "\n"); 

        if (token == NULL) continue; 
        if (file_acc_num == acc_num && strcmp(token, passwd) == 0) {
            fclose(file);
            return 1;      
        }
  
	



}
}