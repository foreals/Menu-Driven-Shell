#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void  parse(char *line, char **argv);
void  execute(char **argv);

int main(void){

  char option; //choice from list of commands
  char com[35] = " "; //char array for the command
  char *arg[10]; //argument array to pass in execute function
  char filename[30]; //filename char array 

  //Print out choices
  printf("\nWelcome to the menu-shell!\n\n");
  printf("Choose from one of the following commands:\n");
  printf("\tA. Listing all files.\n");
  printf("\tB. Delete a file.\n");
  printf("\tC. Open emacs.\n");
  printf("\tEnter L to list choices.\n");
  printf("\tEnter Q to QUIT\n");
  printf("Enter your choice (A,B,C): ");
  option = getc(stdin);

  //loop while the user choice is not 'Q'
  while(toupper(option) != 'Q')
    {
      if(toupper(option) == 'A')
	{
	  strcpy(com,"ls -a\0");
	  //parse the above command
	  parse(com, arg);
	  printf("\n\n");
	  //execute the command that has been parsed
	  execute(arg);
	  printf("\n");
	  printf("Enter your choice (A,B,C): ");
	}
      else if(toupper(option) == 'B')
	{
	  strcpy(com,"rm ");
	  printf("Enter a file to delete: ");
	  scanf("%s", filename);
	  //append the filename to the command
	  strcat(com, filename);
	  //parse the command
	  parse(com, arg);
	  printf("\n%s has been deleted\n\n", filename);
	  //execute the command
	  execute(arg);
	  printf("Enter your choice (A,B,C): ");
	}
      else if(toupper(option) == 'C')
	{
	  strcpy(com,"emacs ");
	  printf("Enter a file to open with emacs: ");
	  scanf("%s", filename);
	  //append filename to the command
	  strcat(com, filename);
	  //parse the command
	  parse(com, arg);
	  printf("\n%s has been opened\n\n", filename);
	  //execute the command
	  execute(arg);
	  printf("Enter your choice (A,B,C): ");
	}
      else if(toupper(option) == 'L')
	{
	  printf("\nChoose from one of the following commands:\n");
	  printf("\tA. Listing all files.\n");
	  printf("\tB. Delete a file.\n");
	  printf("\tC. Open emacs.\n");
	  printf("\tEnter L to list choices.\n");
	  printf("\tEnter Q to QUIT\n");
	}
      option = getc(stdin);
    }
  
  return 0;
}

void parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     //*argv = "\0";                 /* mark the end of argument list  */
}

void execute(char **argv)
{
     pid_t  pid;
     int status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(argv[0], argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}
