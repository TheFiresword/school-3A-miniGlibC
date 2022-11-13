PS: Lire le fichier README.md qui est mieux présenté


miniGlibC
Projet 3A STI INSA CVL 11/2022

    Implémentation de quelques fonctions de la glibc
    Implémentation de quelques commandes sytèmes
    Simulation d'un mini-shell qui peut gérer l'historique et l'autocomplétion

Exécution

Le projet comporte un makefile qui permet de générer 2 principaux exécutables:

    ./unitTesting: qui permet de tester les fonctions implémentées
    ./mini_shell: qui démarre le mini_shell implémenté

Pour générer les exécutables, exécuter la commande make dans le dossier du projet.

NB: Grâce à la librairie readline, j'ai pu ajouter la gestion de l'historique dans mon mini_shell, ainsi que l'autocomplétion via la touche tabulation.
Cette librairie est installée automatiquement par le makefile.
Si pour une raison ou une autre l'installation de la librairie échoue, ou si vous ne voulez pas l'utiliser, veuillez mettre en commentaire la ligne #define READLINE_INSTALLED dans le fichier header mini_lib.h

La commande make mr_proper permet de supprimer tous les exécutables et tous les fichiers objet générés.
De plus, le dossier comporte quelques fichiers textes utiles au programme de test unitTesting
Commentaires

Toutes mes fonctions et programment fonctionnent parfaitement.J'ai implémenté d'autres fonctions non demandées notamment dans mini_string.c : mini_strcat(), mini_strrchr(), mini_itoa(), etc.
J'ai amélioré l'implémentation des commandes sytèmes pour qu'elles aient le même comportement que les vraies commandes de base. Par exemple,le mini_head peut prendre n'importe quel nombre de fichiers en paramètres; il s'utilise avec l'option -n. Exemple d'utilisation: ./mini_head file1 file2 -n 3 file4.
Quand aucun argument n'est passé à la commande mini_head, elle lit l'entrée standard comme le fait la vraie fonction.
De plus, j'ai redirigé les vraies commandes sytème (head, tail, echo, ...) vers leur équivalent (mini_head, mini_tail, mini_echo,...).
Réponses aux questions
Exercice5: Initialisation buffer

Il faut initialiser le buffer avec des '\0' avant de le renvoyer parce que sinon, des résidus de données peuvent être présentes dans la zone mémoire allouée. Cela peut générer des erreurs si on essaie de lire ces résidus.
Exercie6: Rôle de la fonction free()

La fonction free libère l'espace mémoire dont l'adresse est passée en paramètre. Elle autorise le noyau à allouer cette zone mémoire à une autre variable ou fonction. Elle ne "libère" pas vraiment la mémoire car les données qui étaient stockées sont conservées.
Exercice12: Solution de test de mini_calloc() et mini_free()

Pour tester mini_calloc et mini_free dans le main.c, j'ai alloué plusieurs zones mémoires de type int et char. A l'aide de la fonction void memory_print(), j'affiche les éléments de la liste de zones mémoires, et leur statut. Cf fonction de test void memory_allocation_test()
Exercice17: Problème mini_printf()

Le problème qu'il reste à régler est que lorsque la chaine ne comporte pas de retour à la ligne et n'atteint pas la taille du buffer, elle n'est pas affichée. Elle reste stockée dans le buffer. Il faut donc vider le buffer avant de sortir(exit) de la fonction.
Exercice20: Problème mini_scanf

Si le nombre de caractères lus est supérieur égal à la taille du buffer, ce qui se passe, c'est que le reste de la chaine entrée est stockée sur l'entrée standard, et est exécuté comme une commande système. Pour éviter ce problème, je vide le buffer de stdin avec la fonction getchar() après l'appel à mini_scanf().
Exercice22: Les problèmes de sécurité dans mini_string.c

    Pour la fonction mini_strlen(), si le pointeur s vaut NULL, on ne peut pas calculer la taille.

    Pour la fonction mini_strcpy(), on a le même problème. Si l'un des pointeurs vaut NULL ou (void*)-1, on ne peut rien faire. De plus, si la taille de la chaine d est plus petite que celle de s, on risque de causer un buffer overflow; c'est à dire que la fonction va écrire les caractères débordants dans des cases mémoires qui n'appartiennent pas à la chaine d. Pour régler ce problème, il faut copier au maximum taille de d caractères. On a un 3ème problème: si la chaine d était préalablement remplie, la copie génère une segmentation fault.
    Pour la fonction mini_strcmp(), si l'une des chaînes vaut NULL, on ne peut pas comparer.

Exercice34: Problème buffer d'écriture de mini_fwrite

Si le programme se termine alors que le buffer d'écriture n'était pas plein, alors le contenu du buffer n'est pas écrit dans le fichier. Pour corriger ce problème, il faut flusher tous les fichiers ouverts avant le exit du programme.