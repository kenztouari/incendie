//
// Created by Touari on 14/11/2023.
//

#ifndef INCENDIE_CASE_H
#define INCENDIE_CASE_H

#include <stdbool.h>

//définition des structures utilisées
typedef struct _case {
    int x;
    int y;
    int type;
    bool cendre;
    bool cendre_eteinte;
    int deg;
    bool feu;
    char symbole;
}Case;

typedef struct {
    int type;
    int deg;
    char symbole;
} AssocTypeDegSymbole;

Case **creer_foret(int i, int j);
void association_type_deg_symbole(Case **foret, int x, int y);
void afficher_foret(Case **foret, int i, int j);
void brule_case_depart(Case **foret, int i, int j, int x, int y);
void changement_type_case(Case **foret, int x, int y);
void brule_cases_autour(Case **foret, int i, int j, int x, int y);
bool is_propagation_possible(Case **foret, int x, int y, int i, int j);
void remplissage_aleatoire(Case **foret, int i, int j);
void remplissage_manuel(Case **foret, int i, int j);

#endif //INCENDIE_CASE_H
