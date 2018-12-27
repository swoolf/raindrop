var gpsObj = require('./gpsLocations.json');
var particle = require('./particle');
var darksky = require('./darksky');

var dsKeys = ['someKeys'
            ];

module.exports = function (context, myTimer) {
   var locs = gpsObj.locations;
    for (var i =0; i<locs.length; i++){
        var id = locs[i][1];
        var latLong = locs[i][0][0].toString() +','+ locs[i][0][1].toString();
        var keyNo = Math.floor(i/3);
        darksky.getRainHour(context, dsKeys[keyNo], latLong, id.toString()+'rainDial', particle.send2particle);
        }
    context.done();
};
