### Trabalho final de Redes de Computadores

1. Execute o server.py:
``` bash
python server.py
```
2. Abra um túnel na porta especificada no código:
```bash
ariane@pop-os:~$ ssh -4 -p 443 -R0:localhost:5050 tcp@a.pinggy.io
``` 
3. Copie um IP e uma porta que aparecer na tela após o comando anterior e cole no codigo da esp8266 em IP e PORTA. Altere também a rede e senha para que a placa consiga se conectar.
4. Grave o código na placa e estará rodando.

### Referências
https://pt.stackoverflow.com/questions/22719/cliente-servidor-windows-com-sockets-em-c
https://learn.microsoft.com/pt-br/dotnet/fundamentals/networking/sockets/socket-services
https://realpython.com/python-sockets/
https://www.makerhero.com/blog/monitorando-temperatura-e-umidade-com-o-sensor-dht11/?srsltid=AfmBOopKysBBdVaojCd6P5kBTdBduyq4wSqUO030Rng2LKO5US-78Hw7
https://www.w3schools.com/python/default.asp
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
https://medium.com/desenvolvendo-com-paixao/ngrok-do-localhost-para-o-mundo-5445ad08419
https://www.reddit.com/r/securityCTF/comments/1j8kiq2/alternative_for_ngrok/
https://pinggy.io/blog/local_tunnel/