var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);
var Overlap = require('./overlap_src/main')

module.exports = function (app, db) {
    app.get('/search/:id', (req, res, next) => {
        // get text by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('text').findOne(details, { _id: 0 }, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                req.body.t = item.t;
                // app.use('/search');
                res.send({ t: item.t, d: item.d });
            }
        });
    });

    app.get('/search', (req, res, next) => {
        if (!req.body.t) {
            next();
        } else {
            const details = {t: req.body.t};
            db.collection('text').findOne(details, (err, item) => {
                if (err) {
                    res.send({ 'error': 'An error has occured' });
                } else {
                    res.send({ r: Overlap(req.body.p, item.d) });
                }
            });
        }
    });

    app.get('/search', (req, res, next) => {
        // by not all text
        if (!req.body.ts) {
            next();
        } else {
            var ts = req.body.ts.split(' ');
            // console.log(ts);
            var result = new Map();

            ts.forEach((title, i) => {
                db.collection('text').findOne( {t: title}, { _id: 0, t: 0, d: 1 }, (err, item) => {
                    if (err) {
                        res.send({ 'error': 'An error has occured' });
                    } else {
                        // console.log(title + ' 2nd midd ware ' + item.d);
                        // console.log(item);
                        if (item) {
                            console.log(item);
                            // console.log(req.body.p);
                            // console.log(item.d);
                            console.log(Overlap(req.body.p, item.d));
                            result.set(title, Overlap(req.body.p, item.d));
                        }
                    }
                });
            });

            console.log('res ' + result);
            res.send({r: result});
            // res.send('done 2');
        }
    });

    app.get('/search', (req, res) => {
        // by all text
        console.log('2nd midd ware');
        res.send('done 2');
    });
};
