const screenshot = require('./index');

screenshot.saveScreenshot(0, 0, 400, 400, 'test.png', (err) => {
    if (err) console.log(err);
})
