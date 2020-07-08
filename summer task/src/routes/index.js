// const noteRoutes = require('./note_routes');
const washerRoutes = require('./washer_routes');
const workerRoutes = require('./worker_routes');

module.exports = function(app, db) {
    // noteRoutes(app, db);
    washerRoutes(app, db);
    workerRoutes(app, db);
};
