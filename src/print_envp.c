#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char *envp[])
{
  int i = 0;
  while (envp[i])
  {
    fprintf(stdout, "%s\n", envp[i++]);
  }

  exit(EXIT_SUCCESS);
}
