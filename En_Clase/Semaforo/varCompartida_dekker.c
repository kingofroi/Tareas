#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define wants_to_enter[] *(intPt+1)
#define var1 *(intPt+1)
#define var2 *(intPt+2)
#define turn *(intPt+3)

int main(void){
    /*Variables de Dekker*/
    //int var1 = 0;
    //int var2 = 0;
    //int turn = 1;


    int intShmemget;
    int intShmid;

    int intBufsize = 4096;
    char *charPt = 0;
    char str[32];
    int *intPt = (int*)charPt;
    //var1 = 0;
    //var2 = 0;
    //*var1 = 0;
    //*var2 = 0;

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
    *intPt = 0;
    printf("*intPt = %d \n", *intPt);
    pid = fork();
    if(pid == 0){ //Child
        var1 = 1;
        while (var2){
            if(turn!=0){
                var1 = 0;
                while (turn!=0){
                    ;
                }
                var1 = 1;
            }
        }
        //Critical Section
        while(str[0] != 's'){
            //sleep(2);
            printf("CHILD: Pulse una tecla!!! ");
            scanf(" %c", str);
            if(str[0]=='w'){
                *intPt = *intPt+1;
            }
            printf("CHILD: After *intPt = %d \n", *intPt);
        }
        turn = 1;
        var1 = 0;
    } else { //Father
        var2 = 1;
        while (var1==1){
            if(turn!=1){
                //printf("FATHER: Pulse una tecla!!! ");
                var2 = 0;
                while (turn!=1){
                    ;
                }
                var2 = 1;
            }
        }
        while(str[0] != 's'){
            //sleep(2);
            printf("FATHER: Pulse una tecla!!! ");
            scanf(" %c", str);
            if(str[0] == 'q'){
                *intPt = *intPt+1;
            }
            printf("FATHER: *intPt = %d \n", *intPt);
        }
        turn = 0;
        var1 = 0;
    }
    exit(EXIT_SUCCESS);
}
