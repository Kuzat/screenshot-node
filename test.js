const screenshot = require('./index');

screenshot.saveScreenshot(0, 0, 0, 0, 'test.png', (err) => {
	if (err) console.log(err);
})
