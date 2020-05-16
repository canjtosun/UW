//Can Tosun
//CSS 430 P3

#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "cpu.h"
#include "list.h"
#include "schedulers.h"

struct node* head = NULL;

void pickNextTask()
{

    //if the list is empty, return
    if(!head)
        return;

    //create a new node and assign to head
    struct node* newNode;
    newNode = head;

    /*
    we need to pick next task fcfs priority
    but after decrement the QUANTUM time
    we need to go next process and delete the task
    until we are run out of burst
    */
    while(newNode != NULL)
    {
        //check if less than or rqual 10
        if(newNode->task->burst <= QUANTUM)
        {
            //print out and delete
            run(newNode->task, newNode->task->burst);
            delete(&head, newNode->task);
        }

        else // if bigger than 10
        {
            //print out and decrement QUANTUM time
            run(newNode->task, QUANTUM);
            newNode->task->burst -= QUANTUM;
        }

        //go thru next task
        newNode = newNode -> next;
    }
}


void schedule()
{
    reverseList(&head); //fcfs reverse list

    while(head != NULL) //go until the end of the list
    {
        pickNextTask();  // choose next task  
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

