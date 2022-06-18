const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const filesSchema = new Schema({
    fileType: { type: String, required: true },
    fileName: { type: String, required: true },
    user: { type: String, required: true },
    compressedData: { type: String, required: false },
    codes: { type: Array, requiered: false },
    dictionary: { type: Array, required: false },
    tree: { type: Array, requiered: false },
})

const files = mongoose.model('files', filesSchema);

module.exports = files;