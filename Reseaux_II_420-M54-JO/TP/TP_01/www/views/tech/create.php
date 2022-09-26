<?php
$bd = new PDO('mysql:dbname=atelier_1_3;host=host.docker.internal; port=3306', 'root', 'root');

$query = $bd->prepare("SELECT * FROM categories;");
$query->execute();
$categList = $query->fetchAll();

if (isset($_POST['Enregistrer'])){
    if (isset($_POST['gameName']) && isset($_POST['categ'])){
        $query = $bd->prepare("SELECT nom FROM jeux;");
        $query->execute();
        $nomList = $query->fetchAll();

        $isGood = true;

        foreach ($nomList as $name){
            if($name[0] == $_POST['gameName'])
                $isGood = false;
        }

        if($isGood){
            $query = $bd->prepare("INSERT INTO jeux (id, nom, categorie_id) VALUES (NULL, :gameName, :categID);");
            $query->bindParam('gameName', $_POST['gameName'], PDO::PARAM_STR);
            $query->bindParam('categID', $_POST['categ'], PDO::PARAM_INT);
            $query->execute();
    
            ?>
            <script type="text/javascript">
                window.location.href = 'read.php';
            </script>
            <?php
        }
        else{
            echo    '<div class="alert alert-danger mt-3" role="alert"> 
                        Le nom existe déjà 
                    </div>';
        }
    }
}

if (isset($_POST['Annuler'])):?>
    <script type="text/javascript">
        window.location.href = 'read.php';
    </script>
<?php endif; ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <title>Nouveau jeu</title>
</head>

<body class="container">
    <h1>Ajouter un jeu</h1>

    <form method="post">
        <div class="form-group mb-3">
            <label> Nom </label>
            <input class="form-control" type="text" id="gameName" name="gameName">
        </div>
        <div class="form-group mb-3">
            <label>Catégorie</label>
            <select class="form-select" type="text" id="categ" name="categ">
                <?php
                foreach ($categList as &$categ)
                    echo '<option value="' . $categ[0] . '">' . $categ[1] . '</option>';
                ?>
            </select>
        </div>
        <button type="submit" name="Enregistrer" class="btn btn-primary"> Enregistrer </button>
        <button type="submit" name="Annuler" class="btn btn-secondary"> Annuler </button>
    </form>

</body>

</html>
