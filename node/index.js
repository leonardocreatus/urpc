import { exec } from "child_process";
import path from "path";
import util from "util";
import { setTimeout } from "timers/promises";
import fs from "fs/promises";

const execAsync = util.promisify(exec);
const rpcPath = path.resolve("..");

const datagram = 256;

async function* foo() {
  for (let payload = 16; payload <= 1024; payload += 16) {
    yield payload;
  }
}

for await (const payload of foo()) {
  let ss = payload.toString().padEnd(10);
  await setTimeout(1000);
  const clientChield = await execAsync(
    `${rpcPath}/client 192.168.64.8 550 64 ${datagram} ${payload}`
  );
  if (clientChield.stderr) {
    console.log("client", clientChield.stderr);
    process.exit(1);
  }

  const time = clientChield.stdout.trim();

  ss += time.toString().padEnd(10);
  ss += "\n";

  await fs.appendFile("result.txt", ss);
}
