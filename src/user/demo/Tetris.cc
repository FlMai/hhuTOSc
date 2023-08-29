#include "user/demo/Tetris.h"
#include "kernel/Globals.h"
#include "lib/Input.h"
#include "user/demo/ScrollThread.h"
#include "user/demo/KeyboardThread.h"
#include "user/demo/SoundDemo.h"

void Tetris::run () {
    kout.clear();

    kout.setpos(5,1);
    kout << "Press Enter to start." << endl;
    kout << "A - Move current piece to the left." << endl;
    kout << "S - Move current piece down." << endl;
    kout << "D - Move current piece right." << endl;
    kout << "IPC via shared memory at:" << endl << shared_mem_kb << " for Keyboard Thread." << endl << shared_mem_scroll_down << " for game ticks." << endl; 

    waitForReturn();
    kout.clear();
    draw_outlines();
    ScrollThread *scroll_timer = new ScrollThread(shared_mem_scroll_down);
    KeyboardThread *kbt = new KeyboardThread(shared_mem_kb);
    scheduler.ready(kbt);
    scheduler.ready(scroll_timer);

    char scroll_signal = 0x0;

    int game_piece[8];                      // current piece coordinates
    int old_game_piece[8];                  // old coordinates

    select_next_piece(game_piece);

    bool next_piece = false;
    bool scroll_by_player = false;

    while(true) { 
        copy_game_piece(game_piece, old_game_piece);
        char command = check_kb_signal();
        if (command != 0x0) {
            switch (command)
            {
            case 'a':
                move_piece_left(game_piece);
                break;
            case 'd':
                move_piece_right(game_piece);
                break;
            case 's':
                scroll_by_player = true;
                break;
            default:
                break;
            }
        }
        if (check_scroll_signal(&scroll_signal) || scroll_by_player) {
            scroll_by_player = false;
            next_piece = scroll_down(game_piece);
        }
        cpu.disable_int();
        check_full_rows();
        cpu.enable_int();

        if (next_piece) {
            select_next_piece(game_piece);
            continue;
        }

        if (!compare_pieces(game_piece, old_game_piece)) {               // old and new same = dont redraw
            continue;
        } else {
            draw_game_piece(game_piece, old_game_piece);                    // erease old game_piece, draw new one
        }
    }
}

void Tetris::check_full_rows() {
    for (int i = 0; i < 20; i++) {
        bool full = false;
        for (int j = 0; j < 10; j++) {      // test for full row
            if (!collision_points[i*10+j]) {
                full = false;
                break;
            }
            full = true;
        }
        if (full) {
            for (int x = i; x > 0; x--) {
                for (int y = 0; y <10; y++) {
                    collision_points[x*10+y] = collision_points[(x-1)*10+y];     // move all collisons one down
                }
            }
            for (int y = 0; y <10; y++) {
                collision_points[y] = false;        // set new top row
            }
            kout.tetris_scroll(i+4);
            i--;            // test new row, this is nor *true* tetris
        }
    }
}

void Tetris::copy_game_piece(int *game_piece, int *old_game_piece) {
    for (int i = 0; i < 8; i++) {
        old_game_piece[i] = game_piece[i];
    }
}

bool Tetris::compare_pieces(int *game_piece, int *old_game_piece) {
    for (int i = 0; i< 9; i++) {
        if (game_piece[i] != old_game_piece[i]) return true;
    }
    return false;
}

void Tetris::draw_game_piece(int *game_piece, int *old_games_piece) {
    cpu.disable_int();
    for (int i = 0; i < 9; i += 2) {
        kout.show(old_games_piece[i], old_games_piece[i+1], ' ');
    }
    for (int i = 0; i < 9; i += 2) {
        kout.show(game_piece[i], game_piece[i+1], '*');
    }
    cpu.enable_int();
}

void Tetris::select_next_piece(int *game_piece) {
    uint64_t s = systime;
    s = s % 7;
    switch (s)
    {
    case 0:     // flat piece
        game_piece[0] = 38;
        game_piece[2] = 39;
        game_piece[4] = 40;
        game_piece[6] = 41;
        for (int i = 1; i < 8; i += 2) {
            game_piece[i] = 4;
        }
        break;
    case 1:     // l left
        game_piece[0] = 39;
        game_piece[1] = 3;
        game_piece[2] = 39;
        game_piece[3] = 4;
        game_piece[4] = 40;
        game_piece[5] = 4;
        game_piece[6] = 41;
        game_piece[7] = 4;
        break;
    case 2:     // l right
        game_piece[0] = 39;
        game_piece[1] = 4;
        game_piece[2] = 40;
        game_piece[3] = 4;
        game_piece[4] = 41;
        game_piece[5] = 4;
        game_piece[6] = 41;
        game_piece[7] = 3;
        break;
    case 3:     // quader
        game_piece[0] = 39;
        game_piece[1] = 3;
        game_piece[2] = 39;
        game_piece[3] = 4;
        game_piece[4] = 40;
        game_piece[5] = 3;
        game_piece[6] = 40;
        game_piece[7] = 4;
        break;
    case 4:     // stairs r
        game_piece[0] = 38;
        game_piece[1] = 4;
        game_piece[2] = 39;
        game_piece[3] = 4;
        game_piece[4] = 39;
        game_piece[5] = 3;
        game_piece[6] = 40;
        game_piece[7] = 4;
        break;
    case 5:     // stair l
        game_piece[0] = 38;
        game_piece[1] = 4;
        game_piece[2] = 39;
        game_piece[3] = 4;
        game_piece[4] = 40;
        game_piece[5] = 4;
        game_piece[6] = 39;
        game_piece[7] = 3;
        break;
    case 6:     // pyramid
        game_piece[0] = 38;
        game_piece[1] = 3;
        game_piece[2] = 39;
        game_piece[3] = 3;
        game_piece[4] = 39;
        game_piece[5] = 4;
        game_piece[6] = 40;
        game_piece[7] = 4;
        break;     
    default:
        break;
    }
}

char Tetris::check_kb_signal() {
    cpu.disable_int();
    char tmp = *shared_mem_kb;
    if (tmp != 0x0) *shared_mem_kb = 0x0;
    cpu.enable_int();
    return tmp;
}

bool Tetris::check_scroll_signal(char *current) {
    cpu.disable_int();
    if (*current != *shared_mem_scroll_down) {
        *current = *shared_mem_scroll_down;
        cpu.enable_int();
        return true;
    }
    cpu.enable_int();
    return false;
}

bool Tetris::scroll_down(int *game_piece) {
    cpu.disable_int();
    for (int i = 0; i < 8; i += 2) {
        if (collision_points[(game_piece[i] - 35) + ((game_piece[i+1] - 4) * 10)+10] || game_piece[i+1] + 1 == 24) {
            update_collisions(true, game_piece, 8);
            cpu.enable_int();
            return true;
        }
    }
    cpu.enable_int();
    for (int i = 1; i < 8; i += 2) {
        game_piece[i] += 1;
    }
    return false;
}

void Tetris::update_collisions(bool value, int *positions, int length) {
    for (int i = 0; i < length; i+=2) {
        collision_points[positions[i] - 35 + ((positions[i+1] - 4) * 10)] = value;
    }
}

void Tetris::move_piece_left(int *game_piece) {
    for (int i = 0; i < 8; i+=2) {
        if (game_piece[i] - 1 == 34 || collision_points[game_piece[i] - 35 + ((game_piece[i+1] - 4)*10) - 1]) {
            return;
        }
    }
    for (int i = 0; i < 8; i+=2) {
        game_piece[i] -= 1;
    }
}

void Tetris::move_piece_right(int *game_piece) {
    for (int i = 0; i < 8; i+=2) {
        if (game_piece[i] + 1 == 45 || collision_points[game_piece[i] - 35 + ((game_piece[i+1] - 4)*10) + 1]) {
            return;
        }
    }
    for (int i = 0; i < 8; i+=2) {
        game_piece[i] += 1;
    }
}


void Tetris::draw_outlines() {
    for (int i = 4; i < 25; i++) {
        kout.show(34, i, '|');
        kout.show(45, i, '|');
    }
    for (int i = 35; i < 45; i++) {
        kout.show(i, 24, '-');
    }
}