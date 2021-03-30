const dgram = require('dgram');
const colors = require('colors');
const PORT = 4834;
const HOST = '127.0.0.1';
const server = dgram.createSocket('udp4');
var clients = [];
console.log('\n\n');
server.on('listening', function () {
    var address = server.address();
    log('Starting server...');
    log('Listening at -> ' + (address.address + ':' + address.port).red);
});
server.on('message', function (message, rinfo) {
    if (message == 'con') clients[rinfo.port] = rinfo;
    else {
        log('From <- ' + (rinfo.address + ':' + rinfo.port).red + ' Message: ' + message.toString().replace(new RegExp("\\r?\\n", "g"), "").green, 'client');
        clients.forEach(e => {
            if (e.port != rinfo.port) {
                m = ' [' + rinfo.address + ':' + rinfo.port + ']: ' + message;
                server.send(m, 0, m.length, e.port, e.address)
            }
        });
    }
});
server.on('error', function (error) {
    log('server error:' + error.stack);
    server.close();
});
server.bind(PORT, HOST);
function log(data, user) { 
    user = !!user ? user : 'server'; 
    let time = new Date; 
    return console.log((time.toLocaleTimeString() + ' [' + user + ']: ').yellow + data); 
}