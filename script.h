const char _script[] PROGMEM = R"=====(
const dev = true;
var Socket;
//variables
var brightnessValue = 100;
var currentSelectStatus = []; //whether a pixel is selected
var colorSelected = false; //flag to check if pixels are selected or not
var colorArray = []; //store the selected color without applying brightness
var neoPixelColors = {}; //json to send to esp8266
var count = 0;
while(doc("M"+count)){
  count++;
}
//Init of variables
for(var i = 0; i<16; i++){
  currentSelectStatus[i] = 0;
  colorArray[i] = "#000000";
  neoPixelColors[String.fromCharCode(i+65)] = "#000000";
}
doc("generalRangeValue").innerHTML = brightnessValue;


//end of variables


//drawing the neoPixel on the webpage (completed)
  // getting the size of the neoPixel
  doc("ringInterface").innerHTML = "<span class=\"box\"></span>";
  const pixelSize = docOC("box").offsetWidth;
  doc("ringInterface").innerHTML = "";

  //Outer radius of the neoPixel Ring
  const neoRadius = (doc("ringInterface").offsetWidth-(2*pixelSize))/2;
  const offset = pixelSize/2;

  for(var i=0; i<16; i++){
    //some init stuff
    //main drawing code
    //absolute position coordinates of top and left are calculated
    var topVal = parseInt(neoRadius + (neoRadius*Math.sin(i*22.5*Math.PI/180)))+offset;
    var leftVal = parseInt(neoRadius + (neoRadius*Math.cos(i*22.5*Math.PI/180)))+offset;
    var rotationVal = i*22.5; //individual pixels are rotated

    doc("ringInterface").innerHTML += "<button id=\"n"+i+"\" class=\"box\" style = \"top : "+topVal+"px; left : "+leftVal+"px; transform: rotate("+rotationVal+"deg);"+"\" onclick = \"selectPixel(this);\"><span id=\"d"+i+"\" class=\"innerDot center\"></button>";
  }
  //draw the inner ring or inner circle matching the background-color
  doc("ringInterface").innerHTML += "<span class=\"innerRing\"></span>";
  //End of drawing
  if(!dev){
    document.body.style.opacity = 0.8;
    document.body.style.cursor = "not-allowed";
    elements = docOC("container").querySelectorAll('input, select, textarea, checkbox, radio, button');
    for(i=0; i<elements.length;i++) {
      elements[i].setAttribute('disabled', true);
    }
  }



document.addEventListener('DOMContentLoaded', init, false);

//init function

function init(){
  Socket = new WebSocket('ws://'+window.location.hostname+':81/');
  Socket.onmessage = function(event){
    var data = event.data;
    if(data[0] == "c"){
      var json = JSON.parse(data.substring(1));
      brightnessValue = (json["br"] >0)? json["br"] : 1;
      doc("wiFiMODE").checked = (json["wifimode"] == 1)? true : false;
      doc("M0").checked = (json["chase"] == 1)? true : false;
      doc("M1").checked = (json["pf"] == 1)? true : false;
      doc("M2").checked = (json["flash"] == 1)? true : false;
      doc("brightness").value = brightnessValue;
      doc("generalRangeValue").innerHTML = brightnessValue;

      elements = docOC("container").querySelectorAll('input, select, textarea, checkbox, radio, button');
      document.body.style.opacity = 1;
      for(i=0; i<elements.length;i++) {
          elements[i].removeAttribute('disabled');
      }
      document.body.style.cursor = "auto";
    }
}
  Socket.onopen = function(event){
    send("I", "");
  }
}

//xhr to send colorJSON
function sendColors(){
  var sendString = "";
  for(var k in neoPixelColors){
    sendString += neoPixelColors[k].substring(1);
  }
  send("n", sendString);
}


//function to select pixels
function selectPixel(self){
    const currentSel = self.id.substring(1);
    if(self.style.boxShadow != ""){
      self.style.boxShadow = "";
      currentSelectStatus[currentSel] = 0;
    }else{
      self.style.boxShadow = "0 0 15px #ffd384";
      currentSelectStatus[currentSel] = 1;
    }
  }

//function to color pixels
doc("colorInput").addEventListener('change', changeColor);

function changeColor(){
  colorSelected = true;//activate deselection of pixels on clicking the DOM
  var colorVal = addBrightness(this.value);
  docOC("colorWrapper").style.backgroundColor = colorVal;
  for(var i=0; i<16; i++){
      if(currentSelectStatus[i] == 1){
        neoPixelColors[String.fromCharCode(i+65)] = colorVal;
        applyColor(colorVal,i);
        colorArray[i] = this.value;
      }
  }
  sendColors();
}

//function for brightness change
doc("brightness").addEventListener('change', changeBrightness);

function changeBrightness(){
  doc("generalRangeValue").innerHTML = this.value;
  brightnessValue = this.value;
  docOC("colorWrapper").style.backgroundColor = addBrightness(doc("colorInput").value);
  for(var i=0; i<16; i++){
      const colorVal = addBrightness(colorArray[i]);
      applyColor(colorVal, i);
      neoPixelColors[String.fromCharCode(i+65)] = colorVal;
  }
  sendColors();
  send('B', brightnessValue);
}

doc("wiFiMODE").addEventListener('click', function(){
  send('CW',(this.checked)? 1 : 0);
});
doc("restart").addEventListener('click', function(){
  send('CR','');
});

doc("realtimeMode").addEventListener('click', function(){
  doc("brightness").removeEventListener((this.checked)? 'change' : 'input', changeBrightness);
  doc("brightness").addEventListener((this.checked)? 'input' : 'change', changeBrightness);
  doc("colorInput").removeEventListener((this.checked)? 'change' : 'input', changeColor);
  doc("colorInput").addEventListener((this.checked)? 'input' : 'change', changeColor);
  send('CT',(this.checked)? 1 : 0);
});


for(var i = 0; i<count; i++){
  doc("M"+i).addEventListener('click', features);
}

function features(){
    if(this.checked){
      for(var i = 0; i<count; i++){
        if(this.id[1] != i)
          doc("M"+i).checked = false;
      }
    }
    send(this.id, (this.checked)? 1 : 0);
}

doc("random").addEventListener('click', function(){
  for(var i=0; i<16; i++){
      var randColor = randomHex();
      var colorVal = addBrightness(randColor);
      neoPixelColors[String.fromCharCode(i+65)] = colorVal;
      applyColor(colorVal,i);
      colorArray[i] = randColor;
  }
  sendColors();
});


//basic functions
function doc(id){
  return document.getElementById(id);
}
function docOC(className){
  return document.getElementsByClassName(className)[0];
}
function er(msg){
  console.log(msg);
}
function applyColor(color, num){
  doc("d"+num).style.backgroundColor = color;
}
function send(head, data){
  er(head+data);
  Socket.send(head+data);
}

  //button to switch to controls
doc("flag_settings").addEventListener('click', function(){
  doc("colorInterface").style.display = (this.checked)? 'none' : 'table';
  doc("controls").style.display = (this.checked)? 'table' : 'none';
});

//function to deselect pixels
document.addEventListener('click', function(){
  if(colorSelected){
    colorSelected = false;
    for(var i=0; i<16; i++){
      currentSelectStatus[i] = 0;
      doc("n"+i).style.boxShadow = "";
    }
  }
});

//convert rgb to hsv
function addBrightness(rgbVal, reverse){
  reverse = reverse || false;
  rgbVal = parseInt(rgbVal.substring(1),16);
  const blue = rgbVal & 255;
  const green = (rgbVal >> 8) & 255;
  const red = (rgbVal >> 16) & 255;
  const _R = parseFloat(red/255);
  const _G = parseFloat(green/255);
  const _B = parseFloat(blue/255);

  const Cmax = Math.max(_R,_G,_B);
  const Cmin = Math.min(_R,_G,_B);

  const delta = Cmax - Cmin;
  var hsv = {};

  hsv.hue = (delta == 0)? 0 : (Cmax == _R)? 60*mod(((_G-_B)/delta),6) : (Cmax == _G)? 60*((_B-_R)/delta + 2) : 60*((_R-_G)/delta + 4);
  hsv.sat = (Cmax == 0)? 0 : delta/Cmax;
  hsv.val = (reverse)? Math.round((Cmax*100/brightnessValue)*100)/100 :  Math.round((Cmax*brightnessValue/100)*100)/100;//this is where the brightness is changed

  er(hsv.val);
  return convertToRGB(hsv);
}

//js can't do mod of negative numbers
function mod(n, m) {
  return ((n % m) + m) % m;
}

//function to convert hsv back to rgb
function convertToRGB(hsv){
  const H = hsv.hue;
  const S = hsv.sat;
  const V = hsv.val;
  const C = V*S;
  const X = C*(1-(Math.abs((H/60)%2 - 1)));
  const m = V - C;
  //underLying codes are based on rapid tables do not modify
  //just assigns C, X, 0 to _R, _G, _B
  //used ternary operator to avoid if else ladder
  const _R = (H >= 60)? ((H >= 120)? ((H>=180)? ((H>=240)? ((H>=300)? C: X) : 0): 0): X) : C;
  const _G = (H >= 60)? ((H >= 120)? ((H>=180)? ((H>=240)? ((H>=300)? 0: 0) : X): C): C) : X;
  const _B = (H >= 60)? ((H >= 120)? ((H>=180)? ((H>=240)? ((H>=300)? X: C) : C): X): 0) : 0;

  const R = Math.round((_R+m)*255);
  const G = Math.round((_G+m)*255);
  const B = Math.round((_B+m)*255);

  //er("RGB: " + ("000"+String(R)).slice(-3) + ("000"+String(G)).slice(-3) + ("000"+String(B)).slice(-3));

  var hexString = ((R<<16) + (G<<8) + B).toString(16);
  hexString = ("000000" + hexString).slice(-6);
  return "#"+ hexString;
}

function randInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1) + min); //The maximum is inclusive and the minimum is inclusive
}

function randomHex(){
  var rgb = [0,1,2];
  var random = Math.floor(Math.random() * rgb.length);
  const random1 = rgb[random];
  rgb.splice(random,1);
  random = random = Math.floor(Math.random() * rgb.length);
  const random2 =  rgb[random];
  rgb.splice(random,1);

  var rgbVals = []
  rgbVals[random1] = 0;
  rgbVals[random2] = 255;
  rgbVals[rgb[0]] = randInt(0,256);
  var hexString = ((rgbVals[0]<<16) + (rgbVals[1]<<8) + rgbVals[2]).toString(16);
  hexString = ("000000" + hexString).slice(-6);
  return "#"+ hexString;
}

)=====";