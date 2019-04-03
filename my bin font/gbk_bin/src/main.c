#include "head.h"

/**************************************************************************
* 函数名：CombinationSave
* 函数功能：合并文件
* 参数：fd_bin 点阵16进制文件，fd_c所有字符文件【单行】， fd_out 保存文件
* 返回值：成功返回0， 失败返回-1
**************************************************************************/
int CombinationSave(FILE *fd_bin, FILE *fd_c, FILE *fd_out)
{
	int binLineLen=0;
	int bufbinlen=0;
	char bufbin[128];
	
	int cpos=0;
	unsigned char *pbuf=NULL, *poutbuf=NULL;
	int pbuflen=0, poutbuflen=0;
	unsigned long offset=0;
	
	int outbuflen=0;
	char outbuf[128];
	
	/*注：char.txt 文件以utf-8保存*/
	int wordlen=0;
	char word[4];
	int count=0;
	int utf8wordlen=0;
	char utf8word[8];
	int tmp_wordlen=0;
	
	int ret=0;
	/*==============init=====start============*/
	bufbinlen=sizeof(bufbin);
	memset(bufbin, 0, bufbinlen);
	fseek(fd_bin, 0, SEEK_SET);
	fgets(bufbin, bufbinlen, fd_bin);
	binLineLen=strlen(bufbin);
	memset(bufbin, 0, bufbinlen);
	
	fseek(fd_c, 0, SEEK_END);
	offset=ftell(fd_c);
#if 1	
	printf("offset:%d\n", offset);
#endif

	poutbuflen=offset<<1;
	poutbuf=(unsigned char *)malloc(poutbuflen);
	if(poutbuf==NULL){
		perror("malloc fial");
		return -1;
	}
	memset(poutbuf, 0, poutbuflen);
	
	pbuflen=offset+2;
	pbuf=(unsigned char *)malloc(pbuflen);
	if(pbuf==NULL){
		perror("malloc fial");
		return -1;
	}
	memset(pbuf, 0, pbuflen);
	
	outbuflen=sizeof(outbuf);
	memset(outbuf, 0, outbuflen);
	
	wordlen=sizeof(word);
	memset(word, 0, wordlen);
	utf8wordlen=sizeof(utf8word);
	memset(utf8word, 0, utf8wordlen);
	
	fseek(fd_bin, 0, SEEK_SET);
	fseek(fd_c, 0, SEEK_SET);
	fseek(fd_out, 0, SEEK_SET);
	/*==============init=====end============*/
	
	/*============get all char==start=======*/
	fgets(pbuf, pbuflen, fd_c);
	code_convert(UTF8_STR, GBK_STR, pbuf, pbuflen, poutbuf, poutbuflen);
#if 0
	printf("pbuf %d:%s\n", strlen(pbuf), pbuf);
#endif
	/*============get all char==end=========*/

	
	/*==========combination===start=========*/
	cpos=0;
	while(fgets(bufbin, bufbinlen, fd_bin)){
		/*first line no number*/
		fprintf(fd_out, "%s", bufbin);
		memset(bufbin, 0, bufbinlen);
		
		/*second line have number*/
		fgets(bufbin, bufbinlen, fd_bin);
		
		#if 0
		printf("poutbuf[%d]:%d##", cpos, poutbuf[cpos]);
		#endif
		if(poutbuf[cpos]>128){
			memcpy(word, poutbuf+cpos, 2);
			cpos+=2;
			word[2]='\0';
			tmp_wordlen=2;
		}
		else{
			memcpy(word, poutbuf+cpos, 1);
			cpos++;
			word[1]='\0';
			tmp_wordlen=1;
		}
		
		count++;
		memcpy(outbuf, bufbin, binLineLen);
		
		/*save data convert to UTF-8*/
		code_convert(GBK_STR, UTF8_STR, word, tmp_wordlen, utf8word, utf8wordlen);
		#if 0
		printf("tmp_wordlen:%d; utf8word len:%d:%s\n",tmp_wordlen, strlen(utf8word), utf8word);
		#endif
		
		snprintf(outbuf+binLineLen, outbuflen-binLineLen, " \"%s\", %d*/", utf8word, count);
		fprintf(fd_out, "%s\n", outbuf);
		
		memset(word, 0, wordlen);
		memset(utf8word, 0, utf8wordlen);
		memset(outbuf, 0, outbuflen);
		memset(bufbin, 0, bufbinlen);
	}
	/*==========combination===end=========*/
	
	free(pbuf);
	free(poutbuf);
}

int main(const int argc, const char *argv[])
{
	int i=0;
	FILE *fd_bin, *fd_c, *fd_out;
	
	if(argc!=4){
		perror("Usage: %s bin char outName");
		return 0;
	}
	
	fd_bin=fopen(argv[1], "r");
	if(fd_bin==NULL){
		fprintf(stderr, "fopen fail: %s\n", argv[1]);
		return -1;
	}
	
	fd_c=fopen(argv[2], "r");
	if(fd_c==NULL){
		fprintf(stderr, "fopen fail: %s\n", argv[2]);
		return -1;
	}
	
	fd_out=fopen(argv[3], "w");
	if(fd_out==NULL){
		fprintf(stderr, "fopen fail: %s\n", argv[3]);
		return -1;
	}
	
	CombinationSave(fd_bin, fd_c, fd_out);
	
	fclose(fd_bin);
	fclose(fd_c);
	fclose(fd_out);
	
	return -1;
}