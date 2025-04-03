# Esp32_WebServer
#### Este projeto visa dar exemplo de como fazer o Esp32 trabalhar como um Servidor de páginas Web e um Servidor de Websocket.
#### Com o Servidor de página Web vamos enviar para o navegador os arquivos de HTML, JavaScript, CSS, BootStrap, Imagem png.
#### Usaremos o Servidor WebSocket para enviar e receber Strings no formato JSON entre o Esp32 e o Navegador para fazer comandos e exibir os status dos ADCs e dos Leds no Navegador.
#### Para implementar este projeto é necessário o conhecimento de como usar a IDE do Arduino para gravar o Esp32.
#### Também é preciso fazer o upload da pasta "data" que está junto com o arquivo web01.ino (estar junto é mandatório) para a memória SPIFFS do Esp32 conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/data.jpg)
#### Para isto precisamos descompactar o arquivo ESP32FS-1.0.zip ( está na pasta bibliotecas ) e colar na pasta na instalação da IDE do arduino conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/tools.jpg)
#### Depois disto a IDE do Arduino passará a apresentar a opção conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/upload.jpg)
#### A montagem para teste pode ser visto na imagem abaixo do lado esquerdo do protoboard:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/esp_web.jpg)
#### Como se trata de um circuito simples os pinos utilizados está nos comentários do arquivo web01.ino.
#### Olhando o diagrama simplificado temos uma ideia geral de como funciona o sistema:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/Diagrama_01.jpg)
#### A pasta "data" que foi gravada na memória SPIFFS tem os arquivos do Front End ( HTML,CSS, Javascript, Imagem .png).
#### Quando o navegador faz o "Request", o Servidor de página Web faz um "Response" enviando arquivos da pasta "data" para o navegador.
#### Com estes arquivos o navegador exibe a GUI (Graphical User Interface ou Interface Gráfica do Usuário) conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/gui.jpg)
#### Além da GUI também é criado no navegador um cliente de webSocket e uma lógica.
#### A lógica.js no navegador recebe informação do Esp32 via Websocket e atualiza a GUI bem como envia comando para o Esp32 para fazer o on/off dos leds.
#### As mensagens trocadas entre o Esp32 e o Navegador estão no formato JSON para uma melhor escalabilidade.
#### Exemplo de JSON enviado do ESP32 para o Navegador -> {"adc1":"0.50","adc2":"15.29","led1":"off","led2":"off"}
#### Exemplo de JSON enviado do Navegador para o ESP32 -> {"led1":"on","led2":"on"}
#### O objeto JSON é convertido para STRING antes de ser enviado pelo Websocket.
#### No Esp32 e no Navegador existe funções para converter objeto JSON para String e de String para objeto JSON.
#### O display LCD usa o protocolo I2C para economia de pinos que poderão ser usados futuramente.
#### Todas as bibliotecas usadas estão dentro da pasta bibliotecas.
#### Como estamos usando WebSocket para trocar mensagens o navegador não precisa dar refresh na página para atualizar
#### Observar que o WebSocket é assincrono e portanto é acionado quando ocorre eventos.
#### Para facilitar o entendimento do código a maioria das funções foram escritas fora do setup() e do loop() e chamadas em sequência.
#### O código web01.ino está bem comentado e seguindo as chamadas das funções a partir do setup() e depois a partir do loop() é possivel identificar as funcionalidades conforme o diagrama.
#### Haaa... o módulo do lado direito do protoboard é o W5500 para conectar o Esp32 via RJ45 na rede mas ainda não implementei !!!
#### Sugestões são bem vindas e espero que este repositório ajude em partes de projetos de outras pessoas.
#### PY2 RHJ       
#### ID DMR:7245251          
###  Rubens Hübner Junior 
### 73's
 

