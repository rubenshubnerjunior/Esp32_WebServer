# Esp32_WebServer
### Este projeto visa dar exemplo de como fazer o Esp32 trabalhar como um servidor de pagina Web e um servidor de websocket.
#### Para seguir este tutorial é nescessário o conhecimento de como usar a IDE do Arduino para gravar o Esp32 bem como conhecimento de como gravar a memoria SPIFFS.
 
#### Para isto vamos dar uma olhada no diagrama simplificado abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/Diagrama_01.jpg)
#### Como podemos observar no diagrama a memoria SPIFFS do Esp32 fica com os arquivos do Front End (HTML,CSS,Javascript).
#### Os arquivos do Front End ficam dentro de uma pasta chamada "data" e para fazer o upload dest pasta para a memoria SPIFFS deve ficar junto com o schetch .ino
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/data.jpg)
#### Quando o navegador faz o request destes arquivos além de apresentar a interface com o usuario também passa a rodar o cliente WebSocket e a lógica que tratará as mensagens.
