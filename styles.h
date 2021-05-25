const char _styles[] PROGMEM = R"=====(
*{
  box-sizing: border-box;
  outline: none;
  margin: 0;
  padding: 0;
}

body{
  background-color: #393e46;
  font-family: Calibri, monospace, sans-serif;
}
/* small css */
.center{
  display: table;
  margin-left: auto;
  margin-right: auto;
}
.d-none{
  display: none;
}
.d-ib{
  display: inline-block;
}
.mt-20{
  margin-top: 20px;
}
.ml-10{
  margin-left: 10px;
}
.w-25{
  width: 25%;
}
.w-50{
  width:50%;
}
.w-100{
  width: 100%;
}
.pb-10{
  padding-bottom : 10px;
}

.title{
  font-size: 30px;
  font-weight: bold;
  text-shadow: 0 0 10px #FFE227;
}
.f-right{
  float:right;
}
.generalWhite{
  color: #fff;
}
.generalWidth{
  width: 90%;
}
.container{
  
  width: 96%;
}
.header{
  margin-top: 10px;
 background-color: #222831;
 border: none;
 border-radius: 10px;
}
/* end of small css */

/*Whole ARC Process*/
.neoRing{
  margin-top: 10px;
  position: relative;
  width: 250px;
  height: 250px;
  border: none;
  border-radius: 50%;
  background-color: #000;
}
.box{
  position: absolute;
  display: inline-block;
  width: 20px;
  height: 20px;
  border: none;
  border-radius: 2px;
  background-color: #FFF;
  z-index: 1;
}
.innerDot{
  position: absolute;
  display: table;
  width: 15px;
  height: 15px;
  top: 50%;
  left: 50%;
  -ms-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);
  border: none;
  border-radius: 50%;
  background-color: #cdd0cb;
  z-index: 2;
}
.innerRing{
  position: absolute;
  display: table;
  top: 50%;
  left: 50%;
  -ms-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);
  width: 170px;
  height: 170px;
  border: none;
  border-radius: 50%;
  background-color: #393e46;
  box-shadow: 0 0 -10px #fff76a;
}
/*ARC process complete*/

/*color picker*/
input[type="color"] {
	visibility: hidden;
}
.colorWrapper{
  display: block;
  background-color: #fff;
  width: 32px;
  height: 32px;
  border: 1px solid #FFF;
  border-radius: 4px;
  transition: 0.2s ease-in-out;
}
.colorWrapper:active{
    transform: scale(0.97);
}
/* end of color picker */

/* Range */
.rangeInput{
  width: 250px;
}
.generalRange {
  -webkit-appearance: none;
  width: 85%;
  height: 10px;
  border-radius: 5px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.generalRange:hover {
  opacity: 1;
}

.generalRange::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  background-color: #a2f371;
  width: 20px;
  height: 20px;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}

.generalRange::-moz-range-thumb {
  width: 20px;
  height: 20px;
  background-color: #a2f371;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}

/* end of Range */

/*Switch*/

.switch {
  position: relative;
  display: inline-block;
  width: 70px;
  height: 30px;
}

.switch input {
 display: none;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #2196F3;
  transition: 0.4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 24px;
  width: 26px;
  left: 4px;
  bottom: 3px;
  background-color: #FFF;
  transition: .4s;
}

input:checked + .slider {
  background-color: #ABDF61;
}

input:focus + .slider {
  box-shadow: 0 0 10px #2196F3;
}

input:checked + .slider:before {
  transform: translateX(36px);
}

/* Rounded sliders */
.slider.round {
  border-radius: 32px;
}

.slider.round:before {
  border-radius: 50%;
}
/* end of switch */


/* Cards */
.card{
  margin-top: 20px;
  display: table;
  padding:10px;
  background-color: #5b5b5b;
  border: none;
  border-radius: 10px;
}
.cardWC{
  width: 25%;
}
.cardWCC{
  width: 100%;
}
.card label{
  display: table;
  margin-top:10px;
  margin-left: auto;
  margin-right: auto;
}

.dot{
  display: inline-block;
  width: 10px;
  height: 10px;
  border: none;
  border-radius: 50%;
}

.bg-blue{
  background-color: #2196F3;
}

.bg-green{
  background-color: #ABDF61;
}
/* end of cards */

/* general buttons */
.generalButtonCircle{
  background-color: #fff;
  margin-top: 10px;
  padding: 20px;
  border: none;
  border-radius: 50%;
  transition-duration: 150ms;
  transition-property: transform;
  transition-timing-function: ease-in-out;
}

.generalButtonCircle:active{
  transform:scale(0.97);
}
.generalSubmitButton{
  margin-top: 10px;
  font-weight: bold;
  border: none;
  border-radius: 4px;
  padding: 10px;
  color: #5b5b5b;
  background-color: #ffc478;
  transition: 0.2s;
}

.generalSubmitButton:hover{
  background-color: #75cfb8;
  color: #FFF;
}

.generalSubmitButton:active{
  background-color: #75cfb8;
  color: #FFF;
  transform:scale(0.97);
}
/* End of general buttons*/

/*General Input*/

.generalInput{
  width: 90%;
  padding: 10px;
  margin-top: 10px;
  border: none;
  border-radius: 4px;
  transition: 0.2s;
}

.generalInput:focus{
  box-shadow: 0 0 10px #fff76a;
}
/*End of General Input*/

/* Responsive */
@media(max-width: 767px) and (min-width: 500px){
  .cardWC{
    width: 50%;
  }
}
@media(max-width: 499px){
  .cardWC{
    width: 80%;
  }
}

)=====";