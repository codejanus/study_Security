/******************************************************************************
*  xcte.c - Extract Chunked Transfer-Encoding from TCP stream files
*
*  Copyright (C) 2010 - Christian North
*
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define version  "v0.2 BETA"

/******************************************************************************/
void usage()
{
	printf("XCTE %s - ",version);
	printf("Extract Chunked Transfer-Encoding from TCP stream files\n");
	printf("Usage: xcte <file>\n");
	exit(0);
}

/******************************************************************************/
int chunked_encoding(FILE *stream)
{
	const char *encoding="Transfer-Encoding: chunked";
	size_t len=1024;
	char data[len];
	long offset=0;
	int bytes=0;
	int c=0;

	while(!feof(stream)){
		if((bytes=fread(data,1,len,stream)) == 0) break;
		for(c=0;c<(bytes-1);c++){
			if(data[c] == 0x0D && data[c+1] == 0x0A){
				data[c]='\0';	
				offset+=strlen(data)+2;
				break;
			}
		}
		if(strstr(data,encoding) != NULL) {
			rewind(stream);
			return 1;
		}
		fseek(stream,offset,SEEK_SET);
	}

	return 0;
}

/******************************************************************************/
FILE *disposition(char *data)
{
	const char *disposition = "Content-Disposition";
	const char *filename = "filename=";
	FILE *fp = NULL;

	if(strstr(data,disposition) != NULL) {
		filename=strtok(data,"=");
		printf("Extracting Content: ");
		printf("%s\n",data+strlen(filename)+1);
		fp=fopen(data+strlen(filename)+1,"a");
		return fp;
	}

	return NULL;
}

/******************************************************************************/
int extract(FILE *stream, FILE *content)
{
	size_t chunk=0;
	size_t len=8;
	char *fragment;
	char data[len];
	char hex[len];

	while(!feof(stream)){
		if(fread(data,1,len,stream) == 0) break;
		snprintf(hex,len,"%c%c%c%c",data[2],data[3],data[4],data[5]);
		chunk=strtoul(hex,NULL,16);
		if((fragment = malloc(chunk)) == NULL) break;
		if(fread(fragment,1,chunk,stream) == 0) break;
		fwrite(fragment,1,chunk,content);
		free(fragment);
	}

	fclose(content);
	return 0;
}

/******************************************************************************/
int main(int argc, char **argv)
{
	char *streamfile=NULL;
	FILE *stream=NULL;
	FILE *content=NULL;
	size_t len=1024;
	char data[len];
	long offset=0;
	int bytes=0;
	int c=0;

	if(argc != 2) usage();
	streamfile = argv[1];
	if((stream = fopen(streamfile,"r")) == NULL) usage();

	if(!chunked_encoding(stream)){
		printf("Transfer-Encoding: chunked - not found in ");
		printf("\"%s\"\n", streamfile);	
		exit(0);
	}

	while(!feof(stream)){
		if((bytes=fread(data,1,len,stream)) == 0) break;
		for(c=0;c<(bytes-1);c++){
			if(data[c] == 0x0D && data[c+1] == 0x0A) {
				data[c]='\0';	
				offset++;
				break;
			}
			offset++;
		}
		content = disposition(data);
		if(content != NULL) break;
		fseek(stream,offset,SEEK_SET);
	}

	offset--;
	fseek(stream,offset,SEEK_SET);

	while(!feof(stream)){
		if((bytes=fread(data,1,len,stream)) == 0) break;
		for(c=0;c<(bytes-4);c++){
			if(data[c]   == 0x0D && data[c+1] == 0x0A &&
			   data[c+2] == 0x0D && data[c+3] == 0x0A ){
				offset+=2; 
				fseek(stream,offset,SEEK_SET);
				extract(stream,content);
				fclose(stream);
				break;
			}
			offset++;
		}
	}

	return 0;
}
/******************************************************************************/
