# ViewModel

La classe ViewModel permet de stocker et gérer des données de l'interface dans un mode respectant le lifecycle des applications (onCreate, onStop, onStart, onPause). Entre autres, il permet de survivre aux rotations de l'écran.

Le framework Android dicte la vie des contrôleurs d'interface tel que les activités et les fragments. Ce dernier peut décider de détruire et de recréer un contrôleur d'interface en réponse à certaines intéractions utilisateurs ou événements qui sont complètement hors de votre contrôle:

Si le system détruit ou recrée l'interface utilateur, toute donnée transitoire non stockée sera perdue. Bien sûr que vous pouvez utiliser onSaveInstanceState() et les restaurez dans le onCreate, mais c'est idéal uniquement pour une petite quantitée de données.

Un autre problème est que les contrôleur d'interface peuvent faire plusieurs appels asynchrones qui peut prendre quelques temps pour répondre (downloader une page web, downloader un fichier, questionner un API, ...). Le contrôleur d'interface a besoin d'effectuer ces appels, cependant, si le contrôleur se fait détruire, il faut que les appels qu'il a créés soient détruits également afin d'éviter les fuites de mémoire. Cette gestion prend beaucoup de gestion et si un objet doit être recréé, il s'agit d'une dépense de ressource puisque l'objet devra refaire les mêmes appels qu'il avait fait précédemment.

Les contrôleurs d'interface comme les fragments et les activités devraient seulement être responsables d'afficher les données d'interface, de réagir aux intéractions utilisateurs et de gérer les communications avec le système d'exploitation tel que les demandes de permissions.

Leur demander d'être responsable de charger les données d'une base de données locales ou par réseau vont encombrer la classe et surtout ralentir les intéractions avec l'utilisateur.

C'est plus simple et plus efficace de séparer la gestion des données du contrôleur d'interface.

![](images/ViewModel.png)

## Implémentation d'un ViewModel

Le but d'un ViewModel est de préparer les données pour les contrôleurs d'interface. Les donneés des ViewModels survivent la transtition entre deux activités. Par exemple, si vous devez afficher une liste d'utilisateur, assurez-vous de garder cette liste dans un ViewModel plutôt que dans une activité.

```
class MyViewModel : ViewModel() {
    private val users: MutableLiveData<List<User>> 
    
    init {
        users.value = loadUsers()
    }
    
    fun getUsers(): LiveData<List<User>> {
        return users
    }

    private fun loadUsers() {
        // Do an asynchronous operation to fetch users.
    }
}
```
Vous pouvez les obtenir à partir d'une activité avec l'appel suivant:

```
class MyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        // Create a ViewModel the first time the system calls an activity's onCreate() method.
        // Re-created activities receive the same MyViewModel instance created by the first activity.

        // Use the 'by viewModels()' Kotlin property delegate
        // from the activity-ktx artifact
        val model: MyViewModel by viewModels()
        model.getUsers().observe(this, Observer<List<User>>{ users ->
            // update UI
        })
    }
}
```

# Live Data
Le LiveData est une classe de données observable. Contrairement à un observer régulier, LiveData est consciente du cycle de la vie des composants d'applications comme les Activity ou les Fragment. Cette connaissance lui permet de mettre à jour les composants seulement quand ils sont dans un état actif.

## Avantages

### S'assure que les données sont à jour avec l'interface

* LiveData suit le pattern de développement observateur. 

* LiveData avise les objets observés lorsqu'il y a un changement dans le cycle de vie de l'application. On peut donc consolider le code de mise à jour de nos objets à l'intérieur de ses objets *Observer*.

### Il n'y a aucune perte de mémoire

* Les observateurs sont liés au cycle de vie de l'application et se nettoient automatiquement lorsqu'ils sont détruits.

### Pas de crash si les activitées sont terminées

* Si le cycle de vie de l'observateur est inactif, comme lorsque l'application n'est plus en avant plan, il ne recevra aucun événements LiveData.

### Pas besoin de gestion de cycle de vie manuel

* Les composants d'interface ne font qu'observer les données intéressantes, ils ne stoppent et ne recommencent jamais leur opération.

### Toujours à jour

* Aussitôt qu'une activité redevient disponible, l'activitée reçoit la dernière information disponible. Idem lorsqu'il y a une rotation de l'écran. 

## Type de LiveData

1. LiveData: immuable, on peut l'observer mais jamais lui assigner une donnée.

2. MutableLiveData: muable est une sous-classe de LiveData. On peut observer et modifier en utilisant la méthode postValue( thread safe ) ou setValue pour affecter un message aux obserrveurs.

3. MediatorLiveData: obbserve des objets tel que des sources et réagit au changement de celle-ci en utilisant le onchange. Il donne donne contrôle quand nous souhaitons effectuer une action ou propager un événement.

## Comment utiliser un LiveData

1. Créer un objet de type LiveData (ou enfant) généralement dans votre classe ViewModel.

1. Créer un objet Observer qui définira la méthode onChanged(), qui contrôle ce qui survient lorsque les données des objets LiveData subissent des changements. Vous créerez habituellement ces objets dans une activité.

1. On attache l'objet Observer aux données LiveData en utilisant la méthode observe(). Ceci fait que l'objet Observer soit lié au LiveData afin qu'il soit notifié des changements et les applique soit au model soit à l'interface (dans le cas où l'objet aurait été modifié à l'extérieur)


# DataBinding

Permet de lier le layout à un objet externe tel qu'un ViewModel avec ou non des LiveData.


Création d'un lien dans le layout:
```
<data>
    <variable name="userViewModel" type="com.example.a45_databinding.UserViewModel"/>
</data>
```

Dans l'activité, on utilise le dataBindingUtil pour créer la vue et l'associer au ViewModel
```
val userViewModel: UserViewModel =
    ViewModelProvider(this)[UserViewModel::class.java]
val binding: ActivityMainBinding = DataBindingUtil.setContentView(this, R.layout.activity_main)
binding.userViewModel = userViewModel
binding.lifecycleOwner = this
```

Par la suite, le layout est lié à la vue et nous pouvons utiliser cette syntaxe pour joindre des éléments:

```
app:error="@{userViewModel.errorName}"

android:text="@={userViewModel.name}"
android:onClick="@{()-> userViewModel.onLoginClicked()}"
```

Voir https://developer.android.com/topic/libraries/data-binding/expressions#expression_language





Voir l'exemple 4.4 DataBinding