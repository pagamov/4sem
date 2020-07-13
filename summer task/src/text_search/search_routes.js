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

    function ov(ts, db) {
        db.collection('text').find( { t: { $in: ts } } , { _id: 0, t: 0, d: 1 }, (err, item) => {
            return new Promise((resolve, reject) => {
                if (err) {
                    reject({ 'error': 'An error has occured' });
                } else {
                    console.log('item')
                    resolve(item.toArray());
                }
            });
        });
    };

    app.get('/search', (req, res, next) => {
        // by not all text
        if (!req.body.ts) {
            next();
        } else {
            var ts = req.body.ts.split(' ');
            db.collection('text').find( { t: { $in: ts } } , { _id: 0, t: 0, d: 1 } ).toArray((err, item) => {
                if (err) {
                    res.send({ 'error': 'An error has occured' });
                } else {
                    async function f (req, item) {
                        var result = [];
                        for (const ite of item) {
                            await result.push([ite._id, ite.t, Overlap(req.body.p, ite.d)]);
                        }
                        return result;
                    };
                    async function o (req, res, item) {
                        var result = await f (req, item);
                        res.send(result);
                    };

                    o(req, res, item);
                }
            });
        }
    });

    app.get('/search', (req, res) => {
        db.collection('text').find().toArray((err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                async function f (req, item) {
                    var result = [];
                    for (const ite of item) {
                        await result.push([ite._id, ite.t, Overlap(req.body.p, ite.d)]);
                    }
                    return result;
                };
                async function o (req, res, item) {
                    var result = await f (req, item);
                    res.send(result);
                };
                o(req, res, item);
            }
        });
    });
};
