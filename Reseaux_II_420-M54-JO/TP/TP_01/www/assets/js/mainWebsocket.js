let ws = new WebSocket("ws://127.0.0.1:8080/ws"); // Création du socket

ws.onopen = function() {
    console.log("OPEN");
}

ws.onmessage = function(e) {
    console.log("RESPONSE: " + e.data); // Lorsqu'on reçoit un message
}

ws.onclose = function() {
    console.log("CLOSE");
    ws = null; // Fermeture du socket
}
