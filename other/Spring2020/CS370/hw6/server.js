const express = require("express");

const app = express();

app.get('/', (req, res)=> res.send("Hello a"));

app.listen(3000, () => console.log("Listening on 3000 **Make sure this is container or localPort"));