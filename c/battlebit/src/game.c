//
// Created by carson on 5/20/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
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

//    notes:
//    flip int player in array. needs to go both ways

    if(x >= 8 || y >= 8 || y < 0 || x < 0) {
        return 0;
    }

    if(player == 0) {
        game->status = PLAYER_0_TURN;
    } else if(player == 1) {
        game->status = PLAYER_1_TURN;
    }

    player_info *playerBeingFiredAt = &game->players[!(player)];
    player_info *playerFiring = &game->players[player];
    unsigned long long int mask = xy_to_bitval(x, y);
    unsigned long long int oShots = playerFiring->shots; // update shots value
    unsigned long long int dShips = playerBeingFiredAt->ships; // reference of ships, also need to update
    unsigned long long int oHits = playerFiring->hits; // update hits

    playerFiring->shots = oShots | mask;

////    if hit then flip
//    playerBeingFiredAt->ships;

    unsigned long long int shipResult = dShips & mask;
    if (shipResult == mask) {
        playerFiring->hits = oHits | mask;
        playerBeingFiredAt->ships = dShips - mask;
//        printf("shots: %llu \n", oShots);
//        printf("hits: %llu \n", oHits);

//      WAS A PROBLEM BECAUSE CHECKED AFTER BOTH RETURNS!

        if(player == 1) {
            game->status = PLAYER_0_TURN;
        } else if(player == 0) {
            game->status = PLAYER_1_TURN;
        }

        if(playerBeingFiredAt->ships == 0) {
            if(player == 0) {
                game->status = PLAYER_0_WINS;
            } else if(player == 1) {
                game->status = PLAYER_1_WINS;
            }
        }

        return 1;
    } else if (shipResult == 0) {

        if(player == 1) {
            game->status = PLAYER_0_TURN;
        } else if(player == 0) {
            game->status = PLAYER_1_TURN;
        }

        return 0;
    } else {
        printf("error");
    }



//    dont use ints, use ull
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



    player_info *playerInfo = &game->players[player];
//    const int possible = 10;
//    char used[possible];
    int count = 0;
    int length;

//    use this instead of used[possible] as per Prof Gross suggestion
    int seenCarrier = 0;
    int seenBattleship = 0;
    int seenDestroyer = 0;
    int seenSub = 0;
    int seenPatrol = 0;



    //    determine if length of a spec is fine (15 chars)
    //    strlen()

    if(spec == NULL) {
        return -1;
    }

//    if(strlen(spec) != 15) {
//        return -1;
//    }

    int countSpec = 0;

//  bump loop by 3 everytime
    for(int i = 0; i < 15; i+=3) {
        char * current = spec;
        char ship = *(current + i);
        char col = *(current + 1 + i);
        char row = *(current + 2 + i);
//        char two = '3';
//        int twoInt = atoi(&two);
        int colInt = col - 48;
        int rowInt = row - 48;

//        convert ascii to 0 = 48, 3 = 51,
//          deduct 48 from value

//        for (int i = 0; i < possible; i++) {
//            if(ship == used[i]) {
//                return -1;
//            }
//        }

        if (ship >= 65 && ship <= 90) {
            if(ship == 'C') {
                length = 5;
                if(seenCarrier == 1) {
                    return -1;
                }
                seenCarrier = 1;
            } else if(ship == 'B') {
                length = 4;
                if(seenBattleship == 1) {
                    return -1;
                }
                seenBattleship = 1;
            } else if(ship == 'D') {
                length = 3;
                if(seenDestroyer == 1) {
                    return -1;
                }
                seenDestroyer = 1;
            } else if(ship == 'S') {
                length = 3;
                if(seenSub == 1) {
                    return -1;
                }
                seenSub = 1;
            } else if(ship == 'P') {
                length = 2;
                if(seenPatrol == 1) {
                    return -1;
                }
                seenPatrol = 1;
            } else {
                return -1;
            }

//            TODO: NEW ERROR
            if (add_ship_horizontal(playerInfo, colInt, rowInt, length) == -1) {
                return -1;
            }
//            used[count] = ship;
//            count++;
//            used[count] = ship + 32;
//            count++;
            countSpec += 3;
        } else if(ship >= 97 && ship <= 122) {

            if(ship == 'c') {
                length = 5;
                if(seenCarrier == 1) {
                    return -1;
                }
                seenCarrier = 1;
            } else if(ship == 'b') {
                length = 4;
                if(seenBattleship == 1) {
                    return -1;
                }
                seenBattleship = 1;
            } else if(ship == 'd') {
                length = 3;
                if(seenDestroyer == 1) {
                    return -1;
                }
                seenDestroyer = 1;
            } else if(ship == 's') {
                length = 3;
                if(seenSub == 1) {
                    return -1;
                }
                seenSub = 1;
            } else if(ship == 'p') {
                length = 2;
                if(seenPatrol == 1) {
                    return -1;
                }
                seenPatrol = 1;
            } else {
                return -1;
            }

            if (add_ship_vertical(playerInfo, colInt, rowInt, length) == -1) {
                return -1;
            }
//            used[count] = ship;
//            count++;
//            used[count] = ship - 32;
//            count++;
            countSpec += 3;
        } else {
            return -1;
        }
    }

    if(countSpec != 15) {
        return -1;
    }

    if(player == 1) {
        game->status = PLAYER_0_TURN;
    } else if(player == 0) {
        game->status = CREATED;
    }
    return 1;
}

int add_ship_horizontal(player_info *player, int x, int y, int length) {
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively


    // check to make sure that x and y are on the board (between 0 and 7)
    // this needs to be in recursive so doesnt run off ^W

    if(length == 0) {
        return 1;
    }

    if(!((x >= 0 && x <= 8) || (y >= 0 && y <= 8))) {
        return -1;
    }

    // check if already ship at position x, y
    unsigned long long int mask = xy_to_bitval(x, y);
    unsigned long long int ship = player->ships;
    unsigned long long int result = ship | mask;

    if(ship == result) {
        return -1;
    }

    // flip the players ships bit to 1
    // SET RESULTS == player->SHIPS
    player->ships = result;

    // decrease ship length, manipulate x and y (first for 0 check)
    x++;
    length--;

    // recursively call add_ship_horizontal
    if(length != 0) {
        add_ship_horizontal(player, x, y, length);
    }

    return 1;
}

int add_ship_vertical(player_info *player, int x, int y, int length) {
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively

    if(length == 0) {
        return 1;
    }

    // check to make sure that x and y are on the board (between 0 and 7)
    // this needs to be in recursive so doesnt run off ^
    if(!((x >= 0 && x <= 8) || (y >= 0 && y <= 8))) {
        return -1;
    }

    // check if already ship at position x, y
    unsigned long long int mask = xy_to_bitval(x, y);
    unsigned long long int ship = player->ships;
    unsigned long long int result = ship | mask;

    if(ship == result) {
        return -1;
    }

    // flip the players ships bit to 1
    // SET RESULTS == player->SHIPS
    player->ships = result;

    // decrease ship length, manipulate x and y (first for 0 check)
    y++;
    length--;

    // recursively call add_ship_horizontal
    if(length != 0) {
        add_ship_vertical(player, x, y, length);
    }

    return 1;
}