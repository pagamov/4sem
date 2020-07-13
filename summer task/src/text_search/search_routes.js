var ObjectID = require('mongodb').ObjectID; // for new ObjectID(id);
var Overlap = require('./overlap_src/main')
var Shingl = require('./overlap_src/shingl')

module.exports = function (app, db) {
    app.get('/search/:id', (req, res, next) => {
        // get text by id
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('text').findOne(details, { _id: 0 }, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occured' });
            } else {
                var re = Shingl(req.body.pattern.toLowerCase(), item.data);
                res.send({ result: re });
            }
        });
    });

    app.get('/search', (req, res, next) => {
        if (!req.body.title) {
            next();
        } else {
            const details = {title: req.body.title};
            db.collection('text').findOne(details, (err, item) => {
                if (err) {
                    res.send({ 'error': 'An error has occured' });
                } else {
                    var re = Shingl(req.body.pattern.toLowerCase(), item.data);
                    res.send({ result: re });
                }
            });
        }
    });

    app.get('/search', (req, res, next) => {
        // by not all text
        if (!req.body.titles) {
            next();
        } else {
            var ts = req.body.titles.split(' ');
            db.collection('text').find( { title: { $in: ts } } , { _id: 0, t: 0, d: 1 } ).toArray((err, item) => {
                if (err) {
                    res.send({ 'error': 'An error has occured' });
                } else {
                    async function f (req, item) {
                        var result = [];
                        for (const ite of item) {
                            await result.push([ite._id, ite.title, Shingl(req.body.pattern.toLowerCase(), ite.data)]);
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
                        await result.push([ite._id, ite.title, Shingl(req.body.pattern.toLowerCase(), ite.data)]);
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
