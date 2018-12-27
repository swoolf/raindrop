var https = require('https');

var dsKey = 'somekey';
var urlStart = 'https://api.darksky.net/forecast/';
var urlEnd = '?exclude=[currently,hourly,daily,alerts]';

module.exports = {
   getRainHour: function(context, dsKey, gps, id, callback){
      https.get(urlStart +dsKey +'/'+ gps + urlEnd , (res) => {
              res.setEncoding('utf8');
              res.on('data', (d) => {
                  var myObj = JSON.parse(d);
                  var rainArray = new Array(myObj.minutely.data.length);
                  for (var i = 0, len = myObj.minutely.data.length; i < len; i++) {
            //need to come up with a threshold for precipIntensity and precipProbability
                      if (i>30 && myObj.minutely.data[i].precipProbability>0.3){
                          rainArray[i]=1;
                          }
                  else  if (i<=30 && myObj.minutely.data[i].precipProbability>0.5){
                          rainArray[i]=1;
                          }
                          else{ rainArray[i]=0;}
                      }
                  callback(id, rainArray.toString());
                  });
              }).on('error', (e) => {context.log(e);});
      }
}
