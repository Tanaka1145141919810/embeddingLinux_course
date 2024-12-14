#include<stdio.h>
#include<stdlib.h>

#define MAXLEN 1024 //最多读取1024个字节

int main(int argc , char *argv[]){
	FILE *Need_to_read = NULL;
	const char* file_path = "../hello.txt";
	Need_to_read = fopen(file_path, "r");
	if(Need_to_read == NULL){
		printf("读取文件错误，请检查对应的文件路径");
		exit(-1);
	}

	fseek(Need_to_read, 0 , SEEK_END);
	const long file_size = ftell(Need_to_read);
	fseek(Need_to_read,0,SEEK_SET);

	char * content = (char *)malloc(sizeof(char) * (file_size + 1));
	if(content == NULL){
		printf("分配内存失败，请检查自己的计算机");
		exit(-1);
	}
	fread(content , 1 , file_size , Need_to_read);

	content[file_size] = '\0';
	printf("content is %s",content);
	return 0;
	fclose(Need_to_read);

}
