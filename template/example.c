/***********************************
 *                                 *
 * Template of CLIB for MachiKania *
 *                                 *
 ***********************************/
#include <xc.h>
#include "./clib.h"

// The init() function is called at initiation.
// The initializations of global variables must be done here.
// �֐�init()�́A�������̍ۂɌĂ΂��B
// �O���[�o���ϐ��̏������́A���̊֐����ōs�Ȃ��K�v����B
void init(void){
}

// Example of functions.
// Maximum number of parameter(s) is 4 for public function.
// Do not initialize static variables in the function.
// It will be always initialize with 0 value.
// �֐��̎�����B
// �p�u���b�N�֐��ł́A�����͍ő�S�܂ŁB
// �֐����ŁA�X�^�e�B�b�N�ϐ��̏��������s�Ȃ�Ȃ����B
// �X�^�e�B�b�N�ϐ��́A��ɒl�O�ŏ����������B
char* test_private(int param1){
	switch(param1){
		case 0:
			cls();
			printstr("CLIB test.");
			return "Hello World!";
		default:
			return "This is a test";
	}
}

char* test_public(int param1){
	return test_private(param1);
}

// The list of public function(s)
// This defines the function name(s) and function address(s)
// Length of the name of function must be between 2 and 6 bytes,
// and contain only A-Z, _, and 0-9 as characters.
// This array must end with 0.
// �p�u���b�N�֐��̃��X�g�B
// �֐����ƁA�֐��̃A�h���X���w�肷��B
// �֐����̒�����2-6�o�C�g�ŁA�p�����ƃA���_�[�X�R�A�݂̂��܂ޕ�����B
// ���̔z��̍ŏI�v�f�́A0 �Ƃ��邱�ƁB
const void* const functions[]={
	"TEST",test_public,
	0
};
