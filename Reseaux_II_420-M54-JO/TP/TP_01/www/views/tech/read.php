<?php
    $bd = new PDO('mysql:dbname=atelier_1_3;host=host.docker.internal; port=3306', 'root', 'root');

    if (isset($_GET["gameName"])){
        $query = $bd->prepare("DELETE FROM jeux WHERE jeux.nom = :gameName");
        $query->bindParam('gameName', $_GET['gameName'], PDO::PARAM_STR);
        $query->execute();

        ?>
        <script type="text/javascript">
            window.location.href = 'read.php';
        </script>
        <?php
    }
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Ma liste de jeux</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.3.0/font/bootstrap-icons.css" rel="stylesheet" >
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
</head>

<body class="container">
    <header>
        <h1 style="display:inline-block">Ma liste de jeux</h1>
        <a class="primary mx-2 " href="create.php" style="font-size: 1.8em;">
            <i class="bi-plus-circle-fill"></i>
        </a>
    </header>

    <?php
    $query = $bd->prepare("SELECT jeux.id, jeux.nom, categories.nom AS categorie FROM `jeux` INNER JOIN categories WHERE jeux.categorie_id = categories.id;");
    $query->execute();
    $gameList = $query->fetchAll(PDO::FETCH_OBJ);

    echo '<ul class="list-group">';
    foreach ($gameList as &$game) { ;?>
        <li class="list-group-item d-flex">
        <span class="flex-grow-1 my-auto"><?=$game->nom?><span class="text-muted"> - <?=$game->categorie?></span></span>
        
        <button type="button" class="btn btn-primary mx-1 rounded-0 rounded-start" onclick="location.href = 'update.php?id=<?=$game->id ?>'">
            <i class="bi-pencil"></i>
        </button>
        <button type="button" class="btn btn-danger mx-1 rounded-0 rounded-end" data-bs-toggle="modal" data-bs-target="#deleteModal" data-bs-whatever='<?=json_encode($game)?>'>
            <i class="bi-trash"></i>
        </button>
        </li> <?php 
    }
    echo '</ul>';

    ?>

    <div class="modal fade" id="deleteModal" tabindex="-1" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title">Attention</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <p class="modal-text"></p>
                </div>
                <div class="modal-footer">     
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Annuler</button>
                    <button type="button" onclick="toDelete()" name="supprimer" class="btn btn-danger">Supprimer</button>
                </div>
            </div>
        </div>
    </div>

    <script>
        var gameData

        var modal = document.getElementById('deleteModal')
        modal.addEventListener('show.bs.modal', function(event) {
            var button = event.relatedTarget
            gameData = JSON.parse(button.getAttribute('data-bs-whatever'))
            console.log(gameData)
            var modalText = modal.querySelector('.modal-text')

            modalText.textContent = 'Voulez-vous vraiment supprimer ' + gameData.nom + '?'

        })

        function toDelete(){
            window.location.href="read.php?gameName=" + gameData.nom
        }

    </script>


</body>

</html>
