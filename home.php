<?php //include('./header.php') ?>
<?php
include_once ('./comporter/conn.php');
session_start();

if(!isset($_SESSION['email'])){
  header('location:index.php');
}




include_once "header.php";
?>
<!doctype html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="Mark Otto, Jacob Thornton, and Bootstrap contributors">
    <meta name="generator" content="Hugo 0.101.0">
    <title>ECE In - Bienvenue</title>

    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css" integrity="sha384-xOolHFLEh07PJGoPkLv1IbcEPTNtaed2xpHsD9ESMhqIYd0nLMwNLD69Npy4HI+N" crossorigin="anonymous">

 

    <style>
      .bd-placeholder-img {
        font-size: 1.125rem;
        text-anchor: middle;
        -webkit-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
      }

      @media (min-width: 768px) {
        .bd-placeholder-img-lg {
          font-size: 3.5rem;
        }
      }
    </style>

    
    <!-- Custom styles for this template -->
    <link href="css/pricing.css" rel="stylesheet">
  </head>
  <body>
    


<div class="pricing-header px-3 py-3 pt-md-5 pb-md-4 mx-auto text-center">
  <h1 class="display-4">Bienvenue ECE IN</h1>
  <img class="logo-img" src="bb.png" alt="Logo" width="350px">
  <center><h4>Une école est une institution éducative qui fournit un cadre formel d'apprentissage, dispensant des connaissances, compétences et valeurs aux étudiants, favorisant leur développement intellectuel et social.
  </h4></center>
</div>


<div class="container">
  <div class="card-deck mb-3 text-center">
    <div class="card mb-4 shadow-sm">
      <div class="card-header">
        <h4 class="my-0 font-weight-normal">Événements</h4>
      </div>
      <div class="card-body">
        <h2 class="card-title pricing-card-title"><small class="text-muted">Les nouveaux de ECE</small></h2>
  
        <button type="button" data-toggle="modal" data-target="#exampleModal2" class="btn btn-lg btn-block btn-outline-primary">Événements</button>
      </div>
    </div>
    <div class="card mb-4 shadow-sm">
      <div class="card-header">
        <h4 class="my-0 font-weight-normal">Publications</h4>
      </div>
      <div class="card-body">
        <h2 class="card-title pricing-card-title"><small class="text-muted">Publications étudiantes</small></h2>
     
        <a href="posts.php" class="btn btn-lg btn-block btn-outline-primary">Publications</a>
      </div>
    </div>
    
  </div>


</div>



<!-- Modal -->
<div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalLabel">Contactez-nous</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <span>
          Email:
        <a href="mailto:Scolarite.ece@edu.ece.fr">Scolarite.ece@edu.ece.fr</a>
        </span>
<hr> 
        <span>
          Telephone:
        <a href="tel:123456789">123456789</a>
        </span>
       

        <iframe src="https://www.google.com/maps/embed?pb=!1m14!1m8!1m3!1d2625.337194006927!2d2.2922926!3d48.8583737!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x47e66f1eaf21e833%3A0x64f3b8f4bb1d8b93!2sEiffel%20Tower!5e0!3m2!1sen!2sfr!4v1642619226183" frameborder="0"></iframe> 
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-secondary" data-dismiss="modal">Fermer</button>
       
      </div>
    </div>
  </div>
</div>




<!-- Modal2 -->
<div class="modal fade" id="exampleModal2" tabindex="-1" aria-labelledby="exampleModalLabel2" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalLabel">Événements</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
      <div id="carouselExampleCaptions" class="carousel slide" data-ride="carousel">
  <ol class="carousel-indicators">
    <li data-target="#carouselExampleCaptions" data-slide-to="0" class="active"></li>
    <li data-target="#carouselExampleCaptions" data-slide-to="1"></li>
    <li data-target="#carouselExampleCaptions" data-slide-to="2"></li>
  </ol>
  <div class="carousel-inner">
    <div class="carousel-item active">
      <img src="evenement3.png" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h5>First slide label</h5>
        <p>Some representative placeholder content for the first slide.</p>
      </div>
    </div>
    <div class="carousel-item">
      <img src="evenement2.png" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h5>Second slide label</h5>
        <p>Some representative placeholder content for the second slide.</p>
      </div>
    </div>
    <div class="carousel-item">
      <img src="evenement1.png" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h5>Third slide label</h5>
        <p>Some representative placeholder content for the third slide.</p>
      </div>
    </div>
  </div>
  <button class="carousel-control-prev" type="button" data-target="#carouselExampleCaptions" data-slide="prev">
    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
    <span class="sr-only">Previous</span>
  </button>
  <button class="carousel-control-next" type="button" data-target="#carouselExampleCaptions" data-slide="next">
    <span class="carousel-control-next-icon" aria-hidden="true"></span>
    <span class="sr-only">Next</span>
  </button>
</div>
       

      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-secondary" data-dismiss="modal">Fermer</button>
       
      </div>
    </div>
  </div>
</div>
<div class="footer">
      
      
      <div class="google-map">
        <center><h3>Trouvez-nous sur la carte</h3>
        <iframe src="https://www.google.com/maps/embed?pb=!1m14!1m8!1m3!1d2625.337194006927!2d2.2922926!3d48.8583737!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x47e66f1eaf21e833%3A0x64f3b8f4bb1d8b93!2sEiffel%20Tower!5e0!3m2!1sen!2sfr!4v1642619226183" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy"></iframe>
      </div>
      <center><h1 class="display-4">Contactez-nous</h1></center>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
       <center> <span>
          Email:
        <a href="mailto:Scolarite.ece@edu.ece.fr">Scolarite.ece@edu.ece.fr</a>
        </span></center>
<hr> 
        <center><span>
          Telephone:
        <a href="tel:123456789">123456789</a>
        </span></center>
        </center>
      </form>
      
    </div>


<script src="https://cdn.jsdelivr.net/npm/jquery@3.5.1/dist/jquery.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js" integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.min.js" integrity="sha384-+sLIOodYLS7CIrQpBjl+C7nPvqq+FbNUBDunl/OZv93DB7Ln/533i8e/mZXLi/P+" crossorigin="anonymous"></script>
  </body>
</html>
