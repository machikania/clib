/***********************************
 *                                 *
 * Template of CLIB for MachiKania *
 *                                 *
 ***********************************/
#include <xc.h>
#include "./clib.h"

// The init() function is called at initiation.
// The initializations of global variables must be done here.
// 関数init()は、初期化の際に呼ばれる。
// グローバル変数の初期化は、この関数内で行なう必要あり。
void init(void){
}

// Example of functions.
// Maximum number of parameter(s) is 4 for public function.
// Do not initialize static variables in the function.
// It will be always initialize with 0 value.
// 関数の実装例。
// パブリック関数では、引数は最大４つまで。
// 関数中で、スタティック変数の初期化を行なわない事。
// スタティック変数は、常に値０で初期化される。
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
// パブリック関数のリスト。
// 関数名と、関数のアドレスを指定する。
// 関数名の長さは2-6バイトで、英数字とアンダースコアのみを含む文字列。
// この配列の最終要素は、0 とすること。
const void* const functions[]={
	"TEST",test_public,
	0
};
