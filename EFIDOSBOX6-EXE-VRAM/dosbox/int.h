#ifndef DOSBOX_INT_H
#define DOSBOX_INT_H

#include "stdint.h"

// manejador de interrupciones DOS
extern void handle_int(uint8_t intnum);

#endif
