/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "kernel/Globals.h"


void text_demo() {

   kout.clear();
   kout << "Test der Bildschirmaufagbe.\n" << endl;
   kout << "|--------------------|" << endl;
   kout << "| dec | hex  | bin   |" << endl;
   kout << "|------------------- |" << endl;
   kout << "| 0   | 0x0  | 0001  |" << endl;
   kout << "| 2   | 0x2  | 0010  |" << endl;
   kout << "| 3   | 0x3  | 0011  |" << endl;
   kout << "| 4   | 0x4  | 0100  |" << endl;
   kout << "| 5   | 0x5  | 0101  |" << endl;
   kout << "| 6   | 0x6  | 0110  |" << endl;
   kout << "| 7   | 0x7  | 0111  |" << endl;
   kout << "| 8   | 0x8  | 1000  |" << endl;
   kout << "| 9   | 0x9  | 1001  |" << endl;
   kout << "| 10  | 0xa  | 1010  |" << endl;
   kout << "| 11  | 0xb  | 1011  |" << endl;
   kout << "| 12  | 0xc  | 1100  |" << endl;
   kout << "| 13  | 0xd  | 1101  |" << endl;
   kout << "| 14  | 0xe  | 1110  |" << endl;
   kout << "| 15  | 0xf  | 1111  |" << endl;
   kout << "| 16  | 0x10 | 10000 |" << endl;
   kout << "|--------------------|" << endl;

}
