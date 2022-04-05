<!DOCTYPE>
<html>
<head>
  <title>Caméras Liason série</title>
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
</head>

<body1>
   
<style>
h1
{
text-align: center;
background-color: lime;
}
div{
 text-align:center;
}
div1{
  text-align:center;
}
div2{
  text-align:center;
  height: 150px;
}

#button1{
    position:relative;
    left:92%;
}
#sauv{
position:relative;
    left:41%;
}
caption {
    padding: 10px;
}
table
{
    position:relative;
    left:45%;
    border-collapse: collapse;
    caption-side: top;
}
td, th
{
    border: 1px solid black;
    padding: 10px;
}

</style>  
<h1>La caméra  HBV1517</h1>

<h3> streaming caméra Galaxy Tab GT-P6210</h3>

<script>
function remove(el) {
     var element = el;
     element.remove();
}
function refreshDIV(){

   $('#refresh-section').load(location.href + "#refresh-section");
}
</script>

<button id="button1" name="appuyer" onclick="remove(image_x)"  type="button" class="btn btn-dark">Supprimer</button>  

 <div>
<img id="image_x"  src=""/>
</div> 

<div1 class="container">
  <div class="row row-cols-3">
    <div class="col">1ère photo</div>
    <div class="col">2ème photo</div>
    <div class="col">3ème photo</div>
  </div>
</div1>

<div2 class="container">
  <div class="row row-cols-3">
    <div class="col"><img id="image_x"  src=" " height="100%" width="100%" /></div>
    <div class="col"><img id="image_x"  src=" " height="100%" width="100%" /></div>
    <div class="col"><img id="image_x"  src="" height="100%" width="100%"/></div>
  </div>
</div2>

<?php

       $fichier = "/dev/ttyUSB0";
       $ouverture = fopen($fichier,"r");
              if($ouvreFichier = fopen($fichier,'w+'))
                        {

         $lecture = fgets($ouverture,4096);
         fclose($ouvreFichier);
       }

              $temperature = $lecture[3].$lecture[4].$lecture[5].$lecture[6].$lecture[7];
              $humidite    = $lecture[9].$lecture[10];

?>
<div3 id="#refresh-section">

<table>
  <caption text-align="center" >Résultats du DHT22</caption>

   <tr>
   <td>  Température  </td>
   <td> <?php  echo $temperature;  ?> °C</td>
   </tr>
   <tr>
       <td>Humidité</td>
       <td><?php echo  $humidite; ?> %</td>
   </tr>
</table>

</div3>
<div4>
<?php


$servername = 'localhost';
$database = 'Rover';
$username = 'root';
$password = 'password';

 $conn = mysqli_connect($servername, $username, $password, $database);

 if (!$conn) {
       die("Échec de la connexion : " . mysqli_connect_error());
       }
         $sqlt = "INSERT INTO temp(valeur) VALUES ('$temperature')";

 if (mysqli_query($conn, $sqlt)) {

 } else {
   
    echo "Erreur : " . $sqlt . "<br>" . mysqli_error($conn);
 }

   mysqli_close($conn);

   $conn = mysqli_connect($servername, $username, $password, $database);

   if (!$conn)
   {
    die("Échec de la connexion : " . mysqli_connect_error());
   }

   $sqlh = "INSERT INTO humide(valeur) VALUES ('$humidite')";

   if (mysqli_query($conn, $sqlh)) 
   {
     
   } else {
      
       echo "Erreur : " . $sqlh . "<br>" . mysqli_error($conn);

   }
   
   mysqli_close($conn);
?>

</div4>
<div5>
<br>
<button id="sauv" type="button" class="btn btn-secondary btn-lg btn-block" onClick="history.go(0)"> Sauvegarder les Résultats du DHT22</button>
<br>
</div5>
</body1>
</html>
