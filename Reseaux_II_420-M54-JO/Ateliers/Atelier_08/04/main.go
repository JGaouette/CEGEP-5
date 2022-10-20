//Numéro 4
//Comme les sémaphores n'existent pas en Go, vous devez en coder un:
//
//Dans une salle de bain il y a 4 toilettes. 20 étudiants veulent y accéder
//(arrivent chacun après un temps aléatoire).
//Chaque étudiant utilise la toilette durant 1 seconde
//(pas réaliste, mais on ne veut pas regarder le terminal durant 30 minutes).
//Écrivez en console: le nombre de toilette disponible, quel étudiant attends,
//quel étudiant attend une toilette, quel étudiant libère sa toilette. Exemple avec 1 toilette:
//
//Étudiant 1 prend une toilette, 0 disponible Étudiant 2 attends une toilette
//Étudiant 1 libère sa toilette, 1 disponible Étudiant 2 prend une toilette, 0 disponible
//
//Attention, le but n'est pas de faire un "gestionnaire" de toilette,
//une opération atomique ou un mutex pourrait faire la job.
//Chaque étudiant est responsable de choisir sa toilette s'il y en a une de disponible.
//Si possible garder l'ordre d'arrivé, mais ce n'est pas essentiel.

package main

func main() {

}
