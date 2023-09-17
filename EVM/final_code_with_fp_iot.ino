
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal.h>
SoftwareSerial mySerial(2, 3);

LiquidCrystal lcd( A0,A1,A2,A3,A4,A5);



String mystring;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4}; //connect to the column pinouts of the keypad

#define buzz 11
#define led 12

//initialize an instance of class NewKeypad
Keypad key = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char passs[5]="4321";
char data[5],last[5];
byte count=0,lcount=0;
char c,v,d;
bool verify= false;
bool res = false;
byte p1=0,p2=0,p3=0;
bool endverify = false;


bool vote = false;
bool num = false;
int n;
char m,b,u;
char e='*';
int s[80];




void setup()
{
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  delay(10);
  finger.begin(57600);
  lcd.begin(16,2);

  lcd.print(F("   Electronic "));
  lcd.setCursor(0,1);
  lcd.print(F(" Voting Machine"));
  delay(3000);
  lcd.clear();

  while(1)
  {
    u=key.getKey();
    delay(50);
    if (u=='#')
    {
      break;
    }
    else
    {     
      lcd.setCursor(0,0);
      lcd.print(F(" Department of"));
      lcd.setCursor(0,1);
      lcd.print(F("   ETE, RUET"));
    }
  }

  if (finger.verifyPassword()) 
  {
    lcd.clear();
    lcd.print(F("Found FP sensor"));
    delay(1300);
    finger.getTemplateCount();
    if (finger.templateCount != 0) 
    {
      lcd.clear();
      lcd.print(F("Sensor Contains"));
      lcd.setCursor(1,1);
      lcd.print(finger.templateCount);
      lcd.setCursor(4,1);
      lcd.print(F("samples"));
      delay(2000);
    }
    else
    {
      lcd.clear();
      lcd.print(F("   No data"));
    }
  } 
  else 
  {
    lcd.clear();
    lcd.print(F("  Do not found"));
    lcd.setCursor(0,1);
    lcd.print(F("  FP sensor :("));
    while (1) 
    { 
      delay(1);
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Enter pass to "));
  lcd.setCursor(0,1);
  lcd.print(F("start- "));
  while(count<4 || verify== false)
  {
    c=key.getKey();
    if(c)
    {
    lcd.setCursor(8+count,1);
    lcd.print(c);
    data[count]=c;
    count++;
    }
    if(count== 4)
    {
      if(!strcmp(data,passs))
      {
        lcd.clear();
        lcd.print(F("Password matched"));
        verify = true;
        delay(1500);
        welcome();                           //welcome()
      }
      else
      {
        lcd.clear();
        lcd.print(F("Wrong Password"));
        count= 0;
        delay (1500);
        screen();                           //screen()
      }
    }
  }
  
}
  


void loop()
{ 
  lcd.clear();
  lcd.print(F("  Insert Your"));
  lcd.setCursor(0,1); 
  lcd.print(F("  Fingerprint"));
  delay(50);
  getFingerprintID();                     //getFingerprintID()
  delay(50);
  if (vote == true)
  {
     votee();                             //vote 
     vote = false;
  }
  char m= key.getKey();
  if(m =='#')
  {
    endd();
    res = true;
    lcount= 0;
  }
  if (res == true && endverify == true)
  {
    result();                           //result()

    res = false;
    endverify = false;

  }
}



void votee()
{
  lcd.clear();
  lcd.print(F("  Please vote"));
  lcd.setCursor(0,1);
  lcd.print(F("  Your Party"));
  delay(2000);
  lcd.clear();
  lcd.print(F(" P1   P2   P3 "));
  lcd.setCursor(0,1);
  lcd.print(F(" 1    2    3 "));
  delay(130);
  v = key.waitForKey();
  if(v== '1' || v== '2' || v== '3')
  {
    detect();                           //detect()
  }
  else
  {
    s[finger.fingerID] = 0;
  }
  
}







void screen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Enter pass to "));
  lcd.setCursor(0,1);
  lcd.print(F("start- "));
}



void screen2()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Enter pass to "));
  lcd.setCursor(0,1);
  lcd.print(F("get result- "));
}



void welcome()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("  Welcome to "));
  lcd.setCursor(0,1);
  lcd.print(F(" Iot based EVM"));
  delay(2000);
  lcd.clear();
  lcd.print(F(" * = Enroll FP "));
  lcd.setCursor(0,1);
  lcd.print(F("Any to continue"));
  delay(1500);

  b=key.waitForKey();
  if(b)
  {
    if(b=='*')
    {
      enroll();                           //enroll()
    }
    else
    {
      lcd.clear();
      lcd.print(F("   Starting"));
      lcd.setCursor(0,1);
      lcd.print(F(" Voting process"));
      delay(1500);
    }
  }
}




void detect()
{
  if(v=='1')
  {
    lcd.clear();
    lcd.print(F("   you voted"));
    lcd.setCursor(4,1);
    lcd.print(F("Party 1"));
    digitalWrite(buzz,HIGH);
    delay(1400);
    digitalWrite(buzz,LOW);
    delay(1100);
    p1=p1+1;
    Serial.print("Party 1 =");
    Serial.print(p1);
    Serial.println(" votes,");
    Serial.print(" Party 2 =");
    Serial.print(p2);
    Serial.println(" votes,");
    Serial.print("Party 3 =");
    Serial.print(p3);
    Serial.println(" votes");
  }
  if(v=='2')
  {
    lcd.clear();
    lcd.print(F("   you voted"));
    lcd.setCursor(4,1);
    lcd.print(F("Party 2"));
    digitalWrite(buzz,HIGH);
    delay(1400);
    digitalWrite(buzz,LOW);
    delay(1100);
    p2=p2+1;
    Serial.print("Party 1 =");
    Serial.print(p1);
    Serial.println(" votes,");
    Serial.print(" Party 2 =");
    Serial.print(p2);
    Serial.println(" votes,");
    Serial.print("Party 3 =");
    Serial.print(p3);
    Serial.println(" votes");
  }
  if(v=='3')
  {
    lcd.clear();
    lcd.print(F("   you voted"));
    lcd.setCursor(4,1);
    lcd.print(F("Party 3"));
    digitalWrite(buzz,HIGH);
    delay(1400);
    digitalWrite(buzz,LOW);
    delay(1100);
    p3=p3+1;
    Serial.print("Party 1 =");
    Serial.print(p1);
    Serial.println(" votes,");
    Serial.print(" Party 2 =");
    Serial.print(p2);
    Serial.println(" votes,");
    Serial.print("Party 3 =");
    Serial.print(p3);
    Serial.println(" votes");
  }
  
}


void result()
{
  lcd.clear();
    lcd.print(F("P1="));
    lcd.setCursor(3,0);
    lcd.print(p1);
    lcd.setCursor(10,0);
    lcd.print(F("P2="));
    lcd.setCursor(13,0);
    lcd.print(p2);
     lcd.setCursor(5,1);
    lcd.print(F("P3="));
    lcd.setCursor(8,1);
    lcd.print(p3);
    delay(4000);
    if (p1 !=0 || p2 !=0 || p3!=0)
    {
      if(p1>p2 && p1>p3)
      {
      lcd.clear();
      lcd.print(F("Party 1 winner"));
      Serial.print("Party 1 wins the election by getting ");
      Serial.print(p1);
      Serial.println(" votes");
      delay(5000);
      }
      else if(p2>p1 && p2>p3)
      {
      lcd.clear();
      lcd.print(F("Party 2 winner"));
      Serial.print("Party 2 wins the election by getting ");
      Serial.print(p2);
      Serial.println(" votes");
      delay(5000);
      }
      else if(p3>p2 && p3>p1)
      {
      lcd.clear();
      lcd.print(F("Party 3 winner"));
      Serial.print("Party 3 wins the election by getting ");
      Serial.print(p3);
      Serial.println(" votes");
      delay(5000);
      }
      else if(p1 == p2 && p1 == p3)
      {
      lcd.clear();
      lcd.print(F("All Equal!!!"));
      lcd.setCursor(0,1);
      lcd.print(F(" Need another "));
      Serial.println("All parties got equal votes");
      delay(5000);
      }
      else if(p1 == p2 && p1 > p3)
      {
      lcd.clear();
      lcd.print(F("Party 1&2 winner"));
      lcd.setCursor(0,1);
      lcd.print(F("Need another vote"));
      Serial.println("Party 1 & Party 2 got same votes");
      delay(5000);
      }
      
      else if(p2 == p3 && p2 > p1)
      {
      lcd.clear();
      lcd.print(F("Party 2&3 winner"));
      lcd.setCursor(0,1);
      lcd.print(F("Need another vote"));
      Serial.println("Party 2 & Party 3 got same votes");
      delay(5000);
      }
      
      else if(p1 == p3 && p1 > p2)
      {
      lcd.clear();
      lcd.print(F("Party 1&3 winner"));
      lcd.setCursor(0,1);
      lcd.print(F("Need another vote"));
      Serial.print("Party 1 & Party 3 got same votes");
      delay(5000);
      }

      while(1)
      {
        char y = key.getKey();
        if(y=='#')
        {
          p1=p2=p3=0;
          int u;
          for (u=1;u<80;u++)
          {
            s[u]=0;
          }
          break;
        }        
      }
      
    }
    else
    {
      lcd.clear();
      lcd.print(F("     Sorry"));
      lcd.setCursor(0,1);
      lcd.print(F("    No Vote"));
      delay(3000);
      lcd.clear();
      lcd.print(F("Returning to the"));
      lcd.setCursor(0,1); 
      lcd.print(F("  main page"));     
      delay(2000);
    }
    
}

void endd()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Enter pass to "));
  lcd.setCursor(0,1);
  lcd.print(F("get result- "));
  int w = 0;
  while(lcount<4 || endverify == false)
  {
    
    d=key.getKey();
    if(d)
    {
    lcd.setCursor(12+lcount,1);
    lcd.print(d);
    last[lcount]=d;
    lcount++;
    }
    if(lcount== 4)
    {
      if(!strcmp(passs,last))
      {
        lcd.clear();
        lcd.print(F("Password matched"));
        endverify = true;
        delay(1500);
      }
      else
      {
        lcd.clear();
        lcd.print(F("Wrong Password"));
        lcount= 0;
        delay (1500);
        w=1;
        break;
        screen2();
      }
    }
  }
  if(w == 1)
  {
    endverify == false;
  }
}


void number()
{
  n=0;
  num= false;
  while(num == false)
  {
    m=key.getKey();
    if(m=='1')
    {
      if(n== 0){
        n=1;
      }
      else{
        n=(n*10)+1;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='0')
    {
      if(n== 0){
        n=0;
      }
      else{
        n=(n*10);
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='2')
    {
      if(n== 0){
        n=2;
      }
      else{
        n=(n*10)+2;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='3')
    {
      if(n== 0){
        n=3;
      }
      else{
        n=(n*10)+3;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='4')
    {
      if(n== 0){
        n=4;
      }
      else{
        n=(n*10)+4;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='5')
    {
      if(n== 0){
        n=5;
      }
      else{
        n=(n*10)+5;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='6')
    {
      if(n== 0){
        n=6;
      }
      else{
        n=(n*10)+6;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='7')
    {
      if(n== 0){
        n=7;
      }
      else{
        n=(n*10)+7;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='8')
    {
      if(n== 0){
        n=8;
      }
      else{
        n=(n*10)+8;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='9')
    {
      if(n== 0){
        n=9;
      }
      else{
        n=(n*10)+9;
      }
      lcd.setCursor(12,1);
      lcd.print(n);
    }
    if(m=='#')
    {
       num = true;            
    }
    if (m == '*')
    {
      n= 0;
      lcd.clear();
      lcd.print(F("Ready to enroll"));
      lcd.setCursor(0,1);
      lcd.print(F("Type FP ID #")); 
      lcd.setCursor(12,1);
      lcd.print(n);
    }
  }
}




void enroll()
{
  while(e!='#')
  {
    lcd.clear();
    lcd.print(F("Ready to enroll"));
    lcd.setCursor(0,1);
    lcd.print(F("Type FP ID #"));
    number();                                                    //number()
    id = n;
    lcd.setCursor(12,1);
    lcd.print(id);
    delay(1000);

    while (!  getFingerprintEnroll() );                           //getFingerprintEnroll()
  }
}




uint8_t getFingerprintEnroll() {

  int p = -1;
  lcd.clear();
  lcd.print(F("Waiting finger "));
  lcd.setCursor(0,1);
  lcd.print(F("to enroll as #"));
  lcd.setCursor(14,1);
  lcd.print(id);
  delay(1500);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:    
      lcd.clear();
      lcd.print("Image taken");
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      //lcd.setCursor(0,1);
      //lcd.print(".");
      delay(100);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      lcd.print(F("Imaging error"));
      delay(1000);
      break;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(F("Image converted"));
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.print(F("Image too messy"));
      delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("FP features "));
      delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("FP features "));
      delay(1000);
      return p;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1000);
      return p;
  }

  lcd.clear();
  lcd.print(F("Remove finger"));
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  lcd.clear();
  lcd.print("ID #");
  lcd.setCursor(4,0); 
  lcd.print(id);
  delay(1000);
  p = -1;
  lcd.clear();
  lcd.print(F(" Place same "));
  lcd.setCursor(0,1);
  lcd.print(F(" finger again "));
  delay(1000);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(F("Image taken"));
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      //lcd.setCursor(0,1);
      //lcd.print(".");
      delay(1000);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      lcd.print(F("Imaging error"));
      delay(1000);
      break;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(F("Image converted"));
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.print(F("Image too messy"));
      delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("FP features "));
      delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("FP features "));
      delay(1000);
      return p;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1000);
      return p;
  }

  // OK converted!
  lcd.clear();
  lcd.print(F("Creating model"));
  lcd.setCursor(0,1);
  lcd.print(F(" for #"));
  lcd.setCursor(6,1);  
  lcd.print(id);
  delay(1000);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print(F("Prints matched!"));
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.print(F("Communicate err"));
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    lcd.clear();
    lcd.print(F("Fingerprints "));
    lcd.setCursor(0,1);
    lcd.print(F("did not match"));
    delay(1000);
    return p;
  } else {
    lcd.clear();
    lcd.print(F("Unknown error"));
    delay(1000);
    return p;
  }

  lcd.clear();
  lcd.print(F("ID #"));
  lcd.setCursor(4,1); 
  lcd.print(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print(F("Stored!"));
    digitalWrite(buzz,HIGH);
    delay(1500);
    digitalWrite(buzz,LOW);

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.print(F("Communicate err"));
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    lcd.clear();
    lcd.print(F("Could not store in that location"));
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    lcd.clear();
    lcd.print(F("Er writing flash"));
    delay(1000);
    return p;
  } else {
    lcd.clear();
    lcd.print(F("Unknown error"));
    delay(1000);
    return p;
  }

  lcd.clear();
  lcd.print(F("press # to end /"));
  lcd.setCursor(0,1);
  lcd.print(F("Any to add more"));
  delay(1500);
  e=key.waitForKey();
  return true;
}





uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(F("Image taken"));
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1500);
      return p;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      lcd.print(F("Imaging error"));
      delay(1500);
      return p;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1500);
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(F("Image converted"));
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.print(F("Image too messy"));
      delay(1500);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print(F("Communicate err"));
      delay(1500);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("fingerprint features "));
      delay(1500);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.print(F("Could not find "));
      lcd.setCursor(0,1);
      lcd.print(F("fingerprint features "));
      delay(1500);
      return p;
    default:
      lcd.clear();
      lcd.print(F("Unknown error"));
      delay(1500);
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print(F("Found a match!"));
    lcd.setCursor(0,1);
    lcd.print(F("finger ID#"));
    lcd.setCursor(10,1);
    lcd.print(finger.fingerID);
    delay(2000);
    if (s[finger.fingerID] != 1)
    {
      vote = true;
      s[finger.fingerID] = 1;
    }
    else
    {
      lcd.clear();
      lcd.print(F(" Already Voted"));
      digitalWrite(buzz,HIGH);
      digitalWrite(led,HIGH);
      delay(3000);
      digitalWrite(buzz,LOW);
      digitalWrite(led,LOW);
    }
    
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.print(F("Communicate err"));
    delay(1500);
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    lcd.clear();
    lcd.print(F(" No match found"));
    delay(2500);
    return p;
  } else {
    lcd.clear();
    lcd.print(F("Unknown error"));
    delay(1500);
    return p;
  }

  return finger.fingerID;
}
