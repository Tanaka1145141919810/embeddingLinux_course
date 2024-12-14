#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define MAXLEN 1024
struct myfile{
	const char * file_path;
	int fd;
	char content[MAXLEN];
};

int main(int argc , char * argv[]){
     const char *f_p = "../hello.txt";
     struct myfile *f = (struct myfile *)malloc(sizeof(struct myfile));
     if(f == NULL){
     	printf("内存分配失败");
	exit(-1);
     }
     f->file_path = f_p;
     f->fd = open(f->file_path , O_RDWR);
     if(f->fd == -1){
	     printf("打开文件失败，请设置合适的文件路径");
	     exit(-1);
     }
     ssize_t n = read(f->fd , f->content , sizeof(f->content));
     if( n == -1){
     	printf("读取文件中的内容失败");
	exit(-1);
     }
     ssize_t n2 = write(STDOUT_FILENO,f->content,n);
     if( n2 == -1){
     	printf("写入文件到标准输出失败");
	exit(-1);
     }
     close(f->fd);
     free(f);
     return 0;
}
