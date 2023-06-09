1/*
2  Arduino Ship game 
3
4  coded by: Michael Moreno Gierbolini
5
6 
7  The circuit:
8 * LCD RS pin to digital pin 12
9 * LCD Enable pin to digital pin 11
10 * LCD D4 pin to digital pin 5
11 * LCD D5 pin to digital pin 4
12 * LCD D6 pin to digital pin 3
13 * LCD D7 pin to digital pin 2
14 * LCD R/W pin to ground
15 * 10K potentiometer:
16 * ends to +5V and ground
17 * wiper to LCD VO pin (pin 3)
18 * 10K poterntiometer on pin A0
19 * joystixk
20 
21
22*/
23
24// include the library code:
25#include <LiquidCrystal.h>
26
27// initialize the library by associating any needed LCD interface pin
28// with the arduino pin number it is connected to
29const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
30
31LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
32
33//joystick inputs
34int VRx = A0;
35int VRy = A1;
36//player position
37int current_posx = 0,current_posy;
38
39//this variables keep track of the obtacles position
40int i = 0;
41int c = 3;
42
43//game state
44bool running;
45
46// make some custom characters:
47
48
49byte ship[8] = {
50 0b01000,
51 0b01100,
52 0b00110,
53 0b01111,
54 0b00110,
55 0b01100,
56 0b01000,
57 0b00000 
58};
59
60byte rock[8]={
61 0b01110,
62 0b11111,
63 0b11111,
64 0b11111,
65 0b11111,
66 0b11111,
67 0b11111,
68 0b01110
69};
70
71void setup() {
72  //initialize joystick inputs
73  pinMode(7, INPUT_PULLUP);
74  pinMode(VRx, INPUT);
75  pinMode(VRy, INPUT);
76  // initialize LCD and set up the number of columns and rows:
77  lcd.begin(16, 2);
78
79
80  //create special characters for the game graphics
81  lcd.createChar(5, ship);
82  lcd.createChar(6, rock);
83
84  // set the cursor to the top left
85  lcd.setCursor(0, 0);
86
87  randomSeed(analogRead(3));
88
89
90}
91//this fuction prints the starting screen
92void printStart(){
93  lcd.clear();
94  lcd.setCursor(0,0);
95  lcd.print(" Press Start: ");
96  }
97//this fuction drwas the player in the given position 
98void drawShip(int x, int y){
99  lcd.setCursor(y,x);
100  lcd.write(5);
101  }
102//this fuction drwas an obstacle in the given position   
103void drawRock(int x, int y){
104  if(x == 0 || x == 1 || y == 0){
105    lcd.setCursor(y, x);
106    lcd.print(" ");
107    }
108  lcd.setCursor(y, x);
109  lcd.write(6);
110  
111  }
112
113void loop() {
114  // read the potentiometer on A0 and A1:
115  printStart();
116  int score = 0;
117  int ran = random(5);
118
119  //joystick button
120  int buttonState = digitalRead(7);
121  if(buttonState == 0){
122    
123    if(running){
124      running = false;
125      }
126     if(!running){
127      running = true;
128     }
129     delay(1000);
130    }
131
132  //game frame delay  
133  int delayTime = 300;
134
135  
136  while(running){
137    
138  //joystick button
139  int buttonState = digitalRead(7);
140  if(buttonState==0){
141      running = false;
142    }
143
144  //joystick reads  
145  VRx = analogRead(A0);
146  VRy = analogRead(A1);
147
148  //player movement Note: this part of the code may need to be altered depending on the joystick orientation
149  if(VRx < 120){
150    current_posx = 0;
151    }
152   if(VRx > 900){
153    current_posx = 1;
154    }
155   if(VRy < 120){
156    if(current_posy == 15){
157      current_posy = 15;
158      }
159     else
160      current_posy =current_posy + 1;
161    }
162   if(VRy > 900){
163    if(current_posy == 0){
164      current_posy =0;
165      }
166     else
167      current_posy = current_posy -1;
168    }
169    //clears the screen and draws the player
170  lcd.clear();
171  if(i == c || i ==(c+1)||i==(c -1)){
172    i = i + 3;
173    }
174  drawShip(current_posx,current_posy);
175
176  
177   int ran = random(7);
178  //sets obstacle position to the last row
179  if(c == 0||c < 0){
180    c=15;
181    c = c + ran;
182    }
183  if(i == 0|| i < 0){
184    i = 15;
185    i = i + ran;
186    }
187  drawRock(1,c);
188  drawRock(0,i);
189
190  //this moves the obstacles every loop
191  i = i-1;
192  c = c-1;
193
194  //this detects if the player hits an obstacle and ends the game 
195  if((current_posy == c && current_posx == 1)||(current_posy == i && current_posx == 0)){
196    lcd.clear();
197    lcd.setCursor(0,0);
198    lcd.print(" GAME OVER!!");
199    lcd.setCursor(0,1);
200    lcd.print("Score:");
201    lcd.print(score);
202    delay(2000);
203    running = false;
204    }
205  //add score  
206  score = score+ 1;
207  
208  delay(delayTime);
209  //To make the game faster every frame
210  delayTime = delayTime - 1;
211
212  //this limits the speed the game is running
213  if(delayTime < 50){
214    delayTime = 50;
215  }
216  
217  }
218}
