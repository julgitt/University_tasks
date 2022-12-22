const fs = require('fs');
const https = require('https');
 
(async function () {
    const pfx = await fs.promises.readFile('cert.pfx');
    const server = https.createServer({
        pfx: pfx,           // nasz certyfikat
        passphrase: '1243'  // haslo
    },
    (req, res) => {
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.end(`hello world ${new Date()}`);  // nic nie przetwarzamy wiec nie ma write tylko od razu odpowiedz do klienta
    });
    server.listen(3000);
    console.log('started');
})();
