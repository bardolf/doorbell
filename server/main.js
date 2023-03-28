const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const app = express();

// Constants
const PORT = 3000;
const HOST = '0.0.0.0';

app.use(express.static('public'));

const server = http.createServer(app);
const wss = new WebSocket.Server({port: 3010 });

// Handle WebSocket connection
wss.on('connection', (ws) => {
    console.log('WebSocket connected');
    ws.send('WebSocket connection established');
    ws.on('message', (message) => {
        console.log(`Received message: ${message}`);
    });
});


app.get('/send-notification', (req, res) => {
    wss.clients.forEach((client) => {
        if (client.readyState === WebSocket.OPEN) {
            client.send('notification');
        }
    });
    res.send('Notification sent!');
});

app.listen(PORT, HOST, () => {
    console.log(`Running on http://${HOST}:${PORT}`);
});