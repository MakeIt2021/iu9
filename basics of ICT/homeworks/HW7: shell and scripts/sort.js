#!/usr/bin/env node

const readline = require("readline");
const fs = require("fs");

const args = process.argv.slice(2);
const keys = args.filter(arg => arg.startsWith('-') && !arg.startsWith('-k')); // Исключаем -k для отдельной обработки
const fileArgs = args.filter(arg => arg[0] !== '-');

function parseKFlag(args) {
    const kFlags = args.filter(arg => arg.startsWith('-k'));
    if (kFlags.length === 0) {
        return null;
    }

    const kFlag = kFlags[0];
    const match = kFlag.match(/^-k(\d+)(?:,(\d+))?$/); // захват числа m и n регулярным выражением
    if (match) {
        const m = parseInt(match[1], 10);
        const n = match[2] ? parseInt(match[2], 10) : null;
        return { m, n };
    } else {
        console.error("invalid syntax");
        return null;
    }
}

const kFlag = parseKFlag(args);

function extractKey(line) {
    if (!kFlag) {
        return line;
    }
    const { m, n } = kFlag;
    const fields = line.split(/\s+/); // деление по пробелам
    const start = m - 1;
    const end = n ? n : fields.length;
    const keyFields = fields.slice(start, end).join(' ');
    return keyFields;
}

function compareLines(a, b) {
    let keyA = extractKey(a);
    let keyB = extractKey(b);

    if (keys.includes('-n')) {
        // пытаемся всё преобразовать в float (при неуспехе возвращается NaN)
        const numA = parseFloat(keyA);
        const numB = parseFloat(keyB);

        // если числа
        if (!isNaN(numA) && !isNaN(numB)) {
            return numA - numB;
        }
    }

    return keyA.localeCompare(keyB); // case-insensitive
}

let lines = [];

function readFile(filePath, callback) {
    const rlFile = readline.createInterface({
        input: fs.createReadStream(filePath),
        crlfDelay: Infinity
    });

    rlFile.on('error', () => {
        console.error('invalid file name');
    });

    rlFile.on('line', (line) => {
        lines.push(line);
    });

    rlFile.on('close', () => {
        callback();
    });
}

if (fileArgs.length > 0) {
    let index = 0;

    function readNext() {
        if (index < fileArgs.length) {
            readFile(fileArgs[index], () => {
                index++;
                readNext();
            });
        } else {
            sortAndOutput();
        }
    }

    readNext();
} else {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        terminal: false,
    });

    rl.on('line', (line) => {
        lines.push(line);
    });

    rl.on('close', () => {    
        sortAndOutput();
    });
}

function sortAndOutput() {
    let res;

    if (kFlag || keys.includes('-n') || keys.includes('-i')) {
        res = lines.sort(compareLines);
    } else {
        res = lines.sort();
    }

    if (keys.includes('-r')) {
        res.reverse();   
    }

    if (keys.includes('-u')) {
        res = Array.from(new Set(res));
    }

    for (let line of res) {
        console.log(line);
    }    
}