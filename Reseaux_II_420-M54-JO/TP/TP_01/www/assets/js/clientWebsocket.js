let ws = new WebSocket("ws://127.0.0.1:8080/ws");
const container = document.getElementById("message-container");
let ID = "";

ws.onopen = function() {
    console.log("OPEN");
}

ws.onclose = function() {
    console.log("CLOSE");
    ws.close()
    ws = null;
}

ws.onerror = function(e) {
    //console.log("ERROR: " + e.data);
    window.location.replace("http://127.0.0.1:8080/404");
}

ws.onmessage = function(e) {
    let message = JSON.parse(e.data);
    console.log("RESPONSE: " + e.data);

    if (message.type === "Login") {
        ID = message.id;
        return;
    }

    if (ID === "") {
        error()
        return;
    }

    container.innerHTML += "<p><b>Technicien</b>: " + message.msg +"</p>";
}

document.getElementById("submit").onclick = function(e) {
    e.preventDefault();
    if (!ws) {
        console.log("ERROR: No websocket connection");
        return false;
    }
    let input = document.getElementById("msg");
    console.log("SEND: " + input.value);

    ws.send(JSON.stringify({
        clientID: ID,
        msg: input.value
    }));

    container.innerHTML += "<p><b>Vous</b>: " + input.value +"</p>";
    input.value = "";
    return false;
};

window.addEventListener("beforeunload", function (e) {
    ws.close();
});

function error() {
    window.location.replace("http://127.0.0.1:8080/404");
    /*
    document.getElementById("submit").disabled = true;
    document.getElementById("msg").disabled = true;
     */
}
