#include <stdio.h>  /*printf()*/
#include <sys/types.h> /*pid_t,pid_t_wait(int *wstatus,int options) */
#include <sys/wait.h> /*pid_t waitpid(pid_t pid,int *wstatus,int options)*/
#include <unistd.h> /*pid_t fork(void),man 2 fork*/

int main(int argc,char *argv[])
{
	pid_t pid;
	int intA;
	if((pid=fork())==0){/*Hijo*/
	printf("Teclea un entero: ");
	scanf("%d",&intA);
//	intA=(intA<0)?-intA:intA;
//	return intA%2; /*1 si impar, 0 si par*/
	return intA;
	}else{/*Padre*/
	waitpid(pid,&intA,WUNTRACED|WCONTINUED);
	if(WIFEXITED(intA)){
		printf("intA=%d\n",intA=WEXITSTATUS(intA));
//		printf("el hijo diceque Ud. tecleo un: ");
		printf("Ud. tecleo un: ");
//		if(intA)
		if(intA%2)
			printf("impar.\n");
		else
			
			printf("par.\n");
		}else{
		printf("WIFEXITED(devolvio false!!!!\n");
		} 
	}
	return 0;
}/*end main()*/
