/*
Przygotować aplikację node.js Express, która pozwala wprowadzić i wydrukować stan-
dardowy ”pasek zgłoszenia zadań”.
Aplikacja ma składać się z dwóch widoków: formularza zgłoszenia (widok domyślny \) i
widoku wydruku (\print).
Na formularzu zgłoszenia użytkownik aplikacji powinien mieć możliwość wpisania imienia,
nazwiska i nazwy zajęć oraz kompletu wyników kolejnych deklarowanych 10 zadań z odpo-
wiednią liczbą punktów (uwaga, nie wymagać wpisywania wartości, brak wartości oznacza
0).
Program powinien kontrolować poprawność wpisywanych danych - w przypadku braku
imienia, nazwiska lub nazwy zajęć formularz jest zwracany do przeglądarki do uzupełnie-
nia.
*/
const http = require('http');
const express = require('express'),
app = express(),
bodyParser = require('body-parser');

app.set('view engine', 'ejs');
app.set('views', './views');

//middleware for parsing bodies from URL, extended: true - any type not only string type
app.use(bodyParser.urlencoded({extended: true})); 

app.get('/', (req, res) => {
  let num_ex = 10;
  let arr = Array(num_ex).fill("");
  res.render('form', {numOfExcercises: num_ex,
    firstName:'',
    lastName:'', 
    subject:'', 
    ex_score: arr}); // na poczatku renderujemy formularz
});

app.post('/', (req, res) => {

  const firstName = req.body.firstName;
  const lastName  = req.body.lastName;
  const subject   = req.body.subject;

  let exercises = []; // tablica elementow {name, score}
  let exercises_url = '';
  for (let [name, score] of req.body.exercises.entries()) {
    score = score ? score : 0;
    exercises.push({
      name,
      score
    });

    exercises_url += '&' + name + '=' + score;
  }
  let num_ex = 10;
  if (!firstName || !lastName  || !subject) {
    res.render('form', {
      numOfExcercises: num_ex,
      firstName:firstName,
      lastName:lastName, 
      subject:subject, 
      ex_score: exercises}); 
  } else {
    res.redirect('/print?firstName=' + firstName +
     '&lastName=' + lastName + '&subject=' + subject 
     + exercises_url + '&numOfExcercises=' + num_ex);
  }

  //res.render('print', { firstName, lastName, subject, exercises}); 
});

app.get('/print', (req, res) => {
  var firstName = req.query.firstName;
  var lastName = req.query.lastName;
  var subject = req.query.subject;
  var num_ex = req.query.numOfExcercises;
 
  let exercises = []; // tablica elementow {name, score}
  for (let i = '0'; i <= ('' + num_ex); i++) {
    let [name, score] = [i, req.query[i]];
    score = score ? score : 0;
    exercises.push({
      name,
      score
    });
  }
  res.render('print', { firstName, lastName, subject, exercises});
});
http.createServer(app).listen(3000);