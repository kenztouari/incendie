/*
 * Nom du fichier : case.c
 * Date de création : 14/11/2023
 * Description :
 * Implémenter des fonctions liées à la forêt et à ses cases
 */

#include <stdlib.h>
#include <printf.h>
#include "../include/case.h"
#include "../include/global.h"
#include "../include/point.h"

/*
 * Description : Cette fonction permet de créer la foret
 * Paramètres :
 *   - param1 : int i
 *   - param2 : int j
 * Retour : Case **foret
 */
Case **creer_foret(int i, int j) {
    Case **foret = malloc (i * sizeof (Case *));
    for (int u = 0; u < i; u++) {
        foret[u] = malloc (j * sizeof (Case));
    }
    return foret;
}

/*
 * Description : Cette fonction permet d'afficher la foret'
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
void afficher_foret(Case **foret, int i, int j) {
    for (int k = 0; k < j; k++) {
        for (int u = 0; u < i; u++) {
            printf (" %c ", foret[u][k].symbole);
        }
        printf ("\n");
    }
}

/*
 * Description : Cette fonction permet de changer le type de case
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int x
 *   - param3 : int y
 * Retour : /
 */
void changement_type_case(Case **foret, int x, int y) {
    switch (foret[x][y].deg) {
        case 1:
            foret[x][y].symbole = '-';
            break;
        case 0:
            foret[x][y].symbole = '@';
            break;
        default:
            // Gérer le cas par défaut si nécessaire
            break;
    }
}

/*
 * Description : Cette fonction permet de changer l'état de la première case à brûler
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 *   - param3 : int x
 *   - param4 : int y
 *
 * Retour : /
 */
void brule_case_depart(Case **foret, int i, int j, int x, int y) {
    // Vérifier si les coordonnées sont valides
    if (x < 0 || x >= i || y < 0 || y >= j) {
        printf ("Coordonnees invalides.\n");
        return;
    }
    // Passer l'état à feu et réduit le degré si ce n'est pas déjà en cendres éteintes
    foret[x][y].feu = true;
    foret[x][y].deg--;

    // Appeler  la fonction changement_type_case
    changement_type_case (foret, x, y);
}


/*
 * Description : Cette fonction permet de changer l'état des cases autour de la case de départ
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 *   - param3 : int x
 *   - param4 : int y
 *
 * Retour : /
 */
void brule_cases_autour(Case **foret, int i, int j, int x, int y) {
    for (int u = -1; u <= 1; u++) {
        for (int v = -1; v <= 1; v++) {
            int new_x = x + u;
            int new_y = y + v;
            // Vérifier si les nouvelles coordonnées sont valides
            if (new_x >= 0 && new_x < i && new_y >= 0 && new_y < j) {
                // Vérifier si la case n'est pas déjà en cendres éteintes et n'est pas de type sol (4) ou eau (6)
                if (foret[new_x][new_y].type != 8 && foret[new_x][new_y].type != 4 && foret[new_x][new_y].type != 6) {
                    // Réduire le degré de la case
                    if (foret[new_x][new_y].deg > 0) {
                        foret[new_x][new_y].deg--;
                    }
                    if (foret[new_x][new_y].deg == 1 ){
                        foret[new_x][new_y].type = 7;
                        foret[new_x][new_y].symbole = '-';
                    }
                    // Si le degré atteint zéro, la case devient des cendres éteintes
                    if (foret[new_x][new_y].deg == 0) {
                        foret[new_x][new_y].type = 8;
                        foret[new_x][new_y].symbole = '@';
                    }
                }
            }
        }
    }
}

/*
 * Description : Cette fonction permet d'associer un type à degré  et à un symbole
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int x
 *   - param3 : int y
 *
 * Retour : /
 */
void association_type_deg_symbole(Case **foret, int x, int y) {
    AssocTypeDegSymbole associations[] = {
            {1, DEG_ARBRE, '*'},
            {2, DEG_FEUILLE, ' '},
            {3, DEG_ROCHE, '#'},
            {4, DEG_SOL, '+'},
            {5, DEG_HERBE, 'x'},
            {6, DEG_EAU, '/'},
            {7, DEG_CENDRE, '-'},
            {8, DEG_CENDRE_ETEINTE, '@'}
    };

    int type = foret[x][y].type;

    for (size_t i = 0; i < sizeof(associations) / sizeof(associations[0]); ++i) {
        if (associations[i].type == type) {
            foret[x][y].deg = associations[i].deg;
            foret[x][y].symbole = associations[i].symbole;
            return;
        }
    }
}

/*
 * Description : Cette fonction permet de vérifier si la propagation du feu est possible aux coordonnées x,y
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int x
 *   - param3 : int y
 *   - param4 : int i
 *   - param5 : int j
 *
 * Retour : booléen
 */
bool is_propagation_possible(Case **foret, int x, int y, int i, int j) {
    if (!position_valide (x, y, i, j) || foret[x][y].type == 6 || foret[x][y].type == 4) {
        return false;
    } else if (foret[x][y].deg == 1) {
        return true;
    } else if (foret[x][y].type == 2 || foret[x][y].type == 3 || foret[x][y].type == 1 || foret[x][y].type == 5) {
        return true;
    }
    return false;
}

/*
 * Description : Cette fonction permet de réaliser un remplissage aléatoire de la matrice forêt
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 *
 * Retour : /
 */
void remplissage_aleatoire(Case **foret, int i, int j) {
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            foret[x][y].x = x;
            foret[x][y].y = y;
            foret[x][y].type = 1 + rand () % 7; // Génère un nombre entre 1 et 6 (inclus)
            foret[x][y].feu = false;
            // ligne permettant de faire l'analogie entre les chiffres tirés par le random et les symboles
            association_type_deg_symbole (foret, x, y);
        }
    }
}

/*
 * Description : Cette fonction permet de réaliser un remplissage manuel de la matrice forêt
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int  j
 *
 * Retour : /
 */
void remplissage_manuel(Case **foret, int i, int j) {
    for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
            getchar (); // Nettoyer le tampon d'entrée
            printf ("Rentrer le symbole pour la case %d %d : ", k, l);
            scanf ("%c", &foret[k][l].symbole);
            // Initialise le degré et le symbole
            association_type_deg_symbole (foret, k, l);
            switch (foret[k][l].symbole) {
                case '*':
                    foret[k][l].type = 1;
                    break;
                case ' ':
                    foret[k][l].type = 2;
                    break;
                case '#':
                    foret[k][l].type = 3;
                    break;
                case '+':
                    foret[k][l].type = 4;
                    break;
                case 'x':
                    foret[k][l].type = 5;
                    break;
                case '/':
                    foret[k][l].type = 6;
                    break;
                case '-':
                    foret[k][l].type = 7;
                    break;
                default:
                    printf ("Symbole non reconnu. Utilisez l'un des symboles suivants : *,  , #, +, x, /, -.\n");
                    l--; // Permet de répéter la saisie pour la même case
            }
        }
    }
}