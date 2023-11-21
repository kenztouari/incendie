//
// Created by Touari on 14/11/2023.
//

#ifndef INCENDIE_ETATFORET_H
#define INCENDIE_ETATFORET_H
#include "case.h"
// structure permettant de suivre l'état de la foret au fur et à mesure
typedef struct _etatForet {
    Case **foret;
    struct EtatForet *suivant;
} EtatForet;

#endif //INCENDIE_ETATFORET_H
