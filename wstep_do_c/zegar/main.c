#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
Drugi (3 pkt) powinien jako parametr wywołania przyjąć 3 liczby z zakresów odpowiednio 0-23 0-59 0-59.
A następnie wypisać podane liczby jako godzinę w formacie "gg:mm:ss". Późniejpowinien w pętli czytać kolejne znaki z wejścia,
i za każdym razem gdy pojawi się znak nowej linii(resztę znaków powinien ignorować), aktualizować godzinę dodając do niej 1 sekundę
i wypisując nową godzinę(nie zapomnij znaku nowej linii po wypisaniu).
 Po jego uruchomieniu każde ’enter’ powinno pokazywać godzinę zwiększoną o 1.
 Na końcu (1pkt) połącz terminalem za pomocą pipe’a działania obu programów tak by wyjściepierwszego było przekazywane bezpośrednio na wejście drugiego za pomocą
 LINUX:  ./prog1 | ./prog2 23 59 53
 W wyniku tego wywołania powinien pojawić się zegar aktualizowany co sekundę do nowej godziny.
 Dla uzyskania pozostałych 4 pkt wybierz coś z poniższej listy i doimplementuj do powyższych programów - napisz w komentarzu co wybrałeś:
 •(2pkt) Gdy drugi program zostanie uruchomiony bez argumentów wczytaj aktualną godzinę za pomocą funkcji time() oraz localtime() z time.h .
  Punkt ten wymaga użycia struktur i wskaźników, więc lekko wykracza ponad materiał z tego tygodnia - możewymagać jakiejś chwili dociekania.
  •(2pkt) W obecnej wersji pierwszy program zużywa dość sporo zasobów procesora(sprawdźw menadżerze zadań lub za pomocą top lub htop w linuxie). S
  próbuj użyć funkcji (S)sleep,w celu zredukowania zużycia zasobów - sprawdź czy zadziałało. Funkcja sleep w jestzależna od systemu i jest dostępna w Windows.h, albo w unistd.h.
  Przyjmuje też innejednostki (ms,s) - doczytaj szczegóły o sleep w systemie w którym pracujesz.
*/


int main(int argc, char *argv[])
{
    int godzina;
    int minuta;
    int sekunda;
    char c;
    if (argc == 4)
    {
        godzina = atoi(argv[1]);
        minuta = atoi (argv[2]);
        sekunda = atoi (argv[3]);
    }
    else if (argc == 1)
    {
        time_t now = time (0);
        struct tm *tm_struct = localtime(&now);
        godzina = tm_struct ->tm_hour;
        minuta = tm_struct ->tm_min;
        sekunda = tm_struct ->tm_sec;
    }
    printf("%02d:%02d:%02d\n", godzina, minuta, sekunda);
    while ((c = getchar()))
    {
        if (c == '\n')
        {
            sekunda ++;
            if (sekunda-60 > 0)
            {
            minuta ++;
            sekunda %= 60;
            if (minuta - 60 > 0)
                {
                    godzina ++;
                    minuta%=60;
                    if (godzina - 23 > 0)
                    {
                        godzina == 0;
                    }
                }
            }
            printf("%02d:%02d:%02d\n", godzina, minuta, sekunda);
        }
    }
    return 0;
}