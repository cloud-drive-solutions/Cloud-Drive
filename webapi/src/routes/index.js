const { Router } = require('express');
const router = Router();

//Routes
router.get('/', (req, res) => {
    const data = {
        "Name": "Banano",
        "Description": "q"
    };
    res.json(data);
}); 

router.get('/files', (req, res) => {
    //res.json({"Title": "Hello, world!"});
    res.sendFile('/home/esteban/Descargas/1.pdf');
});

module.exports = router;