
#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

void add_player_aux2(Player **players_list, char *name, char *position, int score, int injured) {
    Player *new_player = (Player *) calloc(1, sizeof(Player)),
            *players = *players_list;
    new_player->name = (char *) calloc(strlen(name) + 1, sizeof(char));
    new_player->position = (char *) calloc(strlen(position) + 1, sizeof(char));
    new_player->score = score;
    new_player->injured = injured; // Campul trebuie completat dupa adaugarea lui intr-o anumita lista
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
        if (players->score < score) {
            break;
        } else if (players->score == score) {
            if (strcmp(name, players->name) < 0)
                break;
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

Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
    FootballClub *aux_A = clubs, *aux_B = clubs;
    if (clubs == NULL) {
        //"Lista de cluburi este goala"
        return NULL;
    }
    while (aux_A != NULL && strcmp(aux_A->name, club_A) != 0) {
        aux_A = aux_A->next;
    }
    while (aux_B != NULL && strcmp(aux_B->name, club_B) != 0) {
        aux_B = aux_B->next;
    }
    if (aux_A == NULL) {
        printf("Clubul A nu se gaseste in lista\n");
    }
    if (aux_B == NULL) {
        printf("Clubul A nu se gaseste in lista\n");
    }
    Player *all_players = NULL, *p_A = aux_A->players, *p_B = aux_B->players;

    while (p_A != NULL && p_B != NULL) {
        add_player_aux(&all_players, p_B->name, 
                p_B->position, p_B->score, p_B->injured);
        add_player_aux(&all_players, p_A->name, 
                p_A->position, p_A->score, p_A->injured);
        p_B = p_B->next;
        p_A = p_A->next;
    }
    if (p_A == NULL && p_B != NULL) {
        while (p_B != NULL) {
            add_player_aux(&all_players, p_B->name, 
                    p_B->position, p_B->score, p_B->injured);
            p_B = p_B->next;
        }
    }
    if (p_A != NULL) {
        while (p_A != NULL) {
            add_player_aux(&all_players, p_A->name, p_A->position, p_A->score, p_A->injured);
            p_A = p_A->next;
        }
    }

    return all_players;

}

Player *get_best_player(FootballClub *clubs, char *position) {
    FootballClub *c = clubs;
    Player *p, *best_player = calloc(1, sizeof(Player));
    best_player->name = calloc(20, sizeof(char));
    best_player->position = calloc(20, sizeof(char));
    strcpy(best_player->name, "z");
    strcpy(best_player->position, "z");
    best_player->score = -105;

    while (c != NULL) {
        p = c->players;
        while (p != NULL) {
            if (strcmp(p->position, position) == 0) {
                if (best_player->score == p->score && 
                                strcmp(best_player->name, p->name) > 0) {
                    strcpy(best_player->name, p->name);
                    strcpy(best_player->position, p->position);
                    best_player->score = p->score;
                } else if (best_player->score < p->score) {
                    strcpy(best_player->name, p->name);
                    strcpy(best_player->position, p->position);
                    best_player->score = p->score;
                }
            }
            p = p->next;
        }
        c = c->next;
    }

    if (best_player->score == -105) {
        free(best_player->name);
        free(best_player->position);
        free(best_player);
        return NULL;
    }
    return best_player;
}

Player *get_top_players(FootballClub *clubs, int N) {
    FootballClub *c = clubs;
    Player *top_players = NULL, *p = NULL, *aux_list, *aux_pointer;
    int i;

    if (c == NULL) {
        return NULL;
    }

    while (c != NULL) {
        p = c->players;
        aux_list = NULL;
        while (p != NULL) {
            add_player_aux2(&aux_list, p->name, 
                    p->position, p->score, p->injured);
            p = p->next;
        }
        aux_pointer = aux_list;
        for (i = 0; i < N && aux_list != NULL; i++) {
            add_player_aux2(&top_players, aux_list->name, 
                    aux_list->position, aux_list->score, aux_list->injured);
            aux_list = aux_list->next;
        }
        destroy_player_list(aux_pointer);
        c = c->next;
    }

    return top_players;
}

Player *get_players_by_score(FootballClub *clubs, int score) {
    Player *players = NULL, *p = NULL;
    FootballClub *c = clubs;
    while (c != NULL) {
        p = c->players;
        while (p != NULL) {
            if (p->score >= score) {
                add_player_aux2(&players, p->name, 
                        p->position, p->score, p->injured);
            }
            p = p->next;
        }
        c = c->next;
    }
    c = clubs;
    p = c->injured_players;
    while (c != NULL) {
        if (c->injured_players != NULL) {
            p = c->injured_players;
        }
        while (p != NULL) {
            if (p->score >= score) {
                add_player_aux2(&players, p->name, 
                        p->position, p->score, p->injured);
            }
            p = p->next;
        }
        c = c->next;
    }
    return players;
}

Player *get_players_by_position(FootballClub *clubs, char *position) {
    Player *players = NULL, *p = NULL;
    FootballClub *c = clubs;
    while (c != NULL) {
        p = c->players;
        while (p != NULL) {
            if (strcmp(p->position, position) == 0) {
                add_player_aux2(&players, p->name, 
                        p->position, p->score, p->injured);
            }
            p = p->next;
        }
        c = c->next;
    }
    c = clubs;
    while (c != NULL) {
        p = c->injured_players;
        while (p != NULL) {
            if (strcmp(p->position, position) == 0) {
                add_player_aux2(&players, p->name, 
                        p->position, p->score, p->injured);
            }
            p = p->next;
        }
        c = c->next;
    }
    return players;
}

Player *get_best_team(FootballClub *clubs) {
    FootballClub *c = clubs;
    Player *best_team = NULL,
            *mijlocasi = get_players_by_position(c, "mijlocas"),
            *fundasi = get_players_by_position(c, "fundas"),
            *atacanti = get_players_by_position(c, "atacant"),
            *portari = get_players_by_position(c, "portar"),
            *m = mijlocasi, *p = portari, *f = fundasi, *a = atacanti;
    int i;
    if (portari != NULL) {
        add_player_aux2(&best_team, portari->name, 
                portari->position, portari->score, portari->injured);
    }
    for (i = 0; i < 3 && mijlocasi != NULL; i++) {
        add_player_aux2(&best_team, mijlocasi->name, 
                mijlocasi->position, mijlocasi->score, mijlocasi->injured);
        mijlocasi = mijlocasi->next;
    }
    for (i = 0; i < 3 && atacanti != NULL; i++) {
        add_player_aux2(&best_team, atacanti->name, 
                atacanti->position, atacanti->score, atacanti->injured);
        atacanti = atacanti->next;
    }
    for (i = 0; i < 4 && fundasi != NULL; i++) {
        add_player_aux2(&best_team, fundasi->name, 
            fundasi->position, fundasi->score, fundasi->injured);
        fundasi = fundasi->next;
    }
    destroy_player_list(m);
    destroy_player_list(a);
    destroy_player_list(f);
    destroy_player_list(p);
    return best_team;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED