/*
 * Nom du fichier :simulation.c
 * Date de création : 14/11/2023
 * Description :
 * Forunir des déclarations de fonctions liées à la simulation d'un incendie de forêt en utilisant des concepts de graphes et
 * de chemins les plus courts
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvisibility"
#ifndef INCENDIE_SIMULATION_H
#define INCENDIE_SIMULATION_H

#include "case.h"

/*
 * Description : Cette fonction permet de réaliser les étapes de la simulation
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 *   - param 4 : struct Noeud *tete
 * Retour : /
 */
void simulation(Case **foret, int i, int j, struct Noeud *tete);
#endif //INCENDIE_SIMULATION_H

#pragma clang diagnostic pop