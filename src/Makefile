CC = gcc
OPTFLAG = -Wall

all : print_envp lancer orphelins terminaison clean

print_envp : print_envp.o
	   $(CC) $<  -o $@

lancer : lancer.o
	$(CC) $< -o $@

orphelins : orphelins.o
	$(CC) $< -o $@

terminaison : terminaison.o
	$(CC) $< -o $@

%o:%c %h
	$(CC) $(OPTFLAG) -o $@ -c $< 


clean:
	rm -f *.o *~
