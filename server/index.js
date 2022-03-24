const express = require("express")
const app = express()

const port = 8000

app.get("/",(res,req)=>{
    return req.send("Hello World")
})

app.listen(port,()=>{
    console.log("Server Started")
})