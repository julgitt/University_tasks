var http = require('http');
var express = require('express');
var cookieParser = require("cookie-parser");
var session = require('express-session');
const FileStore = require("session-file-store")(session);
var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag');

app.use(cookieParser());
app.use(session({
    store: new FileStore,
    resave: true,
    saveUninitialized: true,
    secret: 'qewhiugriasgy'
}));

app.get("/", (req, res) => {
    if (!req.session.views) {
        req.session.views = 0;
    }
    
    req.session.views +=  1;
    res.setHeader('Content-Type', 'text/html');
    res.write('<p>views: ' + req.session.views + '</p>');
    res.end();
    
});

app.get("/delete", (req, res) => {
    try {
        req.session.destroy()
    } catch (e) {
        console.error(e);
    } finally {
        res.redirect('/')
    }
});

http.createServer(app).listen(3000);