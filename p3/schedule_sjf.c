//Can Tosun
//CSS 430 P3

#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "cpu.h"
#include "list.h"
#include "schedulers.h"

struct node *head = NULL;

Task* pickNextTask()
{
    //if the list is empty, return
    if(!head)
        return NULL;

    //create a new node and new task
    struct node *newNode;
    Task *newTask = head->task;
    newNode = head->next;

    /*
    sjf shortest job first, thus burst time is
    important in this case.
    */
    while(newNode != NULL)
    {
        //lowest burst first
        if(newNode->task->burst < newTask->burst)
            newTask = newNode->task;

        newNode = newNode->next;
    }

    //after add to the list, delete the task
    delete(&head, newTask);

    return newTask;

}



void schedule()
{
    Task* newTask; //create a task
    reverseList(&head);

    while(head != NULL) //go until the end of the list
    {
        newTask = pickNextTask();  // choose next task
        run(newTask, newTask->burst); // print out
    }

    printf("Done\n");
}


void add(char* name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task)); //create new task

    //initilization
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    //insertion
    insert(&head, newTask);     
}