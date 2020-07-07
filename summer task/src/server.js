const express = require('express');
const MongoClient = require('mongodb').MongoClient;
const bodyParser = require('body-parser');
const db = require('./config/db')
const app = express().use(bodyParser.urlencoded({ extended: true }));
const port = 3000;

MongoClient.connect(db.url, (err, client) => {
    if (err) return console.log(err);
    const database = client.db('pagamovdb');
    require('./routes/index')(app, database);
    app.listen(port, () => {
        console.log("listen on ", port);
    });
});
