const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const app = express();

// Serve client-side code
app.use(express.static('public'));

// Create server
const server = http.createServer(app);

// Create WebSocket server
const wss = new WebSocket.Server({ server });

// Handle WebSocket connection
wss.on('connection', (ws) => {
  console.log('WebSocket connected');

  // Send message to client
  ws.send('WebSocket connection established');

  // Handle WebSocket message
  ws.on('message', (message) => {
    console.log(`Received message: ${message}`);
  });
});

// Expose endpoint
app.get('/send-notification', (req, res) => {
  // Send notification to browser
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send('notification');
    }
  });
  res.send('Notification sent!');
});

// Start server
server.listen(3000, () => {
  console.log('Server started on port 3000');
});
