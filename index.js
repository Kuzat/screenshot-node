const addon = require('./build/Release/screenshot');
const fs = require('fs');

module.exports.saveScreenshot = (x, y, width, heigth, path, callback) => {
    addon(x, y, width, heigth, path, (msg) => {
        callback(msg)
    });
};
