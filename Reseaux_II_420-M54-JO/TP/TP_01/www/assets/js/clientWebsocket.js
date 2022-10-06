ws = new WebSocket("ws://127.0.0.1:8080/clientWs"); // Création du socket
ws.onopen = function(e) {
    console.log("OPEN");
}
ws.onclose = function(e) {
    console.log("CLOSE");
    ws = null; // Fermeture du socket
}
ws.onmessage = function(e) {
    console.log("RESPONSE: " + e.data); // Lorsqu'on reçoit un message
}
ws.onerror = function(e) {
    console.log("ERROR: " + e.data);
}

document.getElementById("submit").onclick = function(e) {
    e.preventDefault();
    if (!ws) {
        return false;
    }
    let input = document.getElementById("msg").value;
    console.log("SEND: " + input);
    ws.send(input.value); // Envoi d'un message
    return false;
};