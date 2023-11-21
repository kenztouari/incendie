//
// Created by Touari on 14/11/2023.
//

#include <stdbool.h>
#include "../include/point.h"

// fonction qui vérifie si une position (x,y) est valide ( eviter les out of range)
bool position_valide(int x, int y, int i, int j) {
    return x >= 0 && x < i && y >= 0 && y < j;
}