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
    console.log("SEND: " + input.value);
    ws.send(input.value); // Envoi d'un message
    return false;
};






/*
let ws = new WebSocket("ws://127.0.0.1:8080/ws"); // Création du socket

ws.onopen = function() {
    console.log("OPEN");
}

ws.onmessage = function(e) {
    if (e.data === "online") {
        console.log("ONLINE");
        try{
            document.getElementById("button_offline").classList.add("d-none");
            document.getElementById("button_online").classList.remove("d-none");
        }catch (e){}
    }
    else if (e.data === "offline") {
        console.log("OFFLINE");
        try{
            document.getElementById("button_online").classList.add("d-none");
            document.getElementById("button_offline").classList.remove("d-none");
        } catch (e){}
    }
    console.log("RESPONSE: " + e.data); // Lorsqu'on reçoit un message
}

ws.onclose = function() {
    console.log("CLOSE");
    ws = null; // Fermeture du socket
}

 */


