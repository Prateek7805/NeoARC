const char _index[] PROGMEM = R"=====(
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

      <div class="content pb-10 mt-20">

        <div id = "colorInterface" class="colorInterface center">

          <div id = "ringInterface" class="neoRing center">
          </div>
          <div class="inputColorContainer center mt-20">
            <label class="colorWrapper"><input id="colorInput" type="color" value = "#ffffff" ></label>
          </div>
          <div class="rangeInput center">
            <input id="brightness" class="generalRange mt-20" type="range" min="1" max="100" value="100"><span id="generalRangeValue" class="ml-10 generalWhite"></span>
          </div>

            <div class="card cardWCC center">
              <h2 class="generalWhite">Chase</h2>
              <h3 class="generalWhite"><span class="dot bg-green"></span> ON</h3>
              <h3 class="generalWhite"><span class="dot bg-blue"></span> OFF</h3>
              <label class="switch">
              <input id="M0" type="checkbox">
              <span class="slider round"></span>
              </label>
            </div>

            <div class="card cardWCC center">
              <h2 class="generalWhite">PowerOFF</h2>
              <h3 class="generalWhite"><span class="dot bg-green"></span> Activate</h3>
              <h3 class="generalWhite"><span class="dot bg-blue"></span> Deactivate</h3>
              <label class="switch">
              <input id="M1" type="checkbox">
              <span class="slider round"></span>
              </label>
            </div>

            <div class="card cardWCC center">
              <h2 class="generalWhite">Flash</h2>
              <h3 class="generalWhite"><span class="dot bg-green"></span> Activate</h3>
              <h3 class="generalWhite"><span class="dot bg-blue"></span> Deactivate</h3>
              <label class="switch">
              <input id="M2" type="checkbox">
              <span class="slider round"></span>
              </label>
            </div>

            <div class="card cardWCC center">
              <h2 class="generalWhite">Randomizer</h2>
              <button id="random" class="center generalSubmitButton">Random</button>
            </div>

        </div>

        <div id = "controls" class="d-none center generalWidth">

          <div class="card cardWC center">
            <h2 class="generalWhite">WiFi Mode</h2>
            <h3 class="generalWhite"><span class="dot bg-green"></span> AP</h3>
            <h3 class="generalWhite"><span class="dot bg-blue"></span> STA</h3>
            <label class="switch">
            <input id="wiFiMODE" type="checkbox">
            <span class="slider round"></span>
            </label>
          </div>

          <div class="card cardWC center">
            <h2 class="generalWhite">Restart</h2>
            <h4 class="generalWhite">This will restart the wear</h4>
            <button id="restart" class="center generalButtonCircle">R</button>
          </div>

          <div class="card cardWC center">
            <h2 class="generalWhite">Realtime</h2>
            <h3 class="generalWhite"><span class="dot bg-green"></span> Ya</h3>
            <h3 class="generalWhite"><span class="dot bg-blue"></span> No</h3>
            <label class="switch">
            <input id="realtimeMode" type="checkbox">
            <span class="slider round"></span>
            </label>
          </div>

        </div>

      </div>

    </div>

    <script src="script.js" charset="utf-8"></script>

  </body>
</html>

)=====";