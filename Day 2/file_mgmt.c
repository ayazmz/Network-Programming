#include<stdio.h>
#include<stdlib.h>

int main(){

	FILE *f1, *f2;
	char fname[100], c;
	printf("Enter filename for reading\n");
	scanf("%s", fname);
	f1 = fopen(fname, "r");

	if(f1 == NULL){
		printf("Cannot open file %s", fname);
		exit(0);
	}

	printf("Filename for writing:\n");
	scanf("%s", fname);
	f2 = fopen(fname, "w");

	if(f2 == NULL){
		printf("Cannot open file %s", fname);
		exit(0);
	}

	c = fgetc(f1);
	while(c != EOF){
		fputc(c, f2);
		c = fgetc(f1);
	}
    
	printf("Contents copied to %s", fname);
	fclose(f1);
	fclose(f2);
	return 0;
}
