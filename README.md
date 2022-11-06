# miniGlibC

Exercice5:
Il faut initialiser le buffer avec des '\0' avant de le renvoyer parce que sinon, des résidus de données peuvent être présentes dans la zone mémoire allouée. Et si on essaie de lire une zone mémoire qui contient des résidus, on obtient une erreur "undefined behavior"

Exercie6:
La fonction free empêche d'accéder à l'espace mémoire dont l'adresse est passée en paramètre.
Elle ne "libère" pas vraiment la mémoire. Donc les données qui étaient stockées sont conservées mais non accessibles.

Exercice12:
Pour tester mini_calloc et mini_free dans le main.c, j'ai alloué

Exercice17:
Le problème qu'il reste à régler est que lorsque la chaine ne comporte pas de retour à la ligne, elle n'est pas affichée. Elle reste stockée dans le buffer. Il faut donc vider le buffer avant de sortir(exit) de la fonction.

Exercice20:
Si le nombre de caractères lus est égal à la taille du buffer, ce qui se passe, c'est que le retour à la ligne est stockée sur l'entrée standard, et est exécuté comme une commande système.


Exercice22: Les problèmes de sécurité
Pour la fonction mini_strlen(), si le pointeur s vaut NULL, on ne peut pas calculer la taille

Pour la fonction mini_strcpy(), on a le même problème. Si l'un des pointeurs vaut NULL, on ne peut rien faire.
De plus, si la taille de la chaine d est plus petite que celle de s, on risque de causer un buffer overflow; c'est à dire que la fonction va écrire les caractères débordants dans des cases mémoires qui n'appartiennent pas à la chaine d.
Pour régler ce problème, il faut copier au maximum taille de d caractères.
On a un 3ème problème: si la chaine d était préalablement remplie, la copie génère une segmentation fault

Pour la fonction mini_strcmp(), si l'une des chaînes vaut NULL, on ne peut pas comparer

Exercice34:
Si le programme se termine alors que le buffer d'écriture n'était pas plein, alors le contenu du buffer n'est pas écrit dans le fichier.
Pour corriger ce problème, il faut flusher tous les fichiers ouverts avant le exit du programme.
