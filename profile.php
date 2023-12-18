<?php 
session_start();
if(isset($_SESSION['email'])){
  $email = $_SESSION['email'];
  $id = $_SESSION['id'];
include('./header.php');
include_once ('./comporter/conn.php');


if(isset($_POST['submit'])){
  if (empty( $_FILES["picture"]["name"])) {
    $errors[] = 'Picture is required';
  }






if(!isset($errors)){
  $image = $_FILES['picture']['name'];
  $image_size = $_FILES['picture']['size'];
  $image_error = $_FILES['picture']['error'];
  $file = explode('.',$image);
  $fileActual = strtolower(end($file));
  $allowed = array('png','jpg','jpge','svg');
  if(in_array($fileActual,$allowed)){
      if($image_error === 0){
          if($image_size < 4000000){
                  $image_new_name = uniqid('',true).'-'.$image;
                  $target = './comporter/profile_picture/'.$image_new_name;
                  $sql = "UPDATE users SET picture='$image_new_name' WHERE email='$email'";
                  if(!empty($image)){
                      mysqli_query($conn,$sql);
                      if(move_uploaded_file($_FILES['picture']['tmp_name'],$target)){
                          header('location:profile.php');
                      }
                  } 
              }else{
              $errors[] = 'Your picture is to Big';
          }
  
          }
  
      }else{
          $errors[] = 'Check picture type';
      }
}

}

$user_info = mysqli_query($conn,"SELECT * FROM `users`");
while($data = mysqli_fetch_array($user_info)){


?>

<!DOCTYPE html>
<head>
    <link rel="stylesheet" href="../css/style.css" >
</head>
<html>
<body>
    
<div class="container">

<?php if(!empty($errors)): ?>

<div class="alert alert-danger">
<?php foreach($errors as $error): ?>
    <div><?php echo '- '.$error ;?></div>

<?php endforeach ?>
</div>

<?php endif; ?> 


<div class="text-center">
<table class="table">
  <thead>
    <tr>
      <th scope="col">Id</th>
      <th scope="col">Email</th>
      <th scope="col">Username</th>
      <th scope="col">Bio</th>
      <th scope="col">Cv</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row"><?php echo $data['id'];?> </th>
      <td ><?php echo $data['email'];?> </td>
      <td><?php echo $data['username'];?> </td>
      <td ><?php  if($data['bio'] == ""){
      echo "You dont have bio";
      }else{
      
        echo $data['bio'];
       }
      

      
      ?> </td>
    
    
    
    
    
    </td>
      <td ><?php  if($data['cv'] == ""){
      echo "You dont have cv";
      }else{
        ?>
         <a target="blank" href="./comporter/cv/<?= $data['cv'] ?>">CV</a>
     <?php  }
      

      
      ?> </td>
     
    </tr>
  </tbody>
</table>
<!-- Start -->
<?php 
$getcount = mysqli_query($conn,"SELECT * FROM `posts` WHERE user_id='$id'");
if(mysqli_num_rows($getcount) < 1){
echo '<div class="alert alert-danger" role="alert">No Posts Here</div>';

}else{



?>
<h1>Your Posts</h1>
<table class="table">
  <thead>
    <tr>

      <th scope="col">Text</th>
      <th scope="col">Picture</th>
      <th scope="col">Create At</th>

      <th scope="col">Delete</th>
     
    </tr><?php }; ?>
  </thead>
  <tbody>
    <tr>
<?php
$user = mysqli_query($conn,"SELECT * FROM `posts` WHERE user_id='$id'");
while($data= mysqli_fetch_array($user)){
?>


      <td><?php echo $data['text'];?> </td>
      <td> <?php echo "<img id='img' src='./comporter/posts_picture/".$data['picture']."'' width='50px'  class='rounded' >";?> </td>
      <td ><?php echo $data['create_at'];?> </td>
  
      <td><a href="delete.php?id=<?php echo $data['post_id'];?>"  class="btn btn-danger">Delete</a></td>
  </tr>
<!-- End -->
<?php } ?>


  </tbody>
</table>
<?php 
$user_info = mysqli_query($conn,"SELECT * FROM `users` WHERE email='$email'");
while($data = mysqli_fetch_array($user_info)){
?>

<h2>Bienvenue, <span><?php echo $data['username'] ; ?></span></h2>

<?php echo "<img src='./comporter/profile_picture/".$data['picture']."'' width='200px'  class='rounded' >"; ?>
<br>
 <span><?php echo $data['bio'] ; ?></span>

</div>
<?php  

}

}; ?>



<form action="" method="post">
  <div class="form-group">
    <label for="my-textarea">Bio</label>
   <input class="form-control" type="text" name="bio" placeholder="Écrivez tout ce que vous voulez">
   <br>
   <button type="submit" name="update_bio" class="btn btn-outline-success">Sauvegarder</button>
  </div>
</form>

<hr class="mb-4">

<?php
if(isset($_POST['update_bio'])){
  $bio = $_POST['bio'];

  if(!isset($_POST['bio']) || $_POST['bio'] == "" && $_POST['bio'] == null){
    $errors[] = "Entrez s'il vous plait bio";
  }
  $update = mysqli_query($conn,"UPDATE `users` SET `bio`='$bio' WHERE email = '$email'");
  echo '<meta http-equiv="refresh" content="0; URL=profile.php" />';

}


?>



<!-- cv -->

<form action="" method="post" enctype="multipart/form-data">
  <div class="form-group">
    <label for="my-textarea">Votre CV</label>
   <input class="form-control" type="file" name="cv" placeholder="Écrivez tout ce que vous voulez">
   <br>
   <button type="submit" name="update_cv" class="btn btn-outline-success">Sauvegarder CV</button>
  </div>
</form>

<hr class="mb-4">

<?php
if(isset($_FILES['cv'])){
  $image = $_FILES['cv']['name'];
  $image_size = $_FILES['cv']['size'];
  $image_error = $_FILES['cv']['error'];
  $file = explode('.',$image);
  $fileActual = strtolower(end($file));
  $allowed = array('png','jpg','jpge','svg','pdf');
  if(in_array($fileActual,$allowed)){
      if($image_error === 0){
          if($image_size < 5000000){
                  $image_new_name = uniqid('',true).'-'.$image;
                  $target = './comporter/cv/'.$image_new_name;
                  $sql = "UPDATE users SET cv='$image_new_name' WHERE email='$email'";
                  if(!empty($image)){
                      mysqli_query($conn,$sql);
                      if(move_uploaded_file($_FILES['cv']['tmp_name'],$target)){
                          
                         
                          echo '<meta http-equiv="refresh" content="0; URL=profile.php" />';
                      }
                  } 
              }else{
              $errors[] = 'Your cv is to Big';
          }
  
          }
  
      }else{
          $errors[] = 'Check cv type';
      }
}

?>




<!-- cv  -->


<form action="" method="POST" enctype="multipart/form-data">


<label for="formFile" class="form-label">Update Profile Picture</label>
  <p>use this dimensions <span>750x750</span> For looks nice</p>
  <input class="form-control" name="picture" type="file" id="formFile">



                               
                          
                 
                          <br> <button name="submit" type="submit" class="btn btn-primary">
                               Update
                           </button>
</form>                   
                      
                    
                 


</div>
</body>
</html>
<?php
}

?>


