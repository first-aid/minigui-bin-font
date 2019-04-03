#include<stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gbk.h"
#include "ascii.h"

#define Log(fmt, ...) \
do { fprintf(stdout, "%s-%s#%s:%d;#"fmt"\n", __DATE__, __TIME__, __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)

int wfoo()
{
	FILE *fd;
	char *fName="gbk.bin";
	
	fd=fopen(fName, "w+");
	if(fd==NULL){
		perror("fopen fail\n");
		return -1;
	}

	fwrite(GBK_font, sizeof(GBK_font), 1, fd);
	
	fclose(fd);
	return 1;
}

int rfoo(const char *name)
{
	int i=0;
	FILE *fd;
	long offset=0;
	unsigned char  GBK_font[16*7614*2]={0};
	
	if(access(name, F_OK)!=0){
		fprintf(stderr, "%s not exist", name);
		return 0;
	}
	
	fd=fopen(name, "r");
	if(fd==NULL){
		perror("fopen fail\n");
		return -1;
	}
	
	#if 0
	fseek(fd, 0, SEEK_END);
	offset = ftell(fd);
	printf("offset:%d\n", offset);
	#else
	
	fread(GBK_font, sizeof(GBK_font), 1, fd);
	for(i=0; i<sizeof(GBK_font); i++){
		if(i!=0 && i%16==0)
			printf("\n");
		printf("0x%02x,", GBK_font[i]);
	}
	printf("\n");
	#endif
	
	fclose(fd);
	return 1;
	
}

int main(const int argc, const char *argv[])
{
	if(argc<2){
		perror("Usage: %s [r/w] (binfile)");
		return 0;
	}
	if(strcmp(argv[1], "w")!=0 && strcmp(argv[1], "r")!=0){
		perror("Usage: %s [r/w] (binfile)");
		return 0;
	}
	
	if(strcmp(argv[1], "w")==0){
		wfoo();
		return 0;
	}
	
	if(strcmp(argv[1], "r")==0 && argc==3){
		rfoo(argv[1]);
	}
	else{
		perror("Usage: %s w (binfile)");
	}
	
	return -1;
}
