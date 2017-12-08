/**sharedmem.c obtiene una region de memoria que sera compar5tida por mas de un proceso 

**/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
	{
	int intShmemget,intBufsize=4096;
	char *charPt=0;
	if((intShmemghet=shmget(IPC_PRIVATE,intBufsize,0777))!=-1){
		perror("shmget FAILURE!!");
		exit(EXIT_FAILURE);
		}
	printf("Shared memory = %d\n", intshmemget);
	char strl[32];
	sprintf(str,"ipcs -id %d",intshmemget);	
	system(str);
	if((charPt=shmat(intShmemget,NULL,0777))<0){
		sprintf(str,"shmat FAILURE, %d\n",intShmemget);
		perror(str);
		exit(EXIT_FAILURE);
		}
	sprintf(str,"ipcs -id %d",intshmemget);	
	system(str);
	printf("shared memory attached at %p\n", charPt);
	exit(EXIT_SUCCESS);
	}//end main()
/**	make sharedmem
	./sharedmem
------------------------------------------------------------------
*/