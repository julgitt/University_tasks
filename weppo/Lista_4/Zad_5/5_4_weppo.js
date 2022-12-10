/*
Napisać program używający modułu (fs), który przeczyta w całości plik tekstowy a
następnie wypisze jego zawartość na konsoli.
*/
const fs = require('fs');

fs.readFile('./text.txt', 'utf8', function(err, data) {
    if(err){
        console.error(err);
        return;
    }
    console.log(data);
  });