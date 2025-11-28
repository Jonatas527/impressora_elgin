🖨️ Projeto ELGIN
(Coloque aqui o nome do seu projeto)
📘 Sobre o Projeto

Este projeto demonstra o uso de uma impressora fiscal Elgin para realizar operações essenciais de impressão, tais como:

Impressão de texto

Corte de papel

Impressão de QR Code

Impressão de código de barras

Abertura de gaveta

Impressão de XML SAT

Impressão de XML Cancelado SAT

O desenvolvimento foi realizado totalmente em Linguagem C, com foco em aplicações fiscais e automação comercial.

🧰 Tecnologias Utilizadas

Linguagem C

SDK / Driver Elgin

Ferramentas de compilação C (GCC / MinGW / etc.)

(Opcional) Bibliotecas auxiliares para comunicação

📁 Estrutura do Projeto

/C Aluno → Pasta principal contendo o código
/projeto.c → Arquivo-fonte principal
/include → Cabeçalhos e dependências
/docs → Manuais e materiais de apoio
/examples → Exemplos de uso das funções

⚙️ Instalação e Configuração
🔽 1. Baixar o Projeto

Acesse o repositório.

Clique em Code.

Selecione Download ZIP.

Aguarde o download.

📦 2. Extrair o Arquivo ZIP

Localize o arquivo baixado.

Clique com o botão direito → Extrair aqui / Extract All.

Uma pasta contendo os arquivos será criada.

🧭 3. Abrir o Projeto

Abra seu editor/IDE de C preferido.

Abra o arquivo principal:
projeto.c

🔗 4. Configurar a Conexão

No início do programa, configure:

Porta da impressora

Tipo de comunicação (TIPO / MODELO / PARÂMETRO)

🧪 Testes

Configuração da porta de comunicação

Abertura de conexão com a impressora

Impressão de texto simples

Corte de papel

Impressão de XML SAT e XML Cancelado

Impressão de código de barras e QR Code

Teste de abertura de gaveta

🖥️ Como Executar

Após compilar o projeto:

Configurar conexão

Abrir conexão com a impressora

Selecionar uma das funções disponíveis:

Imprimir texto

Cortar papel

Imprimir XML SAT

Imprimir XML Cancelado SAT

Imprimir código de barras

Imprimir QR Code

Abrir gaveta

🧾 Exemplos de Funções (em C)
// Exemplo de impressão simples
ImprimirTexto("Exemplo de impressão na Elgin");

// Exemplo de corte
CortarPapel();

// Exemplo de QR Code
ImprimirQRCode("https://exemplo.com");

// Exemplo de abrir gaveta
AbrirGaveta();

📚 Documentação Adicional

Manual da impressora Elgin i9

Documentação do SDK Elgin

Referência ESC/POS

👥 Autores

(em ordem alfabética)

Eliete Gomes da Silva

Gabriel de Souza Silva

João Pedro dos Santos Matos

Jônatas da Silva Siqueira

Rafael Nascimento

🤝 Contribuição

Contribuições são bem-vindas!
Sinta-se à vontade para melhorar o código, adicionar funções ou sugerir melhorias.
