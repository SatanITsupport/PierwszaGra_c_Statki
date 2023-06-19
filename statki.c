//Projekt zaliczeniowy - Podstawy programowania
//Agnieszka ZOK
//WIMiP Informatyka Techniczna rok 1 sem 2
//Statki
//Data 16.06.2023
//komendy systemowe są wprowadzone zgodnie z powłoką bash
//kompilator użyty do zadania - gcc

//biblioteki
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


//definicje stałych wartości
#define WIERSZE 5
#define KOLUMNY 5

#define L_STATKOW 5

#define PLAYER 0
#define COMPUTER 1

// kod nie zrozumial TRUE/FALSE i wyrzucil mi blad kompilatora
#define TRUE 1
#define FALSE 0

//do rysowania planszy
#define WODA ' '
#define TRAFIENIE 'X'
#define PUDLO '-'
#define STATEK 'S'

//memorandum: do rysowania planszy przeciwnika nie używamy STATKU


//struktury 
typedef struct koordynaty{
	int row;
	int column;
}Koord;

typedef struct statystyka{
	int hit;
	int miss;
	int total;
}Stat;
typedef struct komorka{
	char symbol;
	Koord pozycja;
	}Kom; //do rysowania planszy
//wprowadzenie funkcji

void instrukcja (void);
void inicjalizuj_plansze (Kom plansza[][KOLUMNY]);
void system_out (char *wiadomosc);
void drukuj_plansze (Kom plansza[][KOLUMNY], _Bool pokaz_statki);
void gracz_dodaje_statki (Kom plansza[][KOLUMNY]/*, Koord pozycja*/);
void komputer_losuje_statki (Kom plansza[][KOLUMNY]);

Koord celuj (void);
Koord celujAI (void);
short sprawdzTrafienie (Kom plansza[][KOLUMNY],Koord target);

int losuj_liczbe (int zakres_dol, int zakres_gora);
_Bool wygrana (Stat players[], int player);

//definicje funkcji
void instrukcja (void) {
	printf ("  XXXXX XXXXXX  XXXX  XXXXXX XX  XX XX\n");
	printf (" XX       XX   XX  XX   XX   XX xx  XX\n");
	printf ("  XXXX    XX   XX  XX   XX   XXxx   XX\n");
	printf ("     XX   XX   XXXXXX   XX   XX xx  XX\n");
	printf (" xxxxx    XX   XX  XX   XX   XX  xx XX\n");

	printf ("\n\n\n");
	
	printf ("Gra zaplanowana na 2 graczy: i TY możesz zmierzyć się z AI!\n");
	printf ("Tzn. Prawie, to AI używa funkcji SRAND i IF więc to nie do końca AI.\n");
	printf ("Dysponujesz planszą 5X5 i 5 statkami kategorii motorówka wielkości 1.\n");
	printf ("Legenda: woda ' ', trafienie 'X', pudło '-', Statek 'S'.\n");
	printf ("Ustaw swoje statki wykonując polecenia systemu.\n");
	printf ("Statki ustawiasz podajac koordynaty x/y od 0 do 4 \n");
	printf ("Twoje jednostki nie mogą stykać się bokami ani rogami \n\n");
	
	printf ("Gotowy?!\n");
}
void inicjalizuj_plansze (Kom plansza[][KOLUMNY]){
	int i = 0, j = 0;

	for (i = 0; i < WIERSZE; i++)
		for (j = 0; j < WIERSZE; j++){
			plansza[i][j].symbol = WODA;
			plansza[i][j].pozycja.row = i;
			plansza[i][j].pozycja.column = j;
		}
}
void system_out (char *wiadomosc){
	
	char ch = '\0';

	printf ("%s",wiadomosc);
	getchar(); getchar();
}

void drukuj_plansze (Kom plansza[][KOLUMNY], _Bool pokaz_statki){
	int i = 0, j = 0;

	printf ("  0 1 2 3 4\n");

	for (i = 0; i < WIERSZE; i++){
		printf ("%d ", i);

		for(j = 0; j < KOLUMNY; j++){
			if(pokaz_statki == TRUE){
				printf ("%c ",plansza[i][j].symbol);
			}
			else{
				switch (plansza[i][j].symbol){
					case WODA: 
						printf ("%c ",WODA);
						break;
					case TRAFIENIE:
						printf ("%c ",TRAFIENIE);
						break;
					case PUDLO:
						printf ("%c ",PUDLO);
						break;
					default:
						printf ("%c ",WODA);
						break;
				}
			}
		}
		putchar ('\n'); // zakończenie wiersza
	}
}

void gracz_dodaje_statki (Kom plansza[][KOLUMNY]/*, Koord pozycja*/){
	int i = 0, j = 0 , k = 0;
	Koord pozycja[L_STATKOW];
	_Bool sprawdz_pozycje = TRUE;
	for (i = 0; i < L_STATKOW; i++){
		if (sprawdz_pozycje == FALSE){
			i = i - 1 ; //dekrementacja jeśli źle umieszczono statek
			}
		printf ("Podaj koordynaty staku nr %d: [wiersz][kolumna] (np:> 1 2) \n> ", i + 1);
		scanf ("%d %d", &j, &k);
		if (j < WIERSZE && k < KOLUMNY){
			if (plansza[j][k].symbol == WODA){
				// sprawdzenie wariantow umieszczenia ook innego statku
				switch(j){
					case 0:
						switch(k){
							case 0:
								if (plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;
					case 4:
						switch(k){
							case 0:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
									printf ("invalid input - za blisko statku \n");
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;
					default:
						switch(k){
							case 0:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j-1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									printf ("invalid input - za blisko statku \n");
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;

				}
				//plansza[j][k].symbol = STATEK; //przeniesiony do swich case w ramach sprawdzenia
			}
			else {
				printf ("invalid input - statek już tu jest \n");
				sprawdz_pozycje=FALSE;
			}
		}
		else {
			printf ("invalid input - poza polem planszy \n");
			sprawdz_pozycje=FALSE;
		}
	}
}
void komputer_losuje_statki (Kom plansza[][KOLUMNY]){
	int i = 0, j = 0 , k = 0;
	Koord pozycja[L_STATKOW];
	_Bool sprawdz_pozycje = TRUE;
	printf ("Komputer losuje swoje pozycje \n");
	for (i = 0; i < L_STATKOW; i++){
		
		//printf ("Komputer losuje pozycje staku nr %d.\n", i + 1); //sluzyly do sprawdzenia czy switch jest poprawnie przeniesiony
		j = losuj_liczbe (0, 4);
		k = losuj_liczbe (0, 4);
		if (j < WIERSZE && k < KOLUMNY){
			if (plansza[j][k].symbol == WODA){
				// sprawdzenie wariantow umieszczenia ook innego statku
				switch(j){
					case 0:
						switch(k){
							case 0:
								if (plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;
					case 4:
						switch(k){
							case 0:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;
					default:
						switch(k){
							case 0:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							case 4:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	
							default:
								if (plansza[j-1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k+1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j-1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else if(plansza[j+1][k-1].symbol == STATEK){
									sprawdz_pozycje=FALSE;
								}
								else{
									plansza[j][k].symbol = STATEK;
									sprawdz_pozycje=TRUE;
								}
								break;	

						} break;

				}
			}
			else {
				sprawdz_pozycje=FALSE;
			}
		}
		else {
			printf ("invalid input - poza polem planszy \n"); //zostaje w ramach sprawdzenia czy losowanie działa w zadanym zakresie
			sprawdz_pozycje=FALSE;
		}
		if (sprawdz_pozycje == FALSE){
			i = i - 1 ; //dekrementacja jeśli źle umieszczono statek
			}
	}
}

Koord celuj (void){
	Koord target;
	fflush (stdin);

	printf ("> Wprowadź koordynaty celu (np. > 1 2):\n");
	printf ("> ");
	scanf ("%d %d", &target.row, &target.column);

	return target;

}
Koord celujAI(void){
	Koord targetAI;
	fflush (stdin);
	printf ("Komputer celuje, kryć się!\n");
	targetAI.row = losuj_liczbe(0,4);
	targetAI.column = losuj_liczbe(0,4);
	
	return targetAI;
}
short sprawdzTrafienie (Kom plansza[][KOLUMNY],Koord target){
	int trafienie = -2;

	switch (plansza[target.row][target.column].symbol){
		/* pudło */
		case WODA:
			trafienie = 0;
			break;
		
		case STATEK: 
			trafienie = 1;
			break;
		
		case TRAFIENIE:
		case PUDLO:
			trafienie = -1;
			break;
	}
	return trafienie;
}

int losuj_liczbe (int zakres_dol, int zakres_gora){
	if (zakres_dol == 0){
		return rand () % ++zakres_gora;
	}
	else {
		return rand () % ++zakres_gora + zakres_dol;
	}
}

_Bool wygrana (Stat players[], int player){
	_Bool zwyciestwo = FALSE;

	if (players[player].hit == L_STATKOW)
		zwyciestwo = TRUE;

	return zwyciestwo;
}


//petla główna
int main (void) {
	
	//zmienne w pętli main i zainicjowanie SRAND
	Stat players[2] = {{0,0,0},{0,0,0}}; // inicjalizacja
	Kom planszaGracza[WIERSZE][KOLUMNY]; // definicja planszy gracza jako struktury XY plus symbol
	Kom planszaKomputera[WIERSZE][KOLUMNY]; //analogicznie dla komputera
	srand ((unsigned int) time (NULL)); // seed do funkcji RAND
	_Bool godMode = TRUE; // potrzebne dla mnie i testera
	int wyznacznikGodMode = 0; // do petli proszącej o wybór trybu aby uniknąć niezgodności związanej z wyborem poza bool	
	short player = 0; // inicjalizacja gracza potrzebne do statystyk i rozgrywania tury
	Koord target;
	Koord targetAI;
	short trafienie;
	_Bool wygrales = FALSE;

	//instrukcja uruchomienia gry
	
	instrukcja();
	system_out ("Wcisnij <ENTER> \n");
	system ("clear");
	//wybór trybu god mode - sluzy do sprawdzenia czy statki przeciwnika zostaly rozmieszczone
	do {
		printf ("Wybierz tryb gry \n\n");
		printf ("> 0. Standard\n     Zwykła gra\n");
		printf ("> 1. GDO MODE\n     tryb debugowania - widać statki przeciwnika\n");
		scanf ("%d", &wyznacznikGodMode);
		if (wyznacznikGodMode == 1){ 
			godMode=TRUE;
		}
		else{
			godMode=FALSE;
		}
		system ("clear");
	}
	while (wyznacznikGodMode > 1);


	//wypełnienie symbolem wody
        
	inicjalizuj_plansze(planszaGracza);
	inicjalizuj_plansze(planszaKomputera);

	//rozmieszczenie statkow gracza
	
	drukuj_plansze (planszaGracza, TRUE);
	gracz_dodaje_statki (planszaGracza);
	system ("clear");
	drukuj_plansze (planszaGracza, TRUE);
	
	system_out ("Twoja plansza została przygotowana, wcisnij <ENTER> aby kontynuować");
	system ("clear");
	
	//losowanie pozycji komputera
	
	komputer_losuje_statki (planszaKomputera);
	system_out ("Komputer wylosował swoje pozycje \nWciśnij <ENTER> \n");	

	//wybór pierwszego gracza
	
	player = losuj_liczbe(0, 1);
	printf (" Gracz nr %d zaczyna gre. \n", player + 1);
	system_out ("Wciśnij <ENTER>\n");
	system ("clear");
	
	//rozgrywka
	
	while (TRUE){
		switch (player){
			case PLAYER:
				printf ("Plansza Komputera:\n\n");
				drukuj_plansze(planszaKomputera,godMode);
				printf ("\nTwoja tura!\n");
				
				do {
					target = celuj();
					trafienie = sprawdzTrafienie(planszaKomputera, target);
					
					if (trafienie == -1)
						printf ("invalid input - tutaj już strzelałeś - spróbuj ponownie\n");
				}while (trafienie == -1);
				if (trafienie == TRUE){
					planszaKomputera[target.row][target.column].symbol = TRAFIENIE;
					players[player].hit++;
					players[player].total++;
					}
				else {
					planszaKomputera[target.row][target.column].symbol = PUDLO;
					players[player].miss++;
					players[player].total++;
				}
				system_out ("koniec tury, wciśnij <ENTER>\n");
				system ("clear");
				break;
			case COMPUTER:	
				printf ("Plansza Gracza:\n\n");
				drukuj_plansze(planszaGracza,TRUE);
				printf ("\nTura przeciwnika!\n");
				
				do {
					targetAI = celujAI();
					trafienie = sprawdzTrafienie(planszaGracza, targetAI);
					
				}while(trafienie == -1);
				if (trafienie == TRUE){
					planszaGracza[targetAI.row][targetAI.column].symbol = TRAFIENIE;
					players[player].hit++;
					players[player].total++;
					}
				else {
					planszaGracza[targetAI.row][targetAI.column].symbol = PUDLO;
					players[player].miss++;
					players[player].total++;
				}
				system_out ("koniec tury, wciśnij <ENTER>\n");
				system ("clear");
				break;
		}
		
		wygrales = wygrana (players, player);
		if (wygrales == TRUE){
			break;
		}
		else {
			player = !player;
		}
		
		
		
	
	}


	// na koniec gry jako ekran wyjsciowy wyswietl statystyki
	
	printf ("+===================================================+\n");
	printf ("|                     Statystyka                    |\n");
	printf ("+---------------------------------------------------|\n");
	printf ("| Gracz :    %d trafienia                            |\n", players[0].hit);
	printf ("|            %d pudła                                |\n", players[0].miss);
	printf ("|            %d razem                                |\n", players[0].total);
	printf ("| Komputer : %d trafienia                            |\n", players[1].hit);
	printf ("|            %d pudła                                |\n", players[1].miss);
	printf ("|            %d razem                                |\n", players[1].total);
	printf ("+===================================================+\n");
	
	return 0; //bo main jest intigerem
};



