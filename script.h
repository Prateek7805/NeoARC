const char js[] PROGMEM = R"=====(
var Socket;
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
document.addEventListener('click', function(){
  if(colorSelected){
    colorSelected = false;
    for(var i=0; i<16; i++){
      currentSelectStatus[i] = 0;
      doc("n"+i).style.boxShadow = "";
    }
  }
});
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

doc("colorInput").addEventListener('input', function(){
  colorSelected = true;
  docOC("colorWrapper").style.backgroundColor = this.value;
  for(var i=0; i<16; i++){
      if(currentSelectStatus[i] == 1){
        doc("d"+i).style.backgroundColor = this.value;
        doc("d"+i).style.boxShadow = "0 0 "+parseInt(doc("brightness").value/5)+"px "+this.value;
        colorArray[i] = this.value;
        neoPixelColors["n"+i] = String(this.value);
        coloredPixels[i] = true;
      }
  }
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){

    }
  }
  xhr.open("POST", "/jsonfile", true);
  xhr.send(JSON.stringify(neoPixelColors));
});

doc("brightness").addEventListener('input', function(){
  doc("generalRangeValue").innerHTML = this.value;
  var brightnessValue = parseInt(this.value/5);
  for(var i=0; i<16; i++){
    if(coloredPixels[i])
      doc("d"+i).style.boxShadow = "0 0 "+brightnessValue+"px "+colorArray[i];
  }
    _send("b",this.value);
});

)=====";