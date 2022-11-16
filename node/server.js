import fs from "fs/promises";
import { setTimeout } from "timers/promises";
import axios from "axios";
import express from "express";
import { spawn } from "child_process";
import path from "path";
import kill from "kill-port";

const rpcPath = path.resolve("..");
// const datagram = 512;
// const payloadSize = 1024;
// const timeout = 1;
// const window = 16;
// const ip = "192.168.64.9";

const app = express();
app.use(express.json());
let server;

app.post("/start", async (req, res) => {
  const { ip, timeout, window, datagram, coding } = req.body;
  console.log("start", ip, timeout, window, datagram, coding);
  server = spawn(`${rpcPath}/server`, [
    ip,
    timeout,
    window,
    datagram,
    coding ? "1" : "0",
  ]);
  server.stdout.on("data", (data) => {
    console.log(data.toString());
  });
  res.send("ok");
});

app.post("/stop", async (req, res) => {
  server.kill();
  res.send();
});

app.listen(4000, "0.0.0.0", () => {
  console.log("Server started on port 4000");
});
