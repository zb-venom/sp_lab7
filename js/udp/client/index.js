const dgram = require('dgram');
const colors = require('colors');

var client = dgram.createSocket('udp4');


client.send('con', 0, 3, 4834, '127.0.0.1');
client.on("listening", () => {
    client.on('message', function (message, rinfo) {
        log(message);
    });
});

process.stdin.on('data', function (data) {
    client.send(data, 0, data.length, 4834, '127.0.0.1');
});

client.on('close', function() {
    console.log('connection closed');
    client.close();
});

function log(data) { 
    let time = new Date; 
    return console.log(time.toLocaleTimeString().yellow + data.toString().split(']:')[0].red + ']:'.red + data.toString().split(']:')[1].replace(new RegExp("\\r?\\n", "g"), "").green); 
}