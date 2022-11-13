# miniGlibC
<h3>Projet 3A STI INSA CVL 11/2022</h3>

<ul>
<li>Implémentation de quelques fonctions de la glibc</li>
<li>Implémentation de quelques commandes sytèmes</li>
<li>Simulation d'un mini-shell qui peut gérer l'historique et l'autocomplétion</li>
</ul>

# Exécution
<p>Le projet comporte un makefile qui permet de générer 2 principaux exécutables:</p>
<ul>
<li>./unitTesting: qui permet de tester les fonctions implémentées</li>
<li>./mini_shell: qui démarre le mini_shell implémenté</li>
</ul>


<p>Pour générer les exécutables, exécuter la commande <strong>make</strong> dans le dossier du projet.</p>
<p><strong>NB: </strong>Grâce à la librairie <strong>readline</strong>, j'ai pu ajouter la gestion de l'historique dans mon mini_shell, ainsi que l'autocomplétion via la touche <strong>tabulation</strong>.<br>
Cette librairie est installée automatiquement par le <strong>makefile</strong>.<br>
Si pour une raison ou une autre l'installation de la librairie échoue, ou si vous ne voulez pas l'utiliser, veuillez mettre en commentaire la ligne #define READLINE_INSTALLED dans le fichier header mini_lib.h</p>
<p>La commande <strong>make mr_proper</strong> permet de supprimer tous les exécutables et tous les fichiers objet générés.
<br>De plus, le dossier comporte quelques fichiers textes utiles au programme de test unitTesting</p>

# Commentaires
<p>Toutes mes fonctions et programment fonctionnent parfaitement.J'ai implémenté d'autres fonctions non demandées notamment dans mini_string.c : <strong>mini_strcat(), mini_strrchr(), mini_itoa()</strong>, etc.<br>
J'ai amélioré l'implémentation des commandes sytèmes pour qu'elles aient le même comportement que les vraies commandes de base.
Par exemple,le mini_head peut prendre n'importe quel nombre de fichiers en paramètres; il s'utilise avec l'option -n.
Exemple d'utilisation: <strong>./mini_head file1 file2 -n 3 file4</strong>.<br>
Quand aucun argument n'est passé à la commande mini_head, elle <strong>lit l'entrée standard </strong>comme le fait la vraie fonction.<br>
De plus, j'ai redirigé les vraies commandes sytème (head, tail, echo, ...) vers leur équivalent (mini_head, mini_tail, mini_echo,...).<br>
</p>

# Réponses aux questions
<h4>Exercice5: Initialisation buffer</h4>
<p>Il faut initialiser le buffer avec des '\0' avant de le renvoyer parce que sinon, des résidus de données peuvent être présentes dans la zone mémoire allouée. Cela peut générer des erreurs si on essaie de lire ces résidus.</p>

<h4>Exercie6: Rôle de la fonction <strong>free()</strong></h4>
<p>La fonction free libère l'espace mémoire dont l'adresse est passée en paramètre. Elle autorise le noyau à allouer cette zone mémoire à une autre variable ou fonction.
Elle ne "libère" pas vraiment la mémoire car les données qui étaient stockées sont conservées.</p>

<h4>Exercice12: Solution de test de <strong>mini_calloc() et mini_free()</strong></h4> 
<p>Pour tester mini_calloc et mini_free dans le main.c, j'ai alloué plusieurs zones mémoires de type int et char. A l'aide de la fonction <strong>void memory_print()</strong>, j'affiche les éléments de la liste de zones mémoires, et leur statut.
Cf fonction de test <strong>void memory_allocation_test()</strong>
</p>

<h4>Exercice17: Problème mini_printf()</h4>
<p>Le problème qu'il reste à régler est que lorsque la chaine ne comporte pas de retour à la ligne et n'atteint pas la taille du buffer, elle n'est pas affichée. Elle reste stockée dans le buffer. Il faut donc vider le buffer avant de sortir(exit) de la fonction.</p>

<h4>Exercice20: Problème mini_scanf</h4>
<p>Si le nombre de caractères lus est supérieur égal à la taille du buffer, ce qui se passe, c'est que le reste de la chaine entrée est stockée sur l'entrée standard, et est exécuté comme une commande système.
Pour éviter ce problème, je vide le buffer de stdin avec la fonction <strong>getchar()</strong> après l'appel à <strong>mini_scanf()</strong>.</p>


<h4>Exercice22: Les problèmes de sécurité dans <strong>mini_string.c</strong></h4>
<ul>
<li><p>Pour la fonction <strong>mini_strlen()</strong>, si le pointeur s vaut NULL, on ne peut pas calculer la taille.</p></li>

<li><p>Pour la fonction <strong>mini_strcpy()</strong>, on a le même problème. Si l'un des pointeurs vaut NULL ou (void*)-1, on ne peut rien faire.
De plus, si la taille de la chaine d est plus petite que celle de s, on risque de causer un buffer overflow; c'est à dire que la fonction va écrire les caractères débordants dans des cases mémoires qui n'appartiennent pas à la chaine d.
Pour régler ce problème, il faut copier au maximum taille de d caractères.
On a un 3ème problème: si la chaine d était préalablement remplie, la copie génère une segmentation fault.</p>
</li>
<li>Pour la fonction <strong>mini_strcmp()</strong>, si l'une des chaînes vaut NULL, on ne peut pas comparer.</li>
</ul>

<h4>Exercice34: Problème buffer d'écriture de mini_fwrite</h4>
<p>Si le programme se termine alors que le buffer d'écriture n'était pas plein, alors le contenu du buffer n'est pas écrit dans le fichier.
Pour corriger ce problème, il faut flusher tous les fichiers ouverts avant le exit du programme.</p>