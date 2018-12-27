var https = require('https');

module.exports={
  send2particle: function(name, data, context){
      var dataString = 'name='+ name +'&data=' + data + '&private=true&ttl=60&access_token=someToken';
      const options = {
          method: 'POST',
          host: 'api.particle.io',
          path:'/v1/devices/events',
          headers: {
              'Content-Type': 'application/x-www-form-urlencoded',
              'Content-Length': Buffer.byteLength(dataString)
              }
          };

      const req = https.request(options, (res) => {
          res.setEncoding('utf8');
          });
          req.on('error', (e) => {context.log(e); });
          req.write(dataString);
          req.end()
      }
}
