// server.js
const express = require("express");
const http = require("http");
const socketIO = require("socket.io");
const cors = require("cors"); // Import the cors package
const bodyParser = require("body-parser");

const app = express();
const server = http.createServer(app);
const io = socketIO(server, {
  cors: {
    origin: "*", // Replace with the allowed origin URL
    methods: ["GET", "POST"],
  },
});

app.use(cors());
app.use(bodyParser.json());

io.on("connection", (socket) => {
  console.log("A client connected.");

  // Clean up when the client disconnects
  socket.on("disconnect", () => {
    console.log("A client disconnected.");
  });
});

app.post("/sendNotification", (req, res) => {
  // get body param named text
  io.emit("notification", req.body.text); // Emit the message event to all connected clients
  console.log("socket emitted");
  return res.send("Notification sent successfully.");
});

const port = 3001;
server.listen(port, () => {
  console.log(`Server listening on port ${port}`);
});
