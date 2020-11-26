const textRoutes = require('./text_routes');
const searchRoutes = require('./search_routes');

module.exports = function(app, db) {
    textRoutes(app, db);
    
    searchRoutes(app, db);
};
