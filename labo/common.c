#include "common.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <unistd.h>


#ifndef AFFICHAGE_LABO_H
#include "AffichageLabo.h"
#endif
#ifndef MATRIX_H
#include "matrix.h"
#endif

extern SDL_Renderer*renderer;

const int WINDOW_SIZE_X = 1920;
const int WINDOW_SIZE_Y = 1080;

S_MATRIX*matrice;

unsigned nb_col;
unsigned nb_row;

int pos_x;
int pos_y;

int pos_col;
int pos_row;

int vx;
int vy;

int dx=1;
int dy=0;

void find_salle(S_MATRIX*mat,int*x,int*y){
    for (int i=0;i<mat->row;i++){
        for (int j=0;j<mat->col;j++){
            if (mat->matrix[i][j]==2){
                *x = j+1;
                *y = i+1;
                return;
            }
        }
    }
    *x = 0;
    *y = 0;
}

void init_laboratoire(unsigned cols, unsigned rows, unsigned salles, unsigned p_salles){
    nb_col = cols;
    nb_row = rows;

    int pos_x = 0;
    int pos_y = 0;

    vx = 0;
    vy = 0;

    matrice = generate_matrix(nb_row, nb_col, salles, p_salles);

    find_salle(matrice, &pos_col, &pos_row);

    init_affichage(renderer);
    create_shadow();
    create_objects();
    
}
void end_Laboratoire(){
    free_matrix(matrice);
    free_shadow();
    free_objects();
}

void laboratoire_loop(){
    int ev=1;;
    while(ev){
        //clear
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //print on screen
        print_mat(matrice->matrix, pos_x, pos_y, pos_col, pos_row, nb_col, nb_row);
        print_objet(pos_x, pos_y, pos_col, pos_row);
        print_player(dx,dy);
        //print_shadow(renderer);

        //render
        SDL_RenderPresent(renderer);

        //event
        ev = event_loop(&vx, &vy, &dx, &dy);
        calc_move(&pos_col, &pos_row, &pos_x, &pos_y, vx, vy, nb_col, nb_row, matrice->matrix);
        //if (ev==2){
            //test use event
        //}
    }
}