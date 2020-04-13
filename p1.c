#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX_LINE 80 /* The maximum length command */
#define LIST "/bin/ls"

int main(void)
{  

	char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char line[MAX_LINE + 1]; //line for read and split and then push to args
	char storeLastCommand[MAX_LINE + 1]; // storing last command
    char *token; //token is for splitting the words
    int should_run = 1; /* flag to determine when to exit program */
    int pos = 0;
	int pid, newfd;
	int fd[2]; // file description
	bool history = false;
	

	

	while(should_run)
	{	
	
		bzero(line, sizeof(line)); // clean the line

        while (strnlen(line, sizeof(line)) == 0) { //while length is 0
            printf("osh>");  //printout osh>
            fflush(stdout);  
            fgets(line, sizeof(line), stdin); //gets the line and store in line var
			line[strnlen(line, sizeof(line)) - 1] = '\0';
        }
		
		//storing the last command process
		if(strcmp(line,"!!") == 0)
		{
			//if there is no command, then print this out
			if(history == false)
				printf("No command in history.\n");
			
			else
			{
				for(int i=0; i<MAX_LINE; i++)
					line[i] = storeLastCommand[i];
			}
		}
			
		else
		{
			//if there is a command in history then assign to line
			for(int i=0; i<MAX_LINE; i++)
					storeLastCommand[i] = line[i];
				
			//and make sure now there is a history	
			history = true;
		}


		
        token = strtok(line, " \t");
        pos = 0;

		//splitting the line and push to args
        while (token != NULL) {
            if (token[0] != '\0')
                args[pos++] = token;
            token = strtok(NULL, " \t");
        }

        args[pos] = NULL;
		
		//if the pos is 0, means user just entered without value.
        if (pos == 0)
            continue;
		
		//ls process
		if(args[1] == NULL)
		{
			//if user type exit, simply break the loop
			if(strcmp(args[0],"exit") == 0) 
			{
				should_run = 0;
			}
			

			//if user type like ls, pwd, whoami etc., execute
			else
			{
				pid = fork();
			
				if(pid<0)// check if fork fails
				{
					perror("Fork failed");
					exit(1);		
				}

				else if(pid == 0) // child 
				{				
					execvp(args[0], args);									
				}
				
				else //parent
				{
					wait(NULL);										
				}
			}
		

		}	

		//ls -al process
		else if(args[2] == NULL)
		{
			
			pid = fork();
			
			if(pid<0)
			{
				perror("Fork failed");
				exit(1);		
			}

			else if(pid == 0) // child 
			{
				
				if(execvp(args[0], args) < 0)
				{
					perror(args[0]);
					exit(1); //this exit only terminate the child
				}		
			}
			
			else
			{
				wait(NULL);		
			}	
		}
		
		/* & and ; and printout ls & whoami process
		i am forking the child progress and
		creating grandchild process
		the parent process which is outer else statement
		has to wait for child and grandchild
		2 waiting there
		*/
		else if(strcmp(args[1],"&") == 0 || strcmp(args[1],";") == 0)
		{
			
			args[1] = NULL; //getting rid of & and ;
			pid = fork(); //forking
			
			if(pid<0)//error checking
			{
				perror("Fork failed");
				exit(1);		
			}

			else if(pid == 0) // child 
			{		
				pid = fork(); //fork again
				
				if (pid < 0)
				{
					perror("Fork failed");
					exit(1);
				}
				
				else if(pid == 0) //this is gradchild
				{
					execvp(args[0], args);//execute first command		
				}
				
				else
				{
					execvp(args[2], args+2);//execute second command
				}
			
			}
			
			else
			{				
				wait(NULL);//wait for child
				wait(NULL);//wait for grandchild
			}	
		}
		
		// > in direction process
		else if(strcmp(args[1],">") == 0)
		{
			args[1] = NULL; //getting rid of & and ;
			pid = fork(); //forking
			
			if(pid<0)//error checking
			{
				perror("Fork failed");
				exit(1);		
			}

			else if(pid == 0) // child 
			{				
				//asign newfd to creating and writing a file
				if ((newfd = open(args[2], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
					perror(args[0]);	/* open failed */
					exit(1);
				}

				/*The dup2() system call is similar to dup() but the basic difference
				between them is that instead of using the lowest-numbered unused file
				descriptor, it uses the descriptor number specified by the user.
				*/
				dup2(newfd, 1); 
				execvp(args[0],args); //executing
	
			}
			else
			{
				wait(NULL);										
			}
			
		}
		
		// < out direction process
		else if(strcmp(args[1],"<") == 0)
		{
			args[1] = NULL; //getting rid of & and ;
			pid = fork(); //forking
			
			if(pid<0)//error checking
			{
				perror("Fork failed");
				exit(1);		
			}

			else if(pid == 0) // child 
			{				
				//check the file and read it
				if ((newfd = open(args[2], O_RDONLY)) < 0) {
					perror(args[0]);	/* open failed */
					exit(1);
				}

				dup2(newfd, 0); 
				execvp(args[0],args); //excecute the first command
	
			}
			else
			{
				wait(NULL);										
			}			
		}	
		// piping process
		else if(strcmp(args[1],"|") == 0)
		{
			
			args[1] = NULL; //getting rid of & and ;
			pid = fork(); //forking
			
			if(pid<0)//error checking
			{
				perror("Fork failed");
				exit(1);		
			}

			else if(pid == 0) // child 
			{		
				//pipe is a connection between two processes read and write
				pipe(fd);
				pid = fork(); //fork again
				
				if(pid<0)//error checking
				{
					perror("Fork failed");
					exit(1);
				}
				
				else if(pid == 0)//child process
				{		
					close(0); //closing the std 
					dup2(fd[0],0); 
					close(fd[1]); //closing the writing part of the pipe
					execvp(args[2], args+2); //
				}
				
				else
				{
					close(1); //closing the stdout
					dup2(fd[1],1); 
					close(fd[0]);  //closing the read part of the pipe
					execvp(args[0], args); //excecuting the command
				}
			
			}
			
			else
			{		
				wait(NULL); //waiting for child
				wait(NULL); //waiting for grandchild				
			}			
		}
		
		else
		{
			printf("There is no such a command! Try again.\n");
		}	
	}
	
	return 0;
}