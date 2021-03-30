var net = require('net');
const colors = require('colors');

const PORT = 4835;
const HOST = '127.0.0.1';
var sockets=[];

console.log('\n\n');
var server = net.createServer(function (socket) {
    log('Connected <- '.green + (socket.remoteAddress.toString().replace(new RegExp("\\r?::ffff:", "g"), "") + ':' + socket.remotePort).red, 'client');
    socket.on('data', function (data) {
        log('From <- ' +  (socket.remoteAddress.toString().replace(new RegExp("\\r?::ffff:", "g"), "") + ':' + socket.remotePort).red
         + ' Message: ' + data.toString().replace(new RegExp("\\r?\\n", "g"), "").green, 'client');
        sockets.forEach(e => {
            e.write(' [' + socket.remoteAddress.toString().replace(new RegExp("\\r?::ffff:", "g"), "") + ':' + socket.remotePort + ']: ' + data);
        });
    });
    var clientName = socket.remotePort;
    sockets[clientName] = socket;
    socket.on('close', function() {
        delete sockets[clientName];
    });
}).listen(PORT);
server.on('listening', function () {
    log('Starting server...');
    log('Listening at -> ' + (HOST + ':' + PORT).red);
});
function log(data, user) { 
    user = !!user ? user : 'server'; 
    let time = new Date; 
    return console.log((time.toLocaleTimeString() + ' [' + user + ']: ').yellow + data); 
}