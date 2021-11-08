//
// Created by carson on 5/20/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"

// STEP 9 - Synchronization: the GAME structure will be accessed by both players interacting
// asynchronously with the server.  Therefore the data must be protected to avoid race conditions.
// Add the appropriate synchronization needed to ensure a clean battle.

static game * GAME = NULL;

void game_init() {
    if (GAME) {
        free(GAME);
    }
    GAME = malloc(sizeof(game));
    GAME->status = CREATED;
    game_init_player_info(&GAME->players[0]);
    game_init_player_info(&GAME->players[1]);
}

void game_init_player_info(player_info *player_info) {
    player_info->ships = 0;
    player_info->hits = 0;
    player_info->shots = 0;
}

int game_fire(game *game, int player, int x, int y) {
    // Step 5 - This is the crux of the game.  You are going to take a shot from the given player and
    // update all the bit values that store our game state.
    //
    //  - You will need up update the players 'shots' value
    //  - you You will need to see if the shot hits a ship in the opponents ships value.  If so, record a hit in the
    //    current players hits field
    //  - If the shot was a hit, you need to flip the ships value to 0 at that position for the opponents ships field
    //
    //  If the opponents ships value is 0, they have no remaining ships, and you should set the game state to
    //  PLAYER_1_WINS or PLAYER_2_WINS depending on who won.
}

unsigned long long int xy_to_bitval(int x, int y) {
    // Step 1 - implement this function.  We are taking an x, y position
    // and using bitwise operators, converting that to an unsigned long long
    // with a 1 in the position corresponding to that x, y
    //
    // x:0, y:0 == 0b00000...0001 (the one is in the first position)
    // x:1, y: 0 == 0b00000...10 (the one is in the second position)
    // ....
    // x:0, y: 1 == 0b100000000 (the one is in the eighth position)
    //
    // you will need to use bitwise operators and some math to produce the right
    // value.
    unsigned long long x_bit = x;
    unsigned long long y_bit = y;
    unsigned long long val = 1ull;
    unsigned long long increment = 0;

    if (x >= 8 || x < 0 || y >= 8 || y < 0) {
        return 0;
    }

    if (x == 0 && y == 0) {
        return 1ull;
    }

    if (y > 0) {
        increment = 8 * y;
    }

    increment += x;
    val = val << increment;
    return val;
}

struct game * game_get_current() {
    return GAME;
}

int game_load_board(struct game *game, int player, char * spec) {
    // Step 2 - implement this function.  Here you are taking a C
    // string that represents a layout of ships, then testing
    // to see if it is a valid layout (no off-the-board positions
    // and no overlapping ships)
    //

    // if it is valid, you should write the corresponding unsigned
    // long long value into the Game->players[player].ships data
    // slot and return 1
    //
    // if it is invalid, you should return -1


//  bump loop by 3 everytime
//    determine if length of a spec is fine (15 chars)
//    strlen()
//    char * current = spec;
//    char ship = *current;
//    char col = *(current + 1);
//    char row = *(current + 2);
//    do this in a loop
//
//    int colInt = 0; //somthing something
//    int rowInt = 0; //something something
//
//    if (add_ship_horizonatl (playerInfo, colInt, rowInt, length) == -1) {
//             return -1;
//    }
//
//    player_info *playerInfo = &game->players[player];
//
//
//    checks:
//    keep track of ships we've seen
//
//    call add shi phoriz and vert
//    if -1 return -1

}

int add_ship_horizontal(player_info *player, int x, int y, int length) {
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively

//    check to make sure that x and y are on the board (between 0 and 7)
//      this needs to be in recursive so doesnt run off ^

//      check if already ship at position x, y
    unsigned long long int mask = xy_to_bitval(x, y);
    player->ships;

//      flip the players ships bit to 1
//      recursively call add_ship_horizontal
//      decrease ship length, manipualte x and y
}

int add_ship_vertical(player_info *player, int x, int y, int length) {
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively



}