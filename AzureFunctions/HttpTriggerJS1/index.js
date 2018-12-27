var lh = require('./locHelpers');

module.exports = function (context, req) {
    context.log('JavaScript HTTP trigger function processed a request.');

    if (req.query.zip || (req.body && req.body.zip)) {
       if (req.query.zip){var zip = req.query.zip;}else{var zip= req.body.zip;
       context.log(zip);}
       lh.getGPS(context, zip, lh.getID, lh.sendID );
    }
    else {
        context.done(null, "Please use a real zip");
    }
};