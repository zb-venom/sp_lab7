const net = require('net');
const colors = require('colors');

var client = new net.Socket();

client.setEncoding('utf8');

client.connect('4835', '127.0.0.1', function () {
    console.log('Connected to server'.red);
});

process.stdin.on('data', function (data) {
    client.write(data);
});

client.on('data', function (data) {
    log(data);
});

client.on('close', function() {
    console.log('connection closed');
});

function log(data) { 
    let time = new Date; 
    return console.log(time.toLocaleTimeString().yellow + data.split(']:')[0].red + ']:'.red + data.split(']:')[1].replace(new RegExp("\\r?\\n", "g"), "").green); 
}
