<?php



$host ="localhost";
$username ="root";
$password ="";
$db ="utilisateur_db";


$connection = mysqli_connect($host,$username,$password,$db);
$Id		="2"
$Nom	="alaoui balghiti"
$Prenom ="abdelhadi"
$Email	="abdelhadi.alaouibalghti@edu.ece.fr"
$Mot_de_passe	="abdel1234"
$Photo	="abdelhadi.png"
$Description="etudiant"

$query = "insert into utilisateur (Id,Nom,Prenom,Email,Mot_de_passe,Photo,Description) values('$Id','$Nom','$Prenom','$Email','$Mot_de_passe','$Photo','$Description')";

echo $query;