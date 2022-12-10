var array = [100000]

for(var i = 2; i <= 100000; i++){
     array[i] = true;
}
for(var i = 2; i <= Math.sqrt(100000); i++)
{
    if(array[i] == true) {
        for(var j = i * i; j <= 100000; j += i) {
            array[j] = false;
        }
    }
}

for(var i = 2; i <= 100000; i++)
{
    if(array[i] === true) {
        console.log(i);
    }
}
