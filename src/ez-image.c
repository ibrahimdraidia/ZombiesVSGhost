#include "../include/ez-draw.h"
#include "../include/ez-image.h"
#include "../include/stb_image.h"

/* ezx, le contexte global d'ez-draw, n'est pas declare dans ez-draw.h */
extern Ez_X ezx;

/* fonction qui echange les valeurs de bleu et rouge des pixels.
   hypothese : les pixels sont sur 32 bits.
*/
void rgb2bgr(unsigned char* data, int width, int height) {
    unsigned char* pixel, tmp;
    for(pixel = data; pixel < data + width * height * 4; pixel += 4) {
        tmp = pixel[0];
        pixel[0] = pixel[2];
        pixel[2] = tmp;
    }
}

/* cree un masque a partir de tous les pixels d'une image d'une couleur donnee */
unsigned char* create_mask(unsigned char* data, int width, int height, unsigned int mask_color) {
    unsigned int* pixels = (unsigned int*) data;
    int id;
    int i, j;
    unsigned char* mask;
    int scanline = width + (8 - width % 8) % 8;
    mask = calloc((scanline * height) / 8, 1);
    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            id = (i + j * scanline) / 8;
            if((pixels[i + j * width] & 0xffffff) != mask_color) {
                mask[id] |= 1 << (i % 8);
            }
        }
    }
    return mask;
}

/* charge une image et cree le masque correspondant */
Image* ez_load_image(const char* filename, unsigned int mask_color) {
    int nbytes;
    Image* image;
    unsigned char* data;
    if(ezx.visual->class != TrueColor) {
        fprintf(stderr, "ez_load_image(%s): unsupported visual\n", filename);
        return NULL;
    }
    image = (Image*) malloc(sizeof(Image));
    if(image == NULL) {
        fprintf(stderr, "ez_load_image(%s): could not allocate memory\n", filename);
        return NULL;
    }
    data = stbi_load(filename, &image->width, &image->height, &nbytes, 4);
    if(data == NULL) {
        fprintf(stderr, "ez_load_image(%s): file not found or bad format\n", filename);
        free(image);
        return NULL;
    }
    rgb2bgr(data, image->width, image->height);
    image->ximage = XCreateImage(ezx.display, ezx.visual, 24, ZPixmap, 0, (char*) data, image->width, image->height, 32, 0);
    if(mask_color != EZ_IMAGE_NO_MASK) {
        image->mask = create_mask(data, image->width, image->height, mask_color);
    } else {
        image->mask = NULL;
    }
    return image;
}

/* libere l'image */
void ez_free_image(Image* image) {
    if(image != NULL) {
        if(image->ximage != NULL) XDestroyImage(image->ximage);
        if(image->mask != NULL) free(image->mask);
        free(image);
    }
}

/* dessine une sous-image en prenant en compte le masque de transparence */
void ez_draw_subimage(Window win, Image* image, int x, int y, int src_x, int src_y, int width, int height) {
    Pixmap mask;
    if (win == ezx.dbuf_win) win = ezx.dbuf_pix;
    if(image->mask != NULL) {
        mask = XCreateBitmapFromData(ezx.display, win, (char*) image->mask, image->width, image->height);
        XSetClipOrigin(ezx.display, ezx.gc, x, y);
        XSetClipMask(ezx.display, ezx.gc, mask);
        XPutImage(ezx.display, win, ezx.gc, image->ximage, src_x, src_y, x, y, width, height);
        XSetClipOrigin(ezx.display, ezx.gc, 0, 0);
        XSetClipMask(ezx.display, ezx.gc, None);
        XFreePixmap(ezx.display, mask);
    } else {
        XPutImage(ezx.display, win, ezx.gc, image->ximage, src_x, src_y, x, y, width, height);
    }
}

/* version simple qui dessine l'image en entier */
void ez_draw_image(Window win, Image* image, int x, int y) {
    ez_draw_subimage(win, image, x, y, 0, 0, image->width, image->height);
}

