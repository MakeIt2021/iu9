#!/usr/bin/env node

const fs = require("fs");
const { tokenize } = require("./scanner");

const args = process.argv.slice(2);

if (args.length !== 2) {
    console.error('Usage: speller.js <dictionary-file> <text-file>');
    process.exit(1);
}


const dictionaryFile = args[0];
const textFile = args[1];

let dictionary;
try {
    const dictContent = fs.readFileSync(dictionaryFile, 'utf8');
    const dictWords = dictContent.split(/\r?\n/).map(word => word.toLowerCase());
    dictionary = new Set(dictWords);
} catch {
    console.error("couldn't read dictionary file");
    process.exit(1);
}


const readStream = fs.createReadStream(textFile, { encoding: 'utf8'});

tokenize(readStream)
    .then(tokens => {
        const misspellings = [];
        
        for (let token of tokens) {
            if (/^[A-Za-z’]+$/.test(token.word)) {
                if (!dictionary.has(token.word.toLowerCase())) {
                    misspellings.push({
                        line: token.line,
                        column: token.column,
                        word: token.word
                    });
                }
            }
        }

        for (let misspelling of misspellings) {
            console.log(`${misspelling.line}, ${misspelling.column}    ${misspelling.word}`);
        }
    })
    .catch(err => {
        console.error("couldn't process text file");
        process.exit(1);
    });