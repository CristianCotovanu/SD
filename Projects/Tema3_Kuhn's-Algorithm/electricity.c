#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void print_matrix(int **G, int N) {
    int i, j;
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            printf("%d ", *(G[i] + j));
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(int *v, int N) {
    int i;
    for (i = 1; i <= N; i++) {
        printf("%d ", *(v + i));
    }
    printf("\n\n");
}

//Structura auxiliara pentru accesarea coordonatelor
//x si y ale unui oras/centrale
typedef struct xy {
    int x;
    int y;
} coord;

int get_min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int get_max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int compute_dist(coord a, coord b) {
    return (int) (abs(a.x - b.x) + abs(a.y - b.y));
}

int *alloc(int size) {
    return calloc(size + 1, sizeof(int));
}

//Citire a numarului de orase, respectiv centrale
int *read_size(char *file_name) {
    int M, N;
    FILE *f;
    if ((f = fopen((file_name), "r")) == NULL) {
        printf("Error opening file:");
        exit(-1);
    }
    fscanf(f, "%d %d", &M, &N);
    int *MN = calloc(2, sizeof(int));
    MN[0] = M;
    MN[1] = N;
    return MN;
}

//Citire matrice de costuri
int **read_matrix(int *size, char input_path[]) {
    FILE *input = fopen(input_path, "r");
    int n, m;
    fscanf(input, "%d%d", &n, &m);
    *size = get_max(n, m);

    coord *city, *central;
    city = calloc(n + 1, sizeof(coord));
    central = calloc(m + 1, sizeof(coord));

    for (int i = 1; i <= n; i++) {
        fscanf(input, "%d%d", &city[i].x, &city[i].y);
    }
    for (int i = 1; i <= m; i++) {
        fscanf(input, "%d%d", &central[i].x, &central[i].y);
    }
    fclose(input);

    int **m_cost = (int **) calloc(*size + 1, sizeof(int *));
    for (int i = 1; i <= *size; i++) {
        m_cost[i] = (int *) calloc(*size + 1, sizeof(int));
        for (int j = 1; j <= *size; j++) {
            m_cost[i][j] = compute_dist(central[i], city[j]);
        }
    }
    free(city);
    free(central);
    return m_cost;
}

//Gaseste un cuplaj intre un oras si o centrala
void find_path(int l, int c, int *central_assign, int *city_assign, int *marked) {
    int point;
    do {
        point = city_assign[c];
        central_assign[l] = c;
        city_assign[c] = l;
        l = point;
        c = marked[l];
    } while (point != 0);
}

int Kuhn(int size, int **m_cost, int *city_assign, int *central_assign,
                 int *marked, int *covered_row, int *covered_col, int *val_row, int *val_col) {
    int min;
    min = m_cost[1][1];
    for (int i = 1; i <= size; i++) {
        if (covered_row[i] == 0) {
            for (int j = 1; j <= size; j++) {
                if (covered_col[j] == 0)
                    min = get_min(min, m_cost[i][j] + val_row[i] - val_col[j]);
            }
        }
    }
    for (int i = 1; i <= size; i++) {
        if (covered_row[i] != 0)
            val_row[i] += min;
    }
    for (int j = 1; j <= size; ++j) {
        if (covered_col[j] == 0)
            val_col[j] += min;
    }

    for (int i = 1; i <= size; i++) {
        if (covered_row[i] == 0) {
            for (int j = 1; j <= size; ++j) {
                if (covered_col[j] == 0 && m_cost[i][j] == val_col[j] - val_row[i]) {
                    if (central_assign[i]) {
                        marked[i] = j;
                        covered_row[i] = 1;
                        covered_col[central_assign[i]] = 0;
                        break;
                    } else {
                        find_path(i, j, central_assign, city_assign, marked);
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

//Functie care elibereaza toate variabilele utilizate
void free_all(int size, int **m_cost, int *city_assign, int *central_assign,
             int *marked, int *covered_row, int *covered_col, int *val_row, int *val_col, int *sizes) {
    free(city_assign);
    free(central_assign);
    free(marked);
    free(covered_row);
    free(covered_col);
    free(val_row);
    free(val_col);
    free(sizes);
    for (int i = 1; i <= size; i++)
        free(m_cost[i]);
    free(m_cost);
}

int main(int argc, char *argv[]) {
    int size, **m_cost, *city_assign, *central_assign, *marked;
    int *covered_row, *covered_col, *val_row, *val_col;
    int i, j, total_cost = 0, *sizes;

    m_cost = read_matrix(&size, argv[1]);
    sizes = read_size(argv[1]);
    city_assign = alloc(sizes[1]);
    central_assign = alloc(sizes[1]);
    marked = alloc(sizes[1]);
    covered_row = alloc(sizes[1]);
    covered_col = alloc(sizes[1]);
    val_row = alloc(sizes[1]);
    val_col = alloc(sizes[1]);

    for (i = 1; i <= size; i++)
        val_row[i] = val_col[i] = city_assign[i] = central_assign[i] = 0;

    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size; j++) {
            covered_row[j] = marked[j] = 0;
            covered_col[j] = city_assign[j];
        }
        while (Kuhn(size, m_cost, city_assign, central_assign, marked,
                            covered_row, covered_col, val_row, val_col) != 0);
    }
    //Scriere in fisierul de output
    FILE *out = fopen(argv[2], "w");
    for (i = 1; i <= sizes[0]; i++) {
        total_cost += m_cost[city_assign[i]][i];
        fprintf(out, "%d\n", city_assign[i] - 1);
    }
//    print_matrix(m_cost,sizes[0]);
//    print_vector(covered_row,sizes[0]);
//    print_vector(covered_col,sizes[0]);
//    print_vector(marked, sizes[0]);
//    print_vector(val_row, sizes[0]);
//    print_vector(val_col,sizes[0]);
//    print_vector(city_assign,sizes[0]);
//    print_vector(central_assign,sizes[0]);
    free_all(size, m_cost, city_assign, central_assign, marked, covered_row,
            covered_col, val_row, val_col, sizes);
    fclose(out);
    return 0;
}