#ifndef ESP_HTML_H
#define ESP_HTML_H

// Your HTML content or declarations go here
const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Control</title>
    <style>
        body {
            font-family: Verdana, Arial, sans-serif;
            background-color: #efefef;
        }
        .navbar {
            width: 100%;
            height: 50px;
            background-color: #FFF;
            border-bottom: 5px solid #293578;
            padding: 10px 0;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
        }
        .container {
            max-width: 600px;
            height:300px;
            margin: 20px auto;
            text-align: center;
            background-color: lightgrey;
            border-radius:10px;
            border: 2px solid #333;
            box-shadow: 4px 4px 8px rgba(0, 0, 0, 0.3);
        }
        .btn {
            background-color: #444444;
            border: none;
            color: white;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            cursor: pointer;
        }
        .foot {
            font-size: 20px;
            text-align: center;
            color: #AAAAAA;
            padding: 10px 0;
        }
        /*button*/
        h1 {
            color: green;
        }
        .toggle {
            position : relative ;
            display : inline-block;
            width : 100px;
            height : 52px;
            background-color: red;
            border-radius: 30px;
            border: 2px solid gray;
        }
              
        .toggle:after {
            content: '';
            position: absolute;
            width: 50px;
            height: 50px;
            border-radius: 50%;
            background-color: gray;
            top: 1px; 
            left: 1px;
            transition:  all 0.5s;
        }
              
        p {
            font-family: Verdana, Arial, sans-serif;
            font-weight: bold;
            color: white;
        }
              
        .checkbox:checked + .toggle::after {
            left : 49px; 
        }
              
        /* Checkbox checked toggle label bg color */
        .checkbox:checked + .toggle {
            background-color: green;
        }
              
        /* Checkbox vanished */
        .checkbox { 
            display : none;
        }
        .toggleButton{
            padding-top:40px;
            padding-bottom:40px;
        }
    </style>
</head>
<body>
    <div class="navbar">ESP32 Control</div>
    <div class="container">
        <br>
        <h2>Control LED</h2>
        <div class="toggleButton">
            <center>
            <input type="checkbox" id="switch" class="checkbox" onclick="sendToggleState()" />
            <label for="switch" class="toggle">
                <p>
                    ON &nbsp;&nbsp; OFF
                </p>
            </label>
            </center>
        </div>

    
    <footer class="foot">ESP32 Web Page</footer>

    <script type="text/javascript">
        function sendToggleState() {
            var switchElement = document.getElementById('switch');
            var state = switchElement.checked ? 'ON' : 'OFF';
            console.log('Current toggle state:', state);

            var xhttp = new XMLHttpRequest();
            xhttp.open("PUT", "/BUTTON_" + state, true);
            xhttp.send();
        }
    </script>
</body>
</html>

)=====";

#endif // ESP_HTML_H
