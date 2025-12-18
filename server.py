import socket

HOST = "0.0.0.0"
PORTA = 5050
TEMPERATURA_MAXIMA = 35.0
TEMPERATURA_MINIMA = 30.0
TOKEN_CHECK = "KSHA627ESP"

# IP, TCP
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORTA)) #servidor no endereco host e porta

server.listen(5) # limite de conexoes

print("servidor rodando na porta " + str(PORTA))

while True:
    conexao, endereco = server.accept() # quando um cliente conecta, retorna obj conexao e o endereco
    msg = conexao.recv(1024).decode().strip() # escuta ate1024 caracteres, decode converte de Byte pra texto

    if not msg.startswith("token:"):
        print("token ausente, conexao fechada")
        conexao.close()
        continue
        
    token_recebido = msg.split("token:")[1].split(";")[0]

    if token_recebido != TOKEN_CHECK:
        print("token invalido, conexao fechada")
        conexao.close()
        continue

    dados = msg.replace(f"token:{TOKEN_CHECK};", "")
    print(f"vindo de  {endereco} \n dados:  {dados}\n")

    try:
        parte_01 = dados.split("temperatura:") #["", "x;umidade:y"]
        #print(parte_01)

        trecho_temperatura = parte_01[1]  # parte q vem depois de 'temperatura:', "x;umidade:y"
        #print(trecho_temperatura)

        separacao = trecho_temperatura.split(";")  #divide onde tem ';' o estilo é tipo json, ["x", "umidade:y"]
        #print(separacao)

        temperatura_str = separacao[0]  # valor antes de ';' ou seja a temperatura, mas em string, x
        #print(temperatura_str)

        temperatura = float(temperatura_str)  #convertendo em numero float
    except:
        temperatura = 0

    if temperatura >= TEMPERATURA_MAXIMA:
        conexao.sendall(b"TEMPERATURA_QUENTE\n") # sendall envia todos os dados de uma vez, garantia de chegada
        print("led vermelho")
    elif temperatura <= TEMPERATURA_MINIMA:
        conexao.sendall(b"TEMPERATURA_FRIA\n")
        print("led azul")
    else:
        conexao.sendall(b"TEMPERATURA_ALERTA\n") # b é pra converter pra bytes, rede trabalha em B
        print("led amarelo")

    conexao.close()