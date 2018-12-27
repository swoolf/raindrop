var obj = require("./gpsLocations.json");

module.exports = {
  getIDfromGPS: function(gps){
    var dist = 1000;
    var id = null;
    var locs = obj.locations;
    for(var i=0; i<locs.length;i++ ){
      var curr = (Math.hypot(locs[i][0][0]-gps[0], locs[i][0][1] - gps[1]));
      if (curr< dist){dist=curr; id = locs[i][1];}
    }
    console.log('dist', dist, 'id', id);
    return id;
  }
}
