# viewbinding

ViewBinding
Le viewbinding est la liaison des données entre le XML et le code sans devoir faire une recherche d'élément par l'entremise de findViewById(). Pour mettre ceci en place, vous devez ajouter ces lignes de code au fichier build.gradle(Module: ...):

```
buildFeatures {
  viewBinding true
}
```

Dans le onCreate:

```
val binding : ActivityMainBinding = ActivityMainBinding.inflate(layoutInflater)
val view = binding.root
setContentView(view)
```

Notez que ActivityMainBinding n'est pas une classe existante d'Android. Elle est générée dynamique par le layout et se situe dans le répertoire java(generated)/com/exemple/.../ClasseBinding. 

```
Pour accéder à l'objet, on utilise le id de l'objetL

binding.id
```

https://gitlab.com/drynish/ecole/-/tree/master/420-C56%20---%20Programmation%20mobile/Android/Exemples/1.2-%20SelecteurDeBiere%20(intent)

# Intent

Les activités sont un élément de communication afin d'obtenir une action d'une autre portion d'une composante d'application. 

Voici les 3 cas d'utilisation d'une intention:
* Démarrer une activité
* Démarrer un service
* Envoyer un broadcast à tous

## Types d'intention

### Explicite

Indique quelle application doit satisfaire l'intention: en indiquant soit le nom de l'application ou la classe spécifique. On utilise l'intention explicite quand on veut spécifier une portion précise dans notre application.

La première partie sert à définir le context de notre activité actuelle. Habituellement, elle sera l'objet *this* qui représente l'activité en cours. La deuxième portion est la classe que l'on souhaite appeler.


```
Pour ajouter de l'information à travers l'intention, nous utilisons la méthode PutExtra. Il faut comprendre dans la signe suivante que clé est votre choix.

Intent i = Intent(this, TargetActivity::class.java).apply {
  i.putExtra("clé", valeur);
}
startActivity(i);
```

### Implicite

Ne spécifient aucune qui doit répondre à la demande. Si vous souhaitez montrer l'emplacement de l'utilisateur sur une carte, vous allez faire une intention implicite et laisser un autre application dessiner la carte.

Voici la liste des intentions communes d'Android:

https://developer.android.com/guide/components/intents-common

Exemple:

```
fun dialPhoneNumber(phoneNumber: String) {
    val intent = Intent(Intent.ACTION_DIAL).apply {
        data = Uri.parse("tel:$phoneNumber")
    }
    if (intent.resolveActivity(packageManager) != null) {
        startActivity(intent)
    }
}
```

Et à la la seconde activité, on utilise getStringExtra sur l'intention qui a été utilisée pour appeler cette activité.

```
val intent = this.intent;
val message = intent.getStringExtra("message")
```

N'oubliez pas que chaque activité doit être inscrite dans le fichier Manifest, sinon elle ne pourra pas être appelée par votre activité dans le cas d'une intention explicite.

Il est possible d'effectuer un appel vers une information externe par l'entremise d'une startActivityForResult(Intent, int) et d'obtenir un résultat par l'entremise de onActivityResult(int, int, Intent):

```
const val REQUEST_SELECT_CONTACT = 1
fun selectContact() {
  val intent = Intent(Intent.ACTION_PICK).apply {
    type = ContactsContract.Contacts.CONTENT_TYPE
  }
  if (intent.resolveActivity(packageManager) != null) {
    startActivityForResult(intent, REQUEST_SELECT_CONTACT)
  }
}
override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent) {
  if (requestCode == REQUEST_SELECT_CONTACT && resultCode == RESULT_OK) {
    val contactUri: Uri = data.data
    // data.data contient l'information du contact
    //...
  }
}
```

Voici la liste des intentions par défaut sur Android, rien ne vous empêche de créer vos propres intentions qui seront répondues par l'entremise de votre application.

https://developer.android.com/guide/components/intents-common

## Explicit Intent vs Implicit Intent

La différence est que dans le premier cas, on indique la classe devant être appelée, dans le deuxième cas, le système choisit lui-même l'application appropriée pour répondre à la tâche.

Est-ce que l'on doit savoir quelle application va être utilisée ?  

* Si on spécifie une application, elle pourrait ne pas être installée ou encore ne pas être choisie comme action par défaut par l'utilisateur. 
* S'il n'y a qu'une seule application pouvant répondre à cette intention, elle sera automatiquement démarrée. 
* S'il y a plusieurs choix, l'utilisateur aura l'opportunité de choisir l'application qu'il voudra exécutée et il pourra indiquer s'il veut la définir par défaut pour les prochaines exécutions.
* Finalement, si aucune activité ne peut répondre à votre intention, l'exception ActivityNotFoundException sera retournée et vous devrez la traiter.

## Intent-Filter

Vous pouvez programmer une application qui va pouvoir répondre à une Intent implicite, il suffit d'ajouter l'information dans votre Android Manifest afin de spécifier que votre application peut répondre à une Intent.ACTION_SEND (partage email, sms, ...) : 

```
<activity android:name="MainActivity" android:exported="true">
    <!-- This activity is the main entry, should appear in app launcher -->
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
</activity>

<activity android:name="ShareActivity" android:exported="false">
    <!-- This activity handles "SEND" actions with text data -->
    <intent-filter>
        <action android:name="android.intent.action.SEND"/>
        <category android:name="android.intent.category.DEFAULT"/>
        <data android:mimeType="text/plain"/>
    </intent-filter>
    <!-- This activity also handles "SEND" and "SEND_MULTIPLE" with media data -->
    <intent-filter>
        <action android:name="android.intent.action.SEND"/>
        <action android:name="android.intent.action.SEND_MULTIPLE"/>
        <category android:name="android.intent.category.DEFAULT"/>
        <data android:mimeType="application/vnd.google.panorama360+jpg"/>
        <data android:mimeType="image/*"/>
        <data android:mimeType="video/*"/>
    </intent-filter>
</activity>
```

# Le cycle de vie d'une application

![](images/activity_lifecycle.png)


### onCreate(savedInstanceState: Bundle?)
Vous devez implémenter obligatoirement cette méthode qui s'effectue lorsque le système crée cette activité. On l'utilise pour l'implémentation des vues et pour permettre la restauration de l'état de l'application par l'entremise d'un saveBundleStates. Les initialisations qui doivent se faire qu'une seule fois et l'inflation des interfaces.

### onStart()
Cette méthode est disponible quand votre application s'exécute en avant-plan. Démarrer les objets seulement qui sont disponibles quand l'application est visible à l'écran (GPS, base de donnée).

### onResume()
L'application reste dans l'état resume tant que l'utilisateur utilise l'application. Lorsque l'application revient d'une pause, onResume sera appelé de nouveau.

### onPause()
L'utilisateur quitte votre activité (cela ne signifie pas que votre activité est détruite), il peut avoir appuyer sur le bouton récent (bouton carré). Cet état ne dure vraiment pas longtemps et n'est pas assez long pour effectuer des sauvegardes, faire des appels réseaux ou des transactions de bases de données. Il peut même être nécessaire de continuer la mise à jour de l'UI.

### onStop()
Le système appelle cette méthode lorsque l'application n'est plus vue par l'utilisateur. Lorsque cet état est atteint, vous devriez libérer toutes les ressources consommées par votre application  (connexion à un site distant, connexion à une base de données, ...) et sauvegarder les données de façon permanentes.

### onDestroy()
L'activité a terminé de s'exécuter, vous devez libérez les ressources ouvertes (bd, connexion, ...)

### onSaveInstanceState(savedInstanceState: Bundle?)
Cette fonctionnalité permet de sauvegarder les données avant la destruction de notre
activité. Ainsi Android appelle cette méthode juste avant de détruire nos informations, le plus formidable dans tout ça c'est que lors du onCreate, le paramètre savedInstananceState est passé à la méthode et donc peut être utilisé pour restaurer les données afin d'éviter de relancer l'application (à froid) et que l'utilisateur perd la session actuelle.

https://gitlab.com/drynish/ecole/-/tree/master/420-C56%20---%20Programmation%20mobile/Android/Exemples/2.2%20-%20StopWatch%20(LifeCycle)

# ConstraintLayout

### Dimensions 
* dp : pixel densities, unité de mesure qui permet d'être uniforme sur plusieurs appareils différents. Vos mesures devraient obligatoirement être en pixel density.
* sp : scale independant pixel, comme les dp mais pour les tailles de caractère.
* dimens.xml : fichier des différentes dimensions utilisées dans votre programme (standardisé)
* styles.xml : permet d'enregistrer l'ensemble des paramètres de configuration d'un objet dans un fichier xml.

### Création d'interface

Les 4 étapes de création d'interface :

* Inflation : Crée des objets à partir du fichier XML
* Mesure : Calcule des dimensions des parents jusqu'aux enfants (chaque layout calcule la taille de chaque enfant sous lui)
* Layout : Maintenant qu'on sait la taille, on les positionne correctement sous chacun des parents.
* Dessin : Dessin des objets à afficher à l'écran


https://developer.android.com/training/constraint-layout

* Première version offerte en 2016 
* Centrée sur l'utilisation des contraintes.
* Supporte l'API à partir de 9, 2.3, Gingerbread
* Positionnement utilisant les contraintes afin de positionner les objets.
* Utilise le positionnement relatif tel le relativeLayout mais avec beaucoup plus de possibilités (flexible).
* Utilisation de Helpers: Guideline, Barrier
* Permet d'éviter les nestings 
```
linearLayout	constraintLayout
  linearLayout	  textview
    textview	  edit text
    edit text	  textview
  /linearLayout	  edit text
  linearlayout	/constraintlayout
    textview	
    edit text	
  /linearlayout	
/linearlayout	
```

Vous devez ajouter ceci dans votre fichier build.gradle (module)
```
dependencies {
    implementation "androidx.constraintlayout:constraintlayout:2.1.4"
    // To use constraintlayout in compose
    implementation "androidx.constraintlayout:constraintlayout-compose:1.0.1"
}
```


### Propriété des vues

On peut gérer les contraintes internes et externes, i-e par rapport à l'extérieur, et par rapport à son contenu (fixe, match_parent, wrap_content ou match_constraints). 

Double-cliquer sur l'item dans le designer.

### Auto Connect

Pour autocréer les contraintes, il s'agit de l'icône aimant en haut de l'écran de design.

### Baseline

Connect un objet à un autre afin de s'assurer que le texte soit à la même hauteur que le label. Cliquer droit sur l'objet et choisir show baseline.

### Bias

Déplacement l'objet par rapport où il est situé par rapport à des contraintes relatives. Le slider au bas de l'écran de propriété.

### Chains

Distribution équivalent entre / autour les différents éléments de la chaîne. Tu sélectionnes plusieurs éléments, cliques droit et choisir Chains.

### Guideline

Tracer une ligne qui permet d'aligner les objets avec ceux ci. Cliques droit, Guideline

Propriété des guidelines, on peut avoir à partir de la gauche, de la droite et pourcentage de l'écran.

### Barrier

Une barrière c'est une union de plusieurs éléments afin d'établir une contrainte pour d'autre éléments. C'est donc une contrainte malléable en fonction de position de d'autres objets.

Sélectionner les objets, cliques droit et faire Helper.

### Ratio

Permet de spécier les contraintes une par rapport à l'autre lorsqu'une est ”match_constraint”. Cliquer sur le petit triangle en haut à gauche.

https://gitlab.com/drynish/ecole/-/tree/master/420-C56%20---%20Programmation%20mobile/Android/Exemples/2.3%20-%20Login%20(ConstraintLayout)