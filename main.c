#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <allegro.h>
#include <math.h>


typedef struct _case {
    int x;
    int y;
    int type;
    bool cendre;
    bool cendre_eteinte;
    int deg;
    bool feu;
    char symbole;
} Case;

typedef struct EtatForet {
    Case** foret;
    struct EtatForet* suivant;
}EtatForet;

typedef struct _point {
    int x;
    int y;
} Point;

void deg (Case** foret, int x, int y);
void brule(Case** foret, int i, int j, int x, int y);
bool position_valide(int x, int y, int i, int j);
void init(Case** foret, int i, int j);
int chemin_le_plus_court(Case** foret, Point start, Point end, int i, int j);
bool position_valide(int x, int y, int i, int j);
void affichage (Case** foret, int i, int j);
bool is_valid(int *x, int *y, int xp, int yp, int i, int j);
void choisir_case_depart(BITMAP * page, BITMAP * decor, int i, int j, Case** foret);
void feu_animation(Case** foret, int i, int j, BITMAP * decor, BITMAP * page);
void simulation (Case** foret, int i, int j, int nb_it, BITMAP* page, BITMAP* decor);


// On d�finit des variables globales pour le degr� initiale de chaque type
#define DEG_ARBRE 7
#define DEG_FEUILLE 6
#define DEG_ROCHE 5
#define DEG_SOL 4
#define DEG_HERBE 3
#define DEG_EAU 2
#define DEG_CENDRE 1
#define DEG_CENDRE_ETEINTE 0



int main() {
    initialisation();
    srand(time(NULL)); // Initialisation du g�n�rateur de nombres al�atoires
    int i, j = 0;
    menuprincipal(&i, &j);



    //simulation(foret, i, j);
    return 0;
} END_OF_MAIN()




        void initialisation()
{
    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen); // pour voir le pointeur de la souris

}


void menuprincipal()
{
    int W=275;
    int H=65;
    int EPAISSEUR=3;


    BITMAP * buffer = create_bitmap(1280,720);
    BITMAP*buffer1=create_bitmap(1280, 720);
    BITMAP*buffer2=create_bitmap(1280, 720);
    BITMAP*buffer3=create_bitmap(1280, 720);
    BITMAP * decor;
    BITMAP * page = create_bitmap(1312,656);

    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran


    BITMAP*buf=load_bitmap(".\\photos\\logo_menu.bmp",NULL);
    buffer=load_bitmap(".\\photos\\menu_screen.bmp",NULL);
    buffer1=load_bitmap(".\\photos\\menu_screen.bmp",NULL);
    buffer2=load_bitmap(".\\photos\\menu_screen.bmp",NULL);
    buffer3=load_bitmap(".\\photos\\menu_screen.bmp",NULL);
    decor=load_bitmap(".\\photos\\fond_2.bmp",NULL);

    install_mouse();
    if(install_keyboard() == -1)
    {
        // Initialisation du clavier
        printf("Error install_keyboard()");
        exit(EXIT_FAILURE);
    }
    if(install_mouse() == -1)
    {
        // Initialisation de la souris
        printf("Error install_mouse()");
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    char boutons[3][20] = { "Nouvelle partie", "Regles du jeu", "Quitter le jeu"};

    // Boucle de dessin
    while(!key[KEY_ESC])
    {
        draw_sprite(buffer, buf, 380, 25);

        for (int i = 0; i < 3; i++)
        {
            int y = 300 + i * (H + 50); // Calcul de la position Y
            // Dessin du bouton
            rectfill(buffer, SCREEN_W/2-W/2, y-H/8, SCREEN_W/2+W/2, y+H/2, makecol(255,255,255));

            // Dessin de la bordure
            for (int k = 0; k < EPAISSEUR; k++)
            {
                rect(buffer, SCREEN_W/2-W/2-k, y-H/8-k, SCREEN_W/2+W/2+k, y+H/2+k, 0);
            }

            int textW = text_length(font, boutons[i]);
            // Dessin du texte du bouton
            textprintf_ex(buffer, font, SCREEN_W/2-textW/2, y+8, 0, -1, "%s", boutons[i]);

            if(mouse_b & 1 && mouse_x>=500 && mouse_x <= 900 && mouse_y >= 280 && mouse_y <= 340)// zone de la case � cliquer
            {
                while(!key[KEY_ESC])
                {
                    blit(buffer1, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

                    textout_centre_ex(buffer1, font, "CHOISISSEZ LE MODE DE JEU", 450, 120, makecol(0,0,0),-1);
/*                   circle(buffer1,350,400,60,makecol(0,0,0));
                    circle(buffer1,650,400,60,makecol(0,0,0));
                    circle(buffer1,950,400,60,makecol(0,0,0));
                    textout_centre_ex(buffer1, font, "2", 350, 400, makecol(0,0,0),-1);
                    textout_centre_ex(buffer1, font, "3", 650, 400, makecol(0,0,0),-1);
                    textout_centre_ex(buffer1, font, "4", 950, 400, makecol(0,0,0),-1);
*/
                    rectfill(buffer1,200,350, 200+85, 350+40 ,makecol(255,255,255));
                    rectfill(buffer1,735, 350, 735+85, 350+40,makecol(255,255,255));

                    textout_centre_ex(buffer1, font, "Manuel", 240, 350+20, makecol(0,0,0),-1);
                    textout_centre_ex(buffer1, font, "Aleatoire", 735+40, 350+20, makecol(0,0,0),-1);


                    if(mouse_b & 1 && mouse_x>=200 && mouse_x <= 200+85 && mouse_y >= 350 && mouse_y <= 350+40)
                    {

                        textout_centre_ex(buffer2, font, "Rentrez le nombre d'iterations souhaitees sur le terminal: ", 350, 400, makecol(0,0,0),-1);
                        int nb_it = 0;
                        blit(buffer2, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        printf("=> "); scanf("%d", &nb_it);



                        textout_centre_ex(buffer2, font, "Rentrez les dimensions de la foret sur le terminal: ", 350, 450, makecol(0,0,0),-1);

                        int x, y = 0;
                        blit(buffer2, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        printf("x: "); scanf("%d", &x);
                        printf("y: "); scanf("%d", &y);



                    }

                    if(mouse_b & 1 && mouse_x>=735 && mouse_x <= 735+85 && mouse_y >= 350 && mouse_y <= 350+40)
                    {

                        clear_bitmap(buffer1);


                        textout_centre_ex(buffer2, font, "Rentrez le nombre d'iterations souhaitees sur le terminal: ", 350, 400, makecol(0,0,0),-1);
                        int nb_it = 0;
                        blit(buffer2, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        printf("=> "); scanf("%d", &nb_it);



                        textout_centre_ex(buffer2, font, "Rentrez les dimensions de la foret sur le terminal: ", 350, 400, makecol(0,0,0),-1);

                        int i, j = 0;

                        blit(buffer2, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        printf("i: "); scanf("%d", &i);
                        printf("j: "); scanf("%d", &j);
                        Case **foret = malloc (i * sizeof (Case *));
                        for (int u = 0; u < i; u++) {
                            foret[u] = malloc (j * sizeof (Case));
                        }

                        intitialisation_mode(i, j, foret);
                        affichage2(page, decor, foret, i, j);
                        choisir_case_depart(page, decor, i, j, foret);
                        printf("Appuyer sur s pour commencer: ");
                        simulation(foret, i, j, nb_it, page, decor);

                    }


                }

            }

            if(mouse_b & 1 && mouse_x>=500 && mouse_x <= 900 && mouse_y >= 400 && mouse_y <= 450)// zone de la case � cliquer
            {
                while(!key[KEY_ESC])
                {
                    blit(buffer3, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    menuAide(buffer3);
                }
            }

            if(mouse_b & 1 && mouse_x>=500 && mouse_x <= 900 && mouse_y >= 500 && mouse_y <= 550)// zone de la case � cliquer
            {
                exit(EXIT_FAILURE);
            }
        }



        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


void menuAide(BITMAP* buffer)
{
    FILE* file = fopen("dofus.txt","r"); // Ouverture du fichier d'aide

    // Boucle de dessin
    while(!key[KEY_ESC])
    {
        clear_to_color(buffer, makecol(0,150,230)); // On efface l'�cran

        if(file != NULL) // Si on a r�ussi � ouvrir le fichier
        {
            char lettre[5000];
            int ligne = 0; // Ligne actuelle dans le fichier
            fseek(file, SEEK_SET, 0); // On se place au d�but du fichier
            // Pour chaque ligne du fichier
            while(fgets(lettre, sizeof(lettre), file) != NULL)
            {
                lettre[strlen(lettre) - 1] = '\0'; // On supprime le retour � la ligne

                ligne++; // On augmente la ligne actuelle pour calculer la position y � l'�cran
                int w = text_length(font, lettre);
                // On affiche la ligne actuelle
                textout_ex(buffer, font, lettre, SCREEN_W/2-w/2, 50 + ligne * 20, 0, makecol(220, 150, 250));
            }
        }
        // Dessin du buffer sur l'�cran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    fclose(file); // On ferme le fichier d'aide
}



void jeu(){
    clear_bitmap(screen);

    BITMAP * page;

    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(1312,656);
    clear_bitmap(page);

    int xp;
    int yp;
    int x, y;

    // Image de fond
    BITMAP * decor;

    decor=load_bitmap(".\\photos\\fond_2.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver fond_2.bmp");
        exit(EXIT_FAILURE);
    }

    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

}




void deg (Case** foret, int x, int y){
    switch (foret[x][y].type) {

        case 1:
            foret[x][y].deg = DEG_ARBRE;
            foret[x][y].symbole = '*';
            break;

        case 2:
            foret[x][y].deg = DEG_FEUILLE;
            foret[x][y].symbole = '-';
            break;

        case 3:
            foret[x][y].deg = DEG_ROCHE;
            foret[x][y].symbole = '#';
            break;

        case 4:
            foret[x][y].deg = DEG_SOL;
            foret[x][y].symbole = '+';
            break;

        case 5:
            foret[x][y].deg = DEG_HERBE;
            foret[x][y].symbole = 'x';
            break;

        case 6:
            foret[x][y].deg = DEG_EAU;
            foret[x][y].symbole = '/';
            break;
    }
}


void affichage (Case** foret, int i, int j){
    for (int u = 0; u < i; u++){
        for (int k= 0; k < j; k++){
            printf(" %c ", foret[u][k].symbole);

        }
        printf("\n");
    }
}


void affichage2 (BITMAP* page, BITMAP* decor, Case** foret, int x, int y){
    clear_bitmap(page);


    int xp;
    int yp;

    if (!decor)
    {
        allegro_message("pas pu trouver fond_2.bmp");
        exit(EXIT_FAILURE);
    }


    BITMAP* eau = load_bitmap(".\\photos\\eau.bmp", NULL);
    BITMAP* feu = load_bitmap(".\\photos\\fire.bmp", NULL);

    BITMAP* arbre = load_bitmap(".\\photos\\arbre.bmp", NULL);
    BITMAP* cendre_eteinte = load_bitmap(".\\photos\\cendre_eteinte.bmp", NULL);
    BITMAP* feuilles = load_bitmap(".\\photos\\feuilles.bmp", NULL);
    BITMAP* sol = load_bitmap(".\\photos\\sol.bmp", NULL);
    BITMAP* cendre = load_bitmap(".\\photos\\cendre_braises.bmp", NULL);
    BITMAP* herbe = load_bitmap(".\\photos\\herbe.bmp", NULL);
    BITMAP* roche = load_bitmap(".\\photos\\roche.bmp", NULL);

    BITMAP* case_type;
    for (int i = 0; i < x; i++){

        for (int u = 0; u < y; u++){
            switch (foret[i][u].type) {
                case 0:
                    case_type = cendre_eteinte;
                    break;
                case 1:
                    case_type = cendre;
                    break;
                case 2:
                    case_type = eau;
                    break;
                case 3:
                    case_type = herbe;
                    break;
                case 4:
                    case_type = sol;
                    break;
                case 5:
                    case_type = roche;
                    break;
                case 6:
                    case_type = feuilles;
                    break;
                case 7:
                    case_type =arbre;
                    break;

            }
            draw_sprite(decor, case_type, i*40, u*40);
        }
    }



    //textout_centre_ex(decor, font, "Cliquer sur la case de depart: ", 400, 650, makecol(255,255,255), -1);

    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    //}

}
/*

void iterations (Case** foret, int i, int j, BITMAP * decor, BITMAP * page){

}

*/


void choisir_case_depart(BITMAP * page, BITMAP * decor, int i, int j, Case** foret){
    int x, y = 0;

    while(!key[KEY_ESC]){

        textout_centre_ex(decor, font, "Cliquer sur la case de depart: ", 400, 650, makecol(255,255,255), -1);
        if (mouse_b & 1 && is_valid(&x, &y, mouse_x, mouse_y, i, j) && foret[x][y].type != 2){
            rectfill(decor, x*40, y*40,  (x+1)*40, (y+1)*40, makecol(0,0,255));
            foret[x][y].feu = true;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            feu_animation(foret, i, j, decor, page);
            break;




        }
        //feu_animation(foret, i, j, decor, page);
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }



}

bool is_valid(int *x, int *y, int xp, int yp, int i, int j){
    *x = xp/40;
    *y = yp/40;
    if (i>=(*x) && j>=(*y)){
        return true;
    }
    else return false;
}

void intitialisation_mode(int i, int j, Case** foret){
    /*
	// mode manuel
	int type = 0;
	for (int k = 0; k < i; k++){
		for (int l = 0; l < j; l++){
			printf("Rentrer le type pour la case %d %d (1-6)", k, l);
			scanf("%d", &type);
			foret[k][l].type = type;
			deg(foret, k, l);
		}
	}
    */
    // mode al�atoire

    // Remplissage du tableau avec des cases de types al�atoires
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            foret[x][y].x = x;
            foret[x][y].y = y;
            foret[x][y].type = 1 + rand() % 7; // G�n�re un nombre entre 1 et 6 (inclus)
            foret[x][y].feu = false;
            deg(foret, x, y);
        }
    }
}







void simulation (Case** foret, int i, int j, int nb_it, BITMAP* page, BITMAP* decor){

    char s;
    printf("Appuyer sur s pour commencer la simulation: ");
    do {
        scanf("%c", &s);
    } while (s != 's');

    for (int n = 0; n < nb_it; n++){

        for (int x = 0; x < i; x++){
            for (int y = 0; y < j; y++){
                if (foret[x][y].feu == true){
                    //printf("%d:%d - ", x, y);
                    for (int u = -1; u < 2; u++){
                        if ( ((x+u) > 0 || (x+u) < i) || ((y-1) > 0 || (y-1) < j)){
                            printf("%d %d - ", x+u, y-1);
                            brule(foret, i, j, x+u, y-1);
                        }
                    }

                    for (int u = -1; u < 2; u++){
                        if ( ((x+u) > 0 || (x+u) < i) || ((y+1) > 0 || (y+1) < j)){
                            printf("%d %d - ", x+u, y+1);
                            brule(foret, i, j, x+u, y+1);
                        }
                    }


                    // A gauche de la case de d�part x, y
                    if ( ((x-1) > 0 || (x-1) < i) ){
                        printf("%d %d - ", x-1, y);
                        brule(foret, i, j, x-1, y);
                    }


                    if ( ((x+1) > 0 || (x+1) < i) ){
                        printf("%d %d - ", x+1, y);
                        // A droite de la case de d�part x, y
                        brule(foret, i, j, x+1, y);
                    }
                }

            }
        }


        feu_animation(foret, i, j, decor, page);
        rest(5000);
        char resp;
        do {
            printf("Appuyer sur i pour avancer d'iteration: ");
            scanf("%c", &i);
        } while (resp != 'i');
    }


}


void brule(Case** foret, int i, int j, int x, int y){

    if (foret[x][y].type != 2){
        if (foret[x][y].type < 7 && foret[x][y].type > 0 && foret[x][y].deg > 1){
            foret[x][y].feu = true;
            foret[x][y].deg--;
        }

        if (foret[x][y].type == 1){
            foret[x][y].cendre = true;
            foret[x][y].cendre_eteinte = false;
        }

        if (foret[x][y].type == 0){
            foret[x][y].cendre = false;
            foret[x][y].cendre_eteinte = true;
        }
    }


}

void feu_animation(Case** foret, int i, int j, BITMAP * decor, BITMAP * page){
    char feu[9][100] = {".\\photos\\animation_feu\\feu_0.bmp", ".\\photos\\animation_feu\\feu_1.bmp", ".\\photos\\animation_feu\\feu_2.bmp", ".\\photos\\animation_feu\\feu_3.bmp",
                        ".\\photos\\animation_feu\\feu_4.bmp", ".\\photos\\animation_feu\\feu_5.bmp", ".\\photos\\animation_feu\\feu_6.bmp", ".\\photos\\animation_feu\\feu_7.bmp", ".\\photos\\animation_feu\\feu_8.bmp"};
    for (int l = 0; l < 20; l++){
        for (int k = 0; k < 8; k++){
            BITMAP * feu_b = load_bitmap(feu[k], NULL);

            for (int x = 0; x < i; x++){
                for (int y = 0; y < j; y++){
                    if (foret[x][y].feu == true){
                        draw_sprite(page, feu_b, x*40, y*40);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    }
                }
            }
            rest(50);
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
        }
    }
    printf("finito");

}


bool position_valide(int x, int y, int i, int j) {
    return x >= 0 && x < i && y >= 0 && y < j;
}

bool propagation_feu(Case** foret, int x, int y, int i, int j ){
    if (!position_valide(x, y, i, j) || foret[x][y].type == 6||foret[x][y].type == 4) {
        return false;
    }

    if (foret[x][y].deg== 1) {
        return true;
    }

    if (foret[x][y].type == 2 || foret[x][y].type == 3 ||foret[x][y].type == 1 ||foret[x][y].type == 5 ) {
        return true;
    }

    return false;
}


//TODO : v�rifier la complexit� du code
// Dijkstra a une complexit� polynomiale

int chemin_le_plus_court(Case** foret, Point start, Point end, int i, int j) {
    // Tableau pour suivre les cellules visit�es ( aucune cellule visit�e pour le moment)
    bool visitee[i][j];
    for (int k = 0; k < i; k++) {
        for (int u = 0; u < j; u++) {
            visitee[k][u] = false;
        }
    }
    // Tableau pour stocker la distance de chaque cellule � la cellule de d�part ( aucune distance stock�e pour le moment )
    int distance[i][j];
    for (int k = 0; k < i; k++) {
        for (int u = 0; u < j; u++) {
            distance[k][u]=0;

            // D�calages pour explorer les voisins (les 8 directions possibles)
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            // File pour stocker les cellules � explorer
            Point queue[i * j];
            int front = 0, rear = 0;
            // Ajouter le point de d�part � la file et le marquer comme visit�
            queue[rear++] = start;
            visitee[start.x][start.y] = true;

            // Parcours BFS de la for�t
            while (front != rear) {
                // Prendre le prochain point dans la file
                Point current = queue[front++];
                // Si le point actuel est le point final recherch�, renvoyer la distance
                if (current.x == end.x && current.y == end.y) {
                    return distance[current.x][current.y];
                }
                // Parcourir les 8 directions possibles pour les voisins
                for (int k = 0; k < 8; k++) {
                    int new_x = current.x + dx[i];
                    int new_y = current.y + dy[i];

                    // V�rifier si le voisin est valide et peut propager le feu, et s'il n'a pas �t� visit�
                    if (propagation_feu(foret, new_x, new_y, i, j) &&  propagation_feu(foret, new_x, new_y, i, j) && !visitee[new_x][new_y]) {
                        // Marquer le voisin comme visit� et mettez � jour sa distance
                        visitee[new_x][new_y] = true;
                        distance[new_x][new_y] = distance[current.x][current.y] + 1;
                        // Ajouter le voisin � la file pour l'exploration ult�rieure
                        queue[rear++] = (Point){new_x, new_y};
                    }
                }
            }

            return -1;
        }
    }
}

// revenir en arri�re


void init(Case** foret, int i, int j){
    EtatForet* tete = NULL;

// au moment de l'initialisation de la foret
// Cr�ation d'un nouvel �tat de la for�t
    EtatForet* nouvelEtat=(EtatForet*)malloc(sizeof(EtatForet));
    memcpy(nouvelEtat->foret, foret, sizeof(Case) * i * j);
    nouvelEtat->suivant = NULL;
    EtatForet* current = NULL;
// Si c'est le premier maillon, initialisez la t�te de la liste

    if (tete == NULL) {
        tete = nouvelEtat;
    }

    else {
        // Ajout du nouvel �tat � la fin de la liste
        current = tete;
        while (current->suivant != NULL) {
            current = current->suivant;
        }
        current->suivant = nouvelEtat;
    }

// ajouter un maillon
    current->suivant = nouvelEtat;

// Pour trouver un �tat dans la liste
    current = tete;
    while (current->suivant!= NULL) {
        current = current->suivant;
    }

}
// D�claration de la t�te de la liste cha�n�e


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////::

