/*
 * Nom du fichier :noeud.c
 * Date de création : 21/11/2023
 * Description :
 * Forunir des implémentations de fonctions liées aux différentes versions de forêt
 */


#include <stdlib.h>
#include "../include/noeud.h"

// Fonction pour

/*
 * Description : Cette fonction permet d'ajouter un nœud (une foret ) à la fin de la liste chaînée
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *   - param2 : struct Case** foret
 *
 * Retour : /
 */
void ajouter_version_foret (struct Noeud** tete, struct Case** foret) {
    // Créer un nouveau nœud
    struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
    nouveauNoeud->foret = foret;
    nouveauNoeud->suivant = NULL;

    // Si la liste est vide, le nouveau nœud devient la tête de la liste
    if (*tete == NULL) {
        *tete = nouveauNoeud;
        return;
    }
    // Sinon, parcourir la liste jusqu'au dernier nœud
    struct Noeud* dernier = *tete;
    while (dernier->suivant != NULL) {
        dernier =  dernier->suivant;
    }
    // Ajouter le nouveau nœud à la fin
    dernier->suivant = nouveauNoeud;
}

/*
 * Description : Cette fonction permet de libérer la liste contenant les anciennes forêts
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *
 * Retour : /
 */
void libererListe(struct Noeud* tete) {
    while (tete != NULL) {
        struct Noeud* suivant = tete->suivant;
        free(tete->foret); // Libérer la mémoire du tableau 2D de la forêt
        free(tete);        // Libérer la mémoire du nœud
        tete = suivant;
    }
}

/*
 * Description : Cette fonction permet d'accéder à une version de la forêt à une certaine étape
 * Paramètres :
 *   - param1 : struct Noeud** tete
 *   - param2 : int position
 *
 * Retour : foret
 */
struct Case ** obtenir_version_foret(struct Noeud* tete, int position){
// Vérifier si la liste est vide
    if (tete == NULL || position <1) {
        return NULL; // La liste est vide, aucun élément à cette position
    }
    // Parcourir la liste jusqu'à la position souhaitée
    struct Noeud* courant = tete;
    int currentPosition = 1;
    while (courant != NULL && currentPosition < position) {
        courant = courant->suivant;
        currentPosition++;
    }

    // Vérifier si la position demandée est valide
    if (courant == NULL) {
        return NULL; // La position demandée est hors de portée
    }

    // Maintenant, courant pointe vers le nœud à la position souhaitée
    return courant->foret;
}
