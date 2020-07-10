const express = require('express');
const MongoClient = require('mongodb').MongoClient;
const bodyParser = require('body-parser');
const db = require('./config/db') // url for connect to db
const app = express().use(bodyParser.urlencoded({ extended: true }));
const port = 3000;

MongoClient.connect(db.url, (err, client) => {
    if (err) return console.log(err);
    const database = client.db('pagamovdb');

    require('./routes/index')(app, database);
    require('./text_search/index')(app, database);
    
    app.listen(port, () => {
        console.log("listen on ", port);
    });
});
