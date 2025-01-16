#!/usr/bin/env node

const fs = require("fs");
const path = require("path");
const dirOnly = process.argv.includes('-d');
const toFile = process.argv.includes('-o');
let outputPath;

if (toFile) {
    outputPath = process.argv[process.argv.indexOf('-o') + 1];
}

let inPath = process.argv[2];

if (inPath === undefined || inPath === '-o' || inPath === '-d') {
    inPath = process.cwd();
    if (!toFile)
        console.log('.');
    else {
        try {
            fs.appendFileSync(outputPath, '.\n');
        } catch (err) {
            console.error(err);
        }
    }
} else {
    if (!toFile)
        console.log(inPath);
    else {
        try {
            fs.appendFileSync(outputPath, `${inPath}\n`);
        } catch (err) {
            console.error(err);
        }
    }
}

function treerer(dirPath, indent = "") {
    let items 
    try {
        items = fs.readdirSync(dirPath);
    } catch (err) {
        console.log('[error opening dir]');
    }

    // оставляем только папки
    if (dirOnly) {
        items = items.filter(item => {
            try {
                return fs.statSync(path.join(dirPath, item)).isDirectory();
            } catch {
                return false;
            }
        });
    }

    const total = items.length;

    for (let i = 0; i < total; i++) {
        let fullPath = `${dirPath}/${items[i]}`;
        let connector = (i === total - 1) ? "└── " : "├── ";
        
        try {
            if (fs.statSync(fullPath).isDirectory()) {
                if (!toFile)
                    console.log(`${indent}${connector}${path.basename(fullPath)}`);
                else {
                    try {
                        fs.appendFileSync(outputPath, `${indent}${connector}${path.basename(fullPath)}\n`);
                    } catch (err) {
                        console.error(err);
                    }
                }
    
                if (i === total - 1) {
                    treerer(fullPath, indent + "    ");
                } else {
                    treerer(fullPath, indent + "│   ");
                }
            } else if (!dirOnly) {
                if (!toFile)
                    console.log(`${indent}${connector}${items[i]}`);
                else {
                    try {
                        fs.appendFileSync(outputPath, `${indent}${connector}${items[i]}\n`);
                    } catch (err) {
                        console.error(err);
                    }
                }
            }
        } catch (err) {
            console.log(`${indent}${connector}${path.basename(fullPath)} [error opening dir]`);
        }
    }
}

treerer(inPath);