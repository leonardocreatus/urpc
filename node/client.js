import { setTimeout } from "timers/promises";
import express from "express";
import util from "util";
import { exec, spawn } from "child_process";
import kill from "kill-port";
import fs from "fs/promises";
// const kill = require("kill-port");
import path from "path";
const execAsync = util.promisify(exec);
const rpcPath = path.resolve("..");

const datagram = 512;
const payloadSize = 1024;
const timeout = 1;
const window = 16;
const ip = "192.168.64.10";

const app = express();
app.use(express.json());
/*
const callback = async (payload) => {
  const cmd = `${rpcPath}/client ${ip} ${timeout} ${window} ${datagram} ${payload}`;
  const promise = new Promise((resolve, reject) => {
    const p1 = new Promise((resolve, reject) => {
      const clientChield = spawn(cmd, {
        shell: true,
        //   stdio: "inherit",
      });

      clientChield.on("close", (code) => {
        clientChield.kill();
        if (code === 0) {
          resolve(true);
        } else {
          reject();
        }
      });

      clientChield.stdout.on("data", (data) => {
        console.log("data", data.toString());
      });

      clientChield.stderr.on("data", (data) => {
        clientChield.kill();
        console.log("data", data.toString());
        reject();
      });
    });

    const p2 = new Promise((resolve, reject) => {
      setTimeout(1000).then(() => {
        // resolve(throw Error());
        reject();
      });
    });

    return Promise.race([p1, p2]).then((res) => {
      try {
        resolve(res);
      } catch (e) {
        reject();
      }
    });
  });
  return promise;
};
*/

let clientChield = null;
app.post("/", async (req, res) => {
  try {
    const payload = req.body.data.payload;
    console.log("payload", payload);
    const promise = new Promise((resolve, reject) => {
      const cmd = `${rpcPath}/client ${ip} ${timeout} ${window} ${datagram} ${payload}`;
      clientChield = spawn(cmd, {
        shell: true,
        //   stdio: "inherit",
      });

      clientChield.on("close", (code) => {
        clientChield.kill();
        if (code === 0) {
          resolve(true);
        } else {
          reject();
        }
      });

      clientChield.stdout.on("data", async (data) => {
        const str = data.toString();
        if (Number.isInteger(parseInt(str))) {
          console.log("Integer", str);
          const msg = `${payload.toString().padEnd(10, " ")} ${str
            .toString()
            .padEnd(10, " ")}\n`;
          await fs.appendFile("log.dat", msg);
          clientChield.kill();
          resolve(parseInt(str));
        } else {
          if (str.includes("bind")) {
            kill(3001, "udp").then(console.log).catch(console.log);
          }
          console.log("data", str);
          clientChield.kill();
          reject();
        }
        // console.log(`${payload} data: `, data.toString());
        // if()
      });

      clientChield.stderr.on("data", (data) => {
        clientChield.kill();
        console.log(`${payload} error: `, data.toString());
        reject("error");
      });
    });

    const timeoutPromise = new Promise((resolve, reject) => {
      setTimeout(5000).then(() => {
        console.log("timeout");
        clientChield.kill();
        reject("timeout");
      });
    });
    const result = await Promise.race([promise, timeoutPromise]);
    console.log("res", result);
    if (result) {
      res.status(200).send({
        payload: payload + payloadSize,
      });
    } else {
      res.status(200).send({
        payload,
      });
    }
  } catch (error) {
    console.log("catch error", error);
    res.status(400).send(error);
  }
});

app.listen(4000, () => {
  console.log("server started");
});
