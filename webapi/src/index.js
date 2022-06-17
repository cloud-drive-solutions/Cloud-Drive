const express = require('express');
const morgan = require('morgan');
const cors = require('cors');
const app = express();

//Configuration
app.set('port', process.env.PORT || 3000);

//Middle configuration
app.use(express.json());
app.use(morgan('dev'));
app.use(cors());

app.use(require('./routes/index'));
app.use('/info/' , require('./routes/info'));

//Start server
app.listen(app.get('port'), () => {
    console.log('listening on port ' + app.get('port'));
});