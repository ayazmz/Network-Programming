#include<stdio.h>
#include <dirent.h>
#include<stdlib.h>

int main(){

	char dir_name[20];
	printf("Enter name of directory to be read:\n");
	scanf("%s", dir_name);
	DIR *dir;
	struct dirent *de;

	if((dir=opendir(dir_name))==NULL){
		printf("Cannot open\n");
		exit(1);
	}

	while((de=readdir(dir))!=NULL)
		printf("%s\n", de->d_name);
	closedir(dir);
	return 0;
}
	
