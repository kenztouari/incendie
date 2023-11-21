/*
 * Nom du fichier :interaction_utilisateur.c
 * Date de création : 14/11/2023
 * Description :
 * Fournir des implémentations de fonctions pour interagir avec l'utilisateur dans le contexte d'un programme lié à un feu de forêt
 */

#include <printf.h>
#include <stdlib.h>
#include "../include/interaction_utilisateur.h"


/*
 * Description : Cette fonction permet de demander les dimensions de la forêt au joueur
 * Paramètres :
 *   - param1 : int i
 *   - param2 : int j
 * Retour : /
 */
void saisir_dimensions(int *i, int *j) {
    printf ("Rentrer i: ");
    scanf("%d", i);
    printf ("Rentrer j: ");
    scanf ("%d", j);
}


/*
 * Description : Cette fonction permet de demander à l'utilisateur de choisir entre les modes de remplissage de la matrice forêt
 * Paramètres :
 *   - param1 : Case ** foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
void saisie_choix(Case **foret,int i, int j){
    int choix;
    printf ("Choisir le mode de remplissage (1 pour manuel, 2 pour aléatoire): ");
    scanf ("%d", &choix);

    if (choix == 1) {
        // Remplissage manuel de la forêt
        remplissage_manuel (foret, i, j);
    } else if (choix == 2) {
        // Remplissage aléatoire de la forêt
        remplissage_aleatoire (foret, i, j);
    } else {
        printf ("Choix non valide. Utilisez 1 pour manuel, 2 pour aléatoire.\n");
        return ; // Quitter le programme en cas de choix invalide
    }
}

/*
 * Description : Cette fonction permet de demander à l'utilisateur le nombre d'itérations qu'il souhaite réaliser tant que la saisie n'est pas conforme
 * Retour : nb_itérations
 */
int demander_nb_iterations() {
    int nb_iteration;
    do {
        printf ("Choisir le nombre d'iteration (positif ): ");
        scanf ("%d", &nb_iteration);
    } while (nb_iteration <= 0);
    return nb_iteration;
}

/*
 * Description : Cette fonction permet de demander à les coordonnées de départ du feu
 * Paramètres :
 *   - param1 : int i
 *   - param2 : int j
 *   - param3 : int Case **foret
 *   - param4 : int *x
 *   - param5 : int *y
 * Retour : /
 */

void demander_coordonnees_depart(BITMAP * page, BITMAP * decor,int i, int j, Case **foret, int *x, int *y) {
    do {
        printf ("Choisir la case de depart du feu (x y): ");
        scanf ("%d %d", x, y);
    } while (*x < 0 || *x >= i || *y < 0 || *y >= j || foret[*x][*y].type == 4 || foret[*x][*y].type == 6);
}

/*
 * Description : Cette fonction permet à l'utilisateur de contrôler la propagation du feu entre les différentes étapes.
 * Retour : /
 */
void commencer_simulation() {
    char s;
    printf ("Appuyer sur s pour commencer la simulation: ");

    while (1) {
        scanf (" %c", &s);  // Notez l'espace avant %c pour ignorer les espaces, tabulations, etc.

        // Consommer tous les caractères restants dans le tampon
        while (getchar () != '\n');


        if (s == 's') {
            return;
        }
        printf ("Appuyer sur s pour commencer la simulation: ");
    }
}

/*
 * Description :  Cette fonction permet à l'utilisateur de contrôler la poursuite des itérations
 * Paramètres :
 *   - param1 : Case ** foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
void poursuivre_iteration(){
    char resp;
    do {
        printf ("Appuyer sur i pour avancer d'une iteration: ");
        scanf ("%c", &resp);
        getchar ();
    } while (resp != 'i');
}
