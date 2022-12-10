var sum = 0;
for (var i = 1; i <= 100000; i++){
    sum = 0
    for (var j = i; j > 0; j = Math.floor(j / 10)){
        sum += j % 10;
        if (i % sum != 0 || i % (j % 10) != 0){
            break;
        }
    }
    if (j === 0){
        console.log(i);
    }
}