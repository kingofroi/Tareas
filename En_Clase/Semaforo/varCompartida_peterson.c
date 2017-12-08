#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define N 2

/*Variables de Peterson*/
int turn;
int interested[N];


void enter_region(int process);
void leave_region(int process);

int main(void){

    int intShmemget;
    int intShmid;

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
    *intPt = 0;
    printf("*intPt = %d \n", *intPt);
    pid = fork();

    if(pid==0){ // child
        enter_region(0);
            printf("CHILD: Pulse una tecla!!! ");
        leave_region(0);

        enter_region(0);
            scanf(" %c", str);
        leave_region(0);

        if(str[0]=='w'){
            *intPt = *intPt+1;
        }

        enter_region(0);
            printf("CHILD: After *intPt = %d \n", *intPt);
        leave_region(0);

    } else { // father
        enter_region(1);
            printf("FATHER: Pulse una tecla!!! ");
        leave_region(1);

        enter_region(1);
            scanf(" %c", str);
        //sleep(30);
        leave_region(1);

        if(str[0]=='q'){
            *intPt = *intPt+1;
        }

        enter_region(1);
            printf("FATHER: After *intPt = %d \n", *intPt);
        leave_region(1);
    }

    exit(EXIT_SUCCESS);
}

void enter_region(int process){
    int other;

    other = 1- process;
    printf("%d \n",other);
    interested[process] = TRUE;
    turn = process;
    while(turn == process && interested[other] == TRUE);
}

void leave_region(int process){
    interested[process] = FALSE;
}
