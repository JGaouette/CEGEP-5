# Atelier 12 - UDP

## Numéro 1

Faites un client-serveur UDP, le serveur envoie l'heure à chaque seconde, le client l'affiche dans la console.

Avec Wireshark, regardez comment circule UDP et comment il gère la fermeture de connexion du client.

## Numéro 2

Faites une histoire (ou une animation ascii) qui s'affiche en boucle dans la console. Par exemple (chaque ligne est 1 frame):

```
(ᴗ˳ᴗ)
(ᴗ˳ᴗ) z
(ᴗ˳ᴗ) zZ
(ᴗ˳ᴗ) zZᶻ
(ᴗ˳ᴗ) zZ
(ᴗ˳ᴗ) z
(ᴗ˳ᴗ)
```

On affiche seulement l'animation dans la console, utilisez GoTerm: https://github.com/buger/goterm.

## Numéro 3

En préparation pour le TP2, prenez un des numéros précédents et implémentez une détection de déconnexion:

- Ajoutez un heartbeat: À toutes les X secondes le client envoie un message au serveur pour tenir la connexion ouverte. Si le serveur n'a pas de heartbeat après X*3 secondes on ferme la connexion.
- Si le client s'attends à avoir des messages à toutes les secondes, après 5 secondes on prétends que la connexion est perdu et on ferme notre client.
- Ajoutez un message de fermeture pour le client et le serveur, si un des côtés ferme, on avertis l'autre avec un message spécial