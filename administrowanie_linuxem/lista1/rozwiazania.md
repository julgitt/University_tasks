# Zad 1

### cloc (Count Lines of Code):
#### Funkcje i cechy:
- Liczenie linii kodu wielu popularnych języków programowania.
- Jest stosunkowo szybki, co umożliwia analizę nawet dużych projektów w rozsądnym czasie.
- Działa m.in na systemach Linux, macOS i Windows.
- Wyniki analizy mogą być wyświetlane w różnych formatach.

### sloccount (SLOCCount):
#### Funkcje i cechy:
- Liczenie linii kodu.
- Sloccount może dostarczyć informacje na temat składu projektu, takie jak udział poszczególnych języków programowania czy liczba plików w każdym języku.
- Narzędzie generuje raporty w różnych formatach.
- Możliwość dostosowania: sloccount oferuje możliwość konfiguracji parametrów analizy.

# Zad 2

```bash=
# ls alias
alias ll='ls -lAFbhv --color=always | less -XER'

# time printing
alias gentmp='date +"tmp-%Y%m%d%H%M%S"'

# random password generator
genpwd() {
	tr -dc '3-9A-HJ-NP-Z' < /dev/urandom | head -c 32 && echo
}
```

### `ls`:
- `l` - wylistowuje szczegółowe informacje o plikach:
    - uprawnienia
    - właściciel
    - nazwa grupy
    - rozmiar
    - czas modyfikacji
    - nazwa
- `A` - wylistowuje wszystkie pliki oprócz . i ..
- `F` - dodaje symbole do końca nazwy pliku oznaczające jego typ
    - `/` - directory
    - `@` - symbolic links 
    - `|` - FIFO
    - `=` - socket
    - `>` - doors
    - nothing - regular files
- `b` - wypisuje znaki niegraficzne jako np. "\n", czyli tak jakby ich nie interpretuje, tylko wypisuje w odpowiedni sposób
- `h` - rozmiar pliku wypisywany "po ludzku" w MB, GB, a nie tylko w bajtach
- `v` - sortowanie naturalne - "a" przed "b" (bez względu na wielkość liter)

### `color`:
- `auto` - koloruje tylko jak standardowe wyjście na terminal
- `never` - nie koloruje
- `always` - koloruje

### `less`:
- `X` - nie wysyła "(de)initialization stringów". W praktyce jeśli wychodzimy z less'a to nie czyści tego co wypisało
- `E` - wyjdź z less'a jeśli dotarliśmy do końca pliku
- `R` - wyświetla kolory jako kolory, a nie tekst

### `date +format`:
wyświetla datę w odpowiednim formacie

### `tr [SET1] [SET2]`:
tłumaczy `SET1` na `SET2`
- `d` - usuwa z `SET2` elementy z `SET1`
- `c` - `SET1` staje się dopełnieniem samego siebie

### `head -c [X]`
wypisuje pierwsze X bajtów 

---

# Zad 3 - Grep

### `Grep [options] pattern [files]`

- `-i` - ignoruje wielkość liter
- `-r` - przeszukuje wszystkie pliki w podkatalogach rekursywnie
- `-v` - wyświetla linie które nie pasują do wzorca
- `-n` - wyświetla ponumerowane linie pasujące do wzorca
- `-w` - dopasowuje tylko całe słowa
- `-c` - wyświetla liczbę pasujących linii, zamiast je wypisywać
- `-A n` - wyświetla dopasowaną linię i n następnych linii 
- `-B n` - jw. i n poprzednich linii
- `-C n` - jw. i n następnych oraz poprzednich linii
- `-l` - wyświetla tylko nazwy plików zawierające dopasowanie
- `-q` - wycisza wyjście, np `grep -q "pattern" file.txt && echo "Pattern found" || echo "Pattern not found"`
- `-h` - wyświetla dopasowane linie, ale nie wyświetla nazw plików
- `-o` wyświetla jedynie dopasowane części linii
- `-E` extended regular expressions
- `-f file` pobiera wzorce z pliku
- `-e exp` np. `grep -e 'pattern1' -e 'pattern2' file.txt`
### Regexy
- `^` - wyszukiwanie wzorca zaczynającego się od "xyz":
    `grep '^xyz' file.txt`
- `$` - wyszukiwanie linii kończących się na "xyz":
    `grep 'xyz$' file.txt`
- `[]` - wyszukiwanie linii zawierających cyfry:
    `grep '[0-9]' file.txt`
- `.` - wyszukiwanie linii zawierających dowolny znak, a następnie "xyz"
    `grep '.xyz' file.txt`
- `+` - np. wyszukaj wystąpienie zawierające a i dowolną ilość b po nim (większą niż 0):
    `grep 'ab+' file.txt`
- `*` - np. wyszukaj wystąpienie zawierające a i 0 lub więcej liter b
    `grep 'ab*' file.txt`
- `?` - Dopasowuje zero lub jedno wystąpienie poprzedzającego wyrażenia (opcjonalne)
    `grep 'colou\?r' file.txt`
- `()` - grupowanie np dopasowanie linii zawierających słowo open lub close:
    `grep '\(open\|close\)' file.txt`
- `\b` - oznacza początek lub koniec słowa
- `\1` - ta sama treść przechwycona wcześniej w pierwszej zdefiniowanej grupie, musi pojawić sie ponownie.
    `grep '\b\([a-zA-Z]\+\) \1 \1\b' file.txt`
---

# Zad 4 - Find

### `find  [path] [options] [conditions]`
Program find jest narzędziem używanym w systemach operacyjnych Unix i Unix-like do wyszukiwania plików i katalogów w drzewie systemu plików. Oto krótkie omówienie jego podstawowych opcji:

- `name pattern`: Wyszukuje pliki i katalogi o określonym nazwie.
    `find /home/user -name "*.txt"`
- `type type`: Pozwala na wyszukiwanie plików określonego typu. 
    - f - pliki 
    - d - katalogi
    - l - symlink, itp.

    `find /etc -type d`
- `exec command {} +`: Wykonuje określoną komendę na znalezionych plikach lub katalogach. '{}' jest zastępowane nazwami plików/katalogów, a '+' oznacza, że komenda będzie wywoływana z wieloma argumentami naraz.
    `find /var/log -name "*.log" -exec cp {} /backup \;`
- `size n[cwbkMG]`: Wyszukiwanie plików o określonym rozmiarze. `n` to liczba, a `[cwbkMG]` to jednostki (bytes, words, kilobytes, blocks, megabytes, gigabytes).
    `find /home -size +1M`
- `maxdepth n`: Określa maksymalną głębokość rekursji podczas przeszukiwania katalogów.
    `find /usr -maxdepth 2 -name "*.txt"`
- `mindepth n`: Określa minimalną głębokość rekursji podczas przeszukiwania katalogów.
    `find /var/log -mindepth 2 -type f`
- `empty`: Wyszukuje puste pliki i katalogi.
    `find /tmp -type d -empty`
- `delete`: Usuwa znalezione pliki i katalogi.
    `find /tmp -type f -name "*.tmp" -delete`
- `print`: Wyświetla znalezione pliki i katalogi na standardowym wyjściu.
    `find /home -name "*.jpg" -print`
    
---

# Zad 5 - Rename

### `rename [opcje] 'wyrażenie_regularne' pliki`

#### Instalacja: 
- sudo cpan
- install File::Rename

#### Opcje:
`-n, --no-act`: Tryb testowy. Wyświetla zmiany, które zostaną dokonane, ale nie wykonuje ich faktycznie.

`-v, --verbose`: Tryb gadatliwy. Wyświetla szczegółowe informacje o dokonywanych zmianach.

`-f, --force`: Wymusza zmianę nazw, nawet jeśli nowa nazwa już istnieje.

`-d, -filename` : nie zmienia nazwy katalogom, tylko plikom

#### Przykładu użycia:
`s` - zmiana ciągu na inny
`g` - nie tylko pierwsze dopasowanie, tylko globalnie w całym tekście
- Zmiana rozszerzenia plików:
`rename -- 's/\.txt$/\.dat/' *.txt`
- Zmiana wielkości liter:
`rename 'y/A-Z/a-z/' ./*`
- Dodanie prefiksu do nazw plików:
`rename 's/^/backup_/' *.txt`
- Zamiana spacji na podkreślenia:
`rename 's/ /_/g' *.txt`
- Usuwanie określonego ciągu znaków:
`rename 's/kot//g'`


---


### Lista zainstalowanych pakietów, które nie posiadają własnego podkatalogu w /usr/share/doc/:
```bash
dpkg -l | awk '/^ii/ {print $2}' | while read pkg; do 
    if [ ! -d "/usr/share/doc/$pkg" ]; then 
        echo "$pkg" 
    fi
done
```
- `dpkg -l`: Wyświetla listę zainstalowanych pakietów w systemie.
- `grep '^ii'`: Filtruje tylko te linie, które zaczynają się od "ii", co oznacza, że są to właściwie zainstalowane pakiety.
- `awk '{print $2}'`: Wyodrębnia nazwy pakietów z wyniku poprzedniego polecenia.
- `while read pkg; do ... done`: Iteruje przez każdy zainstalowany pakiet.
- `[ ! -d "/usr/share/doc/$pkg" ];`: Sprawdza, czy dla danego pakietu nie istnieje katalog w /usr/share/doc/.
- `then echo "$pkg"`: Jeśli nie istnieje, wypisuje nazwę tego pakietu.

### Lista podkatalogów katalogu /usr/share/doc/, których nazwy nie są nazwami żadnego zainstalowanego pakietu:
```bash
find /usr/share/doc/ -maxdepth 1 -mindepth 1 -type d | while read dir; do
    if !  apt list --installed 2>/dev/null | grep -q "$(basename "$dir")"; then
        echo "$dir"
    fi
done
```

- `find /usr/share/doc/ -maxdepth 1 -mindepth 1 -type d`: Zwraca wszystkie katalogi w /usr/share/doc/.
- `while read dir; do ... done`: Iteruje przez każdy katalog.
- `dpkg -S "/usr/share/doc/$dir"`: Sprawdza, czy dany katalog jest przypisany do jakiegoś zainstalowanego pakietu.
- `> /dev/null 2>&1`: Przekierowanie wyjścia do pliku wraz z błędami.
- `echo "$dir"`: Jeśli nie znalazło pakietu to wypisujemy nazwę katalogu.

### Listę pakietów posiadających własny podkatalog w katalogu /usr/share/doc/, który jednak nie zawiera pliku changelog.Debian.gz:
```bash=
dpkg -l | grep '^ii' | awk '/^ii/{print $2}' | while read pkg; do
    if [ -d "/usr/share/doc/$pkg" ] && [ ! -f "/usr/share/doc/$pkg/changelog.Debian.gz" ]; then
        echo "$pkg"
    fi
done
```
- `dpkg -l | grep '^ii' | awk '{print $2}'`: Wyświetla listę zainstalowanych pakietów.
- `while read pkg; do ... done:` Iteruje przez każdy zainstalowany pakiet.
- `[ -d "/usr/share/doc/$pkg" ] && [ ! -f "/usr/share/doc/$pkg/changelog.Debian.gz" ];`: Sprawdza, czy dla danego pakietu istnieje katalog w /usr/share/doc/ i czy nie zawiera on pliku changelog.Debian.gz. 
- `then echo "$pkg"`: Jeśli tak, wypisuje nazwę pakietu.

### Listę pakietów posiadających własny plik changelog.Debian.gz, który zawiera tylko jeden wpis:
```bash=
dpkg -l | awk '/^ii/ {print $2}' | while read pkg; do
    if [ -f "/usr/share/doc/$pkg/changelog.Debian.gz" ]; then
        count=$(zcat "/usr/share/doc/$pkg/changelog.Debian.gz" | grep -c "^[^ ]")
        if [ $count -eq 1 ]; then
            echo "$pkg"
        fi
    fi
done

```

- `dpkg -l | grep '^ii' | awk '{print $2}'`: Wyświetla listę zainstalowanych pakietów.
- `while read pkg; do ... done`: Iteruje przez każdy zainstalowany pakiet.
- `[ -f "/usr/share/doc/$pkg/changelog.Debian.gz" ] `: Sprawdza, czy dla danego pakietu istnieje plik changelog.Debian.gz,
- `count=$(zcat "/usr/share/doc/$pkg/changelog.Debian.gz" | grep -c 'Initial release')`: Zlicza ilość wpisów w zawartości pliku i zapisuje w zmiennej.
- `if [ $count -eq 1 ]; then echo "$pkg" fi`: Jeśli ilość wpisów jest równa 1, wypisuje nazwę pakietu.

### Liczbę wystąpień słowa bash (zapisanego małymi lub wielkimi literami) w pliku /usr/share/doc/bash/INTRO.gz:

```bash=
zcat /usr/share/doc/bash/INTRO.gz | grep -ioc 'bash'
```

- `zcat /usr/share/doc/bash/INTRO.gz`: Rozpakowuje zawartość pliku INTRO.gz.
- `grep -ioc 'bash'`:  Zlicza wystąpienia słowa "bash" (nie biorąc pod uwagę wielkości liter).

---

# Zad 10

**Sed** (stream editor)- narzędzie wiersza poleceń służące do przetwarzania i modyfikowania tekstu na strumieniach danych. 

### Flagi

- `-e` - Możliwość podania wielu edycji w jednym wywołaniu sed.
- `-i` - Bezpośrednia edycja pliku wejściowego (bez konieczności tworzenia kopii zapasowej).
- `-n` - Wyłącza domyślne wyświetlanie przetworzonych linii. Może być używany z poleceniem `p`, aby wyświetlić wybrane linie.
- `-E/ -r` - Rozszerzone wyrażenia regularne.
- `-g` - Zastosowanie zmiany do wszystkich wystąpień w linii. Zamiast g możemy wpisać konkretną liczbę wystąpień.
- `-f` - Pozwala na przetwarzanie skryptów sed z pliku.
- `-s` - Tryb cichego ignorowania błędów.
    
Przykłady użycia:

- Zastępowanie tekstu:

`sed 's/stary/nowy/g' plik.txt`


- Usuwanie linii zawierających określony wzorzec:

`sed '/do_usuniecia/d' plik.txt`

- Wyświetlanie konkretnych linii:

`sed -n '1,10p' plik.txt`

- Usuwanie konkretnych linii:
`sed '5,10d' plik.txt`

- Usuwanie linii od i-tej linii:
`sed 'i,$d' plik.txt`
