function getRandomChar() {
    return String.fromCharCode(Math.random() * (126 - 33) + 33);
}

function gen_string(len) {
    let res = "";
    for (let i = 0; i < len; i++) {
        res += getRandomChar();
    }

    return res;
}

function gen_strings(n, len) {
    for (let i = 0; i < n; i++) {
        console.log(gen_string(len));
    }
}

module.exports = { gen_strings }