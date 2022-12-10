/*
Pokazać w jaki sposób odczytywać duże pliki linia po linii za pomocą modułu readline.
Działanie zademonstrować na przykładowym kodzie analizującym duży plik
logów hipotetycznego serwera WWW, w którym każda linia ma postać
08:55:36 192.168.0.1 GET /TheApplication/WebResource.axd 200
gdzie poszczególne wartości oznaczają czas, adres klienta, rodzaj żądania HTTP, nazwę
zasobu oraz status odpowiedzi.
W przykładowej aplikacji wydobyć listę adresów IP trzech klientów, którzy skierowali do
serwera aplikacji największą liczbę żądań. Przykładowe dane dla aplikacji proszę sobie
wygenerować we własnym zakresie (niekoniecznie ściągać logi z rzeczywistego serwera!)
Wynikiem działania programu powinien być przykładowy raport postaci:
12.34.56.78 143
23.45.67.89 113
123.245.167.289 89
*/

const fs = require('fs');
const readline = require('readline');

var ip_counter = {}; // słownik [ip:wystąpienia]

const rl = readline.createInterface({
    input: fs.createReadStream('./text.txt'),
});

rl.on('line', (line) => {
    var ip = line.split(" ")[1];
    if (ip_counter.hasOwnProperty(ip))
        ip_counter[ip]++;
    else
        ip_counter[ip] = 1;
});

rl.on('close', function() {
    var result = [["ip1", 0], ["ip2", 0], ["ip3", 0]];

    for (var ip in ip_counter) {
        //jezeli ip ma większą liczbę wystąpień niż to które jest na 3 miejscu
        if (ip_counter[ip] > result[2][1]){
            var tuple = [ip, ip_counter[ip]];
            //sprawdzamy na ktorym miejscu powinno sie znajdowac i usuwamy, to które poprzednio było na 3 miejscu
            for (var i = 0; i < 3; i++) {
                //zamiana wartosci
                if (tuple[1] > result[i][1]) {
                    var temp = result[i];
                    result[i] = tuple;
                    tuple = temp;
                }
            }
        }
    }

    
    console.log(result[0][0], result[0][1]);
    console.log(result[1][0], result[1][1]);
    console.log(result[2][0], result[2][1]);
});
