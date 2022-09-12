# Introduction

Les applications Android sont faîtes en grande majorité par un mélange de Java et de XML.

Programmation avec **Java** pour les événements et gestion des données

Utilisation de **XML** pour gestion de l'apparence de l'application

Quelques fois d'autres ressources sont nécessaires pour une application données: images, sons, ... 

## Exécution d'une application Android

* Noyau Linux : pour communiquer avec le matériel (GPS, réseau wifi, réseau antenne cellulaire, écran (input/output) ), la mémoire virtuelle, les processus et les threads et gère l'énergie.

* HAL: permet d'unifier la gestion de la caméra et de tout équipement commun sur tous les téléphones Android afin de permettre au applications de communiquer uniformément avec le matériel

* Librairies C/C++: librairies disponibles pour plusieurs système d'exploitation tel que par exemple la librairie C et la librairie webkit

* Runtime Android: Librairie de base pour Android et l'environnement d'exécution des applications (ART).

* Framework Android: les classes et services d'Android que nous utiliserons pendant le cours.

* Layer d'application:  Votre applicationet les autres applications installées

![](images/android-stack_2x.png)

## SDK

Les applications qui s'exécutent sur un téléphone Android ne sont pas des .class ou .jar comme les applications traditionnelles Java. Elles ont un format particulier qui est offert par une compilation différente.

Celle-ci provient de l'utilisation d'un SDK  particulier offert par Google, il varie à chaque release d'Android.

À l'intérieur, on y retrouve:

* Plateforme SDK (qui contient les librairies, et les frameworks nécessaires pour la compilation)
* Outils SDK
* Documentation
* Exemples
* Android Support (API supplémentaire permettant la rétro-activité du fonctionnement actuel)

La gestion des versions d'Android est réalisée par Gradle et par Android Studio. Lorsque vous développez pour Android, vous devez choisir une version pour laquelle vous développez ce qui vous permet d'être plus ou moins compatible avec les téléphones actuels. (Vous pouvez voir votre % de compatibilité avec les téléphones en utilisation).

# Compilation
Android Studio utilise Gradle, un outil d'automatisation de compilation, pour automatiser et gérer le processus de compilation. Ce dernier est utilisé pour  compiler l'application en bytecode, d'y ajouter les resources et le manifest, finalement la signer et créer un APK.

Ce dernier pourra être installé sur un téléphone connecté directement, émulé ou mis en ligne dans le Play Store.

## Android Studio
Vous devrez l'installer sur votre poste de travail. Il est largement plus rapide sur Linux que sur Windows.

Vous devez le télécharger depuis ce lien: https://developer.android.com/studio



## Application

Sur Android, il y a différents composants disponibles afin de créer une application :

* **Activity** : Gère les interfaces et les intéractions utilisateurs
* **Service** : roule en arrière plan et communique avec nos activités
* **Broadcast Receiver** : écoute les messages du système ou par les autres applications
* **Content Provider** : offre du contenu aux autres applications

Android connaît les composants que nous utiliserons ou offrirons, car nous devons les définir à même le Manifest de notre Application. Il s'agit d'un document présent pour  chaque application afin de définir le nom de notre application, les composantes, les permissions, les versions d'API, ...

Pour l'instant, nous nous concentrerons que sur l'activité.

Une application est composée d'une ou plusieurs activitées. Une activité est ce que l'utilisateur voit et avec quoi il interagit. Une activité peut être d'écrire un courriel, prendre une photo ou choisir un contact dans une liste. Chaque activité est rattaché à un fichier layout qui dicte la mise en place des éléments dans une interface.

Le système maintient les activitées sur une pile et lorsque l'utilisateur quitte une activité en appuyant sur le bouton back (bouton d'interface android), il quitte l'application en cours et revient sur l'activité  précédente. Cependant si la pile est vide, il revient au launcher.

### Comment Android fait-il pour savoir quelle activité lancée lorsqu'il roule notre application ? 

À l'intérieur du manifest, il y a une section nommée intent-filter dans la description de notre  activité qui indique l'activité à lancer lors de l'ouverture de cette application.

Lors de la création d'une application android, une multitude de fichiers et répertoires sont créés :

* **java** : Répertoire du code source de l'application (en java ou kotlin) qui sera compilé ultérieurement. C'est la que vous allez créer le code qui permettra à votre code d'exécuter des opérations suite à un clic de bouton ou à un choix dans une liste.

* **java (generated)** : Répertoire contenant votre code compilé de votre application.

* **res** : Répertoire contenant les ressources de votre application. Il y a entre autres les XML pour la création des interfaces, les fichiers images, les fichiers raws (sons, ...)

* **manifests** : contient la définition de votre application et ses paramètres

* **build.gradle**: fichier de configuration de gradle

## Les ressources Android

Les resources sont des éléments d'une programmation qui ne doivent pas être présentes dans le code source directement par exemple des chaînes de caractères ou des images. Une ressource est un fichier ou une valeur qui est dans le répertoire /res d'une application.

Voici des exemples de ressources :

* **Strings** : Les chaînes de caractères
* **Drawable** : Les images (Bitmaps, jpg, png, …)
* **Colors** : Les couleurs des éléments (associé à un nom)
* **Layouts** : Fichiers de layout (présentation des interfaces)
* **Menus** : Menus d'une application Android
* **Raw** : Fichier binaire, par exemple des fichiers audios.
* **XML** : Fichier xml arbitraire (non utilisé par Android)
* **mipmap** : Les fichiers pour le launcher de l'application, finalement c'est l'apparence de votre application dans le launcher.

Il est possible de créer des ressources différentes (options régionales, format en fonction de l'orientation, taille de l'écran, …) simplement en créant des fichiers du même noms mais avec des options différentes dans les différents répertoires.  Le système lors de l'exécution tente de dénicher la configuration optimale.

Il est fortement encouragé d'utiliser le fichier strings.xml plutôt que de hardcoder les chaînes, vous aurez compris pourquoi, lors de la traduction de votre fichier de langue, vous n'avez qu'à envoyer un fichier avec les valeurs.

## String.xml

Il est aisé de rendre votre application multilangue, il suffit de créer un répertoire additionnel dans le répertoire /res nommé /values-fr/ qui prendra précédence sur le répertoire /values, si l'environnement est en français.

À l'intérieur d'Android Studio, vous verrez une interface simple afin d'ajouter vos propres strings. Il est à noter que la façon d'accéder aux données à l'intérieur de la ressource exemple est de la façon suivante :

String exemple = getString(R.string.exemple)

ou pour un fichier layout :

value = "@string/exemple" 
## Layout.xml

Il est possible d'utiliser plusieurs fichiers layouts dans notre application afin de lui permettre d'être plus appropriée lors de changement de la présentation :

Appareil différent (montre, télé, téléphone, tablette)
Portrait vs Paysage
Jour ou nuit
Version du framework
...

## Views

Il y a deux types d'éléments Views :

* Layouts: Les conteneurs de views, ils permettent de spécifier le positionnement des éléments à l'intérieur de l'activité. On peut imbriquer les layouts dans un layouts. Ils ont le mot Layout comme suffixe tel que LinearLayout ou ConstraintLayout .

* Views: Les éléments d'interface avec lesquels l'utilisateur interragit : TextView, EditText, ImageView, Button, Chromometer, …

Tous les éléments Views (layouts et objets) doivent spécifier minimalement les propriétés suivantes:

android_layout_width : largeur de l'objet
android_layout_height : la hauteur de l'objet
android_id: nom unique d'identification (pour le code kotlin)

## Layout

Un layout est la façon que les views (objets d'interface) sont positionnées dans une interface. Les différents layouts sont situés dans le répertoire resources/layouts. Les 3 layouts principaux de bases sont les suivants :

### LinearLayout 

un layout qui affiche ses vues de façon en ordre un à la suite de l'autre soit verticalement ou horizontalement. Auparavant très utilisé mais il commence à disparaître de plus en plus, Android suggère d'utiliser dorénavant le ConstraintLayout à toutes les sauces. Cependant, il est encore supporté et le premier atelier sera sur ce dernier par sa simplicité. Mais de nos jours, les nouvelles applications sont faites avec le ConstraintLayout que nous verrons au prochain cours.

### ConstraintLayout 

Un layout qui affiche ses vues (composantes) de positionnement relatif (par rapport au parent ou à un autre vue) en utilisant des contraintes pour spécifier l'apparence. C'est le layout traditionnel en AndroidStudio et remplaçant du  RelativeLayout.

### GridLayout 

Un layout qui divise l'écran en lignes, colonnes et des cellules. Vous devez spécifié le nombre de colonnes que vous voulez, ou vous voulez que vos composantes apparaissent et le nombre de rangées ou colonnes elles doivent contenir.

## Chargement du layout

La ligne setContentView(R.layout.activity_selecteur_de_biere) à l'intérieur du fichier MainActivity.kt indique le nom du fichier layout à utiliser lors de la création de l'activité 

La classe R est une classe générée dynamiquement qui référencie tout le contenu du répertoire de ressources res après compilation.

La commande setContentView génère le layout en lisant le fichier XML et en générant tous les objets Java contenu dans votre fichier layout.

Comment accéder à nos views à partir du code java ou kotlin ?

Deux étapes sont nécessaires :

1. Créer un identifiant à l'intérieur du layout permettant de le référencer :

```
android:id=”@+id/test”
```

2. À l'intérieur de kotlin :

```
val selectBeer_button : Button = findViewById(R.id.selectBeer_button)
```

### Important

* Le @ indique à Android de ne pas traiter l'intérieur du contenu comme du texte mais bien d'utiliser une référence vers un objet ressource.
* Le + indique à Android d'ajouter ce dernier à la liste des id s'il n'existe pas déjà.
* Le id signifie la catégorie à ajouter, on pourrait ainsi accéder à la liste des styles, strings ou image.
* Finalement, Java ne permet pas d'utiliser le / à l'intérieur des méthodes, alors nous devons le remplacer par un .

Au prochain cours, nous verrons comment effectuer le databinding de kotlin qui permet d'utiliser le nom des variables directement dans notre code (un peu à la visual studio) sans passer par **getElementById** et le nom de l'objet.

## Gestion des événements
Lorsque vous avez une référence pour un objet, vous pouvez leur ajouter des événement ou modifier leur propriété:

```
var tv = findViewById<TextView>(R.id.textView)
tv.text = "bonjour"
```

L'ajout d'événement peut se faire de deux façons:

XML: en utilisant le paramètre onclick= dans la déclaration XML d'un objet (ou le designer). Vous devez spécifiez le nom d'une méthode du nom que vous souhaitez appelé:

```
<Button android:id="@+id/button"
android:layout_width="match_parent"
android:layout_height="wrap_content"
android:onclick="patate" // ici
android:text="Appuyez ici">
```

À l'intérieur du fichier MainActivity.kt, on ajoute la méthode suivante:

```
// Remarquez le nom de la méthode et l'objet reçu
fun patate(view: View) { 
   tv.text = "bonjour"
}
```

Faisons une petite historique de l'amélioration de la façon d'assigner une méthode onclick:

Au début (en java), il fallait déclarer un objet OnClickListener afin de redéfinir sa méthode onClick pour indiquer ce que nous souhaitons effectuer.  

```
view.setOnClickListener(object : View.OnClickListener {
   override fun onClick(v: View?) {
      toast("Hello") 
   }
})
```

En utilisant les fonctions lambdas, on est capable d'y affecter directement une méthode lambda à v. L'éditeur vous proposera d'utiliser ce genre d'assignation

```
view.setOnClickListener({ v -> toast("Hello") })
```

Si la dernière portion est une méthode, elle peut être sortie des paranthèses, si vous aviez à passer des arguments à la méthode setOnClickListener, vous devriez les mettre à l'intérieur et sortir l'événement.

```
view.setOnClickListener() { v -> toast("Hello") }
```

Si setOnClickListener n'a qu'un seul paramètre, on peut supprimer les paranthèses.

```
view.setOnClickListener { v -> toast("Hello") }
```

Si vous n'avez pas besoin de v, l'objet appelant.
```
view.setOnClickListener { toast("Hello") }
```

Si vous en avez besoin, vous pouvez le passez en paramètre à une méthode

```
view.setOnClickListener { v -> doSomething(v) }
```

Ou tout simplement utiliser l'objet it créé automatiquement.

```
view.setOnClickListener { doSomething(it) }
```

Exemple

```
button.setOnClickListener {
   tv.text = "bonjour"
   if (it !is Button) return@setOnClickListener
   it.text = "Carotte"
}
```

## Déverminage

Lors de l'exécution de votre code, vous avez vu différent message affiché en bas de l'écran. Les différents types de message sont les suivants, du plus critiques au moins critiques. Lors du  déverminage ils peuvent s'avérer critique afin de voir si les données sont bien affectées ou si la connection a bien été initiée (si on interroge un serveur web) ou une base de données.

* Log.e : Error (erreur)
* Log.w : Warn (avertissement)
* Log.i : Info (connecion sur un serveur)
* Log.d : debug (réponse d'un serveur)
* Log.v : verbose

Les 3 premiers niveaux sont conservés lorsque l'application sera déployée en mode Release. Ils seront utilisés un coup que l'application sera disponible pour le public.

Toutes les applications Android loggent leur application au même endroit, alors il est important d'utiliser un Tagname unique généralement le nom de classe. Par exemple:

Log.e(TagName, ”Message”)
