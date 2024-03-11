Notes Minishell
=======================

<br/>
<br/>
<br/>

Sommaire :
=========

<br/>

1. [Liste_Fonctions_externes_autorisees](#partie_1)
2. [Documentation_fonction_externes_autorisees](#partie_2)
3. [Fonctionnalite_basique_minishell](#partie_3)
4. [BASH_PARSING_technique->PRECEDENCE_CLIMBING](#partie_4)
5. [Application_of_PRECEDENCE_CLIMBING_on_bash_arguments](#partie_5)
6. [Environment_and_variables](#partie_6)
7. [Etapes_execution](#partie_7)
8. [Fonctions_builtins](#partie_8)
9. [Historique_de_commandes](#partie_9)
10. [Signaux](#partie_10)
11. [Errno_et_la_gestion_d_erreur](#partie_11)

<br/>
<br/>
<br/>

Liste_Fonctions_externes_autorisees <a id="partie_1"></a>
---------------------------------------------------------

<br/>

readline, rl_clear_history, rl_on_new_line, rl_replace_line
rl_redisplay, add_history

printf, malloc, free, write, acess, open, read, close, fork, wait,
waitpid, exit, unlink, execve, dup, dup2, pipe

wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill,
getcwd, chdir, stat, lstat, fstat, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

<br/>
<br/>
<br/>

Documentation_fonction_externes_autorisees <a id="partie_2"></a>
----------------------------------------------------------------

<br/>
<br/>

**readline** : fonction qui lis une ligne du terminal et la retourne.

**rl_clear_history** : supprime l'historique de la fonction readline et
libere la memoire associee aux donnees privee de la fonction readline.

**rl_on_new_line** : Indique aux fonctions de mise a jour que nous sommes
passes sur une nouvelle ligne (vide), generalement apres avoir affiche
une nouvelle ligne.

**rl_replace_line** : Remplace le contenus de 'rl_line_buffer' par du 
texte. Le 'point' et la 'marque' (mark) sont conserves, si possible.
Si 'clear_undo' (un parametre de la fonction) est different de zero,
la liste d'annulation associee a la ligne actuelle est effacee. 

**rl_redisplay** : Change le contenus de ce qui est affiche a l'ecran
pour refleter le contenus actuel de 'rl_line_buffer'.


**add_history** : place la chaine de caractere fournis en argument a la
fin de l'historique. Le champ de données associé (le cas échéant) est 
défini sur NULL.

Cas de figure lorsqu'il y a un signal 'Ctrl C' avec readline :
https://stackoverflow.com/questions/71685072/return-readline-to-its-original-state-when-recieving-sigint

<br/>

**wait3, wait4** : Les appels systeme wait3 et wait4 sont similaires a 
waitpid, mais retournent egalement des informations sur l'utilisation des 
ressources par le fils dans la structure pointee par 'rusage' (parametre
de la fonction). 'wait3' attend n'importe quel fils, et 'wait4' peut
etre utilise pour selectionner un ou des fils specifique(s) a attendre.

<br/>
<br/>

**signal** : la fonction installe le gestionnaire 'handler' pour le signal
'signum' (parametre de la fonction). 'handler' peut etre 'SIG_IGN',
'SIG_DFL' ou l'adresse d'une fonction definie par le programmeur
(un "gestionnaire de signal").

**sigaction** : Cette fonction modifie l'action effectuee par un processus
a la reception d'un signal specifique.
sigemptyset : Cette fonction vide l'ensemble de signaux fourni par 
set, tous les signaux etant exclus de cet ensemble.
sigaddset : ajoutent le signal signum de l'ensemble 'set'.
kill : Le signal par defaut de kill est TERM. Permet d'arreter un 
ou plusieurs processus.

<br/>

**getcwd** : Cette fonction copie le chemin d'acces absolu du repertoire
de travail courant dans la chaine pointee par 'buf' (parametre de la
fonction), qui est de longueur 'size' (parametre de la fonction).

<br/>

**chdir :** Remplace le repertoire de travail courant du processus appelant
par celui indique dans le chemin path. La fonction chdir() fera en 
sorte que le répertoire nommé par le chemin pointé par l'argument path 
devienne le répertoire de travail actuel ; c'est-à-dire que le point 
de départ de la recherche de chemin pour les noms de chemin ne 
commençant pas par '/' .

<br/>

**stat, lstat, fstat** : Ces fonctions renvoient des renseignements sur 
le fichier indique, dans le tampon pointe par 'stat'. 'stat' et 'fstat'
recuperent des renseignements sur le fichier pointe par 'pathname'.
'lstat' est identique a 'stat', sauf que dans le cas ou 'pathname'
est un lien symbolique, auquel cas il renvoie des renseignements sur
le lien lui-meme plutot que celui du fichier vise. 'fstat' est 
identique a 'stat', sauf que le fichier dont les renseignements sont
a recuperer est reference par le descripteur de fichier fd.

<br/>

**opendir** : La fonction 'opendir' ouvre un flux repertoire correspondant
au repertoire 'name', et renvoie un pointeur sur ce flux. Le flux est
positionne sur la premiere entree du repertoire.

Explication sur les fichiers, repertoires et ouverture de flux de
repertoire : 
https://www.developpez.net/forums/d1638610/c-cpp/c/parcours-d-dossier/

**readdir** : La fonction readdir() renvoie un pointeur sur une structure 
'dirent' representant l'entree suivante du flux repertoire pointe 
par 'dir'. Elle renvoie NULL a la fin du repertoire, ou en cas 
d'erreur.

**closedir** : La fonction ferme le flux de repertoire associe a 'dir'.
Apres cette invocation, le descripteur 'dir' du flux de repertoire 
n'est plus disponible.

<br/>

Parcourir des dossiers en C, explication 'errno', 'perror' :
http://sdz.tdct.org/sdz/arcourir-les-dossiers-avec-dirent-h.html

**strerror** : La fonction 'strerror' renvoie une chaine decrivant le 
code d'erreur passe en argument errnum.
perror : La fonction 'perror' affiche un message sur la sortie
d'erreur standard, decrivant la derniere erreur rencontree durant
un appel systeme ou une fonction de bibliotheque. La chaine de 
caracteres contient generalement le nom de la fonction ou s'est 
produit l'erreur.

<br/>

**isatty** : Verifie si le descripteur de fichier fournis en parametres
est ouvert et connecte a un terminal.

**ttyname** : La fonction renvoie un pointeur sur le nom du peripherique
terminal associe au descripteur de fichier fd, ou NULL en cas d'erreur
(par exemple si le 'fd' n'est pas connecte a un terminal).

**ttyslot** : La fonction renvoie la position de l'entree du terminal en
cours dans un fichier.

<br/>

**ioctl** : La fonction modifie le comportement des peripheriques 
sous-jacents des fichiers speciaux. En particulier, de nombreuses 
caracteristiques des fichiers speciaux en mode caractere (par exemple
des terminaux) peuvent etre controlees avec des requetes ioctl.

Explication requetes ioctl :
https://www.developpez.net/forums/d1013085/c-cpp/c/but-utilite-fonction-ioctl/

<br/>

**getenv** : La fonction recherche dans la liste des variables d'environnement
une variable nommee 'name' (parametre de la fonction), et renvoie un
pointeur sur la chaine 'value'.

<br/>

**Termios** : Les fonctions termios etablissent une interface sous forme
de terminal, permettant de controler les ports de communication 
asynchrone.

**tcsetattr** : la fonction fixe les parametres du terminal (a moins que
le materiel sous-jacent ne le prenne pas en charge) en lisant la
structure 'termios' pointee par 'termios_p'

**tcgetattr** : La fonction recupere les parametres associes a l'objet
reference par 'fd' et les stocke dans la structure 'termios' pointee
par 'termios_p'. Cette fonction peut etre appele par un processus en
arriere-plan ; neanmoins, les attributs de terminal peuvent etre
modifies par la suite par le processus en avant-plan.

Explication structure et fonctions termios :
http://manpagesfr.free.fr/man/man3/termios.3.html

<br/>

**Termcap, Terminfo**

Explication : 
https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

getent, tgetflag, tgetnum, tgetstr, tgoto, tputs : ce sont les 
fonctions utilisee pour la creation d'interface graphique dans un
terminal.

<br/>
<br/>
<br/>
<br/>
<br/>
<br/>


Fonctionnalite_basique_minishell <a id="partie_3"></a>
------------------------------------------------------

<br/>
<br/>

**Explication minishell :**
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

<br/>

**PARSING :**

- ```;``` in command line should be separate commands

- Handle double quotes ```""``` and single quotes ```''```, which should 
escape special characters, beside ```$``` for double quotes (Case of multiline does not handle with ```""``` in minishell project).

- Handle environment variables (```$``` followed by a sequence of characters) and ```$?``` should be function as same as bash.

- Handle signals like in bash (```ctrl + C```, ```ctrl + \```, ```ctrl + D```).

<br/>

**EXECUTION :**

- Run simple commands with absolute path ```/bin/ls```, relative path
```../bin/ls``` and without a path ```ls```, ```cat```, ```grep``` ...

- Working (commands) history (navigating in with up/down arrows). 

- Implement pipes ```|```, redirections ```<```, ```>```, ```>>``` and the here-doc ```<<```  
	-> pipex.

- Implement the following built-ins : echo (option -n only), exit,
env (with no options or arguments), export (with no option), unset
(with no options), cd, pwd.


<br/>
<br/>
<br/>



**Two Part : FRONT-END / BACK-END**

<br/>

- **FRONT-END** -> the part that deals with user input and user interaction
(commands and signal).

Chose to postpone signals until it finish the execution, because 
implementing signals from the start will just add unnecessary 
complication.

- **BACK-END** -> is where the internal work is done (the execution).

<br/>
<br/>

**BASH PARSING** - 2 phases : the **lexical analysis** (lexing) which produces
"lexems" and then the **syntax analysis** (parsing the lexems).

1 - **Lexical analysis / tokenization** : taking the input from the user
and processing it char into "tokens" (type and value).

The most important thing to us is the type of the lexems/tokens and
the order they came in (not the values).

2 - **Syntax analysis / Parsing** : scanning the stream of tokens according
to a specific grammar and then deciding what to do with them 
(generating an AST - Abstract Syntax Tree).

Parsing Abstract Syntax Tree : The Recursive Descent, The Theory of
Computation.

Theory -> what a grammar ? what a language ?

Type of grammar that is used for this project is called CFG (Context
Free Grammar). A grammar is basically a way of telling how a language
can be made, back to the example above ...


<br/>
<br/>

BASH_PARSING_technique->PRECEDENCE_CLIMBING <a id="partie_4"></a>
-----------------------------------------------------------------

<br/>
<br/>
<br/>

**Useful article** : 
https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing

L'objectif fondamental de l'algorithme est le suivant : traiter une 
expression comme un ensemble de sous-expressions imbriquées, où 
chaque sous-expression a en commun le niveau de priorité le plus bas 
des opérateurs qu'elle contient.

<br/>

Concepts :

- Precedence of sus-expressions
- Associativity (left associativem right associative)
- Atoms (either numbers or parenthesized expressions)
- Expressions (atoms connected by binary operators)

<br/>

The algorithm is 'operator-guided'. 

Its fundamental step is to consume
the next atom and look at the operator following it. If the operator
has precedence lower than the lowest acceptable for the current step,
the algorithm returns. Otherwise, it calls itself in a loop to handle
the sub-expression. 

In pseudo-code, it looks like this :

```
compute_expr(min_prec):

	result = compute_atom()

	while cur token is a binary operator with precedence >= min_prec:
		prec, assoc = precedence and associativity of current token
		if assoc is left :
			next_min_prec = prec + 1
		else:
			next_min_prec = prec
		rhs = compute_expr(next_min_prec)
		result = compute operator(result, rhs)

	return result
```

<br/>

Note that the algorithm makes one recursive call per binary operator.
Some of these calls are short lived - they will only consume an atom and
return it because the _while_ loop is not entered. Some are longer lived.
The initial call to **compute_expr** will compute the whole expression.

<br/>

**Handling associativity**

<br/>

Example : 
- 8 * 9 * 10 -> (8 * 9) * 10
- 8 ^ 9 ^ 10 -> (8 ^ 9) ^ 10

<br/>

**Handling sub-expressions**

<br/>

The algorithm pseudo-code presented above doesn't explain how parenthesized
sub-expressions are-handled.

Consider this expression : 2000 * (4 - 3) / 100

It's not clear how the _while_ loop can handle this. The answer is **compute_atom**. When it sees a left parenthesized, it it knows that a sub-expression will follow, so it calls **compute_expr** on the sub expression (which lasts until the matching right parenthesized), and returns
its result as the result of the atom.

So **compute_expr** is oblivious to the existence of sub-expressions.

<br/>
<br/>
<br/>

Application_of_PRECEDENCE_CLIMBING_on_bash_arguments <a id="partie_5"></a>
--------------------------------------------------------------------------

<br/>

Let's set a variable A with the value ```1```.

```export A="1"```

Let's suppose we get the following user input ;

```""$A B "CD"```

The first thing with do, is to replace ```$A``` with its value, so it becomes :

```""1 B "CD"```

Then we get rid of empty string, so we get :

```1 B "CD"```

Then we split the string by spaces (depending on the quotes), so we get three strings :

```1```, ```B```, ```"CD"```

Then we check if there is any globbing (```*``` wildcard), if there is we
replace the wildcard by the appropriate strings - the globbing algorithm
it's a backtracking algorithm, you can learn more about it :
https://www.geeksforgeeks.org/wildcard-pattern-matching/

Finally, we strip out any quotes :

```1```, ```B```, ```CD```

<br/>
<br/>
<br/>

The execution of Abstract Syntax Tree (AST)
-------------------------------------------

<br/>

What we are basically given in the execution part is an AST, and the way
we will execute it is by traversing it recursively, here is a pseudo-code example that traverses the bash arguments AST built earlier in the parsing phase.

```int execute(t_node node)
{
	if (node.type == PIPE)
		return (execute_pipe(node.left, node.right));
	else
		return (execute_simple_command(node.value));
}
```

<br/>

In the execution part, most importantly is how to manage file descriptors
and forking processes.

<br/>
<br/>
<br/>

Environment_and_variables <a id="partie_6"></a>
-----------------------------------------------

The ```$0``` is one of the special variables you get in bash and is used to print the filename of the script that is currently being executed.

The ```$0``` variable can be used in two ways in linux :
- Use ```$0``` to find the logged-in shell.
- Use ```$0``` to print the name of the script that is being executed.

Here's quick look into the special variables you get in bash shell 
(link article : https://linuxhandbook.com/bash-special-variables/)

- ```$0``` : Gets the name of the current script.
- ```$#``` : Gets the number of arguments passed while executing the bash script.
- ```$*``` : Gives you a string containing every command-line argument.
- ```$@``` : It stores the list of every command-line argument as an array.
- ```$1-$9``` : Stores the first 9 arguments.
- ```$?``` : Gets the status of the last command or the most recently executed process.
- ```$!``` : Shows the process ID of the last background command.
- ```$$``` : Gets the process ID of the current shell.
- ```$-``` : It will print the current set of options in your current shell.

Pour minishell on doit juste gerer ```$?```.

<br/>
<br/>
<br/>

Etapes_execution <a id="partie_7"></a>
--------------------------------------

Notes explicatives sur une version de minishell :
https://github.com/LucieLeBriquer/minishell/tree/master

Lorsque l'on est sur une commande/feuille, on regarde le premier mot apres
expansion :
- Si c'est une commande built-in -> go to la fonction dediee
- Si on commence par ```./``` on essaye de lancer l'executable ```./name``` (fork needed)
- S'il y a un ```=``` on cree une variable d'environnement
- Sinon, on essaye de lancer l'executable **$(PATH)/name** (fork needed)

<br/>

**Structure fonction main :**

- malloc env
- Readline
- Parsing
- export variable d'environnement si '=' (Expansion)

- check builtin
- check executable file './'
- check absolute path cmd or cmd and execute (command exist or right to execute ?)
- apply redirection and pipe

<br/>

**Introduction theorique : La representation des fichiers ouverts sur le systeme**

Lien de l'article :
https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/

Pour representer les fichiers ouverts, le systeme utilise trois structures de donnees :

- Une table de descripteurs de fichier **par processus**. Chaque processus possede sa propre table qui contient une suite d'indexes, chacun faisant reference a une entree dans la table des fichiers ouverts.
- Une table des fichiers ouverts qui est **commune a tous les processus**. Chaque entree de ce tableau contient, entres autres,le mode d'acces, la tete de lecture du fichier, et un pointeur vers l'entree correspondante dans la table inode. Cette table garde aussi un compte du nombre de references a ce fichier dans toutes les tables de descripteurs de tous les processus. Lorsqu'un processus ferme le fichier, ce compte est decremente et s'il arrive a 0, l'entree est supprimee de la table des fichiers.
- Une table inode (index node) qui est aussi commune a tous les processus. Chaque entree dans la table inode decrit en detail le fichier en question : le chemin ou il se trouve sur le disque dur, sa taille, ses permissions...

**Particularite de la fonction read**

La fonction read a bien l'air d'avoir un marque-pages integre ! A chaque appel, read reprend la lecture la ou elle s'est arretee la derniere fois. En realite, la fonction read ne retient pas elle-meme sa derniere position dans le fichier : elle incremente la tete de lecture du descripteur de fichier.

**La tete de lecture d'un descripteur de fichier**

Comme on l'aura peut-etre remarque dans le schema au debut de cet article, les references dans la table commune des fichiers ouverts contient une tete de lecture. Celle-ci controle le decalage entre le debut du fichier et la position actuelle a l'interieur du fichier. Et c'est elle que read incremente a la fin de sa lecture. La tete de lecture est simplement appelee "**offset**" en anglais.

Donc quand on ouvre un fichier, la tete de lecture est typique;ent a 0, ce qui veut dire qu'on se trouve en tout debut de fichier. Quand on lit, disons, 12 caracteres avec read, la tete de lecture est mise a jour a 12. La prochaine fois qu'on accede au descripteur de fichier pour y lire ou meme y ecrire, on commencera depuis la position du debut du fichier decale de la valeur de la tete de lecture, ici donc, au 13e caractere.

Notons aussi que malgre son nom, la tete de lecture est aussi la tete d'ecriture : la fonction *write* sera aussi affectee par tout les deplacement de la tete dans le fichier.

**Retrouver le debut du fichier avec un nouveau descripteur**

La solution la plus simple est sans doute d'ouvrir a nouveau le meme fichier avec open. Cela cree une nouvelle entree dans le tableau des fichiers ouverts du systeme sans aucun decalage de tete de lecture.

**Lseek : repositionner la tete de lecture**

Une autre option pour repositionner la tete de lecture a l'endroit qu'on veut, c'est la fonction **lseek** de la bibliotheque <unistd.h>. Elle nous permet d'exercer un controle plus precis sur la position de la tete de lecture.

Il faut faire attention avec *lseek* car cette fonction nous permet de mettre notre tete de lecture au-dela de la fin du fichier ! Si l'on ecrit apres la fin du fichier, sa taille ne changera pas et cela pourrait creer des "trous", des zones remplies de '\0' au milieu du fichier.

**L'interchangeabilite des descripteurs dupliques**

Apres un appel reussi a dup ou dup2, l'ancien et le nouveau descripteurs sont interchangeables : ils font reference au meme fichier dans la table des fichiers ouverts et partagent donc tous ses attributs. Par exe;ple, si on lit avec *read* les premiers caracteres de l'un des descripteurs, la tete de lecture va etre modifiee. Et ce, pour les deux descripteurs de fichier, pas seulement celui avec lequel on a lu.

Pourtant, on a vu precedemment que si l'on rouvrait le meme fichier une deuxieme fois, les deux descripteurs ne se partageaient pas la tete de lecture de cette facon. Alors pourquoi cela fonctionne-t-il differemment pour les descripteurs dupliques ?

Un descripteur de fichier ouvert possede sa propre entree dans le tableau des fichiers ouverts, avec sa propre tete de lecture. Par contre, un descripteur de fichier duplique pointe vers la meme entree dans la table des fichiers ouverts que le descripteur de fichier original, ce qui implique qu'il partage la tete de lecture de son clone.

**Lire et ecrire dans un pipe**

Les descripteurs de fichiers d'un pipe s'utilisent de la meme maniere que tout autre descripteur de fichier. Afin d'y mettre des donnees ou de les recuperer, on pourra se servir respectivement des appels systemes *read* et *write* de la bibliotheque <unistd.h>.

Il y a toutefois deux points a garder a l'esprit :

- Si un processus tente de lire depuis un pipe vide, *read* bloquera le processus jusqu'a ce que des donnees soient ecrites dans le pipe.
- A l'inverse, si un processus tente d'ecrire dans un pipe plein (c'est a dire a la limite de sa capacite), *write* bloquera le processus jusqu'a ce qu'assez de donnees soient lues pour permettre d'y ecrire.

<br/>

**Fermer un pipe**

Les bouts de lecture et d'ecriture d'un pipe se ferment avec l'appel systeme *close* de la bibliotheque <unistd.h> comme tout autre descripteur de fichier. Cependant, il y a quelques particularites a prendre en compte concernant la fermeture des bouts d'un pipe.

Lorsque tous les descripteurs de fichier qui font reference au bout d'ecriture d'un pipe sont fermes, un processus qui tente de lire depuis son bout de lecture verra le caractere de fin de fichier (EOF ou "end of file") et la fonction *read* renverra 0.

A l'inverse, si tous les descripteurs de fichier qui font reference au bout de lecture d'un pipe sont fermes et qu'un processus tente d'y ecrire, *write* lancera le signal SIGPIPE ou, si le signal est ignore, echouera avec l'erreur EPIPE dans *errno*.

Pour s'assurer que les processus recoivent correctement les indications de terminaison (EOF, SIGPIPE/EPIPE), il est primordial de fermer tous les descripteurs dupliques inutilises.

Exemple : Si l'on oublie de fermer les bouts de lecture inutilises du pipe  dans le processus fils, celui-ci reste indefiniment en suspens, puisque read n'a pas recu le caractere de fin de fichier (EOF), meme si le pere a ferme son descripteur pour le bout d'ecriture... Simplement, etant donne que le processus fils n'a pas ferme le sien avant la lecture. D'ou l'importance de s'assurer d'avoir bien ferme les bouts inutilises de nos pipes dans chaque processus.

<br/>

**Creer une pipeline comme un shell**

Ce qu'il faut faire si l'on souhaite construire une pipeline, c'est creer un tube (une paire de descripteurs de fichiers) pour chaque processus fils, moins 1. Comme ca, le premier peut ecrire dans la sortie de son propre tube, le deuxieme lire depuis le tube du premier et ecrire dans son propre tube et ainsi de suite.

<br/>

**Astuces pour deboguer un programme avec des processus fils**

<br/>

Plus de details sur les fork et les processus fils :
https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/

Tout bon programme ne doit avoir aucune fuite de memoire. Dans le cas d'un programme qui cree des processus fils, aucun de ces fils ne doivent avoir de fuites de memoire non plus. On doit donc s'assurer de liberer toute memoire allouee a la terminaison de chaque processus. Si l'on tue nos processus fils avec un signal, on doit veiller a quel signal utiliser : SIGTERM, SIGINT et SIGKILL n'ont pas tous les memes implications en termes de fuites de memoire !

Deboguer un programme qui cree des processus fils peut s'averer assez accablant. En effet, Valgrind affiche souvent un torrent de messages d'erreurs, provenant non seulement du processus pere mais aussi de chacun des fils ! Heuresement, Valgrind nous offre une option pour faire taire les erreurs dans les fils : ```--child-silent-after-fork=yes```. Une fois qu'on a resolu les erreurs du processus pere, on peut enlever cette option pour examiner les erreurs propres aux fils.

<br/>
<br/>
<br/>

Fonctions_builtins <a id="partie_8"></a>
----------------------------------------

The **built-ins** are a set of useful functions that are needed in the Minishell, they differ in complexity, from the easy ones like ```echo``` to
complex ones.

Les fonctions ```built-ins``` n'ont pas besoin d'utiliser ```execve``` car elles sont suffisamment simple pour etre directement implementee. On a donc pas besoin d'utiliser de dupliquer les processus.

**echo :**

La fonction echo avec l'option '-n' ne renvoie pas de '\n', mais on peut mettre plusieus fois le flag '-n' avec un nombre de n non limite et cela doit quand meme fonction et renvoyer le message de l'argument avec un '\n', mais si dans l'un des flag '-n' il y a un caractere qui n'est pas un 'n' alors la fonction considere que ce flag et tout ce qui suit font partit de l'argument a afficher et renvoie cette chaine avec un '\n' si il y a un
flag '-n' devant.
- La commande echo enleve tout les espaces avant et apres l'argument a afficher.

<br/>

**cd :** 

- Lorsque j'effectue un cd je dois mettre a jour PWD et OLDPWD, 
je remplace OLDPWD par PWD et je remplace PWD par le nouveau 
repertoire de travail.
- Il faut que je free le malloc 'current_pwd' de ma fonction 'update_pwds' a
un moment donnee, et il faudrait que je trouve le bon endroit ou le faire (fin
de la fonction ou plutot a la fin du programme avec un free d'une structure
probablemet).
- Il faut que je gere le fait de trouver le bon dossier malgre le fait qu'il y ai un espace apres le nom du dossier avec 'cd'.
- Lorsque le dossier suivant la commande cd n'est pas trouve, il ne faut pas 
mettre a jour les variables d'environnements.
- Il faut que je fasse le 'cd ~' : pour l'instant le cd ~ marche quand meme
lorsque j'ajoute directement quelque chose apres le ~ alors qu'il devrait
renvoyer : No such file or directory. Mais, je ne vais pas rajouter de code
pour gerer cette fonctionnalite car ca va trop surcharger le code. Car,
lorsqu'il y aura l'algo de parsing, tout les cas particulier ne seront
plus a gerer et le code se simplifiera
- Il faudra pas que j'oublie de de proteger la fonction 'getcwd'.
- Ne pas oublier 'cd -' qui revient au pwd d'avant (oldpwd) -> (je l'ai fais mais
pour l'instant ca effectue la commande meme quand il y a des caracteres apres le
'-' du genre 'cd -jsvn').
- Il faudrait que je refasse la fonction cd en rajoutant une fonction qui calcule
tout les new_dir_path en fonction des cas, avec une pour le cas generale et une 
pour les cas particulier et qui gere tout les cas particulier a l'interieur de
cette fonction.

<br/>

- Il faut egalement que je gere le ```cd ..``` et l'histoire du dossier supprime et lorsque l'on fait ```cd ..``` a l'interieur d'un dossier qui se trouve dans le dossier supprimee et que les variables d'environnements PWD et OLDPWD ont ete *unset*.
- A voir si je suis cense trouver le dossier meme quand j'unset le PWD (mais que
du coup je ne l'utilise pas) pour aller au fichier suivant, parce que moi j'arrete la fonction cd des que l'une des variables d'environnement comme le 
'HOME', 'PWD' ou 'OLDPWD' n'est pas defini, mais ce n'est peut-etre pas correct.

<br/>

**export :**

- Lorsque je met 'export' sans argument, il est possible que je doivent
afficher tout ce qui a ete declare dans le env comme le comportement de
export dans bash.
- Je dois renvoyer une erreur avec perror `argument': not a valid identifier lorsque la cle commence par un chiffre.
- Lorsque je met un argument apres le export sans '=' il ne faut pas que 
cela mette un message d'erreur, ca doit juste rien faire.
- Lorsque j'ai un caractere qui n'est pas une lettre ou un chiffre dans 
l'argument, meme s'il y a un egal je dois renvoyer une erreur (en plus,
les chiffres ne sont pas autorisees pour l'index 0 de l'argument).
- Penser a gerer lorsque je met un '==' avec la fonction export : export sfd==wa.

<br/>

**exit :**

- Attention au parsing de ```exit``` : ```a``` ou ```a 1``` ou ```3.14``` : ```exit(2)``` + erreur ```numeric argument required```
- ```1 a``` ou ```1 2``` : pas d'exit + $? = 1 + erreur ```too may arguments```
- Si juste un argument numerique -> le convertir en % 256 et exit avec cette valeur
- Gerer le cas ou il n'y a pas d'argument au niveau de exit

<br/>

- Re-verifier avec d'autres personnes si ma fonction exit est correct

<br/>

Exit status depands of multiple things :
- If the command work : 0
- If a command exist and fail cause of the arg : 1
- If a command exist and you don't have the permission : 126
- If a command doesn't exist : 127
- If a signal Kill or interrupte the commande : 127 + signal
- If error parsing : 2

Exit status come with Error message in your terminal, don't forget that the error fd
is 2 (putstr_fd).


<br/>
<br/>
<br/>

Historique_de_commandes <a id="partie_9"></a>
---------------------------------------------

Pour l'instant, lorsque j'appuie sur les fleches ca me fait des 
symboles avec [[ A ..., parce qu'on ne gere pas encore l'historique
des commandes et le fait de pouvoir le remonter avec la fleche du 
haut, et d'ailleurs les flches de gauche et droite ne sont pas 
censee faire aussi les [[ C quand j'appuie dessus dans la version 
final.

La fonction readline a un historique que l'on peut associer aux touches
fleche du haut et du bas.

<br/>
<br/>
<br/>

Signaux <a id="partie_10"></a>
-----------------------------

<br/>

After finishing the execution, we can implement the signals (```ctrl + C```, ```ctrl + \```, ```ctrl + D```).

For ```ctrl + C```, ```ctrl + \```, we can catch ```SIGINT``` and ```SIGQUIT``` respectively, but in the case of ```ctrl + D``` we have to check the ```EOF``` or the end of string (i.e. ```NULL``` character).

Article explicatif sur les signaux : 
https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/

<br/>

**Definition :** Un signal est un message de notification standardise utilise dans les systemes d'exploitation compatibles POSIX ou de type Unix. On l'envoie a un programme en cours d'execution de facon asynchrone, pour le signaler de l'apparition d'un evenement. Le systeme interrompt alors l'execution normale du processus en question pour declencher une reaction specifique comme, entres autres, la terminaison du processus. On peut donc dire qu'un signal est une forme limitee de communication inter-processus.

<br/>

**L'envoi d'un signal** : Le noyau du systeme d'exploitation peut envoyer un signal pour l'une des deux raisons suivantes :
- Il a detecte un evenement systeme comme une erreur de division par zero ou la terminaison d'un processus fils.
- Un processus lui en a fait la demande avec l'appel systeme ```kill```, sachant qu'un processus peut s'envoyer lui-meme un signal.

"L'envoi" d'un signal est en realite plutot une livraison : le systeme met a jour le contexte du processus destinataire du signal. En effet, pour chaque processus, le systeme maintient deux vecteurs de bits : ```pending``` pour surveiller les signaux en attente, et ```blocked``` pour suivre les signaux bloques. Lorsqu'il envoie un signal, le systeme ne fait que mettre le bit associe au signal a 1 dans le vecteur ```pending``` du processus destinataire.

Il est important de noter qu'il ne peut pas y avoir plusieurs signaux du meme type en attente. Dans l'exemple de l'article, le processus a deja le signal ```17```, ```SIGCHLD```, en attente. Le systeme ne peut donc pas lui envoyer d'autres signaux ```SIGCHLD``` jusqu'a ce que ce signal soit receptionne. Il n'y a pas non plus de file d'attente pour les signaux en attente : tant que ce signal n'est pas receptionne, tous les signaux du meme type qui suivent sont perdus.

**La reception du signal** : Le systeme d'exploitation donne l'impression de pouvoir executer une multitude de programmes a la fois, mais ce n'est qu'une illusion. En realite, il passe constamment d'un processus a l'autre a une vitesse fulgurante. C'est ce qu'on appelle une **commutation de contexte** (*context switch* en anglais).

Lorsque le noyau du systeme reprend le fil d'execution du processus par exemple apres une commutation ou un appel systeme, il verifie l'ensemble de signaux non-bloques en attente pour ce processus. C'est a dire qu'il fait l'operation *bitwise* ```pending & ~blocked```. Si cet ensemble est vide, comme c'est generalement le cas, le noyau passe a la prochaine instruction du programme. Par contre si l'ensemble n'est pas vide, le noyau choisit un signal (generalement le plus petit) et force la force le processus a y reagir avec une action. C'est ce moment-la qu'on appelle la reception du signal. Selon le signal, le processus pourra soit :
- ignorer le signal,
- mettre fin a son execution,
- intercepter le signal en executant sa propre routine de gestion pour le signal recu.

Une fois le signal recu et une de ces actions realisees, le noyau remet le bit qui lui correspond a 0 dans le vecteur ```pending``` et passe a la prochaine instruction du programme s'il n'a pas termine.

<br/>

**Les signaux POSIX et leurs actions par defaut** :

<br/>

Par defaut, lorsqu'un processus recoit un signal, il effectuera l'une de ces quatre actions :
- Terminer : le processus se termine immediatement,
- Core : le processus se termine immediatement et fait un core dump (un fichier contenant une copie de sa memoire vive et de ses registres qui peut etre analysee par la suite),
- Ignorer : le signal est simplement ignore et le programme poursuit son execution normale,
- Stop : l'execution du processus est suspendu jusqu'a recevoir le signal SIGCONT.

Il est possible de changer l'action par defaut associee a un signal. Toutefois, il est impossible d'intercepter, d'ignorer, de bloquer ou de changer l'action des signaux SIGKILL et SIGSTOP.

**Liste des signaux Linux** :

- 1 - SIGHUP (Terminer) -> Rupture detectee sur le terminal controleur ou mort du processus parent
- 2 - SIGINT (Terminer) -> Interruption du clavier (ctrl-c)
- 3 - SIGQUIT (Terminer) -> Fin du processus, parfois du clavier (ctrl-\)
- 4 - SIGILL (Terminer) -> Instruction illegale
- 5 SIGTRAP (Core) -> Point d'arret rencontre
- 6 - SIGABRT (Core) -> Arret anormal du processus (fonction *abort*)
- 7 - SIGBUS (Terminer) -> Erreur de bus
- 8 - SIGFPE (Core) -> Erreur mathematique virgule flottante
- 9 - SIGKILL (Terminer) -> Fin immediate du processus
- 10 - SIGUSR1 (Terminer) -> Signal utilisateur 1
- 11 SIGSEGV (Core) -> Reference memoire non valide (segfault)
- 12 - SIGUSR2 - (Terminer) -> Reference memoire non valide (segfault)
- 13 - SIGPIPE (Terminer) -> Ecriture dans un tupe (pipe) sans lecteur
- 14 - SIGALRM (Terminer) -> Signal du temporisateur definit par *alarm*
- 15 - SIGTERM (Terminer) -> Signal de fin
- 16 - SIGSTKFLT (Terminer) -> Signal de fin
- 17 - SIGCHLD (Ignorer) -> Processus fils arrete ou termine
- 18 - SIGCONT (Ignorer) -> Continuer processus si arrete
- 19 - SIGSTOP (Stop) -> Suspend le processus
- 20 - SIGSTP (Stop) -> Suspend le processus depuis le terminal (ctrl-z)
- 21 - SIGTTIN (Stop) -> Lecture sur terminal en arriere plan
- 22 - SIGTTOU (Stop) -> Ecriture sur terminal en arriere plan
- 23 - SIGURG (Ignorer) -> Condition urgente sur socket
- 24 - SIGXCPU (Terminer) -> Limite de temps CPU depassee
- 25 - SIGXFSZ (Terminer) -> Limite de taille de fichier depassee
- 26 - SIGVTALRM (Terminer) -> Temporisateur virtuel expire
- 27 - SIGPROF (Terminer) -> Temporisateur virtuel expire
- 28 - SIGWINCH (Ignorer) -> Fenetre redimensionnee
- 29 - SIGIO (Terminer) -> I/O a nouveau possible
- 30 - SIGPWR (Terminer) -> Chute d'alimentation
- 31 - SIGSYS (Terminer) -> Mauvais appel systeme

<br/>

**Envoyer des signaux**

<br/>

Dans les systemes de type Unix, il y a plusieurs mecanismes pour envoyer des signaux aux processus. Tous ces mechanismes font appel a la notion de **groupes de processus**.

**Envoyer un signal depuis le clavier**

Depuis le shell dans notre terminal, il y a trois raccourcis de clavier qui nous permettent d'interrompre tous les processus en avant-plan en cours d'execution :
- **ctrl-c** : envoie SIGINT pour les interrompre,
- ctrl-\ : envoie SIGQUIT pour les tuer,
- **ctrl-z** : envoie SIGTSTP pour les suspendre.

<br/>

**Envoyer des signaux avec la commande kill**

Pour envoyer un autre type de signal depuis notre terminal, il faudra utiliser la commande **kill**. Et ce, meme si le signal en question n'a rien a voir avec la terminaison du processus ! Certains shells possedent leur propre commande kill interne. Ici, nous parlerons uniquement du programme qui se situe dans ```/bin/kill```.

```int kill(pid_t pid, int sig);```

Cet appel systeme fonctionne de la meme maniere que la commande ```/bin/kill``` decrite ci-dessus. Ses parametres sont :
- **pid** : l'identifiant du processus ou du groupe de processus auquel envoyer le signal. On peut ici specifier :
	- un entier positif : le PID d'un processus,
	- un entier negatif : le PGID d'un groupe de processus,
	- 0 : tous les processus dans le groupe du processus appelant,
	- -1 : tous les processus dans le systeme pour lequel le processus appelant a la permission d'envoyer un signal (sauf le processus 1, init)
- **sig** : le signal a envoyer au processus.

Voir man kill : http://manpagesfr.free.fr/man/man2/kill.2.html

<br/>

**Intercepter un signal avec sigaction**

La bibliotheque **<signal.h>** propose deux fonctions pour intercepter un signal : *signal* et *sigaction*. La premiere n'est pas recommandee par souci de portabilite ; nous etudierons donc ici **sigaction** dont voici le prototype :

```int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);```

Ce prototype est quelque peu intimidant, alors expliquons ses parametres assez obscurs :

- **signum** : le signal pour lequel on souhaite changer l'action.
- **act** : un pointeur vers une structure de type *sigaction* qui va permettre entres autres d'indiquer une routine de gestion de signaux.
- **oldact** : un pointeur vers une autre structure de type *sigaction* dans lequel on souhaiterait sauvegarder l'ancien comportement en reaction au signal. Si l'on a pas particulierement besoin de sauvegarder l'ancienne reaction, on peut simplement mettre NULL ici.

<br/>

**Indiquer une routine de gestion de signaux dans la structure sigaction** :

Voir man sigaction : https://man7.org/linux/man-pages/man2/sigaction.2.html

On l'aura compris, "sigaction" c'est le nom de la fonction mais aussi celui du type de structure dont la fonction a besoin pour effectuer sa tache. La variable qui va surtout nous interesser, c'est **sa_handler**. C'est elle qui specifie l'action qui doit etre associee au signal. On peut lui indiquer une de ces trois choses :

- SIG_DFL pour l'action par defaut,
- SIG_IGN pour ignorer le signal,
- un pointeur vers une routine de gestion de signal, c'est a dire une fonction qui se declenchera en reponse a ce signal, qui doit avoir pour prototype **void nom_de_fonction(int signal);**. On remarquera que cette fonction prend en parametres le signal, ce qui veut dire qu'on peut utiliser cette meme routine pour gerer plusieurs signaux differents !

Il faut aussi garder a l'esprit que l'une des autres variables de la structure (sa_sigaction) est incompatible avec **sa_handler** : il ne faut pas les renseigner toutes deux. Il est donc prudent de s'assurer que tous les bits de la structure sont mis a 0 avec une fonction comme *bzero* ou *memset* avant de la remplir.

<br/>

**Securiser une routine de gestion de signaux**

Les signaux sont asynchrones, c'est a dire qu'ils peuvent intervenir a n'importe quel moment dans l'execution de notre programme. Lorsqu'on les intercepte avec une routine de gestion, on ne sait pas ou le programme en est dans son execution. Si la routine accede a une variable que le programme est en train d'utiliser lors de son interruption, les resultats pourraient etre desastreux. De plus, il ne faut pas oublier qu'une routine de gestion de signal peut elle-meme etre interrompue par une autre routine si le processus recoit un autre signal en meme temps !

Les routines de gestion de signaux sont une forme de programmation concurrente.

Or, comme nous l'avons vu dans un article precedent sur les treads et les mutex, la programmation concurrente peut entrainer d'imprevisibles erreurs qui sont extremement difficiles a deboguer. Pour eviter ce genre d'erreurs, nous devons prendre beaucoup de precautions lors de l'elaboration de nos routines de gestion de signaux pour qu'ils soient aussi surs que possible. Dans cette optique, voici quelques recommendations a garder a l'esprit.

1. Garder les routines de gestion aussi simples et courtes que possible
2. Uniquement utiliser des fonctions sures pour signaux asynchrones dans les routines (le man de signal maintient une liste des fonctions sures qui peuvent etre utilisees dans une routine de gestion de signal).
3. Sauvegarder errno et la restaurer
4. Bloquer temporairement tous les signaux lors d'un acces a une donnee partagee entre le programme principal et la routine de gestion
5. Declarer une variable globale partagee avec volatile
6. Declarer un drapeau de type sig_atomic_t

<br/>

**Bloquer un signal en C**

Pour bloquer un signal, on doit tout d'abord l'ajouter a un ensemble de signaux a bloquer. Puis il faudra specifier cet ensemble soit dans la variable *sa_mask* de la structure *sigaction* qu'on fournita a la fonction du meme nom, soit dans la fonction dedieem *sigprocmask*. C'est toujours la bibliotheque **<signal.h>** qui nous fournit les types de variables et les fonctions qu'il nous faut.

Voir l'article pour plus de detail :
https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/

<br/>
<br/>
<br/>

Errno_et_la_gestion_d_erreur <a id="partie_11"></a>
--------------------------------------------------------

Lien de l'article : 
https://www.codequoi.com/errno-et-la-gestion-derreur-en-c/

<br/>

**Qu'est-ce qu'errno ?**

Errno ("error number" ou "code erreur" en francais) est une variable de type entier stocke dans la bibliotheque <errno.h>. Quand un appel systeme echoue, il y place systematiquement son code d'erreur pour expliquer les conditions de son echec. Beaucoup d'autres fonctions des bibliotheques standard font de meme. Le code erreur dans cette variable peut alors etre interprete pour comprendre ce qu'il s'est mal passe.

Au debut d'un programme, errno commence toujours par avoir une valeur de 0, ce qui indique le succes. Par contre, une fois que cette variable est modifiee pour contenir un code d'erreur, elle ne retournera jamais a 0. En effet, aucun appel systeme ou fonction standard ne stocke 0 dans errno. C'est pourquoi sa valeur n'est significative qu'immediatement apres l'echec d'un appel systeme ou d'une fonction standard. C'est a dire apres avoir recu generalement -1 ou NULL en retour de fonction.

Pourtant, certaines fonctions peuvent renvoyer -1 ou NULL en cas de succes ou d'erreur. C'est le cas des fonctions *readdir* et *getpriority*. Il est dans ces cas important de remettre errno a 0 avant l'appel de fonction pour pouvoir verifier si une erreur s'est produite pendant l'appel. Pour lui assigner une valeur, rien de plus simple :
```errno = 0;```

**Afficher l'erreur d'errno**

Il y a deux fonctions qui nous permettent de traduire le code d'erreur numerique contenu dans errno en sa phrase descriptive correspondante pour l'afficher dans notre terminal : *perror* et *strerror*.
