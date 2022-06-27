#include "system_program.h"

/*  A program that prints how many summoned daemons are currently alive */
int execute()
{

   // Create a command that trawl through output of ps -efj and contains "summond"
   char *command = malloc(sizeof(char) * 256);
   sprintf(command, "ps -efj | grep summond  | grep -Ev 'tty|pts' > output.txt");

   int result = system(command);
   if (result == -1)
   {
      printf("Command %s fail to execute. Exiting now. \n", command);
      return 1;
   }

   free(command);

   int live_daemons = 0;
   FILE *fptr;

   /* TASK 7 */
   /***** BEGIN ANSWER HERE *****/
   // 1. Open the file output.txt
   fptr = fopen("output.txt", "r");

   // 2. Fetch line by line using getline()
   // 3. Increase the daemon count whenever we encounter a line
   // 4. Store the count inside live_daemons
   size_t buf_size = SHELL_BUFFERSIZE;
   char *line = malloc(sizeof(char) * buf_size);
   while (getline(&line, &buf_size, fptr)!=-1)
   {
      live_daemons += 1;
   }
   live_daemons /= 2;

   // DO NOT PRINT ANYTHING TO THE OUTPUT
   /*********************/
   if (live_daemons == 0)
      printf("No daemon is alive right now.\n");
   else
   {
      printf("Live daemons: %d\n", live_daemons);
   }

   fclose(fptr);

   return 1;
}

int main(int argc, char **args)
{
   return execute();
}