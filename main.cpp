#include <iostream>
#include <stdlib.h>//Biblioteca que possui a função de limpar o console
#include <cstdlib>//Biblioteca que possui a função de gerar um número aleatório
#include <ctime>//Biblioteca que pode pegar o horário atual da máquina
#include <vector>//Biblioteca que possui a classe vector, onde posso usar os métodos para array

using namespace std;

//Macro que contém a função de limpar o console.
#define clearConsole (void)system("clear||cls");
#define space cout << endl;

/*....VARIÁVEIS GLOBAIS....*/
//Assim eu faço um vetor de vetor, ou uma matriz de vetores. No caso fiz uma matriz 3x3
vector <vector <char>> gameVet{{'[', ' ', ']', '[', ' ', ']', '[', ' ', ']'},{'[', ' ', ']', '[', ' ', ']', '[', ' ', ']'},{'[', ' ', ']', '[', ' ', ']', '[', ' ', ']'}};
/*........................*/


//Função que gera um número aleatório entre 0 e o número fornecido no parâmetro
int randomInt(int x){
  srand(time(nullptr));
  int result;

  result = rand() % x;

  return result;
}


//Reseta as posições jogáveis
void resetGameVet(){
  gameVet.at(0).at(1) = ' ';
  gameVet.at(0).at(4) = ' ';
  gameVet.at(0).at(7) = ' ';
  gameVet.at(1).at(1) = ' ';
  gameVet.at(1).at(4) = ' ';
  gameVet.at(1).at(7) = ' ';
  gameVet.at(2).at(1) = ' ';
  gameVet.at(2).at(4) = ' ';
  gameVet.at(2).at(7) = ' ';
}


//Função que imprime o jogo atualizado. O argumento da função é a posição em que o jogador jogou e o caractere que deve ser usado para imprimir onde o jogador jogou, que pode ser 'X' ou 'O'.
void drawGame(int y, char z){
  switch(y){
    case 1:
      //O método at acessa um elemento em específico do vetor. Seu argumento é o index do vetor.
      gameVet.at(2).at(1) = z;//Devido eu estar usando um vetor 2d, preciso usar o at duas vezes para pegar a linha e coluna correta.
      break;

    case 2:
      gameVet.at(2).at(4) = z;
      break;

    case 3:
      gameVet.at(2).at(7) = z;
      break;

    case 4:
      gameVet.at(1).at(1) = z;
      break;

    case 5:
      gameVet.at(1).at(4) = z;
      break;

    case 6:
      gameVet.at(1).at(7) = z;
      break;

    case 7:
      gameVet.at(0).at(1) = z;
      break;

    case 8:
      gameVet.at(0).at(4) = z;
      break;

    case 9:
      gameVet.at(0).at(7) = z;
      break;

    default:
      space;
      cout << "Enter a valid position\n";
      space;
      break;
  }

  /*Aparentemente isto é necessário, pois na comparação de um int com o comprimento de uma array de char (operação .size(), que iria retornar um int como comprimento da array) é conflitante.
   Portanto, é preciso guardar este comprimento numa variável int*/
  int arrayWidth = gameVet.size();
  int arrayHeight;
   
  for(int i = 0; i < arrayWidth; i++){
    arrayHeight = gameVet[i].size();
    for(int j = 0; j < arrayHeight; j++){
      cout << gameVet[i][j];
    }
    cout << endl;
  }
}


//Declara as condições de vitória, cujo parâmetros são as linhas, colunas e o caractere em questão.
bool endGame(int lineA, int lineB, int lineC, int columnA, int columnB, int columnC, char symbol){
  if(gameVet.at(lineA).at(columnA) == symbol && gameVet.at(lineB).at(columnB) == symbol && gameVet.at(lineC).at(columnC) == symbol){
    return true;
  }else{
    return false;
  }
}


//Verifica se o jogo tem um vencedor com uma das combinações possíveis
bool hasWinner(){
  if(endGame(0,0,0,1,4,7,'X') || endGame(1,1,1,1,4,7,'X') || endGame(2,2,2,1,4,7,'X') || endGame(0,1,2,1,1,1,'X') || 
      endGame(0,1,2,4,4,4,'X') || endGame(0,1,2,7,7,7,'X') || endGame(0,1,2,1,4,7,'X') || endGame(0,1,2,7,4,1,'X')){
    cout << "Player X win!\n";
    return true;
  }else if(endGame(0,0,0,1,4,7,'O') || endGame(1,1,1,1,4,7,'O') || endGame(2,2,2,1,4,7,'O') || endGame(0,1,2,1,1,1,'O') || 
      endGame(0,1,2,4,4,4,'O') || endGame(0,1,2,7,7,7,'O') || endGame(0,1,2,1,4,7,'O') || endGame(0,1,2,7,4,1,'O')){
    cout << "Player O win!\n";
    return true;
  }else{
    return false;
  }
}


//Verifica se a posição escolhida já está ocupada.
bool verifyPositionIsTaken(int choosePosition, vector <int> tempVector){
  if(choosePosition < 10 && choosePosition > 0){
    int tempVectorLength = tempVector.size();
    for(int i = 0; i < tempVectorLength; i++){
      if(choosePosition == tempVector[i]){
        cout << "Position already chosen or invalid\n";
        return true;
        break;
      }
    }
    return false;
  }else{
    return false;
  }
}


int cpuTurn(int choosePosition, vector <int> tempVector){
  do{
    choosePosition = randomInt(9);
    verifyPositionIsTaken(choosePosition,tempVector);
  }while(verifyPositionIsTaken(choosePosition,tempVector));
  return choosePosition;
}


void game(){
  clearConsole;
  int round = 1;//Guarda a rodada atual do jogo e define qual o jogador deve jogar
  int position = 0;//Guarda a posição escolhida pelo jogador.
  char symbol = '#';//Guarda qual caractere deve ser usado para a rodada do jogo
  vector <int> tempVet;//Guarda as posições já escolhidas pelo jogador.
  
  
  drawGame(position, symbol);
  do{
    do{
      cin >> position;
      verifyPositionIsTaken(position,tempVet);
    }while(verifyPositionIsTaken(position,tempVet));
    
    tempVet.push_back(position);//Adicionar a posição em que o usuário escolheu no vetor temporário
    // cpuTurn(position,tempVet);
    // tempVet.push_back(position);
    clearConsole;
    
    //Se o jogador for impar, ele é o X, se for par, é o O
    if(round % 2 == 0){
      symbol = 'O';
    }else{
      symbol = 'X';
    }
    
    drawGame(position, symbol);
    space;
    round++;
  }while(hasWinner() == false && round <= 9);

  if(round >= 10){
    cout << "Draw!\n";
  }

  //POST GAME
  space;
  space;
  cout << "Do you want to play again?\n1 - Yes\n2 - No\n";
  int option = 0;
  cin >> option;
  if(option == 1){
    tempVet.clear();
    clearConsole;
    round = 1;
    resetGameVet();
    game();
  }else{
    cout << "Obrigado por jogar!\n";
  }
}


int main(){
  game();
  return 0;
}
