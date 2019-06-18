/***********************************
 *                                 *
 * Template of CLIB for MachiKania *
 *                                 *
 ***********************************/

// Include the main header
#include "./clib.h"
// CLIBINIT is placed at specific address
#define CLIBINIT __attribute__((section(".machikania_clib")))

/*
 * g_data[] contains the data from MachiKania compiler for this library
 * See the comment in clib.h
 */
void*** g_data;

/*
 * clibdata[] contains the data from this library for MachiKania compiler
 * clibdata[0] : Version of CLIB (This library is for MachiKania ver 1.4)
 * clibdata[1] : Size of data memory
 * clibdata[2] : Public function array
 * clibdata[2-]: Reserved for higher verion of CLIB
 */
const void* const clibdata[]={
	(void*) 0x0140,             // clibdata[0]
	(void*) CLIB_DATA_MEM_SIZE, // clibdata[1] 
	&functions[0],              // clibdata[2]
	0                           // Finally, end with 0
};

/*
 * This function will be called when initializing library,
 * and used to exchange data between MachiKania BASIC and this library.
 * This is only a function placed in .machikania_clib section for providing
 * static start address at 0xA0008000. When editing this function is required,
 * the size of kseg2_program_mem and address of kseg0_program_mem 
 * in linker script must be changed.
 * This function is called twice, for exchanging data and for calling init().
 */
void* CLIBINIT clib_init(void*** data){
	// Store pointer to data
	if (data) g_data=data;
	// Call user initialization routine
	else init();
	// Return pointer to clibdata
	return (void*)&clibdata[0];
}

const void* const g_adjustment[]={ adjustment };
void* adjustment(void){
	asm volatile("la $v0,%0"::"i"(&g_adjustment[0]));
	asm volatile("lw $v0,0($v0)");
	asm volatile("subu $v0,$t9,$v0");
}

// Function to get g_data in $v0
void*** __attribute__((section("clib_g_data"))) clib_g_data(){ return g_data; }

/*
	Macros for functions.
	Example for calloc:
		asm volatile("lw $v1,0($a1)"); // g_data[0]
		asm volatile("lw $v0,4($a1)"); // g_data[1]
		asm volatile("lw $v0,0($v0)"); // g_data[1][0]
		asm volatile("lw $gp,0($v1)"); // g_data[0][0]
		asm volatile("jr $v0");
	Exmaple for free:
		asm volatile("lw $v1,0($a1)"); // g_data[0]
		asm volatile("lw $v0,4($a1)"); // g_data[1]
		asm volatile("lw $v0,4($v0)"); // g_data[1][1]
		asm volatile("lw $gp,0($v1)"); // g_data[0][0]
		asm volatile("jr $v0");
	Example for start_composite:
		asm volatile("lw $v1,0($a0)"); // g_data[0]
		asm volatile("lw $v0,12($a0)");// g_data[3]
		asm volatile("lw $v0,0($v0)"); // g_data[3][0]
		asm volatile("lw $gp,0($v1)"); // g_data[0][0]
		asm volatile("jr $v0");
	Example for g_printnum2
		asm volatile("lw $t0,24($sp)");// g_data
		asm volatile("lw $v1,0($t0)"); // g_data[0]
		asm volatile("lw $v0,12($t0)");// g_data[3]
		asm volatile("lw $v0,44($v0)");// g_data[3][11]
		asm volatile("lw $gp,0($v1)"); // g_data[0][0]
		asm volatile("jr $v0");
*/

// The general function macro; x:"$a0","$a1" etc, y:"0","4" etc, z: "0","4" etc
#define machikania_function(x,y,z)\
	asm volatile("lw $v1,0(" x ")");\
	asm volatile("lw $v0," y "(" x ")");\
	asm volatile("lw $v0," z "($v0)");\
	asm volatile("lw $gp,0($v1)");\
	asm volatile("jr $v0")

// The function macro using stack; x:"16","20" etc, y:"0","4" etc, z: "0","4" etc
#define machikania_function_sp(x,y,z)\
	asm volatile("lw $t0," x "($sp)");\
	asm volatile("lw $v1,0($t0)");\
	asm volatile("lw $v0," y "($t0)");\
	asm volatile("lw $v0," z "($v0)");\
	asm volatile("lw $gp,0($v1)");\
	asm volatile("jr $v0")

// call lib_calloc_memory() function
void* clib_calloc(int size, void*** g_data)
{ machikania_function("$a1","4","0"); }

// call lib_delete() function
void clib_free(void* addr, void*** g_data)
{ machikania_function("$a1","4","4"); }

// Video functions
void clib_start_composite(void*** data)
{ machikania_function("$a0","12","0"); }

void clib_stop_composite(void*** data)
{ machikania_function("$a0","12","4"); }

void clib_printchar(unsigned char n,void*** data)
{ machikania_function("$a1","12","8"); }

void clib_printstr(unsigned char *s,void*** data)
{ machikania_function("$a1","12","12"); }

void clib_printnum(unsigned int n,void*** data)
{ machikania_function("$a1","12","16"); }

void clib_printnum2(unsigned int n,unsigned char e,void*** data)
{ machikania_function("$a2","12","20"); }

void clib_cls(void*** data)
{ machikania_function("$a0","12","24"); }

void clib_vramscroll(void*** data)
{ machikania_function("$a0","12","28"); }

void clib_setcursorcolor(unsigned char c,void*** data)
{ machikania_function("$a1","12","32"); }

void clib_setcursor(unsigned char x,unsigned char y,unsigned char c,void*** data)
{ machikania_function("$a3","12","36"); }

void clib_set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g,void*** data)
{ machikania_function_sp("16","12","40"); }

void clib_set_bgcolor(unsigned char b,unsigned char r,unsigned char g,void*** data)
{ machikania_function("$a3","12","44"); }

// Graphic functions
void clib_g_pset(int x,int y,unsigned int c,void*** data)
{ machikania_function("$a3","16","0"); }

void clib_g_putbmpmn(int x,int y,char m,char n,const unsigned char bmp[],void*** data)
{ machikania_function_sp("20","16","4"); }

void clib_g_clrbmpmn(int x,int y,char m,char n,void*** data)
{ machikania_function_sp("16","16","8"); }

void clib_g_gline(int x1,int y1,int x2,int y2,unsigned int c,void*** data)
{ machikania_function_sp("20","16","12"); }

void clib_g_hline(int x1,int x2,int y,unsigned int c,void*** data)
{ machikania_function_sp("16","16","16"); }

void clib_g_circle(int x0,int y0,unsigned int r,unsigned int c,void*** data)
{ machikania_function_sp("16","16","20"); }

void clib_g_circlefill(int x0,int y0,unsigned int r,unsigned int c,void*** data)
{ machikania_function_sp("16","16","24"); }

void clib_g_boxfill(int x1,int y1,int x2,int y2,unsigned int c,void*** data)
{ machikania_function_sp("20","16","28"); }

void clib_g_putfont(int x,int y,unsigned int c,int bc,unsigned char n,void*** data)
{ machikania_function_sp("20","16","32"); }

void clib_g_printstr(int x,int y,unsigned int c,int bc,unsigned char *s,void*** data)
{ machikania_function_sp("20","16","36"); }

void clib_g_printnum(int x,int y,unsigned char c,int bc,unsigned int n,void*** data)
{ machikania_function_sp("20","16","40"); }

void clib_g_printnum2(int x,int y,unsigned char c,int bc,unsigned int n,unsigned char e,void*** data)
{ machikania_function_sp("24","16","44"); }

unsigned int clib_g_color(int x,int y,void*** data)
{ machikania_function("$a2","16","48"); }

// Keyboard functions
unsigned char clib_shiftkeys(void*** data)
{ machikania_function("$a0","20","0"); }

unsigned char clib_ps2readkey(void*** data)
{ machikania_function("$a0","20","4"); }
