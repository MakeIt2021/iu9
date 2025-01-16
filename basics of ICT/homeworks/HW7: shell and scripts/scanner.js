const fs = require("fs");
const readline = require("readline");

function tokenize(input) {
    return new Promise((resolve, reject) => {
        const rl = readline.createInterface({
            input: input,
            crlfDelay: Infinity
        });

        const tokens = [];
        let lineNumber = 0;

        rl.on('line', (line) => {
            lineNumber += 1;
            let columnNumber = 1;

            const regex = /[A-Za-z’]+|[.,!?;:()-]/g;
            let match;
            while ((match = regex.exec(line)) !== null) {
                const word = match[0];
                const start = match.index + 1;
                tokens.push({
                    word: word,
                    line: lineNumber,
                    column: start
                });
            }
        });

        rl.on('close', () => {
            resolve(tokens);
        });
    });
}

module.exports = {
    tokenize
};