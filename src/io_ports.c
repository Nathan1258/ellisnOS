//
// Created by Nathan Ellis on 02/01/2024.
//
#include "io_ports.h"
#include "stdint.h"

/**
 * write a given byte to given port number
 */
void outb(uint16 port, uint8 data) {
    asm volatile("outb %1, %0" :: "Nd"(port), "a"(data));
}
