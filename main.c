#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE 2048

bool validar_fila(char **sudoku, int row, char num) {
    for (int col = 0; col < 9; col++) {
        if (sudoku[row][col] == num) {
            return false;
        }
    }
    return true;
}
bool validar_columna(char **sudoku, int col, char num) {
    for (int row = 0; row < 9; row++) {
        if (sudoku[row][col] == num) {
            return false;
        }
    }
    return true;
}
bool validar_cuadrante(char **sudoku, int startRow, int startCol, char num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (sudoku[row + startRow][col + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}
bool movimiento_valido(char **sudoku, int row, int col, char num) {
    return validar_fila(sudoku, row, num) && validar_columna(sudoku, col, num) && validar_cuadrante(sudoku, row - row % 3, col - col % 3, num);
}


int main(void) {
  printf("Ingrese un puzzle a resolver del 1 al 100: \n");
  int puzzle;
  scanf("%d", &puzzle);

  FILE * archivo;
  archivo = fopen("puzles.txt", "r");
  char temporal[10];

  char buffer[MAX_LINE];
  char **sudoku;
  
  

  bool keep_reading = true;
  int current_line = 1;

  do {
    fgets(buffer, MAX_LINE, archivo);

    if (current_line == puzzle) {
      
      keep_reading = false;
      sudoku = (char **) malloc(sizeof(char *) * 9);
      int i = 0;
      while (i < 9) {
        sudoku[i] = (char *) malloc(sizeof(char) * 9);
        strncpy(sudoku[i], buffer + i * 9, 9);

        for (int j=0 ; j<9; j++) {
          if (sudoku[i][j] == '0') {
            sudoku[i][j] = ' ';
          }
        }

        
        i++;
      }
        
      
    }
    current_line++;
  } while (keep_reading);



  
  printf("  ABCDEFGHI\n");
  for (int i = 0; i < 9; i++) {
    printf("%d %s \n",i+1, sudoku[i]);


  }

  bool juego = true;
  char fila;
  char columna;
  char numero;
  
  
  while (juego) {

    printf("\n Ingrese numero de fila (1-9): \n");
    scanf(" %c", &fila);
    
    if (fila == 'X') {
      printf("Juego terminado \n");
      juego = false;
      break;
    }

    printf("\n Ingrese numero de columna (A-I): \n");
    scanf(" %c", &columna);

    printf("\n Ingrese numero (1-9): \n");
    scanf(" %c",&numero);

   
    
    
    

    int columna_int = columna - 'A';
    int fila_int = fila - '0' - 1;
    int numero_int = numero - '0';

    if (movimiento_valido(sudoku, fila_int, columna_int, numero) == false) { printf( "Movimiento invalido\n");
    
    }

    else {
    
    sudoku[fila_int][columna_int] = numero;
    
    printf("  ABCDEFGHI\n");
    
    for (int i = 0; i < 9; i++) { 

      printf( "%d %s \n",i+1, sudoku[i]);
    
    
    }
    }
    
    
  }

  

 

  free(sudoku);
  fclose(archivo);
  

  



  
  return 0;
}