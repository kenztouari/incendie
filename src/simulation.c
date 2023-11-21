/*
 * Nom du fichier :simulation.c
 * Date de création : 14/11/2023
 * Description :
 * Fournir une implémentation des fonctions liées à la simulation d'un incendie de forêt en utilisant des concepts de graphes et de chemins les plus
 * courts
 */

#include <printf.h>
#include "../include/simulation.h"
#include "../include/interaction_utilisateur.h"
#include "../include/point.h"

/*
 * Description : Cette fonction permet de réaliser les étapes de la simulation
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : int i
 *   - param3 : int j
 * Retour : /
 */
void simulation(Case **foret, int i, int j) {
    // coordonnées de position
    int x, y;

    // récupérer le nombre d'itérations souhaité par l'utilisateur
    int nb_iteration = demander_nb_iterations ();

    // récupérer les coordonées de la case de départ du feu
    demander_coordonnees_depart (i, j, foret, &x, &y);

    // bruler la case de départ
    brule_case_depart (foret, i, j, x, y);

    // affichage de la foret après que la première case ait brulé
    afficher_foret (foret, i, j);

    commencer_simulation();



    // poursuite de l'itération en fonction de la saisie de l'utilisateur
    for (int cmp = 0; cmp < nb_iteration-1; cmp++) {
        poursuivre_iteration();
        brule_cases_autour (foret, i, j, x, y);
        afficher_foret (foret, i, j);
    }

}

/*
 * Description : Cette fonction permet de trouver le chemin le plus court d'un point de départ à un point d'arrivée
 * Paramètres :
 *   - param1 : Case **foret
 *   - param2 : Point start
 *   - param3 : Point end
 *   - param4 : int i
 *   - param5 : int j
 * Retour : distance la plus courte
 */
int  chemin_le_plus_court(Case **foret, Point start, Point end, int i, int j) {
    // Tableau pour suivre les cellules visitées ( aucune cellule visitée pour le moment)
    bool visitee[i][j];
    for (int k = 0; k < i; k++) {
        for (int u = 0; u < j; u++) {
            visitee[k][u] = false;
        }
    }
    // Tableau pour stocker la distance de chaque cellule à la cellule de départ ( aucune distance stockée pour le moment )
    int distance[i][j];
    for (int k = 0; k < i; k++) {
        for (int u = 0; u < j; u++) {
            distance[k][u] = 0;
            // Décalages pour explorer les voisins (les 8 directions possibles)
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            // File pour stocker les cellules à explorer
            Point queue[i * j];
            int front = 0, rear = 0;
            // Ajouter le point de départ à la file et le marquer comme visité
            queue[rear++] = start;
            visitee[start.x][start.y] = true;

            // Parcours BFS de la forêt
            while (front != rear) {
                // Prendre le prochain point dans la file
                Point current = queue[front++];
                // Si le point actuel est le point final recherché, renvoyer la distance
                if (current.x == end.x && current.y == end.y) {
                    return distance[current.x][current.y];
                }
                // Parcourir les 8 directions possibles pour les voisins
                for (int positions = 0; positions < 8; positions++) {
                    int new_x = current.x + dx[positions];
                    int new_y = current.y + dy[positions];
                    // Vérifier si le voisin est valide et peut propager le feu, et s'il n'a pas été visité
                    if (is_propagation_possible(foret, new_x, new_y, i, j) && is_propagation_possible(foret, new_x, new_y, i, j) &&
                        !visitee[new_x][new_y]) {
                        // Marquer le voisin comme visité et mettez à jour sa distance
                        visitee[new_x][new_y] = true;
                        distance[new_x][new_y] = distance[current.x][current.y] + 1;
                        // Ajouter le voisin à la file pour l'exploration ultérieure
                        queue[rear++] = (Point) {new_x, new_y};
                    }
                }
            }
            return -1;
        }
    }

}
