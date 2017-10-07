#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



int main (int argc, char *argv[], char *envp[])
{
  /* verifier arg prog */
  if (argc < 2)
  {
    fprintf(stderr, "Erreur - Usage : %s <1...n>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int n = atoi(argv[1]);
  int i;
  pid_t fils;
  for(i = 0; i < n; i++)
  {
    fils = fork();
    if (fils == -1)
    {
      /* erreur creation fils */
      fprintf(stderr, "erreur creation fils %d\n", i+1);
      exit(EXIT_FAILURE);
    }
    else if (fils == 0)
    {
      /* exécution dans fils */
      fprintf(stdout, "Le pid du fils %d = %d et  Le ppid du fils %d = %d\n", i+1, getpid(), i+1, getppid());
      pause(); 			/* attente reception signal */
    }
    else
    {
      /* dans père donc ne rien faire */
     
    }
  }
  exit(EXIT_SUCCESS);
}
