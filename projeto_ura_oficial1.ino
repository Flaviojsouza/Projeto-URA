#include <LiquidCrystal.h> // Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 13, 7, 6, 5, 4); // Pinagem do LCD

int botaoA=8;
int botaoB=10;
int botaoC=11;
int ledverde=3;
int ledvermelho=2;
int estado_botaoA = 0;
int estado_botaoB = 0;
int estado_botaoC = 0;
int tela=1;
int sorteio=15;
int certo=0;
int errado=0;
bool bug=false;

void setup()
{
  lcd.begin(16, 2); // Inicia o lcd de 16x2
  
  //Declaramos que o botão irá ser do tipo entrada.
  pinMode(botaoA, INPUT);
  pinMode(botaoB, INPUT);
  //Led usará a porta do tipo saída. 
  pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);

}

void loop(){
  if(tela==1){//start: tela inicial
    bug=true;
  	Inicio();
  }else if(tela==2){// Tela de escolha das operações
	Operacao();
  }else if(tela==3){ //Tela de Resposta errada(dualidade)
    continuar();   
  }else if(tela==4){// Tela de sorteio de alocação de resposta
    visual_resp();
  }else if(tela==5){//tela de verificação de resposta e leds
    Verificar_resp();
  }else if(tela==6){ //soma
    soma();
  }else if(tela==7){ //game over
  	fim();
  }else if(tela==8){ //decisão da tela de continuar(tela=3);
    if(Status_botoes() == 'A'){
      tela=2;
    }else if(Status_botoes() == 'B'){
      if(bug==true){
      	tela=2;
      }else{
        tela=7;
      }
  	}  
  }else if(tela==9){
  	multiplicacao();
  }else if(tela==10){
  	subtracao();
  }else if(tela==11){
  	divisao();
  }
}

char Status_botoes(){ //leitura do estado do botao
  estado_botaoA = digitalRead(botaoA);
  estado_botaoB = digitalRead(botaoB);
  
  if (estado_botaoA==true){
  	return 'A';
  }
  else if(estado_botaoB==true){
  	return 'B';
  }
  else{
  	return 'O';
  }
}

void Operacao(){ //tela 02: operações
	int x = rand()%3;
  	//int x = 3;
  	bug=false;
  if(x==0){ //soma
  	tela=6;
  }
  else if(x==1){//multiplicação
  	tela=9;
  }
  else if(x==2){//subtração
  	tela=10;
  }else if(x==3){//divisão
  	tela=11;
  }
}

void continuar(){ //tela 03: fim ou recomeço do jogo
  lcd.clear(); 
  lcd.setCursor(1, 0);
  lcd.print("Erro:Continuar?");                 
  lcd.setCursor(2, 1);      
  lcd.print("1)Sim  2)Nao");
  delay(150);
  tela=8;
}

void Inicio(){ //tela 01: inicio
  lcd.clear(); 
  lcd.setCursor(1, 0);
  lcd.print("Jogar ?");    
  lcd.setCursor(2, 4);      
  lcd.print(" 1)Inicio");
    
  tela=8;
}

void soma(){ //Recurso Soma
  int x = num_aleatorio(10);
  int y = num_aleatorio(10);
  certo=x+y;
  errado=certo+(num_aleatorio(4));
  
  lcd.clear();  
  lcd.setCursor(2, 0);      
  lcd.print(String(x) + "+" + String(y)+" =  ? ");
  delay(150);
  
  tela=4;  
}

void Verificar_resp(){ // verifica resposta e led
  if(Status_botoes() == 'A'){ 
    if(sorteio==0){ //caso A sejá a correta, sorteio==0
	  greenLed();
      tela=2;
    }else{
	  redLed();
      tela=3;
    }
  }else if(Status_botoes() == 'B'){
  	if(sorteio==1){
      greenLed();      
      tela=2;
    }else{
	  redLed(); 
      tela=3;
    } 
  }
}
void visual_resp(){
  sorteio = rand()%2; //Sorteia o btn q recebe a resposta certa
  //0 corresponde ao btnA e 1 ao btnB
  
  if(sorteio==0){ //btn A recebe resposta correta 
    lcd.setCursor(2, 1);    
    lcd.print("A)");
    lcd.print(certo);
    lcd.print("  B)");
    lcd.print(errado);
  
  }else if(sorteio==1){ //btn B recebe resposta correta 
    lcd.setCursor(2, 1);  
    lcd.print("A)");
    lcd.print(errado);
    lcd.print(" B)");
    lcd.print(certo);
  }
  tela=5;
}

//Procedimentos;
void greenLed(){	//controla o led verde
  digitalWrite(ledverde, HIGH);
  delay(300);
  digitalWrite(ledverde, LOW);	
}
void redLed(){		//controla o led vermelho
  digitalWrite(ledvermelho, HIGH);
  delay(300);
  digitalWrite(ledvermelho, LOW);	
}
void fim(){		//tela de fim de jogo
  lcd.clear(); 
  lcd.setCursor(1, 0);
  lcd.print("Game Over");
  delay(2000);
  tela=1;
}
int num_aleatorio(int d){
	int a=rand()%d;
  for(;a==0;){
  	a=rand()%d;
  }
  return a;
}
void multiplicacao(){ //Recurso Soma
  int x = num_aleatorio(10);
  int y = num_aleatorio(10);
  certo=x*y;
  errado=certo+(num_aleatorio(4));
  
  lcd.clear();  
  lcd.setCursor(2, 0);      
  lcd.print(String(x) + "x" + String(y)+" =  ? ");
  delay(150);
  
  tela=4;  
}
void subtracao(){ //Recurso Soma
  int x = num_aleatorio(10);
  int y = num_aleatorio(10);
  certo=x-y;
  errado=certo+(num_aleatorio(4));
  
  lcd.clear();  
  lcd.setCursor(2, 0);      
  lcd.print(String(x) + "-" + String(y)+" =  ? ");
  delay(150);
  
  tela=4;  
}
void divisao(){ //Recurso Soma
  int x = num_aleatorio(10);
  int y = num_aleatorio(10);
  certo=(float)x/y;
  errado=certo+float(num_aleatorio(4));
  
  lcd.clear();  
  lcd.setCursor(2, 0);      
  lcd.print(String(x) + "/" + String(y)+" =  ? ");
  delay(150);
  
  tela=4;  
}