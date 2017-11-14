var http = require('http');
var url = require("url");

var port = 3000;
var ip = 'localhost';

var checkpoints = [[],[],[]];

var server = http.createServer((req, res) => {
	var params = url.parse(req.url,true).query;

	if(params.checkpoint != undefined){
		checkpoints[params.checkpoint].push(new Date());
	}

	console.log(checkpoints);
	res.end('<h1>BatWebServer is online.</h1>')
})

server.listen(port, ip, () => {
	console.log('BatWebServer rodando em ' + ip + ":" + port);
})