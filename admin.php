
<?php
include_once ('./comporter/conn.php');
session_start();

if(!isset($_SESSION['email']) || $_SESSION['email'] != 'admin@gmail.com'){
  header('location:index.php');
}

include_once "header.php";
?>

<div class="container">

<center>
    <img src="./images/photo.png" alt="">
    <h1>Directeur général</h1>
</center>


<table class="table">
  <thead>
    <tr>
      <th scope="col">#</th>
      <th scope="col">id</th>
      <th scope="col">Nom d'utilisateur</th>
      <th scope="col">Mot de passe</th>
      <th scope="col">Bio</th>
      <th scope="col">CV</th>
      <th scope="col">Photo</th>
      <th scope="col">Supprimer un compte</th>
    </tr>
  </thead>
  <tbody>
    
<?php $result = mysqli_query($conn,"SELECT * FROM `users` WHERE email != 'admin@gmail.com'") ;
$i = 0;
foreach($result as $row){
    $i += 1;
?>


    <tr>
      <th scope="row"><?= $i;?></th>
      <td><?= $row['id']; ?></td>
      <td><?= $row['username']; ?></td>
      <td><?= $row['password']; ?></td>
      <td><?= $row['bio']; ?></td>
      <td>

      <?php 

      if($row['cv'] == "" || $row['cv'] == null){
        echo "il n'y a pas CV";
        
      } else { ?>
       
       <a target="_blank" href="./comporter/cv/<?= $row['cv']; ?>">CV</a>
   <?php  }?>

      </td>
      <th><img src="./comporter/profile_picture/<?= $row['picture']; ?>" width="50" alt=""></th>
      <td><a class="btn btn-danger brn-sm" href="delete_user.php?id=<?= $row['id']; ?>">Supprimer</a></td>
    </tr>

    <?php };?>
  </tbody>
</table>


</div>