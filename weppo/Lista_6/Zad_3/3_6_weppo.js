var http = require('http');
var express = require('express');
var app = express();

app.get('/', (req, res) => {
 res.setHeader('Content-disposition', 'attachment; filename="foo.txt"');
 res.send('tekst');
});
http.createServer(app).listen(3000);