#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024  // 共享内存的大小

int main() {
    key_t key;
    int shmid;
    char *data;

    // 创建共享内存的键
    key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 创建共享内存
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子进程：写入共享内存
        data = (char *)shmat(shmid, (void *)0, 0);
        if (data == (char *)(-1)) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        printf("[Child] Writing to shared memory...\n");
        strcpy(data, "Hello from child process!");
        shmdt(data);  // 断开共享内存
        exit(0);
    } else {
        // 父进程：读取共享内存
        wait(NULL);  // 等待子进程完成

        data = (char *)shmat(shmid, (void *)0, 0);
        if (data == (char *)(-1)) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        printf("[Parent] Reading from shared memory: %s\n", data);
        shmdt(data);  // 断开共享内存

        // 删除共享内存
        shmctl(shmid, IPC_RMID, NULL);
        printf("[Parent] Shared memory deleted.\n");
    }

    return 0;
}
