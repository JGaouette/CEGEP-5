# UDP

Contrairement à UDP, TCP ne fais pas de validation de réception de paquet. Si un paquet n'est pas reçu, TCP va s'assurer de le renvoyer et de le remettre dans l'ordre lors de la réception. UDP ne fait aucune manipulation du genre.

UDP est donc utile lorsque:

  - La rapidité est plus importante que la fiabilité, par exemple lors d'une requête DNS. S'il y a un problème on peut refaire la requête, en moyenne ça va être plus rapide que TCP.
  - Le paquet suivant va remplacer le paquet manquant. Par exemple dans un vidéo en ligne, s'il manque 1 image dans du 60 FPS on va survivre.

Il faut faire attention en UDP:

  - La réception du paquet n'est pas assurée.
  - L'ordre de réception n'est pas garantie.
  - Si mon serveur est plus rapide que mon client, je vais perdre des paquets.

UDP fonctionne de manière très similaire à TCP. Par contre, comme UDP n'a pas de "handshake" le client doit envoyer un message au serveur afin d'établire une connection.

Exemple de serveur:

```go
func main() {
	listener, err := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()
	buf := make([]byte, 1024)
	for {
		_, clientAddr, err := listener.ReadFrom(buf)
		if err == nil {
			go manageClient(*listener, clientAddr)
		}
	}
}

func manageClient(server net.UDPConn, address net.Addr) {
	for {
		now := []byte(time.Now().Format(time.ANSIC))
		_, err := server.WriteTo(now, address)
		fmt.Println(err)
		time.Sleep(time.Second)
	}
}
```

Exemple de client:

```go
func main() {
	udpServer, _ := net.ResolveUDPAddr("udp", ":8000")
	conn, _ := net.DialUDP("udp", nil, udpServer)
	conn.Write([]byte("connect pls"))
	for {
		var buf []byte = make([]byte, 1024)
		conn.Read(buf)
		fmt.Println(string(buf))
		time.Sleep(time.Second)
	}
}
```