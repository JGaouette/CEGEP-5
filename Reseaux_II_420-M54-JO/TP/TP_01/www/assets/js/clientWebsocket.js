ws = new WebSocket("ws://127.0.0.1:8080/clientWs"); // Création du socket
ws.onopen = function(e) {
    console.log("OPEN");
}
ws.onclose = function(e) {
    console.log("CLOSE");
    ws = null; // Fermeture du socket
}

ws.onerror = function(e) {
    console.log("ERROR: " + e.data);
}

let container = document.getElementById("message-container");

ws.onmessage = function(e) {
    let message = JSON.parse(e.data);
    console.log("RESPONSE: " + e.data);

    const p = document.createElement("p");
    const b = document.createElement("b");

    b.innerHTML = message.ID === 0 ? "Technicien" : "Vous";

    p.appendChild(b);

    p.innerHTML += ": " + message.Value;
    container.appendChild(p);
}

document.getElementById("submit").onclick = function(e) {
    e.preventDefault();
    if (!ws) {
        return false;
    }
    let input = document.getElementById("msg");
    console.log("SEND: " + input.value);
    ws.send(JSON.stringify({
        ID: -1,
        Value: input.value
    }));

    input.value = "";

    return false;
};

window.addEventListener("beforeunload", function (e) {
    ws.close();
});