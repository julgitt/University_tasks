/*Przedstawić po raz kolejny własne implementacje metod map, forEach i filter
dla tablic, tym razem dodać poprawne sygnatury. Najwygodniej będzie użyć mechanizmu
typów generycznych, na przykład:*/

function example(x: number){
    return x *= 10;
}

function print_example(x: number){
    console.log(x *= 10);
}

function bool_example(x: number){
    if(x % 40 == 0){
        return true;
    }
    return false;
}

function my_map<T>(array: T[], fn: (t: T) => T){
    for(var i = 0; i < array.length; i++){
        array[i] = fn(array[i]);
    }
}

function my_forEach<T>(array: T[] , fun: (t: T) => any){ //any, void or undefinded?
    for(var i = 0; i < array.length; i++){
        fun(array[i]);
    }
}

function my_filter<T>(array: T[], fun: (t: T) => boolean){ //czy funkcje powinny cos zwracac
    for(var i = 0; i < array.length; i++){                 //czy byc typu void i tylko zmieniac array
        if (!fun(array[i])){
            array.splice(i, 1);
            i--;
        }
    }
}


var arr: number[] = [0, 1, 2, 3, 4];
console.log("poczatkowa tablica:\n" + arr);

my_map(arr, example); //*10
console.log("\nmap- mnożenie * 10:\n" + arr);
my_map(arr, (x: number) => x * 2);
console.log("\nmap- mnożenie * 2:\n" + arr);

console.log("\nforEach- print x*10: ");
my_forEach(arr, print_example); //*10

console.log("\nforEach- print x: ");
my_forEach(arr, x => { console.log(x); });

my_filter(arr, bool_example); //%40
console.log("\nfilter %40:\n" + arr);
my_filter(arr, (x: number) => x < 50);
console.log("\nfilter < 50:\n" + arr); 
