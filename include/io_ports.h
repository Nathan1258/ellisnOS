//
// Created by Nathan Ellis on 02/01/2024.
//

#ifndef ELLISNOS_IO_PORTS_H
#define ELLISNOS_IO_PORTS_H

#include "types.h"

/**
 * write a given byte to given port number
 */
void outb(uint16 port, uint8 data);


#endif //ELLISNOS_IO_PORTS_H
