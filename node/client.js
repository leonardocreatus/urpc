import express from "express";
import util from "util";
import { exec, spawn } from "child_process";
import kill from "kill-port";
import fs from "fs/promises";
import path from "path";
import axios from "axios";
const execAsync = util.promisify(exec);
const rpcPath = path.resolve("..");

const datagramSize = 256;
const maxDatagram = 256 * 8;

const size = 1024;
const maxSize = 64 * size;

const timeout = 1;
const window = 16;
const coding = false;

const loss = 24;

const ip = "10.0.1.20";
const thisIp = "10.0.0.20";

/*
1. Fazer requisição para executar o servidor
2. Executar o cliente
3. Fazer requisição para finalizar o servidor
4. Finalizar o cliente
5. Somar payload, voltar ao estado 1 
*/

const obj = {};

const main = async (payload, datagram) => {
  console.log(payload, datagram);
  await axios.post(`http://${ip}:4000/start`, {
    ip: thisIp,
    datagram,
    timeout,
    window,
    coding,
  });

  const client = spawn(`${rpcPath}/client`, [
    ip,
    timeout,
    window,
    datagram,
    payload,
    coding ? "1" : "0",
  ]);

  const stdout = await Promise.race([
    new Promise((resolve) => {
      client.stdout.on("data", (data) => {
        resolve(data.toString());
      });
    }),
    new Promise((resolve) => {
      setTimeout(() => {
        resolve("-1");
      }, 5000);
    }),
  ]);

  client.kill();

  if (stdout != "-1") {
    console.log(payload, datagram, stdout);
    obj[payload] = {
      ...obj[payload],
      [datagram]: stdout,
    };
    if (payload < maxSize) {
      payload += size;
    } else if (datagram == maxDatagram) {
      return;
    } else {
      payload = size;
      datagram += datagramSize;
    }
  } else {
    console.log("timeout");
  }

  await axios.post(`http://${ip}:4000/stop`);
  await main(payload, datagram);
};

await main(size, datagramSize);
/*
{
  "16": {
    "256": "0.000000",
    "512": "0.000000",
    "768": "0.000000",
    "1024": "0.000000",
  },
  "32": {
    "256": "0.000000",
    "512": "0.000000",
    "768": "0.000000",
    "1024": "0.000000",
  }
}
*/

for (let i in obj) {
  console.log(i, obj[i]);
  const v256 = obj[i][256];
  const v512 = obj[i][512];
  const v768 = obj[i][768];
  const v1024 = obj[i][1024];
  const v1280 = obj[i][1280];
  const v1536 = obj[i][1536];
  const v1792 = obj[i][1792];
  const v2048 = obj[i][2048];

  const ss = `${i.toString().padEnd(10)} ${v256.toString().padEnd(10)} ${v512
    .toString()
    .padEnd(10)} ${v768.toString().padEnd(10)} ${v1024
    .toString()
    .padEnd(10)} ${v1280.toString().padEnd(10)} ${v1536
    .toString()
    .padEnd(10)} ${v1792.toString().padEnd(10)} ${v2048
    .toString()
    .padEnd(10)}\n`;

  fs.appendFile(
    `result/without_coding_${timeout}_${window}_${size}-${maxSize}.dat`,
    ss
  );
}

// const keys = Object.keys(obj).sort((a, b) => parseInt(a) - parseInt(b));
// console.log(keys);
// for (const i of keys) {
//   const ss = `${i.toString().padEnd(10)} ${obj[i][datagramSize]}\n`;
//   await fs.appendFile(
//     // `result/loss_${loss}%_${timeout}ms_${window}_${datagramSize}_${size}-${maxSize}.dat`,
//     `result/${
//       coding ? "with" : "without"
//     }_coding_${timeout}ms_${window}_${datagramSize}_${size}-${maxSize}.dat`,
//     ss
//   );
// }
