import fs from "fs/promises";
import { setTimeout } from "timers/promises";
import axios from "axios";
import express from "express";
import { spawn } from "child_process";
import path from "path";
import kill from "kill-port";

console.log("start");

// const execAsync = util.promisify(exec);
const rpcPath = path.resolve("..");
const datagram = 512;
const payloadSize = 1024;
const timeout = 1;
const window = 16;
const ip = "192.168.64.9";

// const app = express();
// app.use(express.json());
let serverChield = null;

console.log("Hello");

const callback = async (payload) => {
  console.log("callback", payload);
  if (payload > 1024 * 32) process.exit(0);
  await setTimeout(10000);

  try {
    const cmd = `${rpcPath}/server ${ip} ${timeout} ${window} ${datagram}`;

    serverChield = spawn(cmd, {
      shell: true,
    });

    const res = await axios.post(`http://${ip}:4000`, {
      data: {
        payload,
      },
    });

    serverChield.stderr.on("data", (data) => {
      console.log("stderr", data.toString());
    });

    serverChield.stdout.on("data", (data) => {
      console.log("stdout", data.toString());
    });

    serverChield.kill();
    if (res.status === 200 && res.data.payload > 0) {
      await callback(res.data.payload);
    }
  } catch (error) {
    serverChield.kill();
    kill(3000, "udp").then(console.log).catch(console.log);
    console.log("catch", error.message);
    await setTimeout(10000);
    await callback(payload);
  }
};

await callback(payloadSize);

// let payload = 1024;
// while (true) {
//   const cmd = `${rpcPath}/server ${ip} ${timeout} ${window} ${datagram}`;

//   const serverChield = spawn(cmd, {
//     shell: true,
//   });

//   const res = await axios.post(`http://${ip}:4000`, {
//     data: {
//       payload,
//     },
//   });

//   serverChield.kill();
//   if (res.status === 200 && res.data.payload > 0) {
//     payload = res.data.payload;
//   } else if (res.status === 200 && res.data.payload === 0) {
//     break;
//   }

//   serverChield.stderr.on("data", (data) => {
//     console.log("stderr", data.toString());
//   });
// }
