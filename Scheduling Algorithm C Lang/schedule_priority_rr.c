//Can Tosun
//CSS 430 P3

#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "cpu.h"
#include "list.h"
#include "schedulers.h"

struct node* head = NULL;
struct node* extraList = NULL;

/*
Task* pickNextTask()
{
    //if the list is empty, return
    if(!head)
        return NULL;

    //create a new node and new task
    struct node *newNode;
    Task *newTask = head->task;
    newNode = head->next;

    
    //priority is priority field first, thus arrival time is
    //important in this case.
    
    while(newNode != NULL)
    {
        //higher the number, more important
        if(newNode->task->priority > newTask->priority)
            newTask = newNode->task;

        newNode = newNode->next;
    }

    //after add to the list, delete the task
    delete(&head, newTask);

    return newTask;

}


void schedule()
{
    Task* current;

    reverseList(&head);

    while(head != NULL)
    {      
        current = pickNextTask(); 

        while(current->burst >= QUANTUM)
        {
            //current = pickNextTask(); 
            run(current, QUANTUM);
            current->burst -= QUANTUM;

            if(current->burst < QUANTUM && current->burst != 0)
                run(current, current->burst);

        }
        
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
*/


void pickNextTask()
{
    //if the list is empty, return
    if(!extraList)
        return;

    //create a new node
    struct node *newNode;
    newNode = extraList;

    
    //we need to pick next task fcfs priority
    //but after decrement the QUANTUM time
    //we need to go next process and delete the task
    //until we are run out of burst
    
    while(newNode != NULL)
    {
        //check if less than or rqual 10
        if(newNode->task->burst <= QUANTUM)
        {
            //print out and delete
            run(newNode->task, newNode->task->burst);
            delete(&extraList, newNode->task);
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

void extraListMethod()
{
    
    while(head != NULL)
    {
        //create 2 new node and assign to head
        struct node* choose; 
        struct node* current;
        current = head;
        choose = head;

        //go thru the list
        while(current != NULL)
        {
            //choose higher priority
            if(current->task->priority < choose->task->priority)
                choose = current;

            current = current->next;
        }

        //insert to the other list and delete from list
        insert(&extraList, choose->task);
        //delete(&head, choose->task);

    }

}


void schedule()
{
    extraListMethod(); //call extralist priority ordered

    while(extraList != NULL) //go until the end of the list
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

