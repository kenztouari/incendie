/*
 * Nom du fichier :noeud.h
 * Date de création : 21/11/2023
 * Description :
 * Forunir des déclarations de fonctions liées aux différentes versions de forêt
 */

#ifndef INCENDIE_NOEUD_H
#define INCENDIE_NOEUD_H

struct Noeud {
    struct Case** foret;  // Pointeur vers le tableau 2D de la forêt
    struct Noeud* suivant; // Pointeur vers le prochain nœud
}Noeud;

/*
 * Description : Cette fonction permet d'ajouter un nœud (une foret ) à la fin de la liste chaînée
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *   - param2 : struct Case** foret
 *
 * Retour : /
 */
void ajouter_version_foret (struct Noeud** tete, struct Case** foret);

/*
 * Description : Cette fonction permet de libérer la liste contenant les anciennes forêts
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *
 * Retour : /
 */
void libererListe(struct Noeud* tete);

/*
 * Description : Cette fonction permet d'accéder à une version de la forêt à une certaine étape
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *   - param2 : int position
 *
 * Retour : foret
 */
struct Case ** obtenir_version_foret(struct Noeud* tete, int position);
#endif //INCENDIE_NOEUD_H
