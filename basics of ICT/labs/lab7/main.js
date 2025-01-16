#!/usr/bin/env node

const logic = require('./gen_strings');

const amount = parseInt(process.argv[2], 10);
const len = parseInt(process.argv[3], 10);

if (Number.isInteger(amount) && 
    Number.isInteger(len) &&
    amount > 0 && len > 0) {
        logic.gen_strings(amount, len);
} else {
    console.error("usage: main amount length");
}