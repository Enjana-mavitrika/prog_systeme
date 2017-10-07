#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char *argv[], char *envp[])
{
  
  /* ---------------------------

     Déclarations des variables

     ------------------------------ */
  pid_t fils, retour_wait;
  int i, n, secondes, attendre, statut;
  
  /* ----------------------------

     Verification usage prog

     ------------------------------*/
  if (argc != 2)
  {
    fprintf(stderr,"Erreur - Usage %s <1..n>\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* --------------------------
     
     Exécution du prog

     ---------------------------*/

  /* ========== creation n fils ============ */
  n = atoi(argv[1]);
  for (i = 0; i < n; i++)
  {
    fils = fork();
    
    if (fils == -1)
    {
      /* === Erreur creation fils === */
      fprintf(stderr, "Erreur creation du fils %d\n", i+1);
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (fils == 0)
    {
      /* ==== éxécution dans fils === */
      fprintf(stdout, "Lancement du fils %d\n", getpid());
      /* === cas de reception d'un signal === */
      sleep(1);
      srand(getpid());
      secondes = (rand()%10) + 20; /* generation temps aléatoire entre 20 et 30 secondes */
      fprintf(stdout, "[%d] je m'endors pendant %d secondes.\n", getpid(), secondes);
      sleep(secondes);		/* dormir pendant secondes 'secondes' */
      exit(secondes);		/* exit avec arg 'secondes' */
      /* === fin execution dans fils === */
    }
    else
    {
      ; 			/* ne rien faire */
    }
  }
  /* ========= fin creation n fils ======== */
    
  /* === éxécution dans père === */
  attendre = 1;		/* attendre fin de tout les fils */
  while (attendre)
  {
    retour_wait = waitpid(-1, &statut, WUNTRACED | WCONTINUED);
    if (retour_wait == -1)
      attendre = 0;		/* plus de fils donc ne plus attendre */

    
    if (attendre)
    {
      if (WIFEXITED(statut))
	fprintf(stdout, "Fils %d fini normalement, valeur de retour %d\n", retour_wait, WEXITSTATUS(statut));
      else if (WIFSIGNALED(statut))
	fprintf(stdout, "Fils %d fini par reception du signal %d [kill -SEGV %d dans un autre terminal]\n", retour_wait, WTERMSIG(statut), retour_wait);
      else if (WIFSTOPPED(statut))
	fprintf(stdout, "Fils %d arrete par reception du signal %d [kill -STOP %d dans un autre terminal]\n", retour_wait, WSTOPSIG(statut), retour_wait);
      else if (WIFCONTINUED(statut))
	fprintf(stdout, "Fils %d relance par reception de SIGCONT [kill -CONT %d dans un autre terminal]\n", retour_wait, retour_wait);
      else
	;			/* ne rien faire */
    }
	
  }
  fprintf(stdout, "Plus de fils, bye\n");
  exit(EXIT_SUCCESS);
  /* === fin exécution dans père === */

}
