<!DOCTYPE html>
<html lang="fr">
   <head>
      <meta charset="utf-8"/>
      <title>Rov 4x</title>
      <link rel="stylesheet" href="style.css"/>
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
   </head>
   <body>
      <h1>Rov 4x contrôle</h1>
      <div id="screenshot">
         <video autoplay></video>
         <canvas style="display:none;"></canvas>
         <div>
            <button id="screenshot-button">prendre une photo</button>
         </div>
         <div class="col">
            <p>Photo :</p>
            <img src = "rien.png" alt = "en attente de photo">
         </div>
         <button id="download">Download</button>
         <script>
            const constraints = {
              video: { width: 640, height: 480 }
            };
            
                     const screenshotButton = document.querySelector('#screenshot-button');
                     const img = document.querySelector('#screenshot img');
                              const video = document.querySelector('#screenshot video');
                             
                               const canvas = document.createElement('canvas');
                             
                              navigator.mediaDevices
                                           .getUserMedia(constraints)
                                                     .then(handleSuccess)
                                                               .catch(handleError);
                             
                               screenshotButton.onclick = video.onclick = function () {
                                              canvas.width = video.videoWidth;
                                                          canvas.height = video.videoHeight;
                                                          canvas.getContext('2d').drawImage(video, 0, 0);
                                                                      img.src = canvas.toDataURL('image/png');
                                                                    };
                               function handleSuccess(stream) {
                                              screenshotButton.disabled = false;
                                                          video.srcObject = stream;
                                                        }
                             
                               function handleError(error) {
                                             console.error('Error: ', error);
                                                       }
                            
         </script>
         <!--Camera-->
         <script>
            (function ($) {
             $(document).ready(function() {
                $("#screenshot img").on("load", function() {
                  $.ajax({
                    type: "POST",
                    url: "/api/faces/register",
                    data: $(this).attr("src")
                  });
                });
              });
            })(jQuery);
         </script>
         <!--Prendre la photo-->
         <script>
            const download = document.getElementById('download');
                    download.addEventListener('click', function (e) {
                                 const link = document.createElement('a');
                                           link.download = 'download.png';
                                           link.href = canvas.toDataURL();
                                                     link.click();
                                                     link.delete;
                                                             });
                   
         </script>
         <!--Enregistrer la photo-->
      </div>
      <div>
         <img id="image_x"  src=""/>
      </div>
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
            <caption text-align="center" ></caption>
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
   </body>
</html>
