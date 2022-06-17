const { Router } = require('express');
const router = Router();

const example = require('../example.json');

router.get('/', (req, res) => {
    res.json(example);
});

router.post('/', (req, res) => {

    // Inserción a la base de datos
    const {name, age} = req.body;
    if (name && age) {
        const id = example.length + 1;

        const newData = {...req.body, id};

        console.log(newData);

        example.push(newData);

        res.json(example);
    } else {
        res.send({error: 'Invalid data'});
    }
})

module.exports = router;