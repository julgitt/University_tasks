#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define limit 5

//Szyfr podstawieniowy z łączeniem bloków CBC
/* POLECENIA
CFG podajemy dwie liczby S (kod pierwszego dopuszczalnego znaku) i M (ilość znaków) (czyli domyślnie: S=32 M=64)
KEY podanie klucza w postaci M (domyślnie M=64) znaków
INI podanie wartości inicjalizującej CBC w postaci liczby
ENC zaszyfrowanie podanego w wierszu tekstu i wypisanie w wierszu na standardowym wyjściu
DEC odszyfrowanie podanego w wierszu tekstu i wypisanie w wierszu na standardowym wyjściu
*/

int main()
{
    //________________________________ZMIENNE____________________________________

    char polecenie[limit] = "";
    int s = 32; //domyslny kod pierwszego znaku
    int m = 64; //domyslna dlugosc znakow
    char tekst [129]; //tekst do zakodowania/odkodowania
    int podano_klucz = 0;
    int podano_ini = 0;
    int ini = 0;
    char klucz [64];

    //___________________________WCZYTYWANIE I WYKONYWANIE POLECEN_________________

    for (int i = 0; (polecenie[i]=getchar())!= EOF; i++)
    {
        if (polecenie[i] == '\n')
        {
            i = -1;
        }
        if (i == limit-2) // jezeli wpisalismy cale polecenie
        {
            polecenie[4] = '\0';
            i = -1;
            if (strcmp(polecenie, "CFG ")==0) //ZMIANA DOMYSLNYCH WARTOSCI
            {
                scanf ("%d%d", &s, &m);
                if (s < 32 || s + m > 127) // jezeli blednie wpisane, to koniec programu
                {
                    return 0;
                }
            }
            if (strcmp(polecenie, "KEY ")==0) //PODANIE KLUCZA
            {
                for (int j = 0; (klucz[j] = getchar())!= '\n'; j++)
                {
                    if (j == m || klucz[j] < s || klucz[j] > s + m) //blednie podany klucz
                        return 0;
                }
                klucz[m]='\0';
                podano_klucz = 1;
            }
            if (strcmp(polecenie, "INI ")==0) //PODANIE WARTOSCI INICJALIZUJACEJ
            {
                podano_ini = 1; //?
                scanf ("%d", &ini);
            }
            if (strcmp(polecenie, "ENC ")==0) //TEKST DO ZAKODOWANIA
            {
                if (podano_klucz == 0 || podano_ini == 0)
                    return 0;
                int j = 0;
                while((tekst[j] = getchar()) != '\n')
                {
                    if (j == 127 || tekst[j] < s || tekst[j] > s + m )
                        return 0;
                    j++;
                }
                tekst[j]='\0';
                //PERMUTACJA
                int init = ini;
                for (int k = 0; k<j; k++)
                {
                    tekst[k] = klucz[(tekst[k] - s + init)%m];
                    printf("%c", tekst[k]);
                    init = (tekst[k] - s)%m;
                }
                printf("\n");
                i=-1;

            }
            if (strcmp(polecenie, "DEC ")==0)
            {
                if (podano_klucz == 0 || podano_ini == 0)
                    return 0;
                int j = 0;
                while((tekst[j] = getchar()) != '\n')
                {
                    if (j == 127 || tekst[j] < s || tekst[j] > s + m )
                        return 0;
                    j++;
                }
                tekst[j]='\0';
                //PERMUTACJA
                int init = ini;
                int init2;
                for (int k = 0; k<j; k++)
                {
                    init2 = tekst[k] - s;
                    if ((tekst[k] - s - init)>=0)
                    {
                        tekst[k] = klucz[(tekst[k] - s - init)%m];
                    }
                    else
                    {
                        tekst[k] = klucz[m + tekst[k] - s - init];
                    }
                    printf("%c", tekst[k]);
                    init = init2;
                }
                //printf("\n");
                i=-1;
            }
        }
    }
    return 0;
}