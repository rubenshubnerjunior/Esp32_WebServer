



var statusLed1 = "off";
var statusLed2 = "off";


  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  
  function onMessage(event) {
    var stringSPIFFS = event.data;
	console.log("Recebendo do Esp32");
	console.log(stringSPIFFS);
	let jsonSPIFFS = JSON.parse(stringSPIFFS); // Converte a String para Objeto para teste
	
	$("#txtADC1").val(jsonSPIFFS.adc1); // valor recebido do ADC 1
	$("#txtADC2").val(jsonSPIFFS.adc2); // Valor recebido do ADC 2
	$("#txtLed1Status").val(jsonSPIFFS.led1); // Valor recebido do status do Led 1
	$("#txtLed2Status").val(jsonSPIFFS.led2); // Valor recebido do status do Led 2
	
  }
  
  
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  
  
  function initButton() {
    document.getElementById('btnOnLed1').addEventListener('click', onLed1);
	document.getElementById('btnOnLed2').addEventListener('click', onLed2);
	document.getElementById('btnOffLed1').addEventListener('click', offLed1);
	document.getElementById('btnOffLed2').addEventListener('click', offLed2);
  }
  
  function onLed1()
  {
	  console.log("led 1 on");
	  statusLed1 = "on"; // atualiza o status do Led
	  enviaParaEsp32();
	  
  }
  
  function onLed2()
  {
	   console.log("led 2 on");
	   statusLed2 = "on"; // atualiza o status do Led
	   enviaParaEsp32();
  }
  
  function offLed1()
  {
	   console.log("led 1 off");
	   statusLed1 = "off"; // atualiza o status do Led
	   enviaParaEsp32();
  }
  
  function offLed2()
  {
	  statusLed2 = "off"; // atualiza o status do Led
	  console.log("led 2 off");
      enviaParaEsp32();	  
  }
  
  
  function enviaParaEsp32()
  {
	  
	  var obJson = { // cria objeto Json com status dos leds
			
		"led1" : statusLed1,
		"led2" : statusLed2,
		
	}
	
	let msgLeds = JSON.stringify(obJson); //Converte objeto Json para string
	console.log("Enviando para o Esp32");
	console.log(msgLeds);
	
	websocket.send(msgLeds); // Envia para o Esp32 via websocket
	 
  }
  
  
  
  
  
 