/*
 * 管道传输消息
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int pipefd[2]; // 定义管道文件描述符
    pid_t pid;
    char buffer[100];
    const char *message = "Hello from parent process!";
    
    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // 子进程
        close(pipefd[1]); // 关闭写端
        read(pipefd[0], buffer, sizeof(buffer)); // 从管道读取数据
        printf("Child received: %s\n", buffer);
        close(pipefd[0]); // 关闭读端
    } else { // 父进程
        close(pipefd[0]); // 关闭读端
        write(pipefd[1], message, strlen(message) + 1); // 向管道写入数据
        close(pipefd[1]); // 关闭写端
    }

    return 0;
}
void server(int a , int b){
    return;
}
