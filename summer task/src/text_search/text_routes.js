var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);

module.exports = function (app, db) {
    app.post('/text', (req, res) => {
        const title = req.body.title;
        const lines = req.body.data.toLowerCase();
        const pack = { title: title, data: lines };
        db.collection('text').insert(pack, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                db.collection('text').findOne( { title: title }, { '_id': 1 }, (err, item) => {
                    if (err) {
                        res.send({ 'error': 'An error has occured' });
                    } else {
                        res.send({ _id: item._id, title: title });
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
