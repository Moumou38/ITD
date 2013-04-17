/*!
 *	\file layer.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 10/04/13
 *	
 *	\brief Structures de données et fonctions des layers
 */

#include "button.h"

typedef enum {
	LS_HORIZONTAL,
	LS_VERTICAL,
	LS_GRID
} Layer_Style;

typedef union {
	unsigned int type;
	Button button;
} Widget;

typedef struct {
	List* widgets;
} Layer;
