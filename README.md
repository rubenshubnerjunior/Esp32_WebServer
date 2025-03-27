# Esp32_WebServer
### Este projeto visa dar exemplo de como fazer o Esp32 trabalhar como um servidor de pagina Web e um servidor de websocket.
#### Para seguir este tutorial é nescessário o conhecimento de como usar a IDE do Arduino para gravar o Esp32.
#### É neceesário fazer o upload da pasta "data" que está junto com o arquivo web01.ino para a memória SPIFFS do Esp32.
#### Para isto precisamos descompactar o arquivo ESPFS.Zip e colar na pasta na instalação da IDE do arduino conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/tools.jpg)
### Depois disto a IDE do Arduino passará a apresentar a opção conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/upload.jpg)
#### Feito a gravação da pasta "data" na memoria SPIFFS com a pasta data a IDE está pronta para trabalhar com o codigo

 
#### Para isto vamos dar uma olhada no diagrama simplificado abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/Diagrama_01.jpg)
#### Como podemos observar no diagrama a memoria SPIFFS do Esp32 fica com os arquivos do Front End (HTML,CSS,Javascript).
#### Os arquivos do Front End ficam dentro de uma pasta chamada "data" e para fazer o upload dest pasta para a memoria SPIFFS deve ficar junto com o schetch .ino
#### Para poder fazer upload é nescessário inserir a pasta ESPFS conforme pode ser visto na imagem abaixo:

  ### Na pasta biblioteca tem o arquivo compactado desta pasta que pode ser colado conforme mostrado acima.
  #### Após isto a IDE do Arduino mostrará a aba de upload da pasta "data" conforme abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/data.jpg)
#### Quando o navegador faz o request dos arquivos da pasta "data" além de apresentar a interface com o usuário também passa a rodar o cliente WebSocket e a lógica que tratará as mensagens.
