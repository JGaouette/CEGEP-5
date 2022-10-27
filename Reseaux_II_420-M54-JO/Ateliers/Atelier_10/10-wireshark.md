# Atelier 10

## Numéro 1

Installez Wireshark et écoutez sur le réseau local sur votre port habituel Go.

Créez un client-serveur TCP en Go. Placez le KeepAlive avec un délais de 5 secondes. Le client demande un int à l'utilisateur, l'envoie au serveur qui retourne le double et le client affiche le résultat. Le tout dans des boucles infinies.

Analysez ce qui ce passe sur Wireshark lors d'un échange et lorsque le service est "idle".

Questions:
  - Est-ce que le KeepAlive s'exécute à toutes les 5 secondes ou seulement après 5 secondes d'inactivité?
  - Commentez les lignes d'activation du KeepAlive sur le serveur, est-ce que KeepAlive est activé par défaut? Si oui, combien de temps entre les appels?

## Numéro 2

Reprenez le numéro précédent mais codez vous-même le KeepAlive (mettre le keep-alive à false). Notez que votre implémentation n'aura pas le ACK, on envoie n'importe quoi et on retourne n'importe quoi en TCP.

Votre solution n'est pas obligé d'être "bullet-proof", vous pouvez interpréter que vous n'avez qu'un seul client et un seul serveur.