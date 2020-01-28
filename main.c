#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void menu(int);
void ZapisCSV(float **, int, char *);
void RysujWykres(float **, int, char *);
void RysujWykresBezSzumu(float **, int, char *);
float **pila(int, int, int, int);
float *Generator_Szumu(int);
float *Generator_Szumu_Amp(int, int);
void Rysunek();
float** Odczyt();
void Spis();
float **F_Mediana(float**, int);
float **F_Srednia(float**, int);


int main() {
	int wybor;

	while (1) {
		Spis();
	}
	return 0;
}

void menu(int w) {

	switch (w) {
	case 1:
		Rysunek();
		break;
	case 2:
		Odczyt();
		break;
	default:
		printf("podaj wlasciwy wybor z menu \n");
		break;
	}
}

void ZapisCSV(float **dane, int N, char *nazwa) {

	FILE *Wsk_do_pliku;
	int i;
	Wsk_do_pliku = fopen(nazwa, "w");

	for (i = 0; i<N; i++) {

		//fprintf(Wsk_do_pliku, "%f;%f;%f;%f\n", dane[0][i], dane[1][i], dane[2][i], dane[3][i]);
		fprintf(Wsk_do_pliku, "%f;%f\n", dane[0][i], dane[1][i]);
	}

	fclose(Wsk_do_pliku);
}

void RysujWykres(float **dane, int l_linii, char *nazwa) {
	FILE *Wsk_do_pliku;
	int i;

	Wsk_do_pliku = fopen(nazwa, "w");

	fprintf(Wsk_do_pliku, "<html>\n");
	fprintf(Wsk_do_pliku, "<head>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
	fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
	fprintf(Wsk_do_pliku, "function drawChart() {\n");
	fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
	fprintf(Wsk_do_pliku, "['i', 'funkcja', 'szum']");

	//
	for (i = 0; i<l_linii; i++) {
		fprintf(Wsk_do_pliku, ",\n[%f, %f, %f]", dane[0][i], dane[1][i], dane[3][i]);    //przekazanie danych na wykres
	}

	//

	fprintf(Wsk_do_pliku, "\n]);\n");

	fprintf(Wsk_do_pliku, "var options = {\n");
	fprintf(Wsk_do_pliku, "title: 'funkcja trojkat'\n");
	fprintf(Wsk_do_pliku, "};\n");
	fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
	fprintf(Wsk_do_pliku, "colors: ['red', 'blue']\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, ");\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, "</script>\n");
	fprintf(Wsk_do_pliku, "</head>\n");
	fprintf(Wsk_do_pliku, "<body>\n");
	fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 1280px; height: 720px;\"></div>\n");
	fprintf(Wsk_do_pliku, "</body>\n");
	fprintf(Wsk_do_pliku, "</html>\n");

	fclose(Wsk_do_pliku);
}

void RysujWykresBezSzumu(float **dane, int l_linii, char *nazwa) {
	FILE *Wsk_do_pliku;
	int i;

	Wsk_do_pliku = fopen(nazwa, "w");

	fprintf(Wsk_do_pliku, "<html>\n");
	fprintf(Wsk_do_pliku, "<head>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
	fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
	fprintf(Wsk_do_pliku, "function drawChart() {\n");
	fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
	fprintf(Wsk_do_pliku, "['czas', 'funkcja']");


	for (i = 0; i<l_linii; i++) {
		fprintf(Wsk_do_pliku, ",\n[%f, %f]", dane[0][i], dane[1][i]);   //przekazanie danych na wykres
	}

	fprintf(Wsk_do_pliku, "\n]);\n");

	fprintf(Wsk_do_pliku, "var options = {\n");
	fprintf(Wsk_do_pliku, "title: 'funkcja trojkatna'\n");
	fprintf(Wsk_do_pliku, "};\n");
	fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
	fprintf(Wsk_do_pliku, "colors: ['red']\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, ");\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, "</script>\n");
	fprintf(Wsk_do_pliku, "</head>\n");
	fprintf(Wsk_do_pliku, "<body>\n");
	fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 1280px; height: 720px;\"></div>\n");
	fprintf(Wsk_do_pliku, "</body>\n");
	fprintf(Wsk_do_pliku, "</html>\n");

	fclose(Wsk_do_pliku);
}

float **pila(int amplituda, int f, int fp, int n) {

	float **tabl;
	int i, j, a, N;
	float tp, t;
	a = amplituda * 4 *f;
	N = (fp / f)*n;
	tp = 1.0 / fp;

	tabl = (float**)calloc(4, sizeof(float*));  //alokacja pamięci
	for (i = 0; i<4; i++) {
		tabl[i] = (float*)calloc(N*n, sizeof(float));
	}

	for (j = 0; j<n; j++)
	{
		for (i = 0; i<N; i++)
		{
			tabl[0][j*(fp / f) + i] = tp*(j*(fp / f) + i); //czas, oś t

			if (i <= fp/(f*4))  tabl[1][j*(fp / f) + i] = a*tp*((fp/f)+i)-4*amplituda;       //wartości dla przedziałów z których składa się funkcja
			//4*amplituda*((1+tp*f*i)-1)
			else {
				if (i <= (3* fp)/(f*4))  tabl[1][j*(fp / f) + i] = -1*a * tp*((fp / f) + i) + 6*amplituda;    //amplituda*((-4*tp*fp-i*4*f*tp) + 6)
				else
					if (i >= 3*fp / (f * 4)) tabl[1][j*(fp / f) + i] = a*tp*((fp / f) + i) - 8* amplituda;
			}
		}
	}
	return tabl;
}

float *Generator_Szumu(int N) {

	int i;
	float *szum;
	srand(time(NULL));
	szum = (float*)calloc(N, sizeof(float));

	for (i = 0; i<N; i++) {

		szum[i] = (rand() % 1000)*1.0 / 5000;
	}
	return szum;
}

float *Generator_Szumu_Amp(int N, int amp) {

	int i;
	float *szum;
	srand(time(NULL));
	szum = (float*)calloc(N, sizeof(float));

	for (i = 0; i<N; i++) {
		szum[i] = (1.0000*(rand() % (20 * amp) - (10 * amp)) / 100);
	}
	return szum;
}

void Rysunek() {
	int f, fp, n, N, amplituda, y, wybor, p, i, wyb_filtr;
	float **dane;
	char nazwa[100];
	printf("podaj liczbe okresow: ");
	scanf("%d", &n);
	printf("podaj czestotlwosc: ");
	scanf("%d", &f);
	printf("podaj czestotlwosc probkowania: ");
	scanf("%d", &fp);
	printf("podaj wartosc amplitudy: ");
	scanf("%d", &amplituda);

	N = (fp / f)*n;
	dane = pila(amplituda, f, fp, n);
	RysujWykresBezSzumu(dane, N, "wykres_google.html");
	system("wykres_google.html");
	system("pause");
	do {
		printf("czy chcesz zapisac wygenerowane dane do pliku CSV? \n");
		printf("1. tak \n");
		printf("2. nie \n");
		scanf("%d", &y);
		if (y == 1) {
			printf("podaj nazwe pliku \n");
			scanf("%s", nazwa);
			ZapisCSV(dane, N, nazwa);
			printf("utworzono plik o nazwie: %s \n", nazwa);
			y = 2;
		}
		if (y == 2) break;
	} while (y != 1 || y!= 2);


	printf("czy chcesz nalozyc szum na funkcje?\n");
	printf("1.tak\n");
	printf("2.nie\n");
	scanf("%d", &p);
	if (0<=p && p<=2) {
		if (p == 1) {
			dane[2] = Generator_Szumu_Amp(N, amplituda);

				for (i = 0; i<N; i++) {

				dane[3][i] = dane[1][i] + dane[2][i];
			}

			RysujWykres(dane, N, "wykres_google.html");
			system("wykres_google.html");
			system("pause");

			printf("czy chcesz wybrac filtr, jesli tak to jaki?\n");
			printf("1.tak, filtr medianowy\n");
			printf("2.tak, filtr sredniej kroczacej\n");
			printf("3.nie\n");
			scanf("%d", &wyb_filtr);
			switch (wyb_filtr) {
			case 1:
				F_Mediana(dane, N);
				break;
			case 2:
				//F_Srednia(dane, N);
				break;
			case 3:
				Spis();
				break;
			default:
				printf("wybrano niepoprawna pozycje");
			}
		}
		else { Spis(); }
	}
	else printf("podano niewlasciwa odpowiedz\n");


}

float** Odczyt() {

	char znak;
	char NazwaOdcz[100], Tytul[100];
	int i, g, l_linii2, f_wyb;
	float **tab;

	printf("podaj nazwe pliku z rozszerzeniem .csv\n");
	scanf("%s", NazwaOdcz);
	FILE *plik;
	plik = fopen(NazwaOdcz, "r");

	l_linii2 = 0;

	while (!feof(plik)) {                       //liczenie linii
		znak = fgetc(plik);
		if (znak == '\n') l_linii2++;
	}

	tab = (float**)calloc(2, sizeof(float*));    //alokacja pamięci dla tablicy 2 wymiarowej
	for (i = 0; i<=3; i++) {
		tab[i] = (float*)calloc(l_linii2 - 1, sizeof(float));
	}

	rewind(plik);
	i = 0;

	while (!feof(plik)) {                                     //wypełnianie tablicy danymi z pliku
		fscanf(plik, "%f; %f", &tab[0][i], &tab[1][i]);
		if (i == (l_linii2) - 1) break;
		i++;
	}

	printf("podaj nazwe pliku html\n");
	scanf("%s", Tytul);
	do {
		printf("czy chcesz nalozyc szum na funkcje z pliku?\n");
		printf("1.nie\n");
		printf("2.tak\n");
		scanf("%d", &g);
		if (g == 1) break;
		if (g == 2) break;
	} while (g != 1 || g != 2);
	switch (g)
	{
	case 1:
		RysujWykresBezSzumu(tab, l_linii2, Tytul);
		break;
	case 2:
		tab[2]=Generator_Szumu(l_linii2);
		for (i = 0; i <= l_linii2; i++) {
			tab[3][i] = tab[1][i] + tab[2][i];
		}
		RysujWykres(tab, l_linii2, Tytul);
		do {
			printf("czy chcesz poddac funkcje filtrowaniu?\n");
			printf("1. tak, filtrem medianowym\n");
			printf("2. tak, filtrem sredniej kroczacej\n");
			printf("3. nie\n");
			scanf("%d", &f_wyb);
		} while (1 < f_wyb && f_wyb > 3);
		switch (f_wyb) {
		case 1: F_Mediana(tab, l_linii2);
			break;
//		case 2: F_Srednia(tab, l_linii2);
			break;
		case 3: break;
		default:
			printf("podano niewlasciwy wybor");
			break;
		}
	default:
		printf("podaj wlasciwy wybor\n");
		break;
	}

	fclose(plik);

	printf("utworzono wykres z wczytanych danych\n");

	return tab;
}

void Spis() {
	int wybor;
	printf("MENU: \n");
	printf("1. Generowanie funkcji trojkatnej \n");
	printf("2. Odczyt z pliku .csv \n");
	scanf("%d", &wybor);
	menu(wybor);
}

float **F_Srednia(float **pierwotna, int lin) {
	int i, j, y;
	char nazwa[100];
	float **filtr1, okno2[5], k, srednia;

	filtr1 = (float**)calloc(2, sizeof(float*));  //alokacja pamięci
	for (i = 0; i<2; i++) {
		filtr1[i] = (float*)calloc(lin, sizeof(float));
	}
	for (i = 2; i <= lin - 2; i++) {
		filtr1[0][i] = pierwotna[0][i];
		okno2[0] = pierwotna[3][i - 2];
		okno2[1] = pierwotna[3][i - 1];
		okno2[2] = pierwotna[3][i];
		okno2[3] = pierwotna[3][i + 1];
		okno2[4] = pierwotna[3][i + 2];

		srednia = (okno2[0] + okno2[1] + okno2[2] + okno2[3] + okno2[4]) / 5;
		filtr1[1][i] = srednia;
	}
	filtr1[0][0] = pierwotna[0][0];
	filtr1[0][1] = pierwotna[0][1];
	filtr1[1][0] = pierwotna[3][0];
	filtr1[1][1] = pierwotna[3][1];
	filtr1[0][i] = pierwotna[0][i];
	filtr1[1][i - 1] = pierwotna[3][i - 1];

	RysujWykresBezSzumu(filtr1, lin, "filtr_sr.html");
	system("filtr_sr.html");

	printf("czy chcesz zapisac wygenerowane dane do pliku CSV? \n");
	printf("1. tak \n");
	printf("2. nie \n");
	scanf("%d", &y);
	if (y == 1) {
		printf("podaj nazwe pliku \n");
		scanf("%s", nazwa);
		ZapisCSV(filtr1, lin, nazwa);
		printf("utworzono plik o nazwie: %s \n", nazwa);
	}
	return filtr1;
}

float **F_Mediana(float **pierw, int linie) {
	int i, j, h, y;
	char nazwa[100];
	float **filtr2, okno[5], k;

	filtr2 = (float**)calloc(2, sizeof(float*));  //alokacja pamięci
	for (i = 0; i<2; i++) {
		filtr2[i] = (float*)calloc(linie, sizeof(float));
	}

	for (i = 2; i <= linie - 2; i++) {
		filtr2[0][i] = pierw[0][i];
		okno[0] = pierw[3][i-2];
		okno[1] = pierw[3][i-1];
		okno[2] = pierw[3][i];
		okno[3] = pierw[3][i+1];
		okno[4] = pierw[3][i+2];

		for (j = 0; j < 4; j++) {
			for (h = 0; h < 4; h++)
				{
					if (okno[h] > okno[h + 1])
					{
						k = okno[h];
						okno[h] = okno[h + 1];
						okno[h + 1] = k;
					}
				}
			}
		filtr2[1][i] = okno[2];
	}
	filtr2[0][0] = pierw[0][0];
	filtr2[0][1] = pierw[0][1];
	filtr2[1][0] = pierw[3][0];
	filtr2[1][1] = pierw[3][1];
	filtr2[0][i] = pierw[0][i];
	filtr2[1][i + 1] = pierw[3][i + 1];
	filtr2[1][i + 2] = pierw[3][i + 2];

	RysujWykresBezSzumu(filtr2, linie, "filtr_med.html");
	system("filtr_med.html");

	printf("czy chcesz zapisac wygenerowane dane do pliku CSV? \n");
	printf("1. tak \n");
	printf("2. nie \n");
	scanf("%d", &y);
	if (y == 1) {
		printf("podaj nazwe pliku \n");
		scanf("%s", nazwa);
		ZapisCSV(filtr2, linie, nazwa);
		printf("utworzono plik o nazwie: %s \n", nazwa);
	}
	return filtr2;
}
