#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ======================= Config DLL ======================= */
static HMODULE g_hDll = NULL;

/* Convenção de chamada (Windows): __stdcall */
#ifndef CALLCONV
#  define CALLCONV WINAPI
#endif

/* ======================= Assinaturas da DLL ======================= */
typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
typedef int (CALLCONV *Corte_t)(int);
typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (CALLCONV *AvancaPapel_t)(int);
typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (CALLCONV *InicializaImpressora_t)(void);

/* ======================= Ponteiros ======================= */
static AbreConexaoImpressora_t        AbreConexaoImpressora        = NULL;
static FechaConexaoImpressora_t       FechaConexaoImpressora       = NULL;
static ImpressaoTexto_t               ImpressaoTexto               = NULL;
static Corte_t                        Corte                        = NULL;
static ImpressaoQRCode_t              ImpressaoQRCode              = NULL;
static ImpressaoCodigoBarras_t        ImpressaoCodigoBarras        = NULL;
static AvancaPapel_t                  AvancaPapel                  = NULL;
static AbreGavetaElgin_t              AbreGavetaElgin              = NULL;
static AbreGaveta_t                   AbreGaveta                   = NULL;
static SinalSonoro_t                  SinalSonoro                  = NULL;
static ImprimeXMLSAT_t                ImprimeXMLSAT                = NULL;
static ImprimeXMLCancelamentoSAT_t    ImprimeXMLCancelamentoSAT    = NULL;
static InicializaImpressora_t         InicializaImpressora         = NULL;

/* ======================= Configuração ======================= */
static int   g_tipo      = 1;
static char  g_modelo[64] = "i9";
static char  g_conexao[128] = "USB";
static int   g_parametro = 0;
static int   g_conectada = 0;

/* ======================= Utilidades ======================= */
#define LOAD_FN(h, name)                                                         \
    do {                                                                         \
        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
        if (!(name)) {                                                           \
            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
                    #name, GetLastError());                                      \
            return 0;                                                            \
        }                                                                        \
    } while (0)

static void flush_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ======================= Funções para manipular a DLL ======================= */
static int carregarFuncoes(void)
{
    g_hDll = LoadLibraryA("E1_Impressora01.dll");
    if (!g_hDll) {
        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
        return 0;
    }

    LOAD_FN(g_hDll, AbreConexaoImpressora);
    LOAD_FN(g_hDll, FechaConexaoImpressora);
    LOAD_FN(g_hDll, ImpressaoTexto);
    LOAD_FN(g_hDll, Corte);
    LOAD_FN(g_hDll, ImpressaoQRCode);
    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
    LOAD_FN(g_hDll, AvancaPapel);
    LOAD_FN(g_hDll, AbreGavetaElgin);
    LOAD_FN(g_hDll, AbreGaveta);
    LOAD_FN(g_hDll, SinalSonoro);
    LOAD_FN(g_hDll, ImprimeXMLSAT);
    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
    LOAD_FN(g_hDll, InicializaImpressora);

    return 1;
}

static void liberarBiblioteca(void)
{
    if (g_hDll) {
        FreeLibrary(g_hDll);
        g_hDll = NULL;
    }
}

/* ======================= Funções a serem implementadas pelos alunos ======================= */

static void exibirMenu()
{
    printf("--------------MENU---------------\n");
	printf("1 - Configurar Conexao\n");
    printf("2 - Abrir Conexao\n");
    printf("3 - Impressao Texto\n");
    printf("4 - Impressao QRCode\n");
    printf("5 - Impressao Cod Barras\n");
    printf("6 - Impressao XML SAT\n");
    printf("7 - Impressao XML Canc SAT\n");
    printf("8 - Abrir Gaveta Elgin\n");
    printf("9 - Abrir Gaveta\n");
    printf("10 - Sinal Sonoro\n");
    printf("0 - Fechar Conexao e Sair\n");
    
}

static void configurarConexao(void)
{
	int tipo, parametro;
	char modelo[64];
	char conexao[128];
	
	
	printf("Informe o tipo : \n");
	scanf("%i",&g_tipo);
	
	printf("Informe o modelo : \n");
	scanf("%s",&g_modelo);
	
	printf("Informe o conexão : \n");
	scanf("%s",&g_conexao);
	
	printf("Informe o parâmetro : \n");
	scanf("%i",&g_parametro);
	
	printf("Dados salvados com sucesso\n");
	
	
    // TODO: pedir ao usuário tipo, modelo, conexão e parâmetro
}

static void abrirConexao(void)
{
    printf("tipo=%d\n  modelo=%s\n  conexao=%s\n  parametro=%d\n",g_tipo, g_modelo, g_conexao, g_parametro);

    if (g_conectada == 1) {
        printf("Já existe conexão aberta.\n");
        return;
    }

    int ret = AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);

    printf("RETORNO AbreConexaoImpressora = %d\n", ret);

    if (ret == 0) {
        InicializaImpressora();
        g_conectada = 1;
        printf("Conexao aberta com sucesso.\n");
    } else {
        printf("Falha ao abrir conexão. Retorno = %d\n", ret);
    }
}


static void fecharConexao(void)
{
    if (g_conectada == 0) {
        printf("Nao ha conexao aberta.\n");
        return;
    }

    int ret = FechaConexaoImpressora();

    if (ret == 0) {
    	g_conectada = 0;
    	printf("Conexao fechada.\n");
    } else {
        printf("Erro ao fechar conexão. Código retornado: %d\n", ret);
    }
}


static void imprimirTexto(void)
{
	
	if (g_conectada == 0) {
        printf("Abra conexão primeiro.\n");
        return;
    }

    int ret = ImpressaoTexto("Teste",1,4,0);
    AvancaPapel(2);

    printf("RETORNO AbreConexaoImpressora = %d\n", ret);

    if (ret == 0) {
        //InicializaImpressora();
        printf("Texto impresso com sucesso.\n");
    } else {
        printf("Falha ao imprimir teste. Retorno = %d\n", ret);
    }
    
    // TODO: solicitar texto do usuário e chamar ImpressaoTexto
    // incluir AvancaPapel e Corte no final
}

static void imprimirQRCode(void)
{
	if (g_conectada == 0) {
        printf("Abra conexão primeiro.\n");
        return;
    }

    int ret = ImpressaoQRCode("teste", 6, 4);

    if (ret == 0) {
       
        printf("Impressao OK");
    } else {
        printf("Falha ao imprimir. Retorno = %d\n", ret);
    }
    
    // TODO: solicitar conteúdo do QRCode e chamar ImpressaoQRCode(texto, 6, 4)
    // incluir AvancaPapel e Corte no final
}

static void imprimirCodigoBarras(void)
{
	
	if (g_conectada == 0) {
        printf("Abra conexao primeiro.\n");
        return;
    }

    int ret = ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);

    if (ret == 0) {
        
        printf("Codigo de barras impresso com sucesso.\n");
    } else {
        printf("Falha ao imprimir Codigo de barras. Retorno = %d\n", ret);
    }
    
    // TODO: usar ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3)
    // incluir AvancaPapel e Corte no final
}

static void imprimirXMLSAT(void)
{
	
	if (g_conectada == 0) {
    	printf("Abra conexão primeiro.\n");
        return;
    }
	
	
	const char* dados = "path=./XMLSAT.xml";

		
    int ret = ImprimeXMLSAT(dados,0);


    if (ret == 0) {
       
        printf("XMlSat impresso com sucesso.\n");
    } else {
        printf("Falha ao imprimir XMLSat. Retorno = %d\n", ret);
    }
    // TODO: ler o arquivo ./XMLSAT.xml e enviar via ImprimeXMLSAT
    // incluir AvancaPapel e Corte no final
}

static void imprimirXMLCancelamentoSAT(void)
{
	if (g_conectada == 0) {
    	printf("Abra conexão primeiro.\n");
        return;
    }
	
	const char* dados = "path=./CANC_SAT.xml";
	const char* assQRCode = "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";
		
    int ret = ImprimeXMLCancelamentoSAT(dados,assQRCode,0);

  

    if (ret == 1) {
       
        printf("Codigo de XMLSat cancelado com sucesso.\n");
    } else {
        printf("Falha ao cancelar XMLSat. Retorno = %d\n", ret);
    }
	
    // TODO: ler o arquivo ./CANC_SAT.xml e chamar ImprimeXMLCancelamentoSAT
    // incluir AvancaPapel e Corte no final
    
	/*usar assinatura abaixo:
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";
        */
}

static void abrirGavetaElginOpc(void)
{
	if (g_conectada == 0) {
    	printf("Abra conexão primeiro.\n");
        return;
    }
	
    int ret = AbreGavetaElgin(1, 50, 50);


    if (ret == 0) {
        printf("Gaveta Elgin aberta com sucesso.\n");
    } else {
        printf("Falha ao abrir gaveta Elgin. Retorno = %d\n", ret);
    }
    // TODO: chamar AbreGavetaElgin(1, 50, 50)
}

static void abrirGavetaOpc(void)
{
	if (g_conectada == 0) {
    	printf("Abra conexão primeiro.\n");
        return;
    }
	
    int ret = AbreGaveta(1, 5, 10);


    if (ret == 0) {
        printf("Gaveta aberta com sucesso.\n");
    } else {
        printf("Falha ao abrir gaveta. Retorno = %d\n", ret);
    }
    // TODO: chamar AbreGaveta(1, 5, 10)
}

static void emitirSinalSonoro(void)
{
	if (g_conectada == 0) {
    	printf("Abra conexão primeiro.\n");
        return;
    }
	
    int ret = SinalSonoro(4, 50, 5);

    if (ret == 0) {
        printf("Sinal sonoro emitido com sucesso.\n");
    } else {
        printf("Falha ao emitir sonoro. Retorno = %d\n", ret);
    }
    // TODO: chamar SinalSonoro(4, 50, 5)
}

/* ======================= Função principal ======================= */
int main(void)
{
    if (!carregarFuncoes()) {
        return 1;
    }

    int x;
    
    while (1) {
        exibirMenu();
        printf("");
    	scanf("%i",&x);
    	
    	if ( g_conectada == 0){
    		FechaConexaoImpressora();
    	}
        
    switch(x) {
    	
    	case 1:
    		configurarConexao();
    		break;
    	case 2:
    		abrirConexao();	
    		break;
    	case 3:
    		imprimirTexto();
    		Corte(3);
    		break;
    	case 4:
    		imprimirQRCode();
    		Corte(3);
    		break;
    	case 5:
    		imprimirCodigoBarras();
    		Corte(3);
    		break;
    	case 6:
    		imprimirXMLSAT();
    		Corte(3);
    		break;
    	case 7:
    		imprimirXMLCancelamentoSAT();
    		Corte(3);
    		break;
    	case 8:
    		abrirGavetaElginOpc();
    		break;
    	case 9:
    		abrirGavetaOpc();
    		break;
    	case 10:
    		emitirSinalSonoro();
    		break;
    	default: printf("Opcao invalida!!\n");
    	
    	
    		
	}
        
        
    	
	}
        //construir o menu e chamar as funçoes aqui!!!
        
                
        
}
