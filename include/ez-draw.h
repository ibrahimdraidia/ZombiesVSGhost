/*
 * ez-draw.h : boite a outil EZ-Draw pour faire du graphisme en C
 *
 * Edouard.Thiel@lif.univ-mrs.fr - 07/07/2011 - version 1.0
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#ifndef EZ_DRAW__H
#define EZ_DRAW__H

/* Rend vsnprintf compatible avec -ansi */
#if defined __STRICT_ANSI__ && !defined _GNU_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#undef _GNU_SOURCE
#else
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#ifndef _WIN32
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>
#include <X11/extensions/Xdbe.h>
#include <sys/time.h>
#else /* _WIN32 */
#include <windows.h>
#include <windowsx.h>
#include <wingdi.h>
#endif /* _WIN32 */
#include <time.h>

/* Constantes diverses */
#define EZ_FONT_MAX    16
#define EZ_WIN_MAX   1024 

/* Couleurs */
extern unsigned long ez_black, ez_white, ez_grey, ez_red, ez_green, ez_blue,
              ez_yellow, ez_cyan, ez_magenta;

#ifndef _WIN32
/* En interne pour la gestion des couleurs en X11 */
typedef struct {
    unsigned long mask, shift, length, max;
} Ez_channel;

typedef struct {
    Ez_channel green, red, blue;
} Ez_TrueColor;

typedef struct {
    Colormap colormap;
    unsigned long palette[6][6][6];
    XColor samples[256];
} Ez_PseudoColor;

/* Gestion des timers */
#define EZ_TIMER_MAX 100

typedef struct {
    Window win;
    struct timeval expiration;
} Ez_timer;
#endif /* _WIN32 */

/* Pour l'affichage de texte */
typedef enum { 
    EZ_AA = 183200, 
    EZ_TL,  EZ_TC,  EZ_TR,     /* Top Left, Top Center, Top Right */
    EZ_ML,  EZ_MC,  EZ_MR,     /* Middle Left, Middle Center, Middle Right */
    EZ_BL,  EZ_BC,  EZ_BR,     /* Bottom Left, Bottom Center, Bottom Right */
    EZ_BB,
    EZ_TLF, EZ_TCF, EZ_TRF,    /* idem avec effacement du Fond */
    EZ_MLF, EZ_MCF, EZ_MRF,    /* idem avec effacement du Fond */
    EZ_BLF, EZ_BCF, EZ_BRF,    /* idem avec effacement du Fond */
    EZ_CC
} Ez_Align;

/* Conversion de types Xlib en Win32 */
#ifdef _WIN32
typedef HWND Window;
typedef HDC XdbeBackBuffer;
typedef MSG XEvent;
typedef int KeySym;
typedef LPCTSTR XContext;
typedef POINT XPoint;
#define True  TRUE
#define False FALSE
#define None  NULL
#endif /* _WIN32 */

/* Type fourre-tout utilise' par toutes les fonctions */
typedef struct {
#ifndef _WIN32
    Display *display;               /* Le display */
    GC gc;                          /* Contexte graphique */
    XdbeBackBuffer dbuf_pix;        /* Double buffer courant */
    Window dbuf_win;                /* Fenetre double-bufferisee courante */
    Atom atom_protoc, atom_delwin;  /* Pour gestion destruction fenetres */
    XFontStruct *font[EZ_FONT_MAX]; /* Pour stocker des fontes */
    int depth;                      /* Nombre de plans : 8, 15, 16, 24, 32 */
    Visual *visual;                 /* Pour la couleur */
    Ez_PseudoColor pseudoColor;     /* Indexation sur palette de 256 couleurs */
    Ez_TrueColor   trueColor;       /* Canaux RGB directement dans les pixels */
    Ez_timer timer_l[EZ_TIMER_MAX]; /* Liste de timers */
    int timer_nb;                   /* Nombre de timers */
#else /* _WIN32 */
    HINSTANCE hand_prog;            /* Handle sur le programme */
    WNDCLASSEX wnd_class;           /* Classe etendue de fenetre */
    HDC hdc;                        /* Contexte de dessin pour le dc_win */
    Window dc_win;                  /* Window associe' au hdc */
    HDC dbuf_dc;                    /* Le dc du double buffer courant */
    Window dbuf_win;                /* Fenetre double-bufferisee courante */
    int dbuf_w, dbuf_h;             /* Taille du double buffer */
    HBITMAP hOldBmp, hMemBmp;       /* Bitmap du window et du double buffer */
    HPEN hpen;                      /* Pen logique pour dessin en couleur */
    HBRUSH hbrush;                  /* Brush pour remplissage en couleur */
    HFONT font[EZ_FONT_MAX];        /* Pour stocker des fontes */
    KeySym key_sym;                 /* Symbole touche : XK_Space, XK_q, etc */
    char  *key_name;                /* Pour affichage : "XK_Space", "XK_q", .. */
    char  *key_string;              /* Chaine correspondante : " ", "q", etc */
#endif /* _WIN32 */
    int screen_num;                 /* Le numero d'ecran */
    int display_width;              /* Largeur display */
    int display_height;             /* Hauteur display */
    Window root_win;                /* Fenetre racine */
    XContext info_prop;             /* xid ou prop pour memoriser les infos dans la fenetre */
    int mv_x, mv_y;                 /* Coord pour filtrer mouvements souris */
    Window mv_win;                  /* Window pour filtrer mouvements souris */
    unsigned long black, white;     /* Couleurs */
    unsigned long color;            /* Couleur courante */
    int thick;                      /* Epaisseur courante */
    int nfont;                      /* Numero fonte courante */
    int main_loop;                  /* Flag boucle principale */
    int last_expose;                /* Flag dernier Expose */
    int auto_quit;                  /* Flag bouton "Fermer" barre fenetres */
    int mouse_b;                    /* Bouton souris enfonce' */
    Window win_l[EZ_WIN_MAX];       /* Liste des fenetres existantes */
    int win_nb;                     /* Nb de fenetres ouvertes */
} Ez_X;

#ifdef _WIN32
/* Evenements de X11/X.h pour Win32 */
#define  KeyPress           2
#define  KeyRelease         3
#define  ButtonPress        4
#define  ButtonRelease      5
#define  MotionNotify       6
#define  Expose            12
#define  ConfigureNotify   22
#define  ClientMessage     33
#define  LASTEvent         35
/* Timer */
#define  EZ_TIMER1        208
/* Messages prives */
enum { EZ_MSG_PAINT = WM_APP+1, EZ_MSG_LAST };
#endif /* _WIN32 */

/* Evenements supplementaires */
enum { WindowClose = LASTEvent+1, TimerNotify, EzLastEvent };


typedef struct {
    int type;                       /* Expose, ButtonPress, etc */
    Window win;                     /* Identifiant de la fenetre */
    int mx, my;                     /* Coordonnees souris */
    int mb;                         /* Numero bouton de la souris, 0=aucun */
    int width, height;              /* Largeur et hauteur */
    KeySym key_sym;                 /* Symbole touche : XK_Space, XK_q, etc */
    char   key_name[80];            /* Pour affichage : "XK_Space", "XK_q", .. */
    char   key_string[80];          /* Chaine correspondante : " ", "q", etc */
    int    key_count;               /* Taille de la chaine */
    XEvent xev;                     /* Evenement X original */
} Ez_event;

/* Type d'une callback */
typedef void (*Ez_func)(Ez_event *ev);

/* Donnees associees a un window avec un xid ou une propriete */
typedef struct {
    Ez_func func;                   /* Callback du window */
    void *data;                     /* User-data associe' au window */
    XdbeBackBuffer dbuf;            /* Back-buffer du window */
    int show;                       /* Pour affichage diffe're' */
} Ez_win_info;


/* Fonctions publiques */

int ez_init ();
Window ez_window_create (int w, int h, const char *name, Ez_func func);
void ez_window_destroy (Window win);
void ez_window_show (Window win, int val);
void ez_window_set_size (Window win, int w, int h);
void ez_window_get_size (Window win, int *w, int *h);
void ez_window_clear (Window win);
void ez_window_dbuf (Window win, int val);
void ez_set_data (Window win, void *data);
void *ez_get_data (Window win);
void ez_quit ();
void ez_auto_quit (int val);
void ez_send_expose (Window win);
void ez_start_timer (Window win, int delay);
void ez_main_loop ();
int ez_random (int n);

unsigned long ez_get_RGB (unsigned char R, unsigned char G, unsigned char B);
unsigned long ez_get_grey (unsigned long g);
void ez_set_color (unsigned long color);
void ez_set_thick (int thick);
void ez_draw_point (Window win, int x1, int y1);
void ez_draw_line (Window win, int x1, int y1, int x2, int y2);
void ez_draw_rectangle (Window win, int x1, int y1, int x2, int y2);
void ez_fill_rectangle (Window win, int x1, int y1, int x2, int y2);
void ez_draw_triangle (Window win, int x1, int y1, int x2, int y2, int x3, int y3);
void ez_fill_triangle (Window win, int x1, int y1, int x2, int y2, int x3, int y3);
void ez_draw_circle (Window win, int x1, int y1, int x2, int y2);
void ez_fill_circle (Window win, int x1, int y1, int x2, int y2);

int ez_font_load (int num, const char *name);
void ez_set_nfont (int num);
void ez_draw_text (Window win, Ez_Align align, int x1, int y1, 
    const char *format, ...);


/* Fonctions privees */

int ez_error_dfl (const char *fmt, va_list ap);
int ez_error_ign (const char *fmt, va_list ap);
extern int (*ez_error_handler) (const char *fmt, va_list ap);
int ez_error (const char *fmt, ...);
int ez_check_state (const char *funcname);

void ez_win_delete (Window win);
void ez_win_delete_all ();
extern int ez_win_delete_final;
void ez_close_disp ();

int ez_timer_add (Window win, int delay);
int ez_timer_remove (Window win);
#ifndef _WIN32
struct timeval *ez_timer_delay ();
void ez_event_next (Ez_event *ev);
Bool ez_predicat_expose (Display *display, XEvent *xev, XPointer arg);
int ez_is_last_expose (XEvent *xev);
void ez_event_dispatch (Ez_event *ev);
#else /* _WIN32 */
LRESULT CALLBACK ez_win_proc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int ez_is_modifier (KeySym key_sym);
int ez_is_repetition (LPARAM lParam);
void ez_cur_win (Window win);
void ez_update_pen ();
#endif /* _WIN32 */
void ez_random_init ();

int ez_win_list_find (Window win);
int ez_win_list_insert (Window win);
int ez_win_list_remove (Window win);

int ez_prop_set (Window win, XContext prop, void *value);
int ez_prop_get (Window win, XContext prop, void **value);
int ez_prop_destroy (Window win, XContext prop);

int ez_info_get (Window win, Ez_win_info **info);

int ez_func_set (Window win, Ez_func func);
int ez_func_get (Window win, Ez_func *func);
int ez_func_call (Ez_event *ev);

void ez_dbuf_init ();
int ez_dbuf_set (Window win, XdbeBackBuffer dbuf);
int ez_dbuf_get (Window win, XdbeBackBuffer *dbuf);
void ez_dbuf_preswap (Window win);
void ez_dbuf_swap (Window win);

void ez_font_init ();
void ez_font_delete ();
int ez_color_init ();
#ifndef _WIN32
void ez_set_palette (unsigned long pixel, int R, int G, int B, 
    int max, int inCube);
void ez_init_PseudoColor ();
void ez_init_TrueColor ();
void ez_init_channel (Ez_channel *channel, unsigned long mask);
#else /* _WIN32 */
int ez_keydown_convert (WPARAM wParam, LPARAM lParam, KeySym *k, char **n, char **s);
int ez_keychar_convert (WPARAM wParam, KeySym *k, char **n, char **s);
#ifdef DEBUG
char *ez_win_msg_name (unsigned int m);
#endif /* DEBUG */
#endif /* _WIN32 */


/* Symboles clavier LATIN1 de X11/keysymdef.h pour Win32 */
#ifdef _WIN32
#define XK_BackSpace                     0xff08  /* Back space, back char */
#define XK_Tab                           0xff09
#define XK_Return                        0xff0d  /* Return, enter */
#define XK_Pause                         0xff13  /* Pause, hold */
#define XK_Scroll_Lock                   0xff14
#define XK_Escape                        0xff1b
#define XK_Delete                        0xffff  /* Delete, rubout */
#define XK_Home                          0xff50
#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */
#define XK_Prior                         0xff55  /* Prior, previous */
#define XK_Next                          0xff56  /* Next */
#define XK_End                           0xff57  /* EOL */
#define XK_Insert                        0xff63  /* Insert, insert here */
#define XK_Menu                          0xff67
#define XK_Num_Lock                      0xff7f
#define XK_KP_Enter                      0xff8d  /* Enter */
#define XK_KP_Home                       0xff95
#define XK_KP_Left                       0xff96
#define XK_KP_Up                         0xff97
#define XK_KP_Right                      0xff98
#define XK_KP_Down                       0xff99
#define XK_KP_Prior                      0xff9a
#define XK_KP_Next                       0xff9b
#define XK_KP_End                        0xff9c
#define XK_KP_Begin                      0xff9d
#define XK_KP_Equal                      0xffbd  /* Equals */
#define XK_KP_Multiply                   0xffaa
#define XK_KP_Add                        0xffab
#define XK_KP_Separator                  0xffac  /* Separator, often comma */
#define XK_KP_Subtract                   0xffad
#define XK_KP_Divide                     0xffaf
#define XK_KP_0                          0xffb0
#define XK_KP_1                          0xffb1
#define XK_KP_2                          0xffb2
#define XK_KP_3                          0xffb3
#define XK_KP_4                          0xffb4
#define XK_KP_5                          0xffb5
#define XK_KP_6                          0xffb6
#define XK_KP_7                          0xffb7
#define XK_KP_8                          0xffb8
#define XK_KP_9                          0xffb9
#define XK_F1                            0xffbe
#define XK_F2                            0xffbf
#define XK_F3                            0xffc0
#define XK_F4                            0xffc1
#define XK_F5                            0xffc2
#define XK_F6                            0xffc3
#define XK_F7                            0xffc4
#define XK_F8                            0xffc5
#define XK_F9                            0xffc6
#define XK_F10                           0xffc7
#define XK_F11                           0xffc8
#define XK_F12                           0xffc9
#define XK_Shift_L                       0xffe1  /* Left shift */
#define XK_Shift_R                       0xffe2  /* Right shift */
#define XK_Control_L                     0xffe3  /* Left control */
#define XK_Control_R                     0xffe4  /* Right control */
#define XK_Caps_Lock                     0xffe5  /* Caps lock */
#define XK_Meta_L                        0xffe7  /* Left meta */
#define XK_Meta_R                        0xffe8  /* Right meta */
#define XK_Alt_L                         0xffe9  /* Left alt */
#define XK_Alt_R                         0xffea  /* Right alt */
#define XK_space                         0x0020  /* SPACE */
#define XK_exclam                        0x0021  /* EXCLAMATION MARK */
#define XK_quotedbl                      0x0022  /* QUOTATION MARK */
#define XK_numbersign                    0x0023  /* NUMBER SIGN */
#define XK_dollar                        0x0024  /* DOLLAR SIGN */
#define XK_percent                       0x0025  /* PERCENT SIGN */
#define XK_ampersand                     0x0026  /* AMPERSAND */
#define XK_apostrophe                    0x0027  /* APOSTROPHE */
#define XK_parenleft                     0x0028  /* LEFT PARENTHESIS */
#define XK_parenright                    0x0029  /* RIGHT PARENTHESIS */
#define XK_asterisk                      0x002a  /* ASTERISK */
#define XK_plus                          0x002b  /* PLUS SIGN */
#define XK_comma                         0x002c  /* COMMA */
#define XK_minus                         0x002d  /* HYPHEN-MINUS */
#define XK_period                        0x002e  /* FULL STOP */
#define XK_slash                         0x002f  /* SOLIDUS */
#define XK_0                             0x0030  /* DIGIT ZERO */
#define XK_1                             0x0031  /* DIGIT ONE */
#define XK_2                             0x0032  /* DIGIT TWO */
#define XK_3                             0x0033  /* DIGIT THREE */
#define XK_4                             0x0034  /* DIGIT FOUR */
#define XK_5                             0x0035  /* DIGIT FIVE */
#define XK_6                             0x0036  /* DIGIT SIX */
#define XK_7                             0x0037  /* DIGIT SEVEN */
#define XK_8                             0x0038  /* DIGIT EIGHT */
#define XK_9                             0x0039  /* DIGIT NINE */
#define XK_colon                         0x003a  /* COLON */
#define XK_semicolon                     0x003b  /* SEMICOLON */
#define XK_less                          0x003c  /* LESS-THAN SIGN */
#define XK_equal                         0x003d  /* EQUALS SIGN */
#define XK_greater                       0x003e  /* GREATER-THAN SIGN */
#define XK_question                      0x003f  /* QUESTION MARK */
#define XK_at                            0x0040  /* COMMERCIAL AT */
#define XK_A                             0x0041  /* LATIN CAPITAL LETTER A */
#define XK_B                             0x0042  /* LATIN CAPITAL LETTER B */
#define XK_C                             0x0043  /* LATIN CAPITAL LETTER C */
#define XK_D                             0x0044  /* LATIN CAPITAL LETTER D */
#define XK_E                             0x0045  /* LATIN CAPITAL LETTER E */
#define XK_F                             0x0046  /* LATIN CAPITAL LETTER F */
#define XK_G                             0x0047  /* LATIN CAPITAL LETTER G */
#define XK_H                             0x0048  /* LATIN CAPITAL LETTER H */
#define XK_I                             0x0049  /* LATIN CAPITAL LETTER I */
#define XK_J                             0x004a  /* LATIN CAPITAL LETTER J */
#define XK_K                             0x004b  /* LATIN CAPITAL LETTER K */
#define XK_L                             0x004c  /* LATIN CAPITAL LETTER L */
#define XK_M                             0x004d  /* LATIN CAPITAL LETTER M */
#define XK_N                             0x004e  /* LATIN CAPITAL LETTER N */
#define XK_O                             0x004f  /* LATIN CAPITAL LETTER O */
#define XK_P                             0x0050  /* LATIN CAPITAL LETTER P */
#define XK_Q                             0x0051  /* LATIN CAPITAL LETTER Q */
#define XK_R                             0x0052  /* LATIN CAPITAL LETTER R */
#define XK_S                             0x0053  /* LATIN CAPITAL LETTER S */
#define XK_T                             0x0054  /* LATIN CAPITAL LETTER T */
#define XK_U                             0x0055  /* LATIN CAPITAL LETTER U */
#define XK_V                             0x0056  /* LATIN CAPITAL LETTER V */
#define XK_W                             0x0057  /* LATIN CAPITAL LETTER W */
#define XK_X                             0x0058  /* LATIN CAPITAL LETTER X */
#define XK_Y                             0x0059  /* LATIN CAPITAL LETTER Y */
#define XK_Z                             0x005a  /* LATIN CAPITAL LETTER Z */
#define XK_bracketleft                   0x005b  /* LEFT SQUARE BRACKET */
#define XK_backslash                     0x005c  /* REVERSE SOLIDUS */
#define XK_bracketright                  0x005d  /* RIGHT SQUARE BRACKET */
#define XK_asciicircum                   0x005e  /* CIRCUMFLEX ACCENT */
#define XK_underscore                    0x005f  /* LOW LINE */
#define XK_grave                         0x0060  /* GRAVE ACCENT */
#define XK_a                             0x0061  /* LATIN SMALL LETTER A */
#define XK_b                             0x0062  /* LATIN SMALL LETTER B */
#define XK_c                             0x0063  /* LATIN SMALL LETTER C */
#define XK_d                             0x0064  /* LATIN SMALL LETTER D */
#define XK_e                             0x0065  /* LATIN SMALL LETTER E */
#define XK_f                             0x0066  /* LATIN SMALL LETTER F */
#define XK_g                             0x0067  /* LATIN SMALL LETTER G */
#define XK_h                             0x0068  /* LATIN SMALL LETTER H */
#define XK_i                             0x0069  /* LATIN SMALL LETTER I */
#define XK_j                             0x006a  /* LATIN SMALL LETTER J */
#define XK_k                             0x006b  /* LATIN SMALL LETTER K */
#define XK_l                             0x006c  /* LATIN SMALL LETTER L */
#define XK_m                             0x006d  /* LATIN SMALL LETTER M */
#define XK_n                             0x006e  /* LATIN SMALL LETTER N */
#define XK_o                             0x006f  /* LATIN SMALL LETTER O */
#define XK_p                             0x0070  /* LATIN SMALL LETTER P */
#define XK_q                             0x0071  /* LATIN SMALL LETTER Q */
#define XK_r                             0x0072  /* LATIN SMALL LETTER R */
#define XK_s                             0x0073  /* LATIN SMALL LETTER S */
#define XK_t                             0x0074  /* LATIN SMALL LETTER T */
#define XK_u                             0x0075  /* LATIN SMALL LETTER U */
#define XK_v                             0x0076  /* LATIN SMALL LETTER V */
#define XK_w                             0x0077  /* LATIN SMALL LETTER W */
#define XK_x                             0x0078  /* LATIN SMALL LETTER X */
#define XK_y                             0x0079  /* LATIN SMALL LETTER Y */
#define XK_z                             0x007a  /* LATIN SMALL LETTER Z */
#define XK_braceleft                     0x007b  /* LEFT CURLY BRACKET */
#define XK_bar                           0x007c  /* VERTICAL LINE */
#define XK_braceright                    0x007d  /* RIGHT CURLY BRACKET */
#define XK_asciitilde                    0x007e  /* TILDE */
#define XK_nobreakspace                  0x00a0  /* NO-BREAK SPACE */
#define XK_exclamdown                    0x00a1  /* INVERTED EXCLAMATION MARK */
#define XK_cent                          0x00a2  /* CENT SIGN */
#define XK_sterling                      0x00a3  /* POUND SIGN */
#define XK_currency                      0x00a4  /* CURRENCY SIGN */
#define XK_yen                           0x00a5  /* YEN SIGN */
#define XK_brokenbar                     0x00a6  /* BROKEN BAR */
#define XK_section                       0x00a7  /* SECTION SIGN */
#define XK_diaeresis                     0x00a8  /* DIAERESIS */
#define XK_copyright                     0x00a9  /* COPYRIGHT SIGN */
#define XK_ordfeminine                   0x00aa  /* FEMININE ORDINAL INDICATOR */
#define XK_guillemotleft                 0x00ab  /* LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
#define XK_notsign                       0x00ac  /* NOT SIGN */
#define XK_hyphen                        0x00ad  /* SOFT HYPHEN */
#define XK_registered                    0x00ae  /* REGISTERED SIGN */
#define XK_macron                        0x00af  /* MACRON */
#define XK_degree                        0x00b0  /* DEGREE SIGN */
#define XK_plusminus                     0x00b1  /* PLUS-MINUS SIGN */
#define XK_twosuperior                   0x00b2  /* SUPERSCRIPT TWO */
#define XK_threesuperior                 0x00b3  /* SUPERSCRIPT THREE */
#define XK_acute                         0x00b4  /* ACUTE ACCENT */
#define XK_mu                            0x00b5  /* MICRO SIGN */
#define XK_paragraph                     0x00b6  /* PILCROW SIGN */
#define XK_periodcentered                0x00b7  /* MIDDLE DOT */
#define XK_cedilla                       0x00b8  /* CEDILLA */
#define XK_onesuperior                   0x00b9  /* SUPERSCRIPT ONE */
#define XK_masculine                     0x00ba  /* MASCULINE ORDINAL INDICATOR */
#define XK_guillemotright                0x00bb  /* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
#define XK_onequarter                    0x00bc  /* VULGAR FRACTION ONE QUARTER */
#define XK_onehalf                       0x00bd  /* VULGAR FRACTION ONE HALF */
#define XK_threequarters                 0x00be  /* VULGAR FRACTION THREE QUARTERS */
#define XK_questiondown                  0x00bf  /* INVERTED QUESTION MARK */
#define XK_Agrave                        0x00c0  /* LATIN CAPITAL LETTER A WITH GRAVE */
#define XK_Aacute                        0x00c1  /* LATIN CAPITAL LETTER A WITH ACUTE */
#define XK_Acircumflex                   0x00c2  /* LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
#define XK_Atilde                        0x00c3  /* LATIN CAPITAL LETTER A WITH TILDE */
#define XK_Adiaeresis                    0x00c4  /* LATIN CAPITAL LETTER A WITH DIAERESIS */
#define XK_Aring                         0x00c5  /* LATIN CAPITAL LETTER A WITH RING ABOVE */
#define XK_AE                            0x00c6  /* LATIN CAPITAL LETTER AE */
#define XK_Ccedilla                      0x00c7  /* LATIN CAPITAL LETTER C WITH CEDILLA */
#define XK_Egrave                        0x00c8  /* LATIN CAPITAL LETTER E WITH GRAVE */
#define XK_Eacute                        0x00c9  /* LATIN CAPITAL LETTER E WITH ACUTE */
#define XK_Ecircumflex                   0x00ca  /* LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
#define XK_Ediaeresis                    0x00cb  /* LATIN CAPITAL LETTER E WITH DIAERESIS */
#define XK_Igrave                        0x00cc  /* LATIN CAPITAL LETTER I WITH GRAVE */
#define XK_Iacute                        0x00cd  /* LATIN CAPITAL LETTER I WITH ACUTE */
#define XK_Icircumflex                   0x00ce  /* LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
#define XK_Idiaeresis                    0x00cf  /* LATIN CAPITAL LETTER I WITH DIAERESIS */
#define XK_ETH                           0x00d0  /* LATIN CAPITAL LETTER ETH */
#define XK_Ntilde                        0x00d1  /* LATIN CAPITAL LETTER N WITH TILDE */
#define XK_Ograve                        0x00d2  /* LATIN CAPITAL LETTER O WITH GRAVE */
#define XK_Oacute                        0x00d3  /* LATIN CAPITAL LETTER O WITH ACUTE */
#define XK_Ocircumflex                   0x00d4  /* LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
#define XK_Otilde                        0x00d5  /* LATIN CAPITAL LETTER O WITH TILDE */
#define XK_Odiaeresis                    0x00d6  /* LATIN CAPITAL LETTER O WITH DIAERESIS */
#define XK_multiply                      0x00d7  /* MULTIPLICATION SIGN */
#define XK_Oslash                        0x00d8  /* LATIN CAPITAL LETTER O WITH STROKE */
#define XK_Ugrave                        0x00d9  /* LATIN CAPITAL LETTER U WITH GRAVE */
#define XK_Uacute                        0x00da  /* LATIN CAPITAL LETTER U WITH ACUTE */
#define XK_Ucircumflex                   0x00db  /* LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
#define XK_Udiaeresis                    0x00dc  /* LATIN CAPITAL LETTER U WITH DIAERESIS */
#define XK_Yacute                        0x00dd  /* LATIN CAPITAL LETTER Y WITH ACUTE */
#define XK_THORN                         0x00de  /* LATIN CAPITAL LETTER THORN */
#define XK_ssharp                        0x00df  /* LATIN SMALL LETTER SHARP S */
#define XK_agrave                        0x00e0  /* LATIN SMALL LETTER A WITH GRAVE */
#define XK_aacute                        0x00e1  /* LATIN SMALL LETTER A WITH ACUTE */
#define XK_acircumflex                   0x00e2  /* LATIN SMALL LETTER A WITH CIRCUMFLEX */
#define XK_atilde                        0x00e3  /* LATIN SMALL LETTER A WITH TILDE */
#define XK_adiaeresis                    0x00e4  /* LATIN SMALL LETTER A WITH DIAERESIS */
#define XK_aring                         0x00e5  /* LATIN SMALL LETTER A WITH RING ABOVE */
#define XK_ae                            0x00e6  /* LATIN SMALL LETTER AE */
#define XK_ccedilla                      0x00e7  /* LATIN SMALL LETTER C WITH CEDILLA */
#define XK_egrave                        0x00e8  /* LATIN SMALL LETTER E WITH GRAVE */
#define XK_eacute                        0x00e9  /* LATIN SMALL LETTER E WITH ACUTE */
#define XK_ecircumflex                   0x00ea  /* LATIN SMALL LETTER E WITH CIRCUMFLEX */
#define XK_ediaeresis                    0x00eb  /* LATIN SMALL LETTER E WITH DIAERESIS */
#define XK_igrave                        0x00ec  /* LATIN SMALL LETTER I WITH GRAVE */
#define XK_iacute                        0x00ed  /* LATIN SMALL LETTER I WITH ACUTE */
#define XK_icircumflex                   0x00ee  /* LATIN SMALL LETTER I WITH CIRCUMFLEX */
#define XK_idiaeresis                    0x00ef  /* LATIN SMALL LETTER I WITH DIAERESIS */
#define XK_eth                           0x00f0  /* LATIN SMALL LETTER ETH */
#define XK_ntilde                        0x00f1  /* LATIN SMALL LETTER N WITH TILDE */
#define XK_ograve                        0x00f2  /* LATIN SMALL LETTER O WITH GRAVE */
#define XK_oacute                        0x00f3  /* LATIN SMALL LETTER O WITH ACUTE */
#define XK_ocircumflex                   0x00f4  /* LATIN SMALL LETTER O WITH CIRCUMFLEX */
#define XK_otilde                        0x00f5  /* LATIN SMALL LETTER O WITH TILDE */
#define XK_odiaeresis                    0x00f6  /* LATIN SMALL LETTER O WITH DIAERESIS */
#define XK_division                      0x00f7  /* DIVISION SIGN */
#define XK_oslash                        0x00f8  /* LATIN SMALL LETTER O WITH STROKE */
#define XK_ugrave                        0x00f9  /* LATIN SMALL LETTER U WITH GRAVE */
#define XK_uacute                        0x00fa  /* LATIN SMALL LETTER U WITH ACUTE */
#define XK_ucircumflex                   0x00fb  /* LATIN SMALL LETTER U WITH CIRCUMFLEX */
#define XK_udiaeresis                    0x00fc  /* LATIN SMALL LETTER U WITH DIAERESIS */
#define XK_yacute                        0x00fd  /* LATIN SMALL LETTER Y WITH ACUTE */
#define XK_thorn                         0x00fe  /* LATIN SMALL LETTER THORN */
#define XK_ydiaeresis                    0x00ff  /* LATIN SMALL LETTER Y WITH DIAERESIS */
#define XK_EuroSign                      0x20ac  /* EURO SIGN */
#endif /* _WIN32 */


#endif /* EZ_DRAW__H */

