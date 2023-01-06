http = require('http');
express = require('express');
app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
    var combo1 = {
        name: 'checkbox',
        options: [
            { value: 1, label: 'element 1' },
            { value: 2, label: 'element 2' },
            { value: 3, label: 'element 3' }
        ]
    };
    var combo2 = {
        name: 'radio',
        options: [
            { value: 4, label: 'never' },
            { value: 5, label: 'rarely' },
            { value: 6, label: 'often' },
            { value: 7, label: 'always' }
        ]
    };
    res.render('index', { combo1, combo2 });
})

app.listen(3000, () => {
    console.log(`server started at port 3000`);
});