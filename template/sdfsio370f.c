/***********************************
 *                                 *
 * Template of CLIB for MachiKania *
 *                                 *
 ***********************************/

#include "./sdfsio370f.h"

// Local prototyping
void clib_g_data();

// File System functions below use following macro
// $v0=g_data;
// lw $v1,0($v0)   // g_data[0]
// lw $v0,8($v0)   // g_data[2]
// lw $v0,"x"($v0) // g_data[2][x/4]
// lw $gp,0($v1)   // g_data[0][0]
// jalr $v0
#define machikania_file(x) \
	clib_g_data();\
	asm volatile("lw $v1,0($v0)");\
	asm volatile("lw $v0,8($v0)");\
	asm volatile("lw $v0,"x"($v0)");\
	asm volatile("lw $gp,0($v1)");\
	asm volatile("jalr $v0")

int FSInit(void)
{ machikania_file("0"); }
FSFILE * FSfopen (const char * fileName, const char *mode)
{ machikania_file("4"); }
int FSfclose(FSFILE *fo)
{ machikania_file("8"); }
size_t FSfread(void *ptr, size_t size, size_t n, FSFILE *stream)
{ machikania_file("12"); }
size_t FSfwrite(const void *data_to_write, size_t size, size_t n, FSFILE *stream)
{ machikania_file("16"); }
int FSfeof( FSFILE * stream )
{ machikania_file("20"); }
long FSftell (FSFILE * fo)
{ machikania_file("24"); }
int FSfseek(FSFILE *stream, long offset, int whence)
{ machikania_file("28"); }
void FSrewind (FSFILE * fo)
{ machikania_file("32"); }
int FindFirst (const char * fileName, unsigned int attr, SearchRec * rec)
{ machikania_file("36"); }
int FindNext (SearchRec * rec)
{ machikania_file("40"); }
int FSmkdir (char * path)
{ machikania_file("44"); }
char * FSgetcwd (char * path, int numchars)
{ machikania_file("48"); }
int FSchdir (char * path)
{ machikania_file("52"); }
int FSremove (const char * fileName)
{ machikania_file("56"); }
int FSrename (const char * fileName, FSFILE * fo)
{ machikania_file("60"); }

