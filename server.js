const express = require("express");
const path = require("path");

const app = express();
app.use(express.static(path.join(__dirname, "src")));
app.listen(3000);
