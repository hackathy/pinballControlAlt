/*
 * Alternative pinball control code
 * Seperate scores for individual bumpers/groups of bumpers
 *
 * Nicholas Tzimos, 2018
 */
int score = 0; //to keep track of score
int tier1 = 2;
int tier2a = 3;
int tier2b = 4;
int tier3a = 5;
int tier3b = 6;
int tier3c = 7; //where the number is how far back the bumper is, and the letter is starting from the left (from the player's point of view)
int setloop = 0; //for pausing the loop
int tier1pts = 50;
int tier2pts = 100;
int tier3pts = 150; //all the *pts variables are for setting different points for different tiers

void setup() {
  Serial.begin(9600); //open a serial connection, for debug purposes - will either be commented out entirely or used for another purpose in later builds
  pinMode(tier1, INPUT);
  pinMode(tier2a, INPUT);
  pinMode(tier2b, INPUT);
  pinMode(tier3a, INPUT);
  pinMode(tier3b, INPUT);
  pinMode(tier3c, INPUT);//setting all of the necessary pins to be inputs  
}

void loop() {
  while(setloop < 49){ //placed all the code inside a while loop to allow for pausing the continuous stream of data being thrown at the computer 49 = 1 (ASCII)
    int tier1state = digitalRead(tier1); //read and save the state (LOW/HIGH) of the tier 1 pin(s)
    int tier2state = (digitalRead(tier2a) || digitalRead(tier2b)); //read and save the state (LOW/HIGH) of the tier 2 pin(s)
    int tier3state = (digitalRead(tier3a) || digitalRead(tier3b) || digitalRead(tier3c)); //read and save the state (LOW/HIGH) of the tier 3 pin(s)

    if(tier1state == 1){
      score = score + (tier1pts/50); //adjust the score
    }
    if(tier2state == 1){
      score = score + (tier2pts/50); //adjust the score
    }
    if(tier3state == 1){
      score = score + (tier3pts/50); //adjust the score
    }
    
    //anything in this paragraph is for debugging purposes
    Serial.print(score);
    Serial.print(",");
    Serial.print(score*50);
    Serial.print(",");
    Serial.print(tier1state);
    Serial.print(",");
    Serial.print(tier2state); //at the moment, anything being printed to the serial console is purely for debugging purposes
    Serial.print(",");
    Serial.println(setloop);
    //end debugging section
    
    if (Serial.available() > 0){ //if there is a serial connection,
      setloop = Serial.read(); //read from serial for pausing
    }
    if (setloop > 48){ //if we are about to pause,
      Serial.println();
      Serial.println("Paused, press space to continue..."); //tell the user/operator we have paused
    }
  }
  if (Serial.available() > 0){ //if there is a serial connection,
    setloop = Serial.read(); //read from serial for resuming
  }
}
