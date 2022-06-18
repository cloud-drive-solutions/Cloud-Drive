const router = require('express').Router();
let user = require('../models/files.model');

router.route('/').get((req, res) => {
    files.find()
    .then(files => res.json(files))
    .catch(err => res.status(400).json('Error: ' + err));
});

router.route('/add').post((req, res) => {
    const fyleType = req.body.fyleType;
    const fyleName = req.body.fyleName;
    const user = req.body.user;

    const newUser = new user({
        username, 
        password,
    });

    newUser.save()
    .then(() => res.json('New File Uploaded'))
    .catch(err => res.status(400).json('Error: ' + err));
});

module.exports = router;
