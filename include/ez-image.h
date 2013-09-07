/*
 * ez-image.h : extension d'ez-draw pour charger des images
 *
 * Benoit.Favre@lif.univ-mrs.fr - 01/03/2013 - version 1.0
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#ifndef __EZ_IMAGE_H__
#define __EZ_IMAGE_H__

/* ez-image est une extension d'ez-draw permettant de charger et d'afficher
   des images au format png ou jpeg dans des fenetres ez-draw. Cette extension
   repose sur stb_image (http://nothings.org/stb_image.c) pour lire les
   image. Elle ne fonctionne *pas* sous windows.
*/

/* exemple d'utilisation :

Image* image;

void win1_event (Ez_event *ev) {
    switch (ev->type) {
        case Expose :
            ez_draw_image(ev->win, image, 0, 0);
            break;
    }
}

int main (int argc, char** argv)
{
    Window win;
    if(argc != 2) {
        fprintf(stderr, "usage: %s <image>\n", argv[0]);
        return 1;
    }
    if (ez_init() < 0) exit(1);
    image = ez_load_image(argv[1], 0xff00ff);
    if(image == NULL) return 1;
    win = ez_window_create (image->width, image->height, argv[1], win1_event);
    ez_main_loop ();
    ez_free_image(image);
    exit(0);
}
*/

#include "ez-draw.h"

/* Constante specifiant qu'aucune couleur n'est transparente */
#define EZ_IMAGE_NO_MASK 0xffffffff

/* Structure stoquant une image. Cette structure est remplie par ez_load_image
   et liberee par ez_free_image
*/ 
typedef struct {
    XImage* ximage;           /* l'image en elle meme */
    unsigned char* mask;      /* masque fonction de la couleur de transparence */
    int width;                /* nombre de pixels en largeur */
    int height;               /* nombre de pixels en hauteur */
} Image;

/* Charge une image png ou jpg a partir d'un fichier. Notez que la librairie
   stb_image ne supporte pas toutes les variantes de png et jpg.
   - filename: nom du fichier a charger
   - mask_color: un entier 32 bits representant la couleur qui doit etre
     interpretee comme transparente. Si mask_color == EZ_IMAGE_NO_MASK, alors
     aucune transparence n'est appliquee.  La couleur du masque est au format BGR.
   Valeur de retour : un pointeur vers l'image chargee ou NULL en cas d'echec.
*/
Image* ez_load_image(const char* filename, unsigned int mask_color);

/* Libere la memoire associee a une image chargee avec ez_load_image.
   - image: un pointeur vers l'image a liberer
*/
void ez_free_image(Image* image);

/* Affiche une image aux coordonnees x, y dans une fenetre ez-draw. Si une couleur
   de transparence a ete specifiee lors du chargement, alors l'arriere plan est
   affiche a la place des pixels de cette couleur.
   - win: la fenetre ou afficher l'image
   - image: un pointeur vers une image valide
   - x, y: coordonnees du coin superieur gauche de l'image dans la fenetre
*/
void ez_draw_image(Window win, Image* image, int x, int y);

/* Affiche une sous-partie d'une image dans une fenetre. Fonctionne comme ez_draw_image
   mais permet de specifier les coordonnes de la sous-partie de l'image a afficher.
   - win, image, x, y: meme signification que pour ez_draw_image.
   - src_x, src_y: decalage depuis le coin superieur gauche de l'image
   - width, height: taille de la sous-image a afficher.
*/
void ez_draw_subimage(Window win, Image* image, int x, int y, int src_x, int src_y, int width, int height);

#endif
