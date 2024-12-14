#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    sem_t sem; // 定义信号量
    pid_t pid;

    // 初始化信号量，初始值为1
    if (sem_init(&sem, 1, 1) == -1) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子进程
        for (int i = 0; i < 5; i++) {
            sem_wait(&sem); // 等待信号量
            printf("[Child] Working... (Step %d)\n", i + 1);
            sleep(1); // 模拟工作
            sem_post(&sem); // 释放信号量
            sleep(1);
        }
        exit(0);
    } else {
        // 父进程
        for (int i = 0; i < 5; i++) {
            sem_wait(&sem); // 等待信号量
            printf("[Parent] Working... (Step %d)\n", i + 1);
            sleep(1); // 模拟工作
            sem_post(&sem); // 释放信号量
            sleep(1);
        }

        // 等待子进程完成
        wait(NULL);

        // 销毁信号量
        sem_destroy(&sem);

        printf("Both processes have completed.\n");
    }

    return 0;
}