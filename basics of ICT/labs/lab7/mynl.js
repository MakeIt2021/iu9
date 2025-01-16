#!/usr/bin/env node

const fs = require('fs');

function numStrings(file, startFrom) {
    if (typeof file === "string") {
        try {
            const data = fs.readFileSync(file);

            for (let st of data.toString().split("\n")) {
                if (st.length != 0) {
                    console.log(`  ${(startFrom++).toString()}\t${st}`);
                } else {
                    console.log();
                }
            }
        } catch (err) {
            console.error("usage: mynl path_to_file");
        }
        
    } else {
        console.error("usage: mynl path_to_file");
    }

    return startFrom;
}

const input = process.argv.slice(2);
const amount = input.length;

let prev = 1;
for (let i = 0; i < amount; i++) {
    console.log(input[i]);
    prev = numStrings(input[i], prev);
}