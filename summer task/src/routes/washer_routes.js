var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);

module.exports = function (app, db) {
    app.post('/washer', (req, res) => {
        // make new washer
        const washer = { x: req.body.x, y: req.body.y, work: [], workers: [] };
        db.collection('washer').insert(washer, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send(result.ops[0]);
            }
        });
    });

    app.get('/washer/:id', (req, res) => {
        // get washer by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('washer').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send(item);
            }
        });
    });

    app.get('/washer', (req, res) => {
        // get all washers
        db.collection('washer').find( {},  { x: { $gte: 0} }).toArray((err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send(item);
            }
        });
    });

    app.delete('/washer/:id', (req, res) => {
        // delete note by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('washer').remove(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send('washer ' + id + ' deleted!');
            }
        });
    });

    app.delete('/washer', (req, res) => {
        // delete note by id
        const coords = { x: req.body.x, y: req.body.y }
        console.log(coords);
        db.collection('washer').remove({}, coords, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                res.send('washer x: ' + coords.x + ' y: ' + coords.y + ' deleted!');
            }
        });
    });

    app.put('/washer/:id', (req, res) => {
        // update note by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('washer').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                const coords = { x: req.body.x, y: req.body.y, work: item.work, workers: item.workers };
                db.collection('washer').update(details, coords, (err, item) => {
                    if (err) {
                        res.send({ 'error': 'An error has occured' });
                    } else {
                        res.send(coords);
                    }
                });
            }
        });
    });
};
