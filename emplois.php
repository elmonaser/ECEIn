<?php 
session_start();
include_once('./header.php');
include_once ('./comporter/conn.php');
$_SESSION['error'] = "";
$_SESSION['ok'] = "";
if(isset($_GET['id'])){
  $id = $_GET['id'];


$email = $_SESSION['email'];
$select = mysqli_query($conn,"SELECT * FROM `users` WHERE email = '$email'");
while($data = mysqli_fetch_array($select)){
  if($data['cv'] == "" || $data['cv'] == null){
    $_SESSION['error'] = "Vous n'avez pas de CV dans votre compte";
  }else{
    $_SESSION['ok'] = "Le CV a été envoyé";
  }
  
}
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ECE In - Mon réseau</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.10.2/dist/umd/popper.min.js" ></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.min.js" ></script>
</head>
<body>
    
    <style>
      .bd-placeholder-img {
        font-size: 1.125rem;
        text-anchor: middle;
        -webkit-user-select: none;
        -moz-user-select: none;
        user-select: none;
      }

      @media (min-width: 768px) {
        .bd-placeholder-img-lg {
          font-size: 3.5rem;
        }
      }

      .b-example-divider {
        height: 3rem;
        background-color: rgba(0, 0, 0, .1);
        border: solid rgba(0, 0, 0, .15);
        border-width: 1px 0;
        box-shadow: inset 0 .5em 1.5em rgba(0, 0, 0, .1), inset 0 .125em .5em rgba(0, 0, 0, .15);
      }

      .b-example-vr {
        flex-shrink: 0;
        width: 1.5rem;
        height: 100vh;
      }

      .bi {
        vertical-align: -.125em;
        fill: currentColor;
      }

      .nav-scroller {
        position: relative;
        z-index: 2;
        height: 2.75rem;
        overflow-y: hidden;
      }

      .nav-scroller .nav {
        display: flex;
        flex-wrap: nowrap;
        padding-bottom: 1rem;
        margin-top: -1px;
        overflow-x: auto;
        text-align: center;
        white-space: nowrap;
        -webkit-overflow-scrolling: touch;
      }
    </style>

    
  </head>
  <body>
    


<main>

  <section class="py-0 text-center container">
    <div class="row py-lg-5">
      <div class="col-lg-6 col-md-8 mx-auto">
        <h1 class="fw-light">Offres d'emplois</h1>
      
        <?php if($_SESSION['error'] != ""): ?>
        <div class="alert alert-danger text-center" role="alert">
        <?= $_SESSION['error'] ; ?>
        </div>
        <?php endif;?>


        <?php if($_SESSION['ok'] != ""): ?>
        <div class="alert alert-success text-center" role="alert">
        <?= $_SESSION['ok'] ; ?>
        </div>
        <?php endif;?>



      </div>
    </div>
  </section>

  <div class="album py-5 bg-light">
    <div class="container">

      <div class="row row-cols-1 row-cols-sm-2 row-cols-md-3 g-3">
        <div class="col">
          <div class="card shadow-sm">
          <img src="images/emploi1.png" alt="" width="100%" >
            <div class="card-body">
              <p class="card-text">Rechercher un employé en développement de sites Web.</p>
              <div class="d-flex justify-content-between align-items-center">
              <a href="emplois.php?id=1"  class="btn btn-primary">Envoyer cv</a>
                <small class="text-muted">CDD</small>
              </div>
            </div>
          </div>
        </div>


        <div class="col">
          <div class="card shadow-sm">
          <img src="images/emploi2.png" alt="" width="100%" >
            <div class="card-body">
              <p class="card-text">Recherche d'un employé en marketing électronique</p>
              <div class="d-flex justify-content-between align-items-center">
              <a href="emplois.php?id=2"  class="btn btn-primary">Envoyer cv</a>
                <small class="text-muted">CDD</small>
              </div>
            </div>
          </div>
        </div>


        <div class="col">
          <div class="card shadow-sm">
          <img src="images/emploi3.png" alt="" width="100%" >
            <div class="card-body">
              <p class="card-text">Recherche d'un employé en gestion des stocks.</p>
              <div class="d-flex justify-content-between align-items-center">
              <a href="emplois.php?id=3"  class="btn btn-primary">Envoyer cv</a>
                <small class="text-muted">CDD</small>
              </div>
            </div>
          </div>
        </div>




      
</main>





      
  </body>
</html>
