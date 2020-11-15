#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

void cifratura(char *plaint_f, char *k_f, char *tcifrato_f, int l_plaint_f){        // Definizione funzione di cifratura
  int i;
  for(i=0; i < l_plaint_f-1; i++)
  {
      tcifrato_f[i] = plaint_f[i] ^ k_f[i];                                         // For con operazione XOR tra plaintext e la chiave per cifrare
  }
}

void decifrazione(char *tcifrato_f, char *k_f, char *tdecifrato_f, int l_plaint_f){ // Definizione funzione di decifrazione
  int i;
  for(i=0; i < l_plaint_f-1; i++)
  {
      tdecifrato_f[i] = tcifrato_f[i] ^ k_f[i];                                     // For con operazione XOR tra testo cifrato e la chiave per decifrare e far tornare il testo originale
  }
}

int main(){
  char plaint[129];
  char k[129];
  char tcifrato[129];
  char tdecifrato[129];
  int s=0;
  int l_plaint, l_k, i;
  bool f = false;
  time_t t;

  srand((unsigned) time(&t));                                                      // Funzione per inizializzare il generatore di numeri

  printf("Digitare 1 per cifrare una stringa con una chiave scelta da lei\nDigitare 2 per cifrare una stringa con una chiave generata casualmente\nDigitare 3 per uscire dal programma\n");
  scanf("%d", &s);

  char ch;
  while((ch = getchar()) != '\n' && ch != EOF);

  switch(s)
  {
    case 1:                                                                        // Primo case dello switch: l'utente inserisce una chiave
      for(i=0; i < 129; i++){                                                      // Inizializzo la chiave a 0
        k[i] = 0;
      }

      printf("Inserisca una stringa da cifrare (massimo 128 caratteri): ");
      fgets(plaint, 129, stdin);                                                   // Inserimento stringa di base
      l_plaint = strlen(plaint);

      if(l_plaint >= 128)                                                          // If per controllare se la stringa supera i 128 caratteri.
      {                                                                            // Se il controllo risulterà vero, verrà fatto un azzeramento del buffer,
        while((ch = getchar()) != '\n' && ch != EOF);                              // in modo tale che i caratteri in più non vengano usati per l'input seguente
      }

      printf("Inserisca una chiave per cifrare la stringa: ");
      fgets(k, 129, stdin);

      f = false;
      l_k = strlen(k);

      while(f == false)
      {
        if(l_k < l_plaint)                                                        // If per controllare se la chiave è minore del plaintext, di conseguenza viene richiesto l'inserimento
        {
          printf("La chiave deve essere uguale o più lunga della stringa da cifrare. Inserisca una nuova chiave: ");
          fgets(k, 129, stdin);
          l_k = strlen(k);
        }
        else
        {
          f = true;
        }
      }

      cifratura(plaint, k, tcifrato, l_plaint);                                  // Chiamata funzione cifratura
      printf("\nIl testo cifrato è: \n");
      for(i=0; i < l_plaint-1; i++)
      {
        if(tcifrato[i] < 31)                                                     // If per controllare se lo cifratura con XOR ha restituito caratteri che il linguaggio non stampa
        {
          printf("c-%d ", tcifrato[i]);                                          // Di conseguenza verrano sostituiti con la stampa "c-"
        }
        else
        {
          printf("%c", tcifrato[i]);
        }
      }

      decifrazione(tcifrato, k,  tdecifrato, l_plaint);                          // Chiamata funzione decifratura
      printf("\nIl testo decifrato è: ");
      printf("\n%s\n", tdecifrato);

      break;

    case 2:                                                                      // Secondo case dello switch: la chiave viene generata casualmente
      for(i=0; i < 129; i++){                                                    // Inizializzo la chiave a 0
        k[i] = 0;
      }

      printf("Inserisca una stringa da cifrare (massimo 128 caratteri): ");
      fgets(plaint, 129, stdin);

      l_plaint = strlen(plaint);
      for(i=0; i < l_plaint-1; i++){                                              // Ciclo per memorizzare i valori casuali dentro l'array
        k[i] = rand()%(127)+32;
      }
      l_k = strlen(k);

      printf("\nLa chiave generata casualmente è: ");
      printf("\n%s", k);

      cifratura(plaint, k, tcifrato, l_plaint);
      printf("\nIl testo cifrato è: ");
      printf("\n%s", tcifrato);

      decifrazione(tcifrato, k, tdecifrato, l_plaint);
      printf("\nIl testo decifrato è: ");
      printf("\n%s\n", tdecifrato);

      break;

    case '3':
      break;
  }

  return 0;
}
