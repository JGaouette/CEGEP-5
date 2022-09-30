ws = new WebSocket("/ws"); // Création du socket
ws.onopen = function() {
    print("OPEN");
}
ws.onclose = function() {
    print("CLOSE");
    ws = null; // Fermeture du socket
}
ws.onmessage = function(e) {
    print("RESPONSE: " + e.data); // Lorsqu'on reçoit un message
}
