let ws = new WebSocket("ws://127.0.0.1:8080/ws");
let currentID = "";
let chatNumber = 0;

const chats = new Map()
const chatContainer = document.getElementById("chat-container")
const clientContainer = document.getElementById("client-container")

ws.onopen = function() {
    console.log("OPEN");
}

ws.onclose = function() {
    console.log("CLOSE");
    ws.close()
    ws = null;
}

ws.onerror = function(e) {
    console.log("ERROR: " + e.data);
}

ws.onmessage = function(e) {
    let message = JSON.parse(e.data);
    //console.log("RESPONSE: " + e.data);

    if (message.type === "Login") {
        createClient(message.id);
        return;
    }

    if (message.type === "Logout") {
        chatContainer.removeChild(chats.get(message.id));
        clientContainer.removeChild(document.getElementById("button-" + message.id));
        chats.delete(message.id);
        return;
    }

    document.getElementById(message.clientID).innerHTML += "<p><b>Client</b>: " + message.msg +"</p>";
}

document.getElementById("submit").onclick = function(e) {
    e.preventDefault();
    if (!ws) {
        console.log("ERROR: No websocket connection");
        return false;
    }
    let input = document.getElementById("msg");
    //console.log("SEND: " + input.value);

    ws.send(JSON.stringify({
        techID: currentID,
        msg: input.value
    }));

    document.getElementById(currentID).innerHTML += "<p><b>Vous</b>: " + input.value +"</p>";
    input.value = "";

    return false;
};

window.addEventListener("beforeunload", function (e) {
    ws.close();
});


function createClient(id) {
    chatNumber++;

    let newChat = document.createElement("div");
    newChat.id = id;
    chatContainer.appendChild(newChat);
    chats.set(id, newChat);

    let newClient = document.createElement("button");
    newClient.id = "button-" + id;
    newClient.classList.add("btn", "btn-primary", "mb-3", "ms-auto", "me-5", "d-block")
    newClient.innerHTML = chatNumber.toString();
    newClient.onclick = () => changeChat(id);
    clientContainer.appendChild(newClient);

    if (chats.size === 1) {
        changeChat(id);
    }
}

function changeChat(id) {
    chats.forEach((chat, id) => {
        chat.classList.add("d-none");
        chat.classList.remove("flex-grow-1");
    });

    currentID = id;
    chats.get(currentID).classList.remove("d-none");
    chats.get(currentID).classList.add("flex-grow-1");
}