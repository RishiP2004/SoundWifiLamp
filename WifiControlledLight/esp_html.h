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
            max-width: 800px;
            margin: 20px auto;
            text-align: center;
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
    </style>
</head>
<body>
    <div class="navbar">ESP32 Control</div>
    <div class="container">
        <h2>Control LED</h2>
        <button type="button" class="btn" id="btnOn" onclick="ButtonPress('ON')">Turn LED ON</button>
        <button type="button" class="btn" id="btnOff" onclick="ButtonPress('OFF')">Turn LED OFF</button>
    </div>
    <footer class="foot">Lamp Control Page</footer>

    <script type="text/javascript">
        function ButtonPress(state) {
            var xhttp = new XMLHttpRequest();
            xhttp.open("PUT", "/BUTTON_" + state, true);
            xhttp.send();
        }
    </script>
</body>
</html>

)=====";

#endif // ESP_HTML_H