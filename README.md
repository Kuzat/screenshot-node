# screenshot-node
---
Takes a screenshot of selected area and saves it to disk.

# LINUX VERSION ONLY. MAC PLANNED FOR VERSION 1.1.0 AND WINDOWS FOR 1.2.0

## Instalation
```sh
$ npm install screenshot-node
```
# Methods
---
call the module
```javascript
var screenshot = require('screenshot-node');
```
### screenshot.saveScreenshot(x, y, width, height, path, callback)

#### x, y
##### Must be whole numbers.
The x and y coordinates for the top left corner of the picture.

#### width, height
##### Must be whole numbers.
The width and height of the screenshot in pixels.

#### path
##### Must be a string
The path including name of the file you want the screenshot to be saved as.

#### callback(err)
A string with error message. Null if there are no error.

#### example
Takes a screenshot from top left corner that have a width and height of 100. Saves it in the current directory name "image.png".
```javascript
screenshot.saveScreenshot(0, 0, 100, 100, "image.png", (err) => {
    if(err) console.log(err);
}
```
# INFO
At the moment this is only working on linux and only tested on ubuntu 16.04
