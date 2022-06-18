const express = require('express');
const morgan = require('morgan');
const cors = require('cors');
const mongoose = require('mongoose');

require('dotenv').config();

//Configuration
const app = express();
app.set('port', process.env.PORT || 3000);

//Middle configuration
app.use(express.json());
app.use(morgan('dev'));
app.use(cors());

app.use(require('./routes/index'));
app.use('/info/' , require('./routes/info'));

//Connecting to Data Base
const uri = 'mongodb+srv://Sapos_Datos2:DanielSapoHP@cluster0.ryokwe7.mongodb.net/?retryWrites=true';
mongoose.connect(uri);
const connection = mongoose.connection;
connection.once('open', () => {
    console.log('Connected to the Data Base')
})

const userRouter = require('./routes/user');

app.use('/user', userRouter);

//Start server
app.listen(app.get('port'), () => {
    console.log('listening on port ' + app.get('port'));
});