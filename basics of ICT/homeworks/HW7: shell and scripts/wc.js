#!/usr/bin/env node

const fs = require("fs");
const readline = require("readline");

const args = process.argv.slice(2);
const keys = args.filter(arg => arg.startsWith('-'));
const files = args.filter(arg => !arg.startsWith('-'));

const counters = {
    lines: keys.includes('-l'),
    words: keys.includes('-w'),
    bytes: keys.includes('-c'),
    characters: keys.includes('-m'),

    linesCount: 0,
    bytesCount: 0,
    wordsCount: 0,
    charsCount: 0,

    totalLines: 0,
    totalBytes: 0,
    totalWords: 0,
    totalChars: 0,
};

function processLine(line) {
    if (counters.lines)
        counters.linesCount++;
    if (counters.bytes)
        counters.bytesCount += Buffer.byteLength(line, 'utf8') + 1; // ещё перевод строки
    if (counters.characters)
        counters.charsCount += Array.from(line).length + 1; // ещё перевод строки
    if (counters.words) {
        const words = line.trim().split(/\s+/) // бьём по пробельным символам
        if (words[0])
            counters.wordsCount += Array.from(words).length;
    }
}

function readFile(filePath, callback) {
    const readStream = fs.createReadStream(filePath, { encoding: 'utf8' });
    const rlFile = readline.createInterface({
        input: readStream,
        crlfDelay: Infinity
    });

    readStream.on('error', () => {
        console.error('invalid file name');
        callback();
    });

    rlFile.on('line', (line) => {
        processLine(line);
    });

    rlFile.on('close', () => {
        callback();
    });
}

function readStdin(callback) {
    const rl = readline.createInterface({
        input: process.stdin,
        crlfDelay: Infinity
    });

    rl.on('line', (line) => {
        processLine(line);
    });

    rl.on('close', () => {
        callback();
    });
}

function processFiles(fileList, done) {
    let index = 0;

    function next() {
        if (index < fileList.length) {
            readFile(fileList[index], () => {
                done(fileList[index]);
                index++;
                next();
            });
        } else {
            done();
        }
    }

    next();
}

function printResults(filename) {
    let results = [];

    if (counters.lines) {
        results.push(counters.linesCount);
    }
    if (counters.bytes) {
        results.push(counters.bytesCount);
    }
    if (counters.characters) {
        results.push(counters.charsCount);
    }
    if (counters.words) {
        results.push(counters.wordsCount);
    }

    counters.totalLines += counters.linesCount;
    counters.totalBytes += counters.bytesCount;
    counters.totalChars += counters.charsCount;
    counters.totalWords += counters.wordsCount;

    counters.linesCount = 0;
    counters.bytesCount = 0;
    counters.charsCount = 0;
    counters.wordsCount = 0;
    
    if (filename === undefined) {
        results = []
        if (counters.lines) {
            results.push(counters.totalLines);
        }
        if (counters.bytes) {
            results.push(counters.totalBytes);
        }
        if (counters.characters) {
            results.push(counters.totalChars);
        }
        if (counters.words) {
            results.push(counters.totalWords);
        }
        console.log(results.join(' '), "total");
    }
    else {
        console.log(results.join(' '), filename);
    }
}

if (files.length > 0) {
    processFiles(files, printResults);
} else {
    readStdin(printResults);
}