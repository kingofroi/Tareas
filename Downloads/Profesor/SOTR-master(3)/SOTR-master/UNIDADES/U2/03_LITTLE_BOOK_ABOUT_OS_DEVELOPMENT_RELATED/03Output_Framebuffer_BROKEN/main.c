/*  main.c  - main */

/*#include <xinu.h>*/
#include "kernel.h"
#include "conf.h"
#include <math.h>

#include "prototypes.h"

process	main(void)
{   
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
