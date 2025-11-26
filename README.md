
#Projeto ELGIN 

Este projeto demonstra o uso de uma impressora fiscal Elgin para emitir notas fiscais e executar funções essenciais, como:	

Impressão de texto 

Corte de papel

Impressão de QR Code

Impressão de código de barras

Abertura de gaveta

Impressão de XML SAT

Impressão de XML Cancelado SAT


O projeto foi desenvolvido totalmente em Linguagem C.

#Instalação e Configuração

1. Baixe o projeto

Faça o download da pasta C Aluno completa que esta no repertorio.

2. Abra o projeto

Abra o arquivo principal:

projeto.c

3. Configure a conexão

No início do programa, ajuste:
	•	Porta da impressora
	•	Tipo de comunicação (USB / MODELO)

#Como Executar

Após a compilação

Dentro da aplicação:
	1.	Configurar conexão
	2.	Abrir conexão com a impressora
	3.	Selecionar e executar uma das funções:

	•	 Imprimir texto
	•	 Cortar papel
	•	 Imprimir XML SAT
	•	 Imprimir XML Canc. SAT
	•	 Imprimir código de barras
	•	 Imprimir QR Code
	•	 Abrir gaveta

⸻

#Exemplos de Funções (em C)

// Exemplo de impressão simples
ImprimirTexto("Exemplo de impressão na Elgin");

// Exemplo de corte
CortarPapel();

// Exemplo de QR Code
ImprimirQRCode("https://exemplo.com");

// Exemplo de abrir gaveta
AbrirGaveta();

#Documentação Oficial

Para funções mais avançadas, consulte o manual da impressora Elgin.

#Contribuição

Contribuições são bem-vindas!
Sinta-se livre para melhorar o código, adicionar funções ou propor ajustes.



