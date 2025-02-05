#include<stdio.h>
#include<string.h>
int verifyaccount(long long int acc_num, const char *passwd);

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
    while(fgets(line,sizeof(line),file)){
        if(sscanf(line,"%lld,%s,%d,%d,%d,%s",&acc_no,&name,&DOB,&adhaar,&phno,&pass)>6){
            if(acc_no==acc_num){
                if((strcmp(pass,passwd))){
                    
                    return 0; // Account or password did match
                }
                else{
                    
                    return 1; // Account or password didn't match
                }
            }
        }
    }

    fclose(file);
    // Account or password didn't match
}

int main()
{
	long long int acc;
	char pass[256];
	int ch;
	printf("Enter acc number: \n");
	scanf("%lld ",&acc);
	printf("Enter pass: ");
	fgets(pass,256,stdin);
	int a = verifyaccount(acc,pass);
	printf("\n%d",a);
}