#include "try.c"
int main()
{
	long long int acc;
	char pass[256];
	int ch;
	printf("Enter acc number: \t");
	scanf("%lld\n",&acc);
	printf("Enter pass: \b");
	fgets(pass,256,stdin);
	int a = verifyaccount(acc,pass);
	printf("\n%d",a);
}