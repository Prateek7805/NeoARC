const char js[] PROGMEM = R"=====(
var Socket;
var brightnessValue = 100;
document.addEventListener('DOMContentLoaded', init, false);
function init(){
  Socket = new WebSocket('ws://'+window.location.hostname+':81/');
  Socket.onmessage = function(event){
  er(event.data);
  }
}
function doc(id){
  return document.getElementById(id);
}
function docOC(className){
  return document.getElementsByClassName(className)[0];
}
function er(msg){
  console.log(msg);
}
function _send(head, data){
  Socket.send(head+data);
}
var currentSelectStatus = [];
var coloredPixels = [];
var colorSelected = false;
var colorArray = [];

var neoPixelColors = {};
doc("ringInterface").innerHTML = "<span class=\"box\"></span>";
const pixelSize = document.getElementsByClassName("box")[0].offsetWidth;
doc("ringInterface").innerHTML = "";
const neoRadius = (doc("ringInterface").offsetWidth-(2*pixelSize))/2;
const offset = pixelSize/2;

for(var i=0; i<16; i++){
  //some init stuff
  coloredPixels[i] = false;
  currentSelectStatus[i] = 0;
  colorArray[i] = "#000000";
  neoPixelColors["n"+i] = "#000000";
  //main drawing code
  var topVal = parseInt(neoRadius + (neoRadius*Math.sin(i*22.5*Math.PI/180)))+offset;
  var leftVal = parseInt(neoRadius + (neoRadius*Math.cos(i*22.5*Math.PI/180)))+offset;
  var rotationVal = i*22.5;
  doc("ringInterface").innerHTML += "<button id=\"n"+i+"\" class=\"box\" style = \"top : "+topVal+"px; left : "+leftVal+"px; transform: rotate("+rotationVal+"deg);"+"\" onclick = \"selectPixel(this);\"><span id=\"d"+i+"\" class=\"dot center\"></button>";
}
  doc("ringInterface").innerHTML += "<span class=\"innerRing\"></span>";

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

//function to select pixels
function selectPixel(self){
    var currentSel = self.id.substring(1);
    if(self.style.boxShadow != ""){
      self.style.boxShadow = "";
      currentSelectStatus[currentSel] = 0;
    }else{
      self.style.boxShadow = "0 0 15px #ffd384";
      currentSelectStatus[currentSel] = 1;
    }
  }

//function to color pixels
doc("colorInput").addEventListener('input', function(){
  colorSelected = true;
  var colorVal = includeBrightness(parseInt(this.value.substring(1), 16));
  docOC("colorWrapper").style.backgroundColor = colorVal;
  for(var i=0; i<16; i++){
      if(currentSelectStatus[i] == 1){
        neoPixelColors["n"+i] = colorVal;
        doc("d"+i).style.backgroundColor = neoPixelColors["n"+i];
        doc("d"+i).style.boxShadow = "0 0 "+parseInt(doc("brightness").value/5)+"px "+neoPixelColors["n"+i];
        colorArray[i] = this.value;
        coloredPixels[i] = true;
      }
  }
  sendColors();
});

//xhr to send json
function sendColors(){
  er(neoPixelColors);
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){

    }
  }
  xhr.open("POST", "/jsonfile", true);
  xhr.send(JSON.stringify(neoPixelColors));
}

//function for brightness change
doc("brightness").addEventListener('input', function(){
  doc("generalRangeValue").innerHTML = this.value;
  docOC("colorWrapper").style.backgroundColor = includeBrightness(parseInt(doc("colorInput").value.substring(1), 16));
  brightnessValue = this.value;
  for(var i=0; i<16; i++){
    if(coloredPixels[i]){
      var colorVal = includeBrightness(parseInt(colorArray[i].substring(1), 16));
      doc("d"+i).style.backgroundColor = colorVal;
      doc("d"+i).style.boxShadow = "0 0 "+(parseInt(brightnessValue/5))+"px "+colorVal;
      neoPixelColors["n"+i] = colorVal;
    }
  }
    sendColors();
});

//convert rgb to hsv
function includeBrightness(rgbVal){
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

  if(delta == 0){
    hsv.hue = 0;
  }else if(Cmax == _R){
    hsv.hue = 60*mod(((_G-_B)/delta),6);
  }else if(Cmax == _G){
    hsv.hue =60*((_B-_R)/delta + 2);
  }else if(Cmax == _B){
    hsv.hue = 60*((_R-_G)/delta + 4);
  }

  if(Cmax == 0){
    hsv.sat = 0;
  }else{
    hsv.sat = delta/Cmax;
  }
  hsv.val = Cmax*brightnessValue/100;
  //er("rgb: " + ("000"+String(red)).slice(-3) + ("000"+String(green)).slice(-3) + ("000"+String(blue)).slice(-3));

  //er("h: "+hsv.hue);
  //er("s: "+hsv.sat);
  //er("v: "+hsv.val);
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

  var hexString = ((Math.round((_R+m)*255)<<16) + (Math.round((_G+m)*255)<<8) + Math.round((_B+m)*255)).toString(16);
  hexString = ("000000" + hexString).slice(-6);
  return "#"+ hexString;
}

)=====";