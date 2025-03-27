# Esp32_WebServer
#### Este projeto visa dar exemplo de como fazer o Esp32 trabalhar como um servidor de pagina Web e um servidor de websocket.
#### Para seguir este tutorial é nescessário o conhecimento de como usar a IDE do Arduino para gravar o Esp32.
#### É neceesário fazer o upload da pasta "data" que está junto com o arquivo web01.ino (estar junto é mandatório) para a memória SPIFFS do Esp32 conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/data.jpg)
#### Para isto precisamos descompactar o arquivo ESPFS.Zip e colar na pasta na instalação da IDE do arduino conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/tools.jpg)
#### Depois disto a IDE do Arduino passará a apresentar a opção conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/upload.jpg)
#### A montagem para teste pode ser visto na imagem abaixo do lado esquerdo do protoboard:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/esp_web.jpg)
#### Como se trata de um circuito simples os pinos utilizados está nos comenários do arquivo web01.ino.
#### Olhando o diagrama simplificado temos uma ideia geral de como funciona o sistema:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/Diagrama_01.jpg)
#### A pasta "data" que foi gravada na memória SPIFFS tem os arquivos do Front End ( HTML,CSS, Javascript).
#### Quando o navegador faz o Request o servidor de pagina Web envia os arquivos da pasta data para o navegador.
#### Com estes arquivos o navegador exibi a GUI (Graphical User Interface ou Interface Gráfica do Usuário) conforme imagem abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/Esp32_WebServer/blob/main/gui.jpg)
#### Além da GUI também é criado no navegador um cliente de webSocket e uma lógica para enviar e receber as mensagens e mostrar o status na GUI.
#### As mensagens trocadas entre o Esp32 e o Navegador estão no formato JSON para uma melhor escalabilidade.
#### O display LCD usa o protocolo I2C para economia de pinos que poderão ser usados futuramente.
#### Todas as bibliotecas usadas estão dentro da pasta bibliotecas.
#### Como estamos usando webSocket para trocar mensagens o navegador não precisa dar refresh na página para atualizar
### Observar que o webSocket é assincrono e portanto é acionado quando ocorre eventos.
#### O código web01.ino está bem comentado e seguindo as chamadas das funções a partir do setup() e depois a partir do loop() é possivel identificar as funcionalidades conforme o diagrama.

#### Sugestões são bem vindas e espero que este repositório ajude em partes de projetos de outras pessoas.
### PY2 RHJ
 

