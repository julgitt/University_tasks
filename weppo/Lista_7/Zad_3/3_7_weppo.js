var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');
var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag');

app.use(cookieParser());

app.use(express.urlencoded({
    extended: true
}));

app.get("/", (req, res) => {
    res.render("index", { cookies: Object.keys(req.cookies) });
});

app.get("/add/:cookie", (req, res) => {
    var cookieValue = new Date().toString();
    res.cookie(req.params.cookie, cookieValue, { maxAge: 360000 } );
    res.redirect('/');
});

app.post("/delete/:cookie", (req, res) => {
    var cookieValue = req.params.cookie;
    res.clearCookie(cookieValue);
    res.redirect('/');
});

http.createServer(app).listen(3000);