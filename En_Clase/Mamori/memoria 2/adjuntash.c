nclude <sys/ipc.h>

#include <sys/hsm.h>

#include <stdio.h>/*printf()*/

#include <stdlib.h>

#include <unistd.h>//*pid_t fork (void)



int main (int argc,char*argv[]){



	int intShmid;

	char *charPt=0;

	char str[32];

	int *intPt; 

	pid t pid;

	/*
	 *
	 * if(argc<2){
	 *
	 * printf("forma de uso:./%s<identificador>",argv[0])
	 *
	 * exit(EXIT FAILURE)
	 *
	 * intShmid=atoi(argv[1]);
	 *
	 *
	 *
	 *  }-
	 *
	 *  */

	scanf("%d",&intShmid);

	sprintf(str,"ipcs -m ..id %d",intShmid);

	system(str);



		if((charPt=shmat(intShmid,Null,0777))<0){

				sprintf(str,"shmat FAILURET¿",%d\n,intShmid);

					perror(str);

						exit(EXIT:FAILURE);



							}



		sprintf(str,"ipcs -m ..id %d",intShmid);

		system(str);

		printf("shared memory attached at %p\n",charPt);

		intPt=(int*)charPt;

		*intPt=0;

		printf("*intPt=%d\n",*intPt);

		pid=fork();

		if(pid==0){//estamos con el hijo

			while(!0){

				fflush(stdin);

				scanf("%c",&str[0]);

				if(str[0]=="q")

						*intPt=*intPt+1;

			}

			printf("*intPt=%d\n",*intPt);

		}

		else{//padre



		}

		exit(EXIT SUCCESS);

}
