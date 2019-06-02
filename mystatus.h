const char status_page[] PROGMEM = R"=====(
<!doctype html>
<html>
  <head>
    <title>LumMoS-My Status</title>
    <link href="main.css" rel="stylesheet" type="text/css"/>
    <script>
      var audio = new Audio('https://vincens2005.github.io/vr/Nyan%20Cat%20[original].mp3'); 
      
     </script>
  </head>
  <body>
 <center>
  
  <p>
    <h1>My STATUS</h1>
  </p>
<p>
    
    <h2>This is my status</h2>

    <div>
        Bend : <span id="angleValue">0</span><br>
        Status : <span id="LEDState">NA</span>
        
    </div>
    <script>
      
  var triggered=false;
  var counter=0;
    
    setInterval(function() {
      // Call a function repetatively with 2 Second interval
      getData1();
      getData2();
      myAlert();
    }, 500); //2000mSeconds update rate
    
    function getData1() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("angleValue").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "readFlex", true);
      xhttp.send();
    }

    function getData2() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("LEDState").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "setLED?LEDstate=", true);
      xhttp.send();
    }

    function myAlert(){
      var av= document.getElementById("angleValue").innerHTML; //angleValue;
      if(av>=1&&!triggered){
        counter++;
        if(counter>=10){
          triggered=true;
          audio.play();
          alert('You are sitting in A WRONG POSTURE!');
          triggered=false;
          audio.pause();
          counter=0;
        }
      
      }else{ counter=0;}
    }
    </script>
    
</p>
</center>
  </body>
</html>
)=====";
