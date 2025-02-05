#include "temp.h"

typedef struct{
    char name[50];
    long long aadhar_no;
    char DOB[8];
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

        FILE *file = fopen("Signup.csv", "w+");
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


int signup()
{
    FILE *file;
    file=fopen("Signup.csv","w");

    if(file == NULL){
        printf("Error: Couldn't open the file");
        return 0;
    }

    Account customer;

    printf("Name: ");
    fgets(customer.name,sizeof(customer.name),stdin);
    removeNewline(customer.name);
    

    printf("Aadhar number: ");
    scanf("%lld",&customer.aadhar_no);

    printf("Date of Birth[yyyy-mm-dd]: ");
    scanf("%s",customer.DOB);

    printf("Mobile number: ");
    scanf("%lld",&customer.mob_no);

    printf("Password: ");
    fgets(customer.passwd,sizeof(customer.passwd),stdin);
    removeNewline(customer.passwd);
    
    long long acc_num=generateUniqueId();


    fprintf(file,"%lld,%s,%lld,%s\n",acc_num,customer.name,customer.aadhar_no,customer.mob_no,customer.passwd);


    return 1;

}