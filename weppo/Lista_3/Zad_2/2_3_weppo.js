/*2. (1p) Napisac wlasne implementacje metod map, forEach i filter dla tablic. 
Zademonstrowac przygotowane implementacje w praktyce, 
przekazujac funkcje zwrotne w postaci zwyklej (function ...)
i jako funkcje strzalkowe (x => ...).*/
function example(x){
    return x *= 10;
}

function print_example(x){
    console.log(x *= 10);
}

function bool_example(x){
    if(x % 40 == 0){
        return true;
    }
    return false;
}

function my_map(array, fun){
    for(var i = 0; i < array.length; i++){
        array[i] = fun(array[i]);
    }
}

function my_forEach(array, fun){
    for(var i = 0; i < array.length; i++){
        fun(array[i]);
    }
}

function my_filter(array, fun){
    for(var i = 0; i < array.length; i++){
        if (!fun(array[i])){
            array.splice(i, 1);
            i--;
        }
    }
}


var arr = [0, 1, 2, 3, 4];
console.log("poczatkowa tablica:\n" + arr);

my_map(arr, example); //*10
console.log("\nmap- mnożenie * 10:\n" + arr);
my_map(arr, x => x * 2);
console.log("\nmap- mnożenie * 2:\n" + arr);

console.log("\nforEach- print x*10: ");
my_forEach(arr, print_example); //*10

console.log("\nforEach- print x: ");
my_forEach(arr, x => { console.log(x); });

my_filter(arr, bool_example); //%40
console.log("\nfilter %40:\n" + arr);
my_filter(arr, x => x < 50);
console.log("\nfilter < 50:\n" + arr); 
