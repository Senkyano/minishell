#include <signal.h>
#include <stdio.h>
#include <strings.h>

// Routine de gestion de SIGINT
void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		printf("\nIntercepted SIGINT!\n");
}

void set_signal_action(void)
{
	// Déclaration de la structure sigaction
	struct sigaction	act;

	// Met à 0 tous les bits dans la structure,
	// sinon on aura de mauvaises surprises de valeurs
	// non-initialisées...
	bzero(&act, sizeof(act));
	// On voudrait invoquer la routine sigint_handler
	// quand on reçoit le signal :
	act.sa_handler = &sigint_handler;
	// Applique cette structure avec la fonction à invoquer
	// au signal SIGINT (ctrl-c)
	sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
	// Change l'action associée à SIGINT
	set_signal_action();
	// Boucle infinie pour avoir le temps de faire ctrl-c autant
	// de fois que ça nous chante
	while(1)
		continue ;
	return (0);
}