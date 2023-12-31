#include<vector>
#include<string>
#include<iostream>
#include<stack>
#include<utility>

using namespace std;


int getMapSize(){
  int c = 0;
  while(c < 4 || c > 64){
    cout << "Enter board size (between 4 and 64): ";
    cin >> c;
  }
  return c;
}

int getNumMines(int s){
  int n = 0;
  while(n < 1 || n > s * s - 9){
    cout << "Enter number of mines " << "(between 1 and " << s * s - 9 << "): ";
    cin >> n;
  }
  return n;
}

vector<vector<char>> initializeBoard(int map_size){
  vector<vector<char>> board(map_size, vector<char>(map_size, '*'));
  return board;
}

bool checkNeighbors(int x1, int y1, int xin, int yin){
  return (xin == x1 && yin == y1) || 
         (xin == x1 - 1 && yin == y1 - 1) ||
         (xin == x1 - 1 && yin == y1) ||
         (xin == x1 - 1 && yin == y1 + 1) ||
         (xin == x1 && yin == y1 - 1) ||
         (xin == x1 && yin == y1) ||
         (xin == x1 && yin == y1 + 1) ||
         (xin == x1 + 1 && yin == y1 - 1) ||
         (xin == x1 + 1 && yin == y1) ||
         (xin == x1 + 1 && yin == y1 + 1);
}

vector<vector<bool>> getMines(int x1, int y1, int map_size, int num_mines){
  vector<vector<bool>> mines(map_size, vector<bool>(map_size, false));
  srand((unsigned) time(NULL));
  int mines_added = 0;
  while(mines_added < num_mines){
    int random_x =  (rand() % (map_size));
    int random_y =  (rand() % (map_size));
    if(!mines[random_x][random_y] && !checkNeighbors(x1, y1, random_x, random_y)){
      mines[random_x][random_y] = true;
      mines_added++;
    }
  }
  return mines;
}


bool isValid(int x, int y, int map_size){
  return !(x >= map_size || y >= map_size || x < 0 || y < 0);
}

vector<vector<int>> assignValues(int map_size, vector<vector<bool>>& mines){ //assign character values that are the 'revealed' versions of all locations on the map 
  vector<vector<int>> actual(map_size, vector<int>(map_size, 0));
  
  //if mine then -1, otherwise count all adjacent squares
  for(int i = 0; i < map_size; i++){
    for(int j = 0; j < map_size; j++){
      if(mines[i][j]){
        actual[i][j] = -1;
        continue;
      }

      //check adjacent nodes
      if(isValid(i - 1, j - 1, map_size)){
        if(mines[i - 1][j - 1]){
          actual[i][j]++;
        }
      }

      if(isValid(i - 1, j, map_size)){
        if(mines[i - 1][j]){
          actual[i][j]++;
        }
      }

      if(isValid(i - 1, j + 1, map_size)){
        if(mines[i - 1][j + 1]){
          actual[i][j]++;
        }
      }

      if(isValid(i, j - 1, map_size)){
        if(mines[i][j - 1]){
          actual[i][j]++;
        }
      }

      if(isValid(i, j + 1, map_size)){
        if(mines[i][j + 1]){
          actual[i][j]++;
        }
      }

      if(isValid(i + 1, j - 1, map_size)){
        if(mines[i + 1][j - 1]){
          actual[i][j]++;
        }
     }

     if(isValid(i + 1, j, map_size)){
        if(mines[i + 1][j]){
          actual[i][j]++;
        }
     }

     if(isValid(i + 1, j + 1, map_size)){
        if(mines[i + 1][j + 1]){
          actual[i][j]++;
        }
      }      
    }
  }
  return actual;
}

bool getInputFlag(int& row, int& col, int map_size){
  int a = -1;
  int b = -1; 
  bool output = false;
  string c;
  while(!isValid(a,b,map_size)){
    output = false;
    cout << "Enter row col (add f for flag): ";
    cin >> a >> b;
    getline(cin, c);
    string::iterator end_pos = remove(c.begin(), c.end(), ' ');
    c.erase(end_pos, c.end());
    if(c == "f"){
      output = true;
    } else if(c != ""){
        a = -1;
    }
    cout << endl;
  }

  row = a;
  col = b;
  return output;
}

void getInput(int& row, int& col, int map_size){
  int a = -1;
  int b = -1;
  while(!isValid(a,b,map_size)){
    cout << "Enter row col (first move): ";
    cin >> a >> b;
    cout << endl;
  }
  row = a;
  col = b;
}

void printBoard(vector<vector<char>>& board, int map_size){
  cout << "Current Board: " << endl;
  for(int i = 0; i < map_size; i++){
    for(int j = 0; j < map_size; j++){
      cout <<  board[i][j] << " ";
    }
    cout << endl;
  }
}


void revealSelectionRec(int x, int y, int map_size, vector<vector<char>>& board, vector<vector<int>>& actual, vector<vector<bool>>& mines, int& remaining){
  if(!isValid(x, y, map_size) || mines[x][y] || (board[x][y] != '*' && board[x][y] != 'f')){
    return;
  }
  
  remaining--;
  board[x][y] = (char) (actual[x][y] + '0');
  if(actual[x][y] == 0){
    revealSelectionRec(x - 1, y - 1, map_size, board, actual, mines, remaining);
    revealSelectionRec(x - 1, y, map_size, board, actual, mines, remaining);
    revealSelectionRec(x - 1, y + 1, map_size, board, actual, mines, remaining);
    revealSelectionRec(x, y - 1, map_size, board, actual, mines, remaining);
    revealSelectionRec(x, y + 1, map_size, board, actual, mines, remaining);
    revealSelectionRec(x + 1, y - 1, map_size, board, actual, mines, remaining);
    revealSelectionRec(x + 1, y, map_size, board, actual, mines, remaining);
    revealSelectionRec(x + 1, y + 1, map_size, board, actual, mines, remaining);
  }
}

void revealSelectionIter(int x, int y, int map_size, vector<vector<char>>& board, vector<vector<int>>& actual, vector<vector<bool>>& mines, int& remaining){
  stack<pair<int,int>> s;
  s.push({x,y});

  while(!s.empty()){
    int xval = s.top().first;
    int yval = s.top().second;
    s.pop();

    if(!(!isValid(xval, yval, map_size) || mines[xval][yval] || (board[xval][yval] != '*' && board[xval][yval] != 'f'))){
      remaining--;
      board[xval][yval] = (char) (actual[xval][yval] + '0');
      if(actual[xval][yval] == 0){
        s.push({xval - 1, yval - 1});
        s.push({xval - 1, yval});
        s.push({xval - 1, yval + 1});
        s.push({xval, yval - 1});
        s.push({xval, yval + 1});
        s.push({xval + 1, yval - 1});
        s.push({xval + 1, yval});
        s.push({xval + 1, yval + 1});
      }
    }
  }
}
 

void gameLoop(int xin, int yin, int map_size, int num_mines, vector<vector<int>>& actual, vector<vector<char>>& board, vector<vector<bool>>& mines){
  int remaining_tiles = map_size * map_size - num_mines; 
  bool first = true;
  bool isFlag = false;
  for(;;){
    if(!first){
      isFlag = getInputFlag(xin, yin, map_size); 
    } 
    first = false;

    //reveal selection
    if(!isFlag){
      if(board[xin][yin] == 'f'){
        cout << "Remove Flag" << endl;
        continue;
      }
      if(mines[xin][yin]){
        board[xin][yin] = 'X';
        printBoard(board, map_size);
        cout << "You Lose" << endl;
        break;
      } 
      revealSelectionIter(xin, yin, map_size, board, actual, mines, remaining_tiles); 
      if(remaining_tiles <= 0){
        printBoard(board, map_size);
        cout << "You Win" << endl;
        break;
      } 
    } else {
        if(board[xin][yin] == '*'){
          board[xin][yin] = 'f';
        } else if(board[xin][yin] == 'f'){
          board[xin][yin] = '*';
        }
     } 

    printBoard(board, map_size);
  }
}


//debugging functions

void printMines(vector<vector<bool>>& mines){
  cout << "Mines map: " << endl;
  for(int i = 0; i < mines.size(); i++){
    for(int j = 0; j < mines[0].size(); j++){
      if(mines[i][j]){
        cout << "T ";
      } else {
        cout << "F ";
      }
    }
    cout << endl;
  }
}

void printActual(vector<vector<int>>& actual){
  cout << "Actual map: " << endl;
  for(int i = 0; i < actual.size(); i++){
    for(int j = 0; j < actual[0].size(); j++){
      cout << actual[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
  int map_size = getMapSize();
  int num_mines = getNumMines(map_size);
  int x1,y1;

  vector<vector<char>> board = initializeBoard(map_size);   
  printBoard(board, map_size);
  getInput(x1, y1, map_size); 
  vector<vector<bool>> mines = getMines(x1, y1, map_size, num_mines);
  //printMines(mines);
  vector<vector<int>> actual = assignValues(map_size, mines); 
  //printActual(actual);
  
  gameLoop(x1, y1, map_size, num_mines, actual, board, mines);
  
  return 0;
}

