const char motorControlHeader_1[]  PROGMEM = R"header1(
<!DOCTYPE html>
<html>
<head>
<title>Robojax ESP32 Motor Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
* {box-sizing: border-box}
.table{
    width:100%;
    display:table;
}
.row{
    display:table-row;
}

.fixedCell {
    width:15%;
    display:table-cell;

}

.cell{
    display: table-cell;
    background: green;
}

.progress_bar {
  font-size: 20px;  
  text-align: right;
  padding-top: 10px;
  padding-bottom: 10px;
  padding-right:10px;
  color: white;
  float:left;
  background-color:#34c0eb;  
}

.buttonsDiv {
  display: flex;
  justify-content: center;
  float:auto;
}
.startStop{
     font-size: 20px;
   background-color: #f44336;
    color: #ffffff;
    border-color: #f44336;  
    border: none;
    display: inline-block;
    padding: 7px 10px;
    vertical-align: middle;    
}

)header1";



const char motorControlHeader_2[] PROGMEM = R"robojaxSpeed2( 
.nextprev a.rj-right, .nextprev a.rj-left {
    background-color: #f44336;
    color: #ffffff;
    border-color: #f44336;
}
.nextprev a {
    font-size: 20px;
    border: 1px solid #cccccc;
}
.rj-right {
    float: right!important;
}
.rj-left {
    float: left!important;
}
.rj-btn, .rj-button {
    border: none;
    display: inline-block;
    padding: 7px 10px;
    vertical-align: middle;
    overflow: hidden;
    text-decoration: none;
    color: inherit;
    background-color: inherit;
    text-align: center;
    cursor: pointer;
    white-space: nowrap;
}
</style>
</head>
<body>

<h1>Robojax ESP32 Speed and Direction Control</h1>)robojaxSpeed2";


////////////////for motor 1 part 1///////////////
const char motor1Control_p1[] PROGMEM = R"robojaxSpeed3(
<h2>Motor 1 Control</h2>
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/speed?do=m1slower">< Slower</a>
            </div>        

        </div><!--fixedCell -->


        <div class="progress_bar bar1">)robojaxSpeed3";


////////////////for motor 1 part 2///////////////
const char motor1Control_p2[] PROGMEM = R"robojaxSpeed4(%</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/speed?do=m1faster">Faster ></a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->


</div><!--table -->
<hr align="center" width="50%">
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/direction?dir=m1CCW">CCW</a>
            </div>        

        </div><!--fixedCell -->


        <div class="buttonsDiv">
            <a class="startStop" href="/stop?do=)robojaxSpeed4";
            
 ////////////////for motor 1 part 3///////////////           
const char motor1Control_p3[] PROGMEM = R"robojaxSpeed5(            
            </a>
        </div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/direction?dir=m1CW">CW</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row - Robojax.com -->


</div><!-- ---- table motor 1 ended -->)robojaxSpeed5";

///////////////// motor 1 end******************************************
///////////////////////*************************************


////////////////for motor 2 part 1///////////////
const char motor3Control_p1[] PROGMEM = R"robojaxSpeed3(
<!-- ---- motor 2 started here ---- -->
<h2>Motor 2 Control</h2>

<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/speed?do=m3slower">< Slower</a>
            </div>        

        </div><!--fixedCell -->
        <div class="progress_bar bar2">)robojaxSpeed3";


////////////////for motor 2 part 2///////////////
const char motor3Control_p2[] PROGMEM = R"robojaxSpeed4(%</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/speed?do=m3faster">Faster ></a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->


</div><!--table -->
<hr align="center" width="50%">
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/direction?dir=m3CCW">CCW</a>
            </div>        

        </div><!--fixedCell -->
        <div class="buttonsDiv">
            <a class="startStop" href="/stop?do=)robojaxSpeed4";
            
 ////////////////for motor 2 part 3///////////////           
const char motor3Control_p3[] PROGMEM = R"robojaxSpeed5(            
            </a>
        </div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/direction?dir=m3CW">CW</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row - Robojax.com -->


</div><!--table -->)robojaxSpeed5";

///////////////// motor one end******************************************
///////////////////////*************************************
