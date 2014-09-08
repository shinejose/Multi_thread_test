/* File sem.c */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXSTACK 100
int stack[MAXSTACK][2];
int size=0;
sem_t sem;
pthread_mutex_t size_mutex = PTHREAD_MUTEX_INITIALIZER ;
pthread_mutex_t handle_mutex = PTHREAD_MUTEX_INITIALIZER ;
/* 从文件1.dat读取数据，每读一次，信号量加一*/
void *ReadData1(void * ){
    FILE *fp=fopen("1.dat","r");
    while(!feof(fp)){
        pthread_mutex_lock(&size_mutex);
        fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
        printf("ReadData1 %d %d , size=%d \n",stack[size][0],stack[size][1],size);
        sem_post(&sem);
        ++size;
        pthread_mutex_unlock(&size_mutex);
    }
    fclose(fp);
    printf("ReadData1 End\n");
    pthread_exit(NULL);
}

/*从文件2.dat读取数据*/
void *ReadData2(void * ){
    FILE *fp=fopen("2.dat","r");
    while(!feof(fp)){
        pthread_mutex_lock(&size_mutex);
        fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
        printf("ReadData2 %d %d , size=%d \n",stack[size][0],stack[size][1],size);
        sem_post(&sem);
        ++size;
        pthread_mutex_unlock(&size_mutex);
    }
    fclose(fp);
    printf("ReadData2 End\n");
    pthread_exit(NULL);
}
/*阻塞等待缓冲区有数据，读取数据后，释放空间，继续等待*/
void *  HandleData1(void *){
    while(1){
        sem_wait(&sem);
        pthread_mutex_lock(&handle_mutex) ;
        pthread_mutex_lock(&size_mutex);
        printf("size = %d , Plus:%d+%d=%d\n",size,stack[size-1][0],stack[size-1][1],
        stack[size-1][0]+stack[size-1][1]);
        size--;
        pthread_mutex_unlock(&size_mutex);
        pthread_mutex_unlock(&handle_mutex) ;
    }
    
}

void * HandleData2(void * ){
    while(1){
        sem_wait(&sem);
        pthread_mutex_lock(&handle_mutex) ;
        pthread_mutex_lock(&size_mutex);
        printf("size= %d ,Multiply:%d*%d=%d\n",size,stack[size-1][0],stack[size-1][1],
        stack[size-1][0]*stack[size-1][1]);
        size--;
        pthread_mutex_unlock(&size_mutex);
        pthread_mutex_unlock(&handle_mutex) ;
    }
}

int main(void){
    pthread_t t1,t2,t3,t4;
    sem_init(&sem,0,0);
    pthread_create(&t1,NULL,HandleData1,NULL);
    pthread_create(&t2,NULL,HandleData2,NULL);
    pthread_create(&t3,NULL,ReadData1,NULL);
    pthread_create(&t4,NULL,ReadData2,NULL);
    
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    printf("main end\n");
    pthread_cancel(t1);
    pthread_cancel(t2);
    pthread_exit(NULL);
    return 0;
}










