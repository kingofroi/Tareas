#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define chsemaph *(intPt+1)
#define fasemaph *(intPt+2)
#define input (char)(intPt+3)

int main(void){
    int intShmid;
    int intShmemget;
    int intBufsize = 4096;
    char *charPt = 0;
    char str[32];
    int *intPt = (int*)charPt;
    pid_t pid;
    if((intShmemget = shmget(IPC_PRIVATE, intBufsize, 0777))==-1){
    	perror("shmget FAILURE!!");
        exit(EXIT_FAILURE);
    }
    intShmid = intShmemget;
    //scanf("%d", &intShmid);
	sprintf(str, "ipcs -m -i %d", intShmid);
    system(str);

    if((charPt = shmat(intShmid, NULL, 0777)) < 0){
        sprintf(str,"shmat FAILURE, %d \n", intShmid);
    	perror(str);
        exit(EXIT_FAILURE);
    }
    sprintf(str, "ipcs -m -i %d", intShmid);
    system(str);
    printf("Shared memory attached at %p \n", charPt);
    intPt = (int*)charPt;
    chsemaph = 1;
    fasemaph = 0;
    *intPt = 0;
    printf("*intPt = %d \n", *intPt);
    pid = fork();
    if(pid == 0){ //Child
        while(str[0] != 's'){
            //*intPt=*intPt+1;
            while(!chsemaph){
                printf("CHILD: Pulse una tecla!!! ");
                scanf(" %c", str);
                if(str[0]=='w'){
                    *intPt = *intPt+1;
                }
                printf("CHILD: After *intPt = %d \n", *intPt);
                fasemaph = 0;
                chsemaph = 1;
            }
        }
    } else { //Father
        while(str[0] != 's'){
            while(!fasemaph){
                printf("FATHER: Pulse una tecla!!! ");
                scanf(" %c", str);
                if(str[0] == 'q'){
                    *intPt = *intPt+1;
                }
                printf("FATHER: *intPt = %d \n", *intPt);
                fasemaph = 1;
                chsemaph = 0;
            }
        }
    }
    exit(EXIT_SUCCESS);
}
