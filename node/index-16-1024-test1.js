import { exec } from "child_process";
import path from "path";
import util from "util";
import { setTimeout } from "timers/promises";
import fs from "fs/promises";

const execAsync = util.promisify(exec);
const rpcPath = path.resolve("..");

for (let payload = 16; payload <= 1024; payload += 16) {
  let ss = payload.toString().padEnd(10);
  let sizeSs = payload.toString().padEnd(10);
  let lastSize = 0;
  for (let datagram = 256; datagram <= 4 * 1024; datagram += 256) {
    await setTimeout(100);
    await (async () => {
      const serverChield = exec(
        `${rpcPath}/server ${datagram}`,
        (error, stdout, stderr) => {
          if (error) {
            console.log("server", error);
          }
        }
      );
      await setTimeout(300);
    })();

    const clientChield = await execAsync(
      `${rpcPath}/client ${datagram} ${payload}`
    );
    if (clientChield.stderr) {
      console.log("client", clientChield.stderr);
    }
    const result = clientChield.stdout.split(" ");

    const bytes = Number(result[0]);
    if (bytes != lastSize) {
      lastSize = bytes;
      sizeSs += bytes.toString().padEnd(10);
    }
    const time = Number(result[1]);

    ss += time.toString().padEnd(10);
  }
  ss += "\n";
  sizeSs += "\n";
  await fs.appendFile("result.txt", ss);
  await fs.appendFile("sizes.txt", sizeSs);
}
