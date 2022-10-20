# Atelier 8 - Synchronisation

Il y aura beaucoup de "sleep" aléatoire dans cet atelier afin de simuler des appels serveurs provenant de plusieurs clients.

## Numéro 1

Avec une opération atomique:

Faire une boucle simple de 1 à 1.000 qui crée des goroutines. Comptez tous les nombres qui sont multiples de 3 ou de 5.

## Numéro 2

Avec un mutex:

Écrire une fonction qui écrit la phrase "Goroutine #X" une lettre à la fois (0.1 sec entre chaque lettre), X étant un numéro reçu en paramètre. Ensuite partir 10 goroutines qui attendent un nombre aléatoire de secondes entre 0 et 10 puis appel la fonction d'écriture (donner le numéro de la goroutine en paramètre).

Vous devez voir les 10 phrases bien écrits.

## Numéro 3

Avec un RWMutex:

Créez une variable numérique qui contient un chiffre.

Créez 10 goroutines de lecture. Chacune "regarde" le chiffre durant 2 secondes puis l'affiche dans la console.

Créez aussi 2 goroutines d'écriture. Chacune va modifier le chiffre.

Pour bien voir ce qui se passe, affichez dans la console un message lorsqu'une goroutine "commence" son travail.

## Numéro 4

Comme les sémaphores n'existent pas en Go, vous devez en coder un:

Dans une salle de bain il y a 4 toilettes. 20 étudiants veulent y accéder (arrivent chacun après un temps aléatoire). Chaque étudiant utilise la toilette durant 1 seconde (pas réaliste, mais on ne veut pas regarder le terminal durant 30 minutes). Écrivez en console: le nombre de toilette disponible, quel étudiant attends, quel étudiant attend une toilette, quel étudiant libère sa toilette. Exemple avec 1 toilette:

Étudiant 1 prend une toilette, 0 disponible
Étudiant 2 attends une toilette
Étudiant 1 libère sa toilette, 1 disponible
Étudiant 2 prend une toilette, 0 disponible

Attention, le but n'est pas de faire un "gestionnaire" de toilette, une opération atomique ou un mutex pourrait faire la job. Chaque étudiant est responsable de choisir sa toilette s'il y en a une de disponible. Si possible garder l'ordre d'arrivé, mais ce n'est pas essentiel.