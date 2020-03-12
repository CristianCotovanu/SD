#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List node which contains information about one football player.
typedef struct Player {
    char *name;                    // player's name
    char *position;                // player's game position
    int score;                    // player's score
    int injured;                // indicator for injury (1 true, 0 false)
    struct Player *next;        // next list node
    struct Player *prev;        // previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
    char *name;                    // club's name
    Player *players;            // list with players in good shape
    Player *injured_players;    // list with injured players
    struct FootballClub *next;    // next list node
} FootballClub;

void destroy_player_list();

void destroy_club_list();

void remove_player();

//Adauga si aloca jucator in orice tip de lista Player*
void add_player_aux(Player **players_list, char *name, 
                    char *position, int score, int injured) {
    Player *new_player = (Player *) calloc(1, sizeof(Player)),
            *players = *players_list;
    new_player->name = (char *) calloc(strlen(name) + 1, sizeof(char));
    new_player->position = (char *) calloc(strlen(position) + 1, sizeof(char));
    new_player->score = score;
    new_player->injured = injured;
    if (new_player->name == NULL) {
        destroy_player_list(new_player);
        return;
    }
    if (new_player->position == NULL) {
        destroy_player_list(new_player);
        return;
    }
    strcpy(new_player->name, name);
    strcpy(new_player->position, position);

    if (players == NULL) {
        (*players_list) = new_player;
        (*players_list)->next = NULL;
        (*players_list)->prev = NULL;
        return;
    }
    Player *last = NULL;
    while (players != NULL) {
        if (strcmp(position, players->position) < 0) {
            break;
            // Daca au aceeasi pozitie se trece la urmatorul criteriu
        } else if (strcmp(position, players->position) == 0) {
            if (score > players->score)
                break;

            // Daca au acelasi scor se trece la urmatorul
            if (score == players->score) {
                if (strcmp(name, players->name) < 0)
                    break;
            }
        }
        last = players;
        players = players->next;
    }

    if (players == NULL) {
        last->next = new_player;
        new_player->prev = last;
        new_player->next = NULL;
        return;
    } else if (players->prev == NULL) {
        new_player->next = players;
        players->prev = new_player;
        *players_list = new_player;
        return;
    } else {
        new_player->next = players;
        new_player->prev = players->prev;
        players->prev->next = new_player;
        players->prev = new_player;
        return;
    }
}

//Extrage un jucator din orice tip de lista, il returneaza si il scoate din lista respectiva
Player *get_player_aux(Player **players_list, char *player_name) {
    Player *p = *players_list;

    if (p == NULL) {
        return NULL;
    }

    while (p != NULL && strcmp(player_name, p->name) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        //Lista nu contine jucatorul
        return NULL;
    } else if (p->prev == NULL && p->next == NULL) {
        *players_list = NULL;
        return p;
    } else if (p->next == NULL) {
        p->prev->next = NULL;
        return p;
    } else if (p->prev == NULL) {
        *players_list = p->next;
        p->next->prev = NULL;
        return p;
    } else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        return p;
    }
}

FootballClub *initialize_clubs(int clubs_no, char **names) {
    int i;
    FootballClub *aux_clubs = NULL, *clubs_list = NULL, *new_club;

    if (names == NULL) {
        //Lista cu nume este goala
        return NULL;
    }

    for (i = 0; i < clubs_no; i++) {
        new_club = calloc(1, sizeof(FootballClub));
        new_club->name = calloc(strlen(names[i]) + 1, sizeof(char));
        new_club->next = NULL;
        new_club->players = NULL;
        new_club->injured_players = NULL;
        strcpy(new_club->name, names[i]);

        if (i == 0) {
            aux_clubs = new_club;
            clubs_list = aux_clubs;
        } else {
            aux_clubs->next = new_club;
            aux_clubs = aux_clubs->next;
        }
    }
    return clubs_list;
}

FootballClub *add_club(FootballClub *clubs, char *name) {
    FootballClub *aux_clubs = clubs;
    FootballClub *new_club = (FootballClub *) calloc(1, sizeof(FootballClub));

    if (new_club == NULL) {
        //Alocarea clubului nu a reusit
        return NULL;
    }

    new_club->name = (char *) calloc(strlen(name) + 1, sizeof(char));

    if (new_club->name == NULL) {
        //Alocarea numelui nu a reusit
        free(new_club);
        return NULL;
    }

    new_club->players = NULL;
    new_club->injured_players = NULL;
    new_club->next = NULL;
    strcpy(new_club->name, name);

    if (clubs == NULL) {
        return new_club;
    }

    while (aux_clubs->next != NULL) {
        aux_clubs = aux_clubs->next;
    }
    aux_clubs->next = new_club;
    return clubs;
}

void add_player(FootballClub *clubs, char *club_name,
                char *player_name, char *position, int score) {
    FootballClub *c = clubs;

    if (c == NULL) {
        //Lista de cluburi goala
        return;
    }
    while (c != NULL && strcmp(c->name, club_name) != 0) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista
        return;
    }
    add_player_aux(&(c->players), player_name, position, score, 0);
}

void transfer_player(FootballClub *clubs, char *player_name,
                     char *old_club, char *new_club) {
    FootballClub *old = clubs, *new = clubs;
    Player *transfered_player;

    while (old != NULL && strcmp(old->name, old_club) != 0) {
        old = old->next;
    }
    while (new != NULL && strcmp(new->name, new_club) != 0) {
        new = new->next;
    }
    if (new == NULL || old == NULL) {
        //Unul dintre cluburi nu se gaseste in lista
        return;
    }

    transfered_player = get_player_aux(&(old->players), player_name);
    //Verificare lista de playeri goala si intrare in lista de jucatori accidentati
    if (transfered_player == NULL) {
        transfered_player = get_player_aux(&(old->injured_players), player_name);
        if (transfered_player == NULL) {
            return;
        } else {
            //Adaugare in lista de jucatori accidentati 
            add_player_aux(&(new->injured_players), transfered_player->name,
                    transfered_player->position, transfered_player->score, 1);
            free(transfered_player->name);
            free(transfered_player->position);
            free(transfered_player);
            remove_player(clubs, old_club, player_name);
            return;
        }
    }

    add_player_aux(&(new->players), transfered_player->name,
                   transfered_player->position, transfered_player->score, 0);
    free(transfered_player->name);
    free(transfered_player->position);
    free(transfered_player);
    remove_player(clubs, old_club, player_name);
}


void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
    Player *p;
    FootballClub *c = clubs;

    if (c == NULL) {
        //Lista de cluburi este goala
        return;
    }

    while (c != NULL && strcmp(club_name, c->name) != 0) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista
        return;
    }

    p = get_player_aux(&(c->players), player_name);
    if (p == NULL) {
        //Lista cu jucatori neaccidentati nu contine jucatorul
        p = get_player_aux(&(c->injured_players), player_name);
        if (p == NULL) {
            //Lista cu jucatori accidentati nu contine jucatorul
            return;
        } else if (p->prev == NULL) {
            c->injured_players = p->next;
            free(p->name);
            free(p->position);
            free(p);
            return;
        }
    } else if (p->prev == NULL) {
        c->players = p->next;
        free(p->name);
        free(p->position);
        free(p);
        return;
    }
    free(p->name);
    free(p->position);
    free(p);
}

void update_score(FootballClub *clubs, char *club_name,
                  char *player_name, int score) {
    FootballClub *c = clubs;
    Player *updated_player;
    while (strcmp(c->name, club_name) != 0 && c != NULL) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista        
        return;
    }
    updated_player = get_player_aux(&(c->players), player_name);
    if (updated_player == NULL) {
        //Jucatorul nu se gaseste in lista de jucatori neaccidentati
        updated_player = get_player_aux(&(c->injured_players), player_name);
        if (updated_player == NULL) {
            //Jucatorul nu se gaseste in lista de jucatori accidentati
            return;
        }
        updated_player->next = NULL;
        updated_player->prev = NULL;
        add_player_aux(&(c->injured_players), updated_player->name,
             updated_player->position, score, 1);
        destroy_player_list(updated_player);
        return;
    }
    updated_player->next = NULL;
    updated_player->prev = NULL;
    add_player_aux(&(c->players), updated_player->name, 
            updated_player->position, score, 0);
    destroy_player_list(updated_player);
}

void update_game_position(FootballClub *clubs, char *club_name,
                          char *player_name, char *position, int score) {
    FootballClub *c = clubs;
    Player *updated_player;
    while (strcmp(c->name, club_name) != 0 && c != NULL) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista
        return;
    }

    updated_player = get_player_aux(&(c->players), player_name);

    if (updated_player == NULL) {
        //Jucatorul nu se gaseste in lista de jucatori neaccidentati
        updated_player = get_player_aux(&(c->injured_players), player_name);
        if (updated_player == NULL) {
            //Jucatorul nu se gaseste in lista de jucatori neaccidentati
            return;
        } else {
            updated_player->next = NULL;
            updated_player->prev = NULL;
            add_player_aux(&(c->injured_players), 
                updated_player->name, position, score, 1);
            destroy_player_list(updated_player);
            return;
        }
    }

    updated_player->next = NULL;
    updated_player->prev = NULL;
    add_player_aux(&(c->players), updated_player->name, position, score, 0);
    destroy_player_list(updated_player);
}

void add_injury(FootballClub *clubs, char *club_name,
                char *player_name, int days_no) {
    FootballClub *c = clubs;
    Player *updated_player;
    int new_score = 0;
    while (c != NULL && strcmp(c->name, club_name) != 0) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista
        return;
    }

    updated_player = get_player_aux(&(c->players), player_name);

    if (updated_player == NULL) {
        //Jucatorul nu se gaseste in lista cu jucatori neaccidentati
        return;
    }
    if (days_no % 10 != 0)
        days_no = days_no + 10;
    new_score = updated_player->score - days_no / 10;
    if (new_score >= -100 && new_score <= 100) {
        updated_player->score = new_score;
    }
    add_player_aux(&(c->injured_players), updated_player->name,
                   updated_player->position, updated_player->score, 1);
    free(updated_player->name);
    free(updated_player->position);
    free(updated_player);
}

void recover_from_injury(FootballClub *clubs, char *club_name,
                         char *player_name) {
    FootballClub *c = clubs;
    Player *updated_player;
    while (strcmp(c->name, club_name) != 0 && c != NULL) {
        c = c->next;
    }
    if (c == NULL) {
        //Clubul nu se gaseste in lista
        return;
    }
    updated_player = get_player_aux(&(c->injured_players), player_name);

    if (updated_player == NULL) {
        //Jucatorul nu se gaseste in lista
        return;
    }

    add_player_aux(&(c->players), updated_player->name, 
            updated_player->position, updated_player->score, 0);
    free(updated_player->name);
    free(updated_player->position);
    free(updated_player);
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
    Player *aux_player;

    while (player != NULL) {
        aux_player = player;
        player = player->next;
        if (aux_player->position != NULL)
            free(aux_player->position);
        if (aux_player->name != NULL)
            free(aux_player->name);
        free(aux_player);
    }
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
    FootballClub *aux_club;

    while (clubs != NULL) {
        aux_club = clubs;
        clubs = clubs->next;
        if (aux_club->players != NULL)
            destroy_player_list(aux_club->players);
        if (aux_club->injured_players != NULL)
            destroy_player_list(aux_club->injured_players);
        // if (aux_club->name != NULL)
        free(aux_club->name);
        free(aux_club);
    }
}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
    fprintf(f, "P: ");
    Player *player = players;
    while (player) {
        fprintf(f, "(%s, %s, %d, %c) ",
                player->name,
                player->position,
                player->score,
                player->injured ? 'Y' : '_');
        player = player->next;
    }
    if (free_memory) {
        destroy_player_list(players);
    }
    fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
    fprintf(f, "P: ");
    Player *player = players;
    if (player) {
        while (player->next) {
            player = player->next;
        }
        while (player) {
            fprintf(f, "(%s, %s, %d, %c) ",
                    player->name,
                    player->position,
                    player->score,
                    player->injured ? 'Y' : '_');
            player = player->prev;
        }
    }
    if (free_memory) {
        destroy_player_list(players);
    }
    fprintf(f, "\n");
}


// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
    fprintf(f, "FCs:\n");
    while (clubs) {
        fprintf(f, "%s\n", clubs->name);
        fprintf(f, "\t");
        show_list(f, clubs->players, 0);
        fprintf(f, "\t");
        show_list(f, clubs->injured_players, 0);
        clubs = clubs->next;
    }
}

#endif // FOOTBALL_CLUB_H_INCLUDED