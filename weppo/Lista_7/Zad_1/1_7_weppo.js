const http = require('http');
const express = require('express');
const multer = require('multer');
const app = express();
const upload = multer({dest: './public/uploads'});

app.set('view engine', 'ejs');
app.set('views','./views');
app.use(express.static('public'));

app.get('/', (req,res) => {
    res.render('index', {});
});

app.post('/avatar', upload.single('avatar'), (req,res) => {
    if(req.file?.mimetype.includes('image')){
        res.render('index', {filename: req.file?.filename});
    } else {
        res.render('index', {message: "Incorrect file type. The file must be an image!"});
    }
});

http.createServer(app).listen(3000);