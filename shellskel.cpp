#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  /* The command buffer */
  string cmdBuff;

  /* The ID of the child process */
  pid_t pid;

  /* The process status for wait */
  int status;

  /* Keep running until the user has typed "exit" */
  do
  {
    /* Prompt the user to enter the command */
    cerr << "cmd>";
    getline(cin, cmdBuff); // Use getline to allow spaces in input

    /* If the user wants to exit */
    if (cmdBuff != "exit")
    {
      /* Create a child */
      pid = fork();

      /* Error check to make sure the child was successfully created */
      if (pid < 0)
      {
        perror("Error in fork()");
        exit(EXIT_FAILURE); // Exit if fork fails
      }

      /* If I am child, I will do this: */
      if (pid == 0)
      {
        // Convert cmdBuff to a format usable by execlp()
        const char *program = cmdBuff.c_str();
        const char *command = program; // Assuming command is the first word in cmdBuff

        // Call execlp() to replace my program with that specified at the command line
        execlp(program, command, NULL);

        // Error check your execlp() system call
        perror("Error in execlp()");
        exit(EXIT_FAILURE); // Exit if execlp fails
      }
      /* If I am a parent, I will do the following */
      else
      {
        /* Wait for the child process to terminate */
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
          cout << "Child exited with status " << WEXITSTATUS(status) << endl;
        }
      }
    }
  } while (cmdBuff != "exit");

  return 0;
}
