var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);

module.exports = function(app, db) {
    app.post('/worker/:id', (req, res) => {
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        const new_worker = {name: req.body.name};
        db.collection('washer').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                if (item.workers.includes(new_worker)) {
                    res.send('already at work');
                } else {
                    item.workers.push(new_worker);
                    db.collection('washer').update(details, item);
                    res.send(new_worker);
                }
            }
        });
    });

    app.get('/worker/:id', (req, res) => {
        const details = { '_id': new ObjectID(req.params.id) };
        db.collection('washer').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                if (item.workers)
                    res.send(item.workers);
                else
                    res.send({});
            }
        });
    });

    app.delete('/worker/:id', (req, res) => {
        const id = req.params.id;
        const name = req.body.name;
        const details = { '_id': new ObjectID(id), workers: {name: name} };
        db.collection('washer').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                var index = item.workers.map(function(it) { return it.name; }).indexOf(name);
                if (index > -1)
                    item.workers.splice(index, 1);
                db.collection('washer').update(details, item, (err, item) => {
                    if (err) {
                        res.send({ 'error': 'An error has occured' });
                    } else {
                        res.send('worker ' + name + ' left ' + id + ' washer');
                    }
                });

            }
        });
    });
};
