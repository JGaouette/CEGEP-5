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
