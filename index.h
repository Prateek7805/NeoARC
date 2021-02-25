const char html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale = 1">
    <link rel="stylesheet" href="styles.css">
    <title>NeoARC</title>
  </head>
  <body>
    <div class="container center">

      <div class="header center w-100">
        <div class= "center generalWidth">
          <div class="d-ib w-25">
          </div>
          <div class="d-ib w-50">
              <p class="title generalWhite center">NeoARC</p>
          </div>

          <div class="d-ib w-25">
            <label class="switch f-right">
            <input id="flag_settings" type="checkbox">
            <span class="slider round"></span>
            </label>
          </div>
      </div>
    </div>

      <div class="content">
        <div id = "ringInterface" class="neoRing center">
          <span class="innerRing"></span>
        </div>
        <div class="inputColorContainer center mt-20">
          <label class="colorWrapper"><input id="colorInput" type="color" value = "#ffd384" ></label>
        </div>
        <div class="rangeInput center">
          <input id="brightness" class="generalRange mt-20" type="range" min="0" max="100" value="100"><span id="generalRangeValue" class="ml-10 generalWhite">100</span>
        </div>
      </div>

    </div>
    <script <script src="script.js" charset="utf-8"></script>
  </body>
</html>

)=====";