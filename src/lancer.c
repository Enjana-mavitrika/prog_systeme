#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main (int argc, char *argv[], char *envp[])
{
  /* variables */
  int i;
  char **new_argv;
  
  /* verifier argument prog */
  if (argc < 2)
  {
    fprintf(stderr, "Usage : %s <prog> [arg_1...arg_n]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* init variables */
  new_argv = malloc((argc-1) * sizeof(char*));
  for (i = 0; i < argc - 1; i++)
  {
    new_argv[i] = malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
    strcpy(new_argv[i],argv[i+1]);
  }
  new_argv[i] = NULL;
  
  /* recouvrement */
  execve(argv[1], new_argv, envp);
  exit(EXIT_FAILURE);
}
