var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);

module.exports = function (app, db) {
    app.post('/text', (req, res) => {
        // make new title and text in db
        const title = req.body.t;
        // const lines = req.body.d.split('\n').map(elem => elem.split(' '));
        const lines = req.body.d;
        const pack = { t: title, d: lines };
        db.collection('text').insert(pack, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                db.collection('text').findOne( { t: title }, { '_id': 1 }, (err, item) => {
                    if (err) {
                        res.send({ 'error': 'An error has occured' });
                    } else {
                        res.send({ _id: item._id, t: title });
                    }
                });
            }
        });
    });

    app.get('/text/:id', (req, res) => {
        // get text by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('text').findOne(details, { _id: 0 }, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send(item);
            }
        });
    });

    app.get('/text', (req, res) => {
        // get all text
        db.collection('text').find( {} ).toArray((err, items) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send(items);
            }
        });
    });

    app.delete('/text/:id', (req, res) => {
        // delete text by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('text').remove(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send('text ' + id + ' deleted!');
            }
        });
    });
};
