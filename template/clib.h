/***********************************
 *                                 *
 * Template of CLIB for MachiKania *
 *                                 *
 ***********************************/

// Definition of data and program area.
// See also linker library.
// When expansion of data area size is required, edit following value
// as well as kseg1_data_mem in linker script.
#define CLIB_PROGMRAM_MEM 0xA0008000
#define CLIB_DATA_MEM_SIZE 0x0080
#define CLIB_DATA_MEM (CLIB_PROGMRAM_MEM-CLIB_DATA_MEM_SIZE)

// List of public function(s))
// This must be defined by user
extern const void* const functions[];

// Prototypes
/*
 * void init(void);
 * This function must be defined by user.
 * It will be called when initializing library.
*/
void init(void);

/*
 * void* adjustment(void);
 * Use this function to determine the adjustment value of const pointers.
 */
void* adjustment(void);

// Variable used in clib.c
extern void*** g_data;

/*
 * For calling MachiKania functions.
 * The structure of g_data[] is the same as g_data_clib[] below.
 * 
const void* const g_data_clib_var[]={
	0, // will be g_gp, g_data[0][0],"0"
};

const void* const g_data_clib_core[]={
	lib_calloc_memory,//  g_data[1][0],"0"
	lib_delete,       //  g_data[1][1],"4"
};

const void* const g_data_clib_file[]={
#ifdef __DEBUG
	0 // Disabled in debug mode
#else
	FSInit,   // g_data[2][0],"0"
	FSfopen,  // g_data[2][1],"4"
	FSfclose, // g_data[2][2],"8"
	FSfread,  // g_data[2][3],"12"
	FSfwrite, // g_data[2][4],"16"
	FSfeof,   // g_data[2][5],"20"
	FSftell,  // g_data[2][6],"24"
	FSfseek,  // g_data[2][7],"28"
	FSrewind, // g_data[2][8],"32"
	FindFirst,// g_data[2][9],"36"
	FindNext, // g_data[2][10],"40"
	FSmkdir,  // g_data[2][11],"44"
	FSgetcwd, // g_data[2][12],"48"
	FSchdir,  // g_data[2][13],"52"
	FSremove, // g_data[2][14],"56"
	FSrename, // g_data[2][15],"60"
#endif
};

const void* const g_data_clib_video[]={
	start_composite,// g_data[3][0],"0"
	stop_composite, // g_data[3][1],"4"
	printchar,      // g_data[3][2],"8"
	printstr,       // g_data[3][3],"12"
	printnum,       // g_data[3][4],"16"
	printnum2,      // g_data[3][5],"20"
	cls,            // g_data[3][6],"24"
	vramscroll,     // g_data[3][7],"28"
	setcursorcolor, // g_data[3][8],"32"
	setcursor,      // g_data[3][9],"36"
	set_palette,    // g_data[3][10],"40"
	set_bgcolor,    // g_data[3][11],"44"
};

const void* const g_data_clib_graphic[]={
	g_pset,         // g_data[4][0],"0"
	g_putbmpmn,     // g_data[4][1],"4"
	g_clrbmpmn,     // g_data[4][2],"8"
	g_gline,        // g_data[4][3],"12"
	g_hline,        // g_data[4][4],"16"
	g_circle,       // g_data[4][5],"20"
	g_circlefill,   // g_data[4][6],"24"
	g_boxfill,      // g_data[4][7],"28"
	g_putfont,      // g_data[4][8],"32"
	g_printstr,     // g_data[4][9],"36"
	g_printnum,     // g_data[4][10],"40"
	g_printnum2,    // g_data[4][11],"44"
	g_color,        // g_data[4][12],"48"
};

const void* const g_data_clib_keyboard[]={
	shiftkeys, //  g_data[5][0],"0"
	ps2readkey,//  g_data[5][1],"4"
};

const void* const g_data_clib[]={
	&g_data_clib_var[0],     // g_data[0],"0"
	&g_data_clib_core[0],    // g_data[1],"4"
	&g_data_clib_file[0],    // g_data[2],"8"
	&g_data_clib_video[0],   // g_data[3],"12"
	&g_data_clib_graphic[0], // g_data[4],"16"
	&g_data_clib_keyboard[0],// g_data[5],"20"
};
 */

/*
 * MachiKanika core functions
 */

/*
 * malloc(int size);
 * calloc(int size);
 * 
 * Allocates size bytes of uninitialized storage.
*/
#define malloc(x) clib_calloc(((x)+3)>>2,g_data) 
#define calloc(x) clib_calloc(((x)+3)>>2,g_data) 
void* clib_calloc(int size, void*** g_data);

/*
 * free(void* addr);
 * 
 * Deallocates the space previously allocated by malloc() or calloc()
*/
#define free(x) clib_free(x,g_data)
void clib_free(void* addr, void*** g_data);

/*
 * MachiKanika file system functions
 * See "sdsfio370f.h" for using these functions.
 * Following functions are supported:
 *   FSInit
 *   FSfopen
 *   FSfclose
 *   FSfread
 *   FSfwrite
 *   FSfeof
 *   FSftell
 *   FSfseek
 *   FSrewind
 *   FindFirst
 *   FindNext
 *   FSmkdir
 *   FSgetcwd
 *   FSchdir
 *   FSremove
 *   FSrename
 */


/*
 * MachiKanika video functions
 */

/*
	void start_composite(void);
	//�J���[�R���|�W�b�g�o�͊J�n
*/
#define start_composite() clib_start_composite(g_data)
void clib_start_composite(void*** data);

/*
	void stop_composite(void);
	//�J���[�R���|�W�b�g�o�͒�~
*/
#define stop_composite() clib_stop_composite(g_data)
void clib_stop_composite(void*** data);

/*
	void printchar(unsigned char n);
	//�J�[�\���ʒu�Ƀe�L�X�g�R�[�hn��1�����\�����A�J�[�\����1�����i�߂�
*/
#define printchar(a) clib_printchar(a,g_data)
void clib_printchar(unsigned char n,void*** data);

/*
	void printstr(unsigned char *s);
	//�J�[�\���ʒu�ɕ�����s��\��
*/
#define printstr(a) clib_printstr(a,g_data)
void clib_printstr(unsigned char *s,void*** data);

/*
	void printnum(unsigned int n);
	//�J�[�\���ʒu�ɕ����Ȃ�����n��10�i���\��
*/
#define printnum(a) clib_printnum(a,g_data)
void clib_printnum(unsigned int n,void*** data);

/*
	void printnum2(unsigned int n,unsigned char e);
	//�J�[�\���ʒu�ɕ����Ȃ�����n��e����10�i���\���i�O�̋󂫌������̓X�y�[�X�Ŗ��߂�j
*/
#define printnum2(a,b) clib_printnum2(a,b,g_data)
void clib_printnum2(unsigned int n,unsigned char e,void*** data);

/*
	void cls(void);
	//�e�L�X�g��ʂ�0�ŃN���A���A�J�[�\������ʐ擪�Ɉړ�
*/
#define cls() clib_cls(g_data)
void clib_cls(void*** data);

/*
	void vramscroll(void);
	//1�s�X�N���[��
*/
#define vramscroll() clib_vramscroll(g_data)
void clib_vramscroll(void*** data);

/*
	void setcursorcolor(unsigned char c);
	//�J�[�\���ʒu���̂܂܂ŃJ���[�ԍ���c�ɐݒ�
*/
#define setcursorcolor(a) clib_setcursorcolor(a,g_data)
void clib_setcursorcolor(unsigned char c,void*** data);

/*
	void setcursor(unsigned char x,unsigned char y,unsigned char c);
	//�J�[�\���ʒu�ƃJ���[��ݒ�
*/
#define setcursor(a,b,c) clib_setcursor(a,b,c,g_data)
void clib_setcursor(unsigned char x,unsigned char y,unsigned char c,void*** data);

/*
	void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g);
	//�e�L�X�g�p���b�g�ݒ�
*/
#define set_palette(a,b,c,d) clib_set_palette(a,b,c,d,g_data)
void clib_set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g,void*** data);

/*
	void set_bgcolor(unsigned char b,unsigned char r,unsigned char g);
	//�o�b�N�O�����h�J���[�ݒ�
*/
#define set_bgcolor(a,b,c) clib_set_bgcolor(a,b,c,g_data)
void clib_set_bgcolor(unsigned char b,unsigned char r,unsigned char g,void*** data);


/*
 * MachiKanika graphic functions
 */

/*
	void g_pset(int x,int y,unsigned int c);
	// (x,y)�̈ʒu�ɃJ���[c�œ_��`��
*/
#define g_pset(a,b,c) clib_g_pset(a,b,c,g_data)
void clib_g_pset(int x,int y,unsigned int c,void*** data);

/*
	void g_putbmpmn(int x,int y,char m,char n,const unsigned char bmp[]);
	// ��m*�cn�h�b�g�̃L�����N�^�[�����Wx,y�ɕ\��
	// unsigned char bmp[m*n]�z��ɁA�P���ɃJ���[�ԍ�����ׂ�
	// �J���[�ԍ���0�̕����͓����F�Ƃ��Ĉ���
*/
#define g_putbmpmn(a,b,c,d,e) clib_g_putbmpmn(a,b,c,d,e,g_data)
void clib_g_putbmpmn(int x,int y,char m,char n,const unsigned char bmp[],void*** data);

/*
	void g_clrbmpmn(int x,int y,char m,char n);
	// �cm*��n�h�b�g�̃L�����N�^�[����
	// �J���[0�œh��Ԃ�
*/
#define g_clrbmpmn(a,b,c,d) clib_g_clrbmpmn(a,b,c,d,g_data)
void clib_g_clrbmpmn(int x,int y,char m,char n,void*** data);

/*
	void g_gline(int x1,int y1,int x2,int y2,unsigned int c);
	// (x1,y1)-(x2,y2)�ɃJ���[c�Ő�����`��
*/
#define g_gline(a,b,c,d,e) clib_g_gline(a,b,c,d,e,g_data)
void clib_g_gline(int x1,int y1,int x2,int y2,unsigned int c,void*** data);

/*
	void g_hline(int x1,int x2,int y,unsigned int c);
	// (x1,y)-(x2,y)�ւ̐������C���������`��
*/
#define g_hline(a,b,c,d) clib_g_hline(a,b,c,d,g_data)
void clib_g_hline(int x1,int x2,int y,unsigned int c,void*** data);

/*
	void g_circle(int x0,int y0,unsigned int r,unsigned int c);
	// (x0,y0)�𒆐S�ɁA���ar�A�J���[c�̉~��`��
*/
#define g_circle(a,b,c,d) clib_g_circle(a,b,c,d,g_data)
void clib_g_circle(int x0,int y0,unsigned int r,unsigned int c,void*** data);

/*
	void g_circlefill(int x0,int y0,unsigned int r,unsigned int c);
	// (x0,y0)�𒆐S�ɁA���ar�A�J���[c�œh��ꂽ�~��`��
*/
#define g_circlefill(a,b,c,d) clib_g_circlefill(a,b,c,d,g_data)
void clib_g_circlefill(int x0,int y0,unsigned int r,unsigned int c,void*** data);

/*
	void g_boxfill(int x1,int y1,int x2,int y2,unsigned int c);
	// (x1,y1),(x2,y2)��Ίp���Ƃ���J���[c�œh��ꂽ�����`��`��
*/
#define g_boxfill(a,b,c,d,e) clib_g_boxfill(a,b,c,d,e,g_data)
void clib_g_boxfill(int x1,int y1,int x2,int y2,unsigned int c,void*** data);

/*
	void g_putfont(int x,int y,unsigned int c,int bc,unsigned char n);
	//8*8�h�b�g�̃A���t�@�x�b�g�t�H���g�\��
	//���W�ix,y)�A�J���[�ԍ�c
	//bc:�o�b�N�O�����h�J���[�A�����̏ꍇ����
	//n:�����ԍ�
*/
#define g_putfont(a,b,c,d,e) clib_g_putfont(a,b,c,d,e,g_data)
void clib_g_putfont(int x,int y,unsigned int c,int bc,unsigned char n,void*** data);

/*
	void g_printstr(int x,int y,unsigned int c,int bc,unsigned char *s);
	//���W(x,y)����J���[�ԍ�c�ŕ�����s��\���Abc:�o�b�N�O�����h�J���[
*/
#define g_printstr(a,b,c,d,e) clib_g_printstr(a,b,c,d,e,g_data)
void clib_g_printstr(int x,int y,unsigned int c,int bc,unsigned char *s,void*** data);

/*
	void g_printnum(int x,int y,unsigned char c,int bc,unsigned int n);
	//���W(x,y)�ɃJ���[�ԍ�c�Ő��ln��\���Abc:�o�b�N�O�����h�J���[
*/
#define g_printnum(a,b,c,d,e) clib_g_printnum(a,b,c,d,e,g_data)
void clib_g_printnum(int x,int y,unsigned char c,int bc,unsigned int n,void*** data);

/*
	void g_printnum2(int x,int y,unsigned char c,int bc,unsigned int n,unsigned char e);
	//���W(x,y)�ɃJ���[�ԍ�c�Ő��ln��\���Abc:�o�b�N�O�����h�J���[�Ae���ŕ\��
*/
#define g_printnum2(a,b,c,d,e,f) clib_g_printnum2(a,b,c,d,e,f,g_data)
void clib_g_printnum2(int x,int y,unsigned char c,int bc,unsigned int n,unsigned char e,void*** data);

/*
	unsigned int g_color(int x,int y);
	//���W(x,y)��VRAM��̌��݂̃p���b�g�ԍ���Ԃ��A��ʊO��0��Ԃ�
*/
#define g_color(a,b) clib_g_color(a,b,g_data)
unsigned int clib_g_color(int x,int y,void*** data);


/*
 * MachiKanika keyboard functions
 */

/*
	unsigned char shiftkeys();
	// SHIFT�֘A�L�[�̉�����Ԃ�Ԃ�
*/
#define shiftkeys() clib_shiftkeys(g_data)
unsigned char clib_shiftkeys(void*** data);

/*
	unsigned char ps2readkey();
	// ���͂��ꂽ1�̃L�[�̃L�[�R�[�h���O���[�o���ϐ�vkey�Ɋi�[�i������Ă��Ȃ����0��Ԃ��j
	// ����8�r�b�g�F�L�[�R�[�h
	// ���8�r�b�g�F�V�t�g��ԁi�����F1�j�A��ʂ���<0><CAPSLK><NUMLK><SCRLK><Win><ALT><CTRL><SHIFT>
	// �p���E�L�������̏ꍇ�A�߂�l�Ƃ���ASCII�R�[�h�i����ȊO��0��Ԃ��j
*/
#define ps2readkey() clib_ps2readkey(g_data)
unsigned char clib_ps2readkey(void*** data);


