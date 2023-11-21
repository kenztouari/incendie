

#include <stdlib.h>
#include <time.h>
#include "include/case.h"
#include "include/interaction_utilisateur.h"
#include "include/simulation.h"

int main() {
    srand (time (NULL)); // Initialisation du générateur de nombres aléatoires

    // demande des dimensions de la forêt à l'utilisateur
    int i, j;
    saisir_dimensions (&i, &j);

    // allocation de mémoire en fonction des saisies
    Case **foret = creer_foret (i, j);

    // Demander à l'utilisateur de choisir le mode de remplissage
    saisie_choix(foret,i, j);

    // Affichage de la forêt une fois créée
    afficher_foret (foret, i, j);

    // Lancement de la simulation
    simulation (foret, i, j);

    // Fin du programme
    return 0;

}
