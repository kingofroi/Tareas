#include <stdio.h>
#include <stdlib.h>
#ifdef __WIN32
#include <windows.h>
#endif /* __WIN32 */
#include "osHeader.h"

int main(void){
  //Create task
  printf("Create task");

  createTask(Task1, 1, TaskId_1);
  createTask(Task2, 2, TaskId_2);

  //Start OS
  startOS();

  return 0;
}

void Task1(){
  while(1){
    printf("I am task 1\n");

    //wait
#ifdef __WIN32
    Sleep(1000);//1 sec
#endif /* __WIN32 */
#ifdef __unix__
    sleep(1);//1 sec
#endif /* __unix__ */

    //stop the task
    waitTask();
  }
}

void Task2(){
  static int dummy2=0;
  while(1){
    printf("I am task 2 dummy2=%i\n", dummy2);
    
    //wait
#ifdef __WIN32
    Sleep(1000);//1 sec
#endif /* __WIN32 */
#ifdef __unix__
    sleep(1);//1 sec
#endif /* __unix__ */
    dummy2++;
    //start the task
    startTask(TaskId_1);
  }
}

