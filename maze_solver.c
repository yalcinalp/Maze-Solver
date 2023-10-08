#include <stdio.h>
#include <stdlib.h>

#define INITIAL 1
#define MAX_QUE 1000000

typedef struct {
    int x, y;
    int predecess_x, predecess_y;
} Nokta;

Nokta que[MAX_QUE];
int bas = 0, son = 0;

void enqueue(Nokta p) {
    que[son++] = p;
}

Nokta dequeue() {
    return que[bas++];
}

int empty_kontrol() {
    return bas == son;
}


int direction_x[4] = {0, -1, 0, 1};
int direction_y[4] = {-1, 0, 1, 0};


void bfs(char **labirent, int row, int col, Nokta start) {

    int cikis_var = 0;
    
    int **visited = (int **)malloc(row * sizeof(int *));
    
    Nokta **predecess = (Nokta **)malloc(row * sizeof(Nokta *));

    Nokta cikis;

    int i, j;


    for (i = 0; i < row; i++) {
        
        visited[i] = (int *)malloc(col * sizeof(int));
        
        predecess[i] = (Nokta *)malloc(col * sizeof(Nokta));
        
        for (j = 0; j < col; j++) {
        
            visited[i][j] = 0;
            predecess[i][j].x = -1;
        
            predecess[i][j].y = -1;
        }
    }

    visited[start.y][start.x] = 1;
    enqueue(start);


    while (!empty_kontrol()) {
        
        Nokta current = dequeue();
        
        if (labirent[current.y][current.x] == ' ' && (current.y == row - 1 || current.x == col - 2 || current.y == 0 || current.x == 0)) {
        
            cikis = current;
            cikis_var = 1;
            break;
        }


        for (i = 0; i < 4; i++) {
            
            Nokta next;
            next.x = current.x + direction_x[i];
            next.y = current.y + direction_y[i];
            
            if (next.x >= 0 && next.x < col && next.y >= 0 && next.y < row 
                && labirent[next.y][next.x] != 'X' && !visited[next.y][next.x]) {
            
                visited[next.y][next.x] = 1;
            
                next.predecess_x = current.x;
                next.predecess_y = current.y;
            
                predecess[next.y][next.x] = current;
                enqueue(next);
            }
        }
    }

    
    if (cikis_var) {
        
        Nokta current = cikis;
        
        while (current.x != start.x || current.y != start.y) {
        
            labirent[current.y][current.x] = '*';
            current = predecess[current.y][current.x];

        }
        
        labirent[start.y][start.x] = '*';
    }

    
    else {
        
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
        
                if (visited[i][j]) {
                    
                    labirent[i][j] = '.';

                }
            }
        }
    }

    /* Temiz */
    for (i = 0; i < row; i++) {
        
        free(visited[i]);
        free(predecess[i]);
    }
    
    free(visited);
    free(predecess);
}


int main() {

    int i;
    int x_coord, y_coord;
    
    char **labirent = malloc(INITIAL * sizeof(char*));
    
    int row_size = INITIAL; 
    int col_size = INITIAL;
    
    int row = 0, col = 0;
    int first_row_read = 0;
    
    char c;
    Nokta s;
    
    s.predecess_x = -1;
    s.predecess_y = -1;


    if (labirent == NULL) {
        
        return 1;
    }

    scanf("%d %d\n", &x_coord, &y_coord);
    
    s.x = x_coord;
    s.y = y_coord;
    

    labirent[row] = malloc(INITIAL * sizeof(char));

    while ((c = getchar()) != EOF) {
        
        if (c == '\n') {
            
            labirent[row][col] = '\0';

            if (!first_row_read) {
                col_size = col + 1;
                first_row_read = 1;
            }

            row++;
            col = 0;

            if (row == row_size) {
                
                row_size *= 2;
                labirent = realloc(labirent, row_size * sizeof(char*));
                
                if (labirent == NULL) {
                    
                    return 1;
                }
            }
            
            labirent[row] = malloc(col_size * sizeof(char));
            continue;
        }

        if (!first_row_read && col == col_size - 1) {
            
            col_size *= 2;
            labirent[row] = realloc(labirent[row], col_size * sizeof(char));
            
            if (labirent[row] == NULL) {
                
                return 1;
            }
        }

        labirent[row][col++] = c;
    }
    
    bfs(labirent, row, col_size, s);

    for (i = 0; i < row; i++) {
        printf("%s\n", labirent[i]);
    }

    for (i = 0; i < row; i++) {
        free(labirent[i]);
    }

    free(labirent);    

    return 0;
}
