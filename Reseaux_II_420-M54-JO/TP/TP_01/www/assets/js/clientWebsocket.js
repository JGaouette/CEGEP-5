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
    alert(JSON.stringify(e.data));

    let message = JSON.parse(e.data);
    //console.log("RESPONSE: " + toString(message)); // Lorsqu'on reçoit un message

    var p = document.createElement("p");
    var b = document.createElement("b");

    b.innerHTML = message.fromTech ? "Technicien" : "Client";

    p.appendChild(b);

    p.innerHTML += ": " + message.value;
    container.appendChild(p);
}

document.getElementById("submit").onclick = function(e) {
    e.preventDefault();
    if (!ws) {
        return false;
    }
    let input = document.getElementById("msg").value;
    console.log("SEND: " + input);
    //ws.send(input);// Envoi d'un message
    ws.send(JSON.stringify({
        fromTech: false,
        value: input
    }));

    return false;
};

window.addEventListener("beforeunload", function (e) {
    ws.close();
});