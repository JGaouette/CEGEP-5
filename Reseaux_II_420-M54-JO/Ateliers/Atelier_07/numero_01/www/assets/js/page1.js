/*
let ws = new WebSocket("ws://localhost:8080/ws");

ws.onmessage = event => {
    console.log(event.data);
};
*/

console.log("Hello from script.js");

document.querySelector("button").addEventListener("click", (event) => {
    event.preventDefault()

    console.log("it is working");

    let nb1 = document.getElementById("nb1").value;
    let nb2 = document.getElementById("nb2").value;
    let sum = parseInt(nb1) + parseInt(nb2);

    sessionStorage.setItem("sum", sum);
    window.location.href = "./result";

});