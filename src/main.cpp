#include <ncurses.h>
#include <string>
#include <unistd.h>
 // Direcciones
//enum Direction { UP, DOWN, LEFT, RIGHT };
    // Estructura para la posición de la serpiente
typedef struct {
    int x, y;
    } Position;
// Variables globales
Position serpent[100];
int serpent_length;
Position comida;
//enum Direction dir;
bool game_over;
bool icolor;
// Inicializar el juego
void initialize_game(int WIDTH,int HEIGHT) {
    serpent_length = 0;
    serpent[0].x = WIDTH / 2;
    serpent[0].y = HEIGHT / 2;
    //dir = RIGHT;
    comida.x = rand() % WIDTH;
    comida.y = rand() % HEIGHT;
    game_over = 0;
    start_color(); // Habilitar colores
    if (has_colors()) {
        icolor= true;
        use_default_colors();
        init_pair(1, COLOR_RED, -1);  // Fondo transparente
        init_pair(2, COLOR_GREEN, -1);
        init_pair(3, COLOR_BLUE, -1);

    }else
        icolor= false;
}

// Dibujar el tablero
void draw_board(int max_x, int max_y) {
    clear();
    move(0,0);
    for (int i = 0; i < max_x; i++) {
        for (int j = 0; j < max_y; j++) {
            if (i == 0 || i == max_x - 1 || j == 0 || j == max_y - 1) {
                if (icolor){
                        attron(COLOR_PAIR(1));
                        printw("#");/// imprimir lo bordes de color rojo
                        attroff(COLOR_PAIR(1));        
                }else
                    printw("#");
            } else if (i == serpent[0].x && j == serpent[0].y) {
                if(icolor){
                    attron(COLOR_PAIR(2));
                    printw("O");
                    attroff(COLOR_PAIR(2));
                }else
                    printw("O");
            } else if (i ==comida.x && j == comida.y) {
                if(icolor){
                    attron(COLOR_PAIR(3));
                    printw("%d", ((serpent_length)%10));
                    attroff(COLOR_PAIR(3));
                }else
                    printw("%d", ((serpent_length)%10));
            } else {
                int printed = 0;
                for (int k = 1; k < serpent_length; k++) {
                    if (i == serpent[k].x && j == serpent[k].y) {
                        if(icolor){
                            attron(COLOR_PAIR(2));
                            printw("o");
                            attroff(COLOR_PAIR(2));
                        }else{
                            printw("o");
                        }
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    printw(" ");
                }
            }
        }
    }
    
}

int main(int argc, char** argv) {
    // Comprobación de los argumentos de la línea de comandos
    if( argc >= 2){
     for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--help" || arg == "-h") {
                printf("Uso: %s [opciones]\n", argv[0]);
                printf("\r--help: Muestra este mensaje de ayuda.");
                return 0;
            } else if (arg == "-v" || arg == "--version") {
                printf("Versión 1.0.0");
                return 0;
            }
        }
    }
    // Inicialización de ncurses
    initscr();
    cbreak();  // Desactiva el buffering de entrada
    noecho();  // No mostrar las teclas presionadas
    curs_set(0);  // Ocultar el cursor
    timeout(100);  // Tiempo de espera en milisegundos para recibir una tecla

    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);
    refresh();
    keypad(stdscr, TRUE); // Habilita teclas especiales

    // Variables del juego
    initialize_game(max_row,max_col);
    int dir_x = 0, dir_y = 1;
    int c;

    // Juego en bucle
    while (true) {
        c = getch();  // Captura las teclas
        if (c == 'q' || c== 27) break;  // Si presiona 'q', salir del juego
        // Actualizar la dirección según las teclas presionadas
        if ((c == KEY_UP || c == 'w') && dir_x != 1 ) {
            dir_x = -1;
            dir_y = 0;
        } else if ((c == KEY_DOWN ||c == 's' )&& dir_x != -1) {
            dir_x = 1;
            dir_y = 0;
        } else if ((c == KEY_LEFT || c == 'a' )&& dir_y != 1) {
            dir_x = 0;
            dir_y = -1;
        } else if ((c == KEY_RIGHT ||c == 'd' )&& dir_y != -1) {
            dir_x = 0;
            dir_y = 1;
        }
        // Limpiar la pantalla y redibujar el mundo
        draw_board(max_row,max_col);
        
        if (serpent[0].x==comida.x && serpent[0].y== comida.y && serpent_length<=99){
            comida.x = rand() % max_row;
            comida.y = rand() % max_col;
            serpent_length++;
        }
        // Actualizar la posición de la serpiente
        if (serpent_length!=0)
        {
             for (int  i = serpent_length; i !=0; --i)
            {
                serpent[i] = serpent[i-1];
            }
        }
        serpent[0].x+= dir_x;
        serpent[0].y+= dir_y;
        // detectar cololicion con su propia cola
        if (serpent_length >= 4)
        {   // Detectar colisión con la cola
            for (int i = 3; i < serpent_length; i++) {  // Comienza desde 1 para evitar comparar con la cabeza
                if (serpent[0].x == serpent[i].x && serpent[0].y == serpent[i].y) {
                    game_over = TRUE;  // Marcar el juego como terminado
                    break;
                }          
            }
        }

        // Verificar fin del juego
        if (game_over) {
            break;  // Salir del bucle principal
        }
        
        // Comprobar si la serpiente choca con el borde
        if (serpent[0].x == 0 || serpent[0].y == 0 || serpent[0].x== max_row - 1 || serpent[0].y == max_col - 1) {
            break;  // Fin del juego
        }
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        if (max_row!=rows && max_col!= cols)// si la ventana ha cambaido el juego se cierra
            break;
        refresh();
        usleep(100000);  // Control de la velocidad del juego (100ms)
    }
    // Finalizar ncurses
    endwin();
    printf("Juego Terminado! Puntuación final: %d\t",serpent_length);
    return 0;
}
