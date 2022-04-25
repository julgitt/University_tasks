#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n; // ilosc stanow automatu
    int m; // ilosc stanow akceptujacych
    int a; //ilosc akceptowanych liter
    int t; // ilosc testow
    int i; // stan poczatkowy

    char w[1001]; //slowo do przeczytania
    scanf ("%d %d %d", &n, &m, &a);
    int stany_akceptujace [m];
    int liczby[a][n];

    //Posortowane numery stanow akceptujacych oddzielonych spacja
    for (int k = 0; k<m; k++)
        scanf("%d", &stany_akceptujace[k]);

    //Liczby określające do którego stanu przejdzie automat będący w  n-stanie przy napotkaniu a-itery (0-litera to 'a',..., 26-litera to 'z' ) ograniczone przez N.
    for (int k = 0; k<a; k++)
    {
        for (int j = 0; j<n; j++)
        {
            scanf("%d", &liczby[k][j]);
        }
    }

    scanf("%d", &t); //ilosc testow
    char c; //kolejne znaki slowa w
    int l = 0; //licznik
    int znaleziono;//czy stan koncowy nalezy do zbiorow stanow akceptowalnych
    //____________________kolejne testy_____________________________________________________________
    for (int k = 0; k<t; k++)
    {
        l = 0;
        znaleziono = 0;
        scanf("%d ", &i); // stan poczatkowy
        while (((c=getchar())!= '\n') && l < 1000) // czytanie slowa
        {
            w[l] = c;
            l++;
        }
        w[l] = '\0';

        for (int j = 0; j<l; j++)//kolejne stany
        {
            i = liczby[w[j]-97][i];
        }
        //czy stan koncowy jest akceptowalny
        for (int akceptujace = 0; akceptujace < m; akceptujace++)
        {
            if (stany_akceptujace[akceptujace] == i)
            {
                znaleziono = 1;
                break;
            }
        }
        if (znaleziono == 1)
        {
            printf ("%d ACCEPT\n", i);
        }
        else
        {
            printf ("%d REJECT\n", i);
        }
    }
    return 0;
}