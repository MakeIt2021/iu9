#!/usr/bin/env node

const fs = require("fs");
const { tokenize } = require('./scanner');

const inputFile = process.argv[2];

const readStream = fs.createReadStream(inputFile, { encoding: 'utf8' });

tokenize(readStream)
    .then(tokens => {
        const dictionary = new Set();
        for (let token of tokens) {
            if (/^[A-Za-z’]+$/.test(token.word)) {
                dictionary.add(token.word.toLowerCase());
            }
        }
    

        const dictionaryArray = Array.from(dictionary).sort();
        fs.writeFile('dictionary.txt', dictionaryArray.join('\n'), 'utf8', () => {});
    })
    .catch(err => {
        console.error('error while processing file');
    });