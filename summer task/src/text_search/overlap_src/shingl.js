function skolar (arr_1, arr_2) {
    var r = 0;
    // console.log(arr_2);
    for (var [key, val] of arr_1) {
        if (arr_2.has(key)) {
            console.log(key, val, arr_2.get(key));
            r += (val * arr_2.get(key));
        }
    }
    return Math.abs(r);
};

function distance (arr) {
    var res = 0;
    for (var [key, val] of arr) {
        res += Math.pow(val, 2)
    }
    return Math.sqrt(res);
};

module.exports = function (patt, text) {
    const patt_spl = patt.split(' ');
    const text_spl = text.split(' ');
    var patt_bag = new Map();
    var text_bag = new Map();
    for (t of patt_spl) {
        if (patt_bag.has(t)) {
            patt_bag[t] += 1;
        } else {
            patt_bag.set(t, 1);
        }
    }
    for (p of text_spl) {
        if (text_bag.has(t)) {
            text_bag[p] += 1;
        } else {
            text_bag.set(p, 1);
        }
    }
    var top =  skolar(patt_bag, text_bag);
    var b_1 =  distance(patt_bag);
    var b_2 =  distance(text_bag);
    return top / (b_1 * b_2);
};
