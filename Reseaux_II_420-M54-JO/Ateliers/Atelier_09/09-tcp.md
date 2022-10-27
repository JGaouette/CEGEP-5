# Numéro 1

Créez un serveur qui reçoit une string et la retourne, tout simple. Ajoutez des print pour afficher ce qui ce passe sur le serveur (ouverture du serveur, connection client, déconnection client, message reçu, etc.).

Créez un client qui envoie une string et reçoit la réponse du serveur

Gérez les erreurs d'ouvertures de connections.

# Numéro 2

Créez un client et un serveur, une fois la connection ouverte, le serveur envoie un nombre aléatoire à toutes les secondes jusqu'à la fermeture du client.

Ouvrez plusieurs clients en même temps lors de vos tests. Sur le serveur numérotez vos clients afin de pouvoir journaliser les messages et ouverture/fermetures des clients. Attention aux bugs possibles, par exemple: si le client crash le serveur devrait arrêter de lui générer des nombres aléatoires.

DÉFI: Utilisez un flag afin de désactiver la journalisation des messages (nombre aléatoire généré) aux clients.

# Numéro 3

Créez un serveur qui permet de faire des maths. Le client envoie l'action à effectuer (somme, moyenne, écart-type, min ou max) puis la liste des nombres. Le serveur effectue et envoie la réponse lorsqu'il reçoit "=".

Pour ce numéro aussi, permettez d'ouvrir plusieurs connections au serveur. Ne gérez pas les erreurs dans ce numéro, le code est assez complexe.

# Numéro 4

Créez un client/serveur TCP. Votre serveur contient une liste de produits (id, nom, quantité). Votre liste de produits doit être une variable globale.

Lorsqu'un client se connecte, on attends 5 secondes pour simuler une interaction BD, on lui envoie la liste de produits (toutes les infos). Le client envoie l'id et la quantité désiré.

Le serveur vérifie que la quantité est exacte, attends 5 secondes pour simuler une interaction BD, modifie la quantité et retourne la confirmation ou un message d'erreur.

Utilisez un RWMutex, notez que vos sleep ou ticker doivent être dans le mutex. Plusieurs clients peuvent avoir la liste de produits en même temps, mais un seul peut commander à la fois. Si vous enlevez votre Mutex vous devriez pouvoir avoir une quantité négative, avec le Mutex ça devrait être impossible.