#ifndef _VGA_HPP_
#define _VGA_HPP_


#include <stdint.h>
#include <stdbool.h>

#define VIDEO_MEMORY (char*) 0xb8000

static char* video_memory = VIDEO_MEMORY;

static int line = 0;
static int pos = 0;

// Function to print to the screen
void printf(const char* format, ...);

#endif