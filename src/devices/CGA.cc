/*****************************************************************************
 *                                                                           *
 *                                    C G A                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man auf den Bildschirm des  *
 *                  PCs zugreifen. Der Zugriff erfolgt direkt auf der Hard-  *
 *                  wareebene, d.h. ueber den Bildschirmspeicher und den     *
 *                  I/O-Ports der Grafikkarte.                               *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 21.8.2016       *
 *****************************************************************************/
#include "devices/CGA.h"


/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {

    unsigned short position = x + y * CGA::COLUMNS;

    CGA::index_port.outb(15);
    CGA::data_port.outb(position & 0xff);
    CGA::index_port.outb(14);
    CGA::data_port.outb((position >> 8 ) & 0xff);

}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {

    unsigned short position;

    CGA::index_port.outb(14);
    position = CGA::data_port.inb() << 8;
    CGA::index_port.outb(15);
    position = position | CGA::data_port.inb();

    y = (unsigned short)(position / CGA::COLUMNS);
    x = position - (y * CGA::COLUMNS);
}


/*****************************************************************************
 * Methode:         CGA::show                                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens mit Attribut an einer bestimmten  *
 *                  Stelle auf dem Bildschirm.                               *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {

    // prevent arbitrary writing to memory 
    if(x > 79 || y > 24 || x < 0 || y < 0){
        return;
    }
    
    char *pos = (char *)(CGA::CGA_START + 2*(x+y*80));
    *pos = character;
    *(pos + 1) = attrib;

}


/*****************************************************************************
 * Methode:         CGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige von 'n' Zeichen ab der aktuellen Cursorposition  *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
    
    int x;
    int y;

    for(int i = 0; i < n; i++){
        getpos(x, y);
        
        if(string[i] == '\n'){
            if(y == 24){
                scrollup();
                setpos(0, y);
            } else {
                setpos(0, y+1);
            }
        } else {

            CGA::show(x, y, string[i], attrib);
            
            if(x > 79) {
                CGA::setpos(0, y+1);
            } else if (x == 79 && y == 24) {
                scrollup();
                setpos(0, y);
            } else {
                CGA::setpos(x+1, y);
            }
        }
    }

}


/*****************************************************************************
 * Methode:         CGA::scrollup                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verschiebt den Bildschirminhalt um eine Zeile nach oben. *
 *                  Die neue Zeile am unteren Bildrand wird mit Leerzeichen  *
 *                  gefuellt.                                                *
 *****************************************************************************/
void CGA::scrollup () {
    
    int x, y, initial_x, initial_y;

    CGA::getpos(initial_x, initial_y);

    for(int h = 0; h < 80; h++){
        for(int v = 0; v < 24; v++) {
            CGA::setpos(h, v+1);
            CGA::getpos(x, y);
            char *cursor = (char *)(CGA::CGA_START + 2*(x+y*80));
            char tmp = *cursor;
            char tmpAttrib = *(cursor+1);
            CGA::show(h, v, tmp, tmpAttrib);
        }
    }

    for(int v = 0; v < 80; v++){
        CGA::show(v, 24, ' ', 0x00);
    }

    if(initial_y == 24) {
        setpos(initial_x, initial_y);
    } else if (initial_y == 0) {
        setpos(initial_x, 0);
    } else {
        setpos(initial_x, initial_y-1);
    }
}

void CGA::tetris_scroll(int row) {
    int x, y;
    for(int h = 35; h < 45; h++){
        for(int v = row; v > 4; v--) {
            CGA::setpos(h, v-1);
            CGA::getpos(x, y);
            char *cursor = (char *)(CGA::CGA_START + 2*(x+y*80));
            char tmp = *cursor;
            char tmpAttrib = *(cursor+1);
            CGA::show(h, v, tmp, tmpAttrib);
        }
    }
}


/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
    
    for(int j = 0; j < 25; j++) {
        for(int i = 0; i < 80; i++) {
            show(i,j, ' ', 0x00);
        }
    }
    setpos(0,0);
    
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
    
    unsigned char attr = 0b0000'0000;
    if(blink) {
        attr |= 0b1000'0000;
    }

    if(bg > 7) {
        // bg has only 3 bits, how to handle / choose default
    } else {
        attr |= (bg << 4);
    }

    attr |= fg;

    return attr;

}