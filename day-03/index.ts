/*
 * Day 3 of advent of code
 *
 * bun index.ts
 * */

const re = RegExp(/mul\((?<a>[0-9]{1,3}),(?<b>[0-9]{1,3})\)/g);

const sample_input =
  "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

const input_data = await Bun.file("input.txt").text();

let total = 0;
for (let match of input_data.matchAll(re)) {
  if (!match.groups) continue;

  const a = parseInt(match.groups["a"]);
  const b = parseInt(match.groups["b"]);
  const r = a * b;
  console.log(match.values().next().value, "\t=", r);

  total += r;
}

console.log("Result \t\t=", total);

export {};
