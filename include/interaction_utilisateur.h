/*
 * Nom du fichier :interaction_utilisateur.h
 * Date de création : 14/11/2023
 * Description :
 * Fournir des déclarations de fonctions pour interagir avec l'utilisateur dans le contexte d'un programme lié à un feu de forêt
 */

#include "case.h"

#ifndef INCENDIE_INTERACTION_UTILISATEUR_H
#define INCENDIE_INTERACTION_UTILISATEUR_H

/*
 * Description : Cette fonction permet de demander les dimensions de la forêt au joueur
 * Paramètres :
 *   - param1 : int i
 *   - param2 : int j
 * Retour : /
 */
void saisir_dimensions(int *i, int *j);

/*
 * Description : Cette fonction permet de demander à l'utilisateur de choisir entre les modes de remplissage de la matrice forêt
 * Paramètres :
 *   - param1 : Case ** foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
void saisie_choix(Case **foret,int i, int j);

/*
 * Description : Cette fonction permet de demander à l'utilisateur le nombre d'itérations qu'il souhaite réaliser tant que la saisie n'est pas conforme
 * Retour : nb_itérations
 */
int demander_nb_iterations();

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
void demander_coordonnees_depart(int i, int j, Case **foret, int *x, int *y);

/*
 * Description : Cette fonction permet à l'utilisateur de contrôler la propagation du feu entre les différentes étapes.
 * Retour : /
 */
void commencer_simulation();

/*
 * Description :  Cette fonction permet à l'utilisateur de contrôler la poursuite des itérations
 * Paramètres :
 *   - param1 : Case ** foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
char poursuivre_iteration();

#endif //INCENDIE_INTERACTION_UTILISATEUR_H
