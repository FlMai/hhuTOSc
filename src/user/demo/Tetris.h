#ifndef __tetris_include__
#define __tetris_include__

#include "kernel/threads/Thread.h"

class Tetris : public Thread {
    
private:
    Tetris (const Tetris &copy); // Verhindere Kopieren
    void draw_outlines();
    bool scroll_down(int *g);
    bool check_scroll_signal(char *c);
    char check_kb_signal();
    void update_collisions(bool value, int *p, int l);
    void select_next_piece(int *p);
    bool compare_pieces(int *n, int *o);
    void draw_game_piece(int *n, int *o);
    void copy_game_piece(int *n, int *o);
    void move_piece_left(int *p);
    void move_piece_right(int *p);
    void check_full_rows();

    uint8_t *shared_mem_kb;
    uint8_t *shared_mem_scroll_down;

    bool collision_points[20*10];           // can hold entire play field

public:
    Tetris (uint8_t *shared_mem, uint8_t *shared_mem_scroll_down) {
        this->shared_mem_kb = shared_mem;
        this->shared_mem_scroll_down = shared_mem_scroll_down;
    }
    void run ();
};

#endif