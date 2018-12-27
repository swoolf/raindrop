var https = require('https');
var fc = require('./findClosest');

var urlStart = 'https://maps.googleapis.com/maps/api/geocode/json?address=';
var urlEnd = '&key=someKey';

module.exports ={
  sendID: function(context, id){
    context.log('sent', id);
    result = id;
    context.done(null, id);
  },

  getID: function(context, callback, gps){
    context.log('the id', gps);
    callback( context, fc.getIDfromGPS([ gps.lat, gps.lng ]) );
  },

  getGPS: function(context, zip, callback1, callback2){
      https.get(urlStart + zip + urlEnd, (resp) => {
        let data = '';
        resp.on('data', (chunk) => {
          data += chunk;
        });
        resp.on('end', () => {
          callback1( context, callback2, JSON.parse(data).results[0].geometry.location );
        });
      }).on("error", (err) => {
          console.log("Error: " + err.message);
          });
    }
}
