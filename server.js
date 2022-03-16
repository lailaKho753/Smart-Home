const express = require('express')
const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://10.33.109.37')
const app = express()

app.use(express.json())

app.get('/', (req, res) => {
    res.send('m-gateway')
})

app.post('/endpoint',(req, res) => {
    var topic = req.body.topic
    var message = req.body.message
    client.publish(topic, message)
    res.send(topic + " " + message)
})

app.listen(3000, () => {
    console.log('m-gateway running on port 3000')
})