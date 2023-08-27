#include "kernel/Globals.h"
#include "lib/Input.h"


void text_demo() {

   kout.clear();
   kout << "Test der Bildschirmausgbe und Tastaturfunktion.\n" << endl;

   kout << "|-----------------------------------------------------------------------|" << endl;
   kout << "|    dec    |      hex      |         oct         |         bin         |" << endl;
   kout << "|-----------------------------------------------------------------------|" << endl;
   kout << "|        " << dec << 0 << "  ";
   kout << "|   " << hex << 0 << "         ";
   kout << "|   " << oct << 0 << "                ";
   kout << "|   " << bin << 0 << "                 |" << endl;

   kout << "|       " << dec << 10 << "  ";
   kout << "|   " << hex << 10 << "         ";
   kout << "|   " << oct << 10 << "               ";
   kout << "|   " << bin << 10 << "              |" << endl;

   kout << "|      " << dec << 100 << "  ";
   kout << "|   " << hex << 100 << "        ";
   kout << "|   " << oct << 100 << "              ";
   kout << "|   " << bin << 100 << "           |" << endl;

   kout << "|     " << dec << 1000 << "  ";
   kout << "|   " << hex << 1000 << "       ";
   kout << "|   " << oct << 1000 << "             ";
   kout << "|   " << bin << 1000 << "        |" << endl;

   kout << "|    " << dec << 10000 << "  ";
   kout << "|   " << hex << 10000 << "      ";
   kout << "|   " << oct << 10000 << "            ";
   kout << "|   " << bin << 10000 << "    |" << endl;

   while (true) {
      char k = getch();
      if (k == 'r') kb.reboot();
      kout.print(&k, 1);
   }

}
