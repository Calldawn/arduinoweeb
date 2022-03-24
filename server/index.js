require("dotenv").config()
const express = require("express")
const linebot = require("linebot")
const bodyParser = require("body-parser")
const app = express()
const port = 8000

const bot = linebot({
    channelId: process.env.LINE_BOT_ID,
    channelSecret: process.env.LINE_BOT_SECRET,
    channelAccessToken: process.env.LINE_BOT_ACCESS_TOKEN
})

const linebotParser = bot.parser()

app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json())

/* Testing */
app.post("/broadcast", (req, res) => {
    try {
        bot.broadcast(req.body.message)
        return res.sendStatus(200).send("Message sent")
    }catch(err){
        return res.sendStatus(403).send(`Error: ${err}`)
    }
})

app.listen(port, () => {
    console.log("Server Started")
})


bot.on("message",event=>{
    const message = event.message.text;
    console.log(`Recieved: ${message}`)
    try{
        event.reply(`Hello, Nice to meet you.`)
        console.log("message replied")
    }catch(err){
        console.log("message reply failed")
    }
})