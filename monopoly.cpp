
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
306
307
308
309
310
311
312
313
314
315
316
317
318
319
320
321
322
323
324
325
326
327
328
329
330
331
332
333
334
335
336
337
338
339
340
341
342
343
344
345
346
347
348
349
350
351
352
353
//Supreet Sandhu
//p5.cpp
//12-03-2019
//
//Purpose: This program is a game of monopoly. This game
//allows for up to six players and players start with $1500
//to use to purchase properties. Players take turns rolling
//dice and collect rent on their properties. The game ends
//when a player reaches $0.
//
//Input: the user must enter in the number of players and
//each players name
//Input: either a 'y' or 'n' if the players whose turn it
//is would like to purchase a property.
//
//Processing: The program will subtract the price
//of the property if a player wants to purchase the
//property they land on. If a player lands on another players
// property, then the rent of the property will be subtracted
//from the players who turn it is and added to the owners
//amount of money. Every time a players total spaces on the board,
//which keeps track of a players spot on the board, reaches 35 then
//their total spaces on the board will reset to one plus their
//total roll of the dice and they willrecieve $200 for reaching go.
//This process will continue until a player reaches $0.
//
//Output: The players turn it is
//Output: The amount of money a player has
//Output: the roll of each die and the total
//spaces the player will move
//Output: The property that the player landed on and
//rather or not they are able to purchase the property
//Output: the outcome of the space, i.e if a property
//is owned, what player obtains the rent, or if a player
//lands on a chance card, the output would be what their
//chance card states
//Output: the players amount of money at the end of their
//turn.
//
//Examples:
//
//how many players are there?
//2
//enter the name for player 1
//jim
//enter the name for player 2
//dim
//
//
//jim's turn.
//your amount of money: $1500
//your first dice is: 4
//your second dice is: 3
//you moved 7 spaces.
//you landed on Chance
//this space is not purchaseable!
//your card chance states:
//move to Chapel of St. Ignatius
//your amount of money now is: $1500
//
//
//dim's turn.
//your amount of money: $1500
//your first dice is: 4
//your second dice is: 6
//you moved 10 spaces.
//you landed on Engineering Building
//this property is not owned.
//the price is 300
//would you like to buy it?(y/n)
//u
//enter in y or n:
//y
//your amount of money now is: $1200
//
//
//dim's turn.
//your amount of money: $160
//your first dice is: 1
//your second dice is: 6
//you moved 7 spaces.
//you landed on Sullivan Hall School of Law
//this property is not owned.
//sorry, you dont have enough money to buy it!
//your amount of money now is: $160
//
//
//jim's turn.
//your amount of money: $370
//your first dice is: 6
//your second dice is: 2
//you moved 8 spaces.
//you passed go! You collected $200.
//you landed on Fees
//this space is not purchaseable!
//your amount of money now is: $170
//
//
//jim's turn.
//your amount of money: $170
//your first dice is: 4
//your second dice is: 1
//you moved 5 spaces.
//you landed on Fine Arts Building
//Oh no! This is an owned property!
//the owner is dim
//the rent is $20
//dim's amount of money is now 650
//your amount of money now is: $150
//
//


#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;


struct PlayerInfo
{
  string playerName;
  float playerMoney;
  int spaceOnBoard;
};

struct BoardGame
{
  string propertyName;
  int propertyOwner;
  int purchasePrice;
  int rent;
};
  

int startGame(PlayerInfo player[], BoardGame space[], int numPlayers);
//This program rolls the players die and moves them forward the number
//of spaces rolled. This program then checks to see if a player
//has reached zero dollars yet.
//Input: the struct that holds all the players information
//Input: the struct tha holds all the board games spots information
//Input: the number of players
//Returns: a zero or one depending when the game ends.


void spaceChecker(PlayerInfo player[], BoardGame space[], int totalRoll, int i);
//This program decides what action to take depending on the space the player
//has landed on. This program will modify a players money amount depending
//upon the rent and status of ownership of the space. This function will
//also prompt the player to purchase properties.
//Input: the struct that holds all the players information
///Input: the struct tha holds all the board games spots information
//Input: the players total roll
//Input: i, the players whose turn it is


int main(){

  //1. Get the number of players and their names
  int numPlayers;
  cout << "how many players are there?" << endl;
  cin >> numPlayers;
  while(numPlayers < 2 || numPlayers > 6){
    cout << "enter a number 2-6" << endl;
    cin >> numPlayers;
  }
  PlayerInfo player[7];
  int index;

  cin.ignore();
  for(index = 1; index <= numPlayers; index++){
    cout << "enter the name for player " << index << endl;
    getline(cin, player[index].playerName);  
    player[index].playerMoney = 1500;
    player[index].spaceOnBoard = 1;
  }

  //2a. Hardcode the file and open the file
  cout << endl << endl;
  BoardGame space[36];
  ifstream inputFile;
  inputFile.open("/home/fac/lillethd/cpsc1420/input/monopoly_board.dat");

  //2b. Store the file into a struct
  if(inputFile){
    for(int count = 1; count < 36; count++){
      getline( inputFile, space[count].propertyName);
      inputFile >> space[count].propertyOwner;
      inputFile  >> space[count].purchasePrice;
      inputFile >> space[count].rent;
      inputFile.ignore(10,'\n');
    }
  }
  //2c. output an error if the file cant
  //be opened.
  else{
    cout << "error!" << endl;
  }
  //3. Send information to a function
  //to start the game.
  startGame(player,space, numPlayers);

  //4. find the winner
  int winnerIndex;
  int highestMoney = 0;
  for(int i = 0; i <= numPlayers; i++){
    if( player[i].playerMoney > highestMoney){
      winnerIndex = i;
      highestMoney = player[i].playerMoney;
    }
  }

  cout << "the winner is " << player[winnerIndex].playerName
       << endl;

  
  return 0;
}



int startGame(PlayerInfo player[], BoardGame space[], int numPlayers){
  srand(time(NULL));
  bool gameOver = false;

  //1. Players alternate having turns until someone
  //loose the game.
  while(!gameOver){

    //2.For each turn, roll two die and add them
    //to the players current space on the board
    for(int i = 1; i <= numPlayers; i++){
      cout << player[i].playerName  << "'s turn." << endl;
      cout << "your amount of money: $" << player[i].playerMoney << endl; 
      int dice1 = rand()%6+1;
      cout << "your first dice is: " << dice1 << endl;
      int dice2 = rand()%6+1;
      cout << "your second dice is: " << dice2 << endl;
      int totalRoll = dice1 + dice2;
      cout << "you moved " << totalRoll << " spaces." << endl;
      player[i].spaceOnBoard += totalRoll;

      //2a. if a player has reached the end of the board at spot 35
      //give the player $200 and reset them to the start of the board
      if(player[i].spaceOnBoard > 35){
        cout << "you passed go! You collected $200. " << endl;
        player[i].spaceOnBoard -= 35;
        player[i].playerMoney +=200;   
      }
      
      //3. peform the action of the space
      spaceChecker(player, space, totalRoll, i);
      
      //4. check to see if the player has lost the game.
      if(player[i].playerMoney <= 0){
        cout << player[i].playerName
             << " has reached $0." << endl;
        cout << "the game is over." << endl;
        gameOver = true;
        return 0;
      }

      //5. display the players updated money at the end of their turn
      cout << "your amount of money now is: $" << player[i].playerMoney << endl;
      cout << endl << endl;
    }  
  }
  return 1;   
}


void spaceChecker(PlayerInfo player[],BoardGame space[], int totalRoll, int i){
  
  //1.Display the property that the player has laned on
  int tempSpaceOnBoard =  player[i].spaceOnBoard;
  cout << "you landed on " << space[tempSpaceOnBoard].propertyName << endl;

  //2. determine if the space is purchasable, unpurchasable, or owned.

  
  //3. if the space is unowned prompt the user to purchase the space
  //3a. if the player wants the property subtract the price from their
  //money and give the player ownership of the property.
  if(space[tempSpaceOnBoard].propertyOwner == 0){
    cout << "this property is not owned." << endl;
    char purchase;
    if(player[i].playerMoney > space[tempSpaceOnBoard].purchasePrice){
      cout << "the price is " << space[tempSpaceOnBoard].purchasePrice << endl;
      cout << "the rent for " << space[tempSpaceOnBoard].propertyName
           << " is $" <<  space[tempSpaceOnBoard].rent << endl;
      cout << "would you like to buy it?(y/n)" << endl;
      cin >> purchase;
      while(purchase != 'y' && purchase != 'n'){
        cout << "enter in y or n: " << endl;
        cin >> purchase;
      }
      
      if(purchase == 'y'){
        player[i].playerMoney -= space[tempSpaceOnBoard].purchasePrice;
        space[tempSpaceOnBoard].propertyOwner = i;
      }
      else{
        cout << "okay, no change!" << endl;
      }
    }
    else{
      cout << "sorry, you dont have enough money to buy it!"
           << endl;
    }
  }
  
  //4. If the space is not purchasable subtract the rent from the
  //the players money amount.
  //4a. if the space is a chance card, then state the
  //chance card based off a role of a dice.
  else if(space[tempSpaceOnBoard].propertyOwner== -1){
    cout << "this space is not purchaseable!" << endl;
    player[i].playerMoney -= space[tempSpaceOnBoard].rent;

    if(space[tempSpaceOnBoard].propertyName == "Chance"){
      cout << "your card chance states: " << endl;
      int chanceDie = rand()%6 +1;
      
      if(chanceDie == 1 || chanceDie == 2 || chanceDie == 3){
        cout << "you won $50!" << endl;
        player[i].playerMoney += 50;
      }
      else{
        cout << "move to Chapel of St. Ignatius " << endl;
        player[i].spaceOnBoard = 20;  
      }    
    } 
  }
  
  //5.If the property if owned, then subtract the rent from the
  //users amount of money and add the rent amount to the owners
  //money amount. 
  else{
    cout << "Oh no! This is an owned property!" << endl;
    int tempOwner = space[tempSpaceOnBoard].propertyOwner;
    cout << "the owner is " << player[tempOwner].playerName << endl;
    cout << "the rent is $" << space[tempSpaceOnBoard].rent << endl;
    player[i].playerMoney -= space[tempSpaceOnBoard].rent;
    player[tempOwner].playerMoney += space[tempSpaceOnBoard].rent;
    cout << player[tempOwner].playerName;
    cout << "'s amount of money is now $" <<  player[tempOwner].playerMoney;
    cout << endl;
   
  }
}
//Supreet Sandhu
//p5.cpp
//12-03-2019
//
//Purpose: This program is a game of monopoly. This game
//allows for up to six players and players start with $1500
//to use to purchase properties. Players take turns rolling
//dice and collect rent on their properties. The game ends
//when a player reaches $0.
//
//Input: the user must enter in the number of players and
//each players name
//Input: either a 'y' or 'n' if the players whose turn it
//is would like to purchase a property.
//
//Processing: The program will subtract the price
//of the property if a player wants to purchase the
//property they land on. If a player lands on another players
// property, then the rent of the property will be subtracted
//from the players who turn it is and added to the owners
//amount of money. Every time a players total spaces on the board,
//which keeps track of a players spot on the board, reaches 35 then
//their total spaces on the board will reset to one plus their
//total roll of the dice and they willrecieve $200 for reaching go.
//This process will continue until a player reaches $0.
//
//Output: The players turn it is
//Output: The amount of money a player has
//Output: the roll of each die and the total
//spaces the player will move
//Output: The property that the player landed on and
//rather or not they are able to purchase the property
//Output: the outcome of the space, i.e if a property
//is owned, what player obtains the rent, or if a player
//lands on a chance card, the output would be what their
//chance card states
//Output: the players amount of money at the end of their
//turn.
//
//Examples:
//
//how many players are there?
//2
//enter the name for player 1
//jim
//enter the name for player 2
//dim
//
//
//jim's turn.
//your amount of money: $1500
//your first dice is: 4
//your second dice is: 3
//you moved 7 spaces.
//you landed on Chance
//this space is not purchaseable!
//your card chance states:
//move to Chapel of St. Ignatius
//your amount of money now is: $1500
//
//
//dim's turn.
//your amount of money: $1500
//your first dice is: 4
//your second dice is: 6
//you moved 10 spaces.
//you landed on Engineering Building
//this property is not owned.
//the price is 300
//would you like to buy it?(y/n)
//u
//enter in y or n:
//y
//your amount of money now is: $1200
//
//
//dim's turn.
//your amount of money: $160
//your first dice is: 1
//your second dice is: 6
//you moved 7 spaces.
//you landed on Sullivan Hall School of Law
//this property is not owned.
//sorry, you dont have enough money to buy it!
//your amount of money now is: $160
//
//
//jim's turn.
//your amount of money: $370
//your first dice is: 6
//your second dice is: 2
//you moved 8 spaces.
//you passed go! You collected $200.
//you landed on Fees
//this space is not purchaseable!
//your amount of money now is: $170
//
//
//jim's turn.
//your amount of money: $170
//your first dice is: 4
//your second dice is: 1
//you moved 5 spaces.
//you landed on Fine Arts Building
//Oh no! This is an owned property!
//the owner is dim
//the rent is $20
//dim's amount of money is now 650
//your amount of money now is: $150
//
//
 
 
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
 
 
struct PlayerInfo
{
  string playerName;
  float playerMoney;
  int spaceOnBoard;
};
 
struct BoardGame
{
  string propertyName;
  int propertyOwner;
  int purchasePrice;
  int rent;
};
  
 
int startGame(PlayerInfo player[], BoardGame space[], int numPlayers);
//This program rolls the players die and moves them forward the number
//of spaces rolled. This program then checks to see if a player
//has reached zero dollars yet.
//Input: the struct that holds all the players information
//Input: the struct tha holds all the board games spots information
//Input: the number of players
//Returns: a zero or one depending when the game ends.
 
 
void spaceChecker(PlayerInfo player[], BoardGame space[], int totalRoll, int i);
//This program decides what action to take depending on the space the player
//has landed on. This program will modify a players money amount depending
//upon the rent and status of ownership of the space. This function will
//also prompt the player to purchase properties.
//Input: the struct that holds all the players information
///Input: the struct tha holds all the board games spots information
//Input: the players total roll
//Input: i, the players whose turn it is
 
 
int main(){
 
  //1. Get the number of players and their names
  int numPlayers;
  cout << "how many players are there?" << endl;
  cin >> numPlayers;
  while(numPlayers < 2 || numPlayers > 6){
    cout << "enter a number 2-6" << endl;
    cin >> numPlayers;
  }
  PlayerInfo player[7];
  int index;
 
  cin.ignore();
  for(index = 1; index <= numPlayers; index++){
    cout << "enter the name for player " << index << endl;
    getline(cin, player[index].playerName);  
    player[index].playerMoney = 1500;
    player[index].spaceOnBoard = 1;
  }
 
  //2a. Hardcode the file and open the file
  cout << endl << endl;
  BoardGame space[36];
  ifstream inputFile;
  inputFile.open("/home/fac/lillethd/cpsc1420/input/monopoly_board.dat");
 
  //2b. Store the file into a struct
  if(inputFile){
    for(int count = 1; count < 36; count++){ 
      getline( inputFile, space[count].propertyName);
      inputFile >> space[count].propertyOwner;
      inputFile  >> space[count].purchasePrice;
      inputFile >> space[count].rent;
      inputFile.ignore(10,'\n');
    }
  }
  //2c. output an error if the file cant
  //be opened.
  else{
    cout << "error!" << endl;
  }
  //3. Send information to a function
  //to start the game.
  startGame(player,space, numPlayers);
 
  //4. find the winner
  int winnerIndex;
  int highestMoney = 0;
  for(int i = 0; i <= numPlayers; i++){
    if( player[i].playerMoney > highestMoney){
      winnerIndex = i;
      highestMoney = player[i].playerMoney;
    }
  }
 
  cout << "the winner is " << player[winnerIndex].playerName
       << endl;
 
  
  return 0;
}
 
 
 
int startGame(PlayerInfo player[], BoardGame space[], int numPlayers){
  srand(time(NULL));
  bool gameOver = false;
 
  //1. Players alternate having turns until someone
  //loose the game.
  while(!gameOver){ 
  
    //2.For each turn, roll two die and add them 
    //to the players current space on the board 
    for(int i = 1; i <= numPlayers; i++){ 
      cout << player[i].playerName  << "'s turn." << endl;
      cout << "your amount of money: $" << player[i].playerMoney << endl; 
      int dice1 = rand()%6+1;
      cout << "your first dice is: " << dice1 << endl;
      int dice2 = rand()%6+1;
      cout << "your second dice is: " << dice2 << endl;
      int totalRoll = dice1 + dice2;
      cout << "you moved " << totalRoll << " spaces." << endl;
      player[i].spaceOnBoard += totalRoll;
 
      //2a. if a player has reached the end of the board at spot 35
      //give the player $200 and reset them to the start of the board
      if(player[i].spaceOnBoard > 35){
        cout << "you passed go! You collected $200. " << endl;
        player[i].spaceOnBoard -= 35;
        player[i].playerMoney +=200;   
      }
      
      //3. peform the action of the space
      spaceChecker(player, space, totalRoll, i);
      
      //4. check to see if the player has lost the game.
      if(player[i].playerMoney <= 0){
        cout << player[i].playerName
             << " has reached $0." << endl;
        cout << "the game is over." << endl;
        gameOver = true; 
        return 0;
      }
 
      //5. display the players updated money at the end of their turn
      cout << "your amount of money now is: $" << player[i].playerMoney << endl;
      cout << endl << endl;
    }  
  }
  return 1;   
}
 
 
void spaceChecker(PlayerInfo player[],BoardGame space[], int totalRoll, int i){ 
  
  //1.Display the property that the player has laned on
  int tempSpaceOnBoard =  player[i].spaceOnBoard;
  cout << "you landed on " << space[tempSpaceOnBoard].propertyName << endl;
 
  //2. determine if the space is purchasable, unpurchasable, or owned.
 
  
  //3. if the space is unowned prompt the user to purchase the space
  //3a. if the player wants the property subtract the price from their
  //money and give the player ownership of the property.
  if(space[tempSpaceOnBoard].propertyOwner == 0){
    cout << "this property is not owned." << endl;
    char purchase;
    if(player[i].playerMoney > space[tempSpaceOnBoard].purchasePrice){
      cout << "the price is " << space[tempSpaceOnBoard].purchasePrice << endl;
      cout << "the rent for " << space[tempSpaceOnBoard].propertyName
           << " is $" <<  space[tempSpaceOnBoard].rent << endl;
      cout << "would you like to buy it?(y/n)" << endl;
      cin >> purchase;
      while(purchase != 'y' && purchase != 'n'){
        cout << "enter in y or n: " << endl;
        cin >> purchase;
      }
      
      if(purchase == 'y'){
        player[i].playerMoney -= space[tempSpaceOnBoard].purchasePrice;
        space[tempSpaceOnBoard].propertyOwner = i;
      }
      else{
        cout << "okay, no change!" << endl;
      }
    }
    else{
      cout << "sorry, you dont have enough money to buy it!"
           << endl;
    }
  }
  
  //4. If the space is not purchasable subtract the rent from the
  //the players money amount.
  //4a. if the space is a chance card, then state the
  //chance card based off a role of a dice.
  else if(space[tempSpaceOnBoard].propertyOwner== -1){
    cout << "this space is not purchaseable!" << endl;
    player[i].playerMoney -= space[tempSpaceOnBoard].rent;
 
    if(space[tempSpaceOnBoard].propertyName == "Chance"){
      cout << "your card chance states: " << endl;
      int chanceDie = rand()%6 +1;
      
      if(chanceDie == 1 || chanceDie == 2 || chanceDie == 3){
        cout << "you won $50!" << endl;
        player[i].playerMoney += 50;
      }
      else{
        cout << "move to Chapel of St. Ignatius " << endl;
        player[i].spaceOnBoard = 20;  
      }    
    } 
  }
  
  //5.If the property if owned, then subtract the rent from the
  //users amount of money and add the rent amount to the owners
  //money amount. 
  else{
    cout << "Oh no! This is an owned property!" << endl;
    int tempOwner = space[tempSpaceOnBoard].propertyOwner;
    cout << "the owner is " << player[tempOwner].playerName << endl;
    cout << "the rent is $" << space[tempSpaceOnBoard].rent << endl;
    player[i].playerMoney -= space[tempSpaceOnBoard].rent;
    player[tempOwner].playerMoney += space[tempSpaceOnBoard].rent;
    cout << player[tempOwner].playerName;
    cout << "'s amount of money is now $" <<  player[tempOwner].playerMoney;
    cout << endl;
   
  }
}