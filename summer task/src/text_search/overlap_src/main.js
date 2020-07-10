module.exports = function (pattern, text) {
    return text.toLowerCase().includes(pattern.toLowerCase());
};
