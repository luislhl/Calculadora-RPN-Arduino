#include <StackArray.h>

char keymap[4][4] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

StackArray <int> stack;

int displayValue = 0;

void setup() {
  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
   
  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  
  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();

}

void loop() {
  for (int ti = 3; ti<7; ti++)
    {
    //Alterna o estado dos pinos das linhas
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    digitalWrite(ti, HIGH);
    //Verifica se alguma tecla da coluna 1 foi pressionada
    if (digitalRead(8) == HIGH)
    {
      while(digitalRead(8) == HIGH){}
      handle_input(keymap[ti-3][0]);
    }
 
    //Verifica se alguma tecla da coluna 2 foi pressionada   
    if (digitalRead(9) == HIGH)
    {
      while(digitalRead(9) == HIGH){};
      handle_input(keymap[ti-3][1]);
    }
     
    //Verifica se alguma tecla da coluna 3 foi pressionada
    if (digitalRead(10) == HIGH)
    {
      while(digitalRead(10) == HIGH){}
      handle_input(keymap[ti-3][2]);
    }
     
    //Verifica se alguma tecla da coluna 4 foi pressionada
    if (digitalRead(11) == HIGH)
    {
      while(digitalRead(11) == HIGH){}
      handle_input(keymap[ti-3][3]);
    }
   }
   delay(10);

}

void printDisplay(){
  Serial.print("Display: ");
  Serial.print(displayValue);
  Serial.println();
}

void numberInput(int input){
  displayValue = 10*displayValue + input;
  printDisplay();
}

void pushToStack(){
  stack.push(displayValue);
  displayValue = 0;
  printDisplay();
}

void addFromStack(){
  int val1 = stack.pop();
  int val2 = stack.pop();
  
  int soma = val1 + val2;
  stack.push(soma);
  displayValue = soma;
  printDisplay();
}

void subFromStack(){
  int val1 = stack.pop();
  int val2 = stack.pop();
  
  int sub = val1 - val2;
  stack.push(sub);
  displayValue = sub;
  printDisplay();
}

void multFromStack(){
  int val1 = stack.pop();
  int val2 = stack.pop();
  
  int mult = val1*val2;
  stack.push(mult);
  displayValue = mult;
  printDisplay();
}

void divideFromStack(){
  int val1 = stack.pop();
  int val2 = stack.pop();
  
  int div = val1/val2;
  stack.push(div);
  displayValue = div;
  printDisplay();
}

void handle_input(char input){
    int inp = int(input) - int('0');
    if(inp >= 0 && inp < 10)
        numberInput(inp);
    else if (input == '#')
        pushToStack();
    else if (input == 'A')
        addFromStack();
    else if (input == 'B')
        subFromStack();
    else if (input == 'C')
        multFromStack();
    else if (input == 'D')
        divideFromStack();
}
