#include <LiquidCrystal.h>

LiquidCrystal
lcd(12,11,5,4,3,2);

int hours=0;                              // hours
int minutes=0;                           // minutes
int seconds=00;                         // seconds
int days;                              // counts the number of days since the beggining of the current month
int year=2018;                        // year
String month;                        // 3 letter string to represent the current month
int DAYS=75;                        // counts the number of days since the beggining of the current year
int stopwatch_seconds=0;           // seconds for the stopwatch
int stopwatch_minutes=0;          // minutes for the stopwatch 
int button;                      // input value to let the program know which button is clicked
int counter=1;                  // counts the number of times the button is clicked (switch for each feature)
int countdown_seconds;         // seconds for the countdown
int countdown_minutes;        // minutes for the countdown





void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  digitalWrite(10, HIGH);
}





void loop() 
{

  Serial.println(analogRead(A5));



  //FOR THE TIME

  lcd.setCursor(0,0);

  seconds++;                // increments the seconds variable after the delay (inside the loop function)

  lcd.print("TIME:");

  if (hours<=9) {
    lcd.print("0");
  }                        //improves readability

  lcd.print(hours);


  lcd.print(":");


  if (minutes<=9) {
    lcd.print("0");
  }                       //improves readability

  lcd.print(minutes);


  lcd.print(":");


  if (seconds<=9)
  {
  lcd.print("0");
  }

  lcd.print(seconds);

  delay(988.481675);        // in theory, should be 1000 ms, but runtime makes the clock lag behind over time

  lcd.clear();              // clears the screen and updates the time after the delay

  if (seconds==60)
  {
    seconds=0;
    minutes++;
  }

  if (minutes==60)
  {
    minutes=0;
    hours++;
    tone(7,500,100);        // emmits a sound
  }




//FOR THE DATE

if (hours==24)
{
  DAYS++;
  hours=0;
}

if (DAYS<=31)
{
  month="JAN";
  days=DAYS;
}
if (DAYS>31 && DAYS<=59)
{
  month="FEB";
  days=DAYS-31;
}
if (DAYS>59 && DAYS<=90)
{
  month="MAR";
  days=DAYS-59;
}
if (DAYS>90 && DAYS<=120)
{
  month="APR";
  days=DAYS-90;
}
if (DAYS>120 && DAYS<=151)
{
  month="MAY";
  days=DAYS-120;
}
if (DAYS>151 && DAYS<=181)
{
  month="JUN";
  days=DAYS-151;
}
if (DAYS>181 && DAYS<=212)
{
  month="JUL";
  days=DAYS-181;
}
if (DAYS>212 && DAYS<=243)
{
  month="AUG";
  days=DAYS-212;
}
if (DAYS>243 && DAYS<=273)
{
  month="SEP";
  days=DAYS-243;
}
if (DAYS>273 && DAYS<=304)
{
  month="OCT";
  days=DAYS-273;
}
if (DAYS>304 && DAYS<=334)
{
  month="NOV";
  days=DAYS-304;
}
if (DAYS>334 && DAYS<=365)
{
  month="DEC";
  days=DAYS-334;
}

if (DAYS==366)
  {
    year++;
    DAYS=0;
  }






//FOR THE BUTTONS

button = analogRead(A5);                  // reads the value given by the voltage divider and stores it in the variable button


// the first button adds one hour
if (button>=1010 && button<=1030)
  {
    hours++;
  }

// the second button adds one minute
else if (button>=990 && button<=1000)
  {
    minutes++;
  }

// the third button subtracts one minute
else if (button>=945 && button<=960)
  {
    minutes--;
      if (minutes<0)
       {
          minutes=60+minutes;
       }
  }

// the fifth button (depending on which feature is displayed) : starts a 5 minute countdown OR remet sets the stopwatch to zero OR adds one to DAYS
else if (button>= 785  && button<=791)
  {
    if (counter==3)
      {
        countdown_minutes=5;
        countdown_seconds=0;
      }
    if (counter==1)
      {
        stopwatch_minutes=0;
        stopwatch_seconds=0;
      }
    if (counter==2)
      {
        DAYS++;
      }
}

// the sixth button (depending on which feature is displayed) starts a 10 minute countdown OR subtracts one year
else if (button>=507  && button<=512)
{if (counter==3)
 {countdown_minutes=10;
 countdown_seconds=0;}
 if (counter==2)
 {year--;}
}

// the seventh button (depending on which feature is displayed) starts a 15 minute countdown OR adds one year
else if (button>=288  && button<=292)
{if(counter==3)
 {countdown_minutes=15;
 countdown_seconds=0;}
 if (counter==2)
 {year++;} 
}





//FOR THE COUNTER (SWITCH)
//the counter loops through numbers 1 to 3 (a feature is associated with each of those numbers)

if (button>=885 && button<=890)
  {
    counter++;
  } 
if (counter==4) 
{
counter=1;
}






//FOR THE COUNTDOWN (15,10 or 5 minutes)

if (counter==3)
{if (not (countdown_minutes==0 && countdown_seconds==0))
{
countdown_seconds--;
}}
if (countdown_seconds<0)
{
  countdown_seconds=59;
 }
 if (countdown_seconds==59) 
 {
  countdown_minutes--;
 }
 if (countdown_minutes==0 && countdown_seconds==0)
{if (counter==3)
 {tone(7,500,2000);}
}
if (countdown_minutes<0)
{
countdown_minutes=0;
}





//LOOP THROUGH EACH FEATURE
 
if (counter==1)
  {
    lcd.setCursor(0,1);
    lcd.print("STPWCH:");
    lcd.print("m:");
    if (stopwatch_minutes<10) 
    {
      lcd.print("0");
    }
    lcd.print(stopwatch_minutes);
    lcd.print(" s:");
    if (stopwatch_seconds<10)
    {
      lcd.print("0");
    }
    lcd.print(stopwatch_seconds);
    stopwatch_seconds++;
    if (stopwatch_seconds==60) 
    {
      stopwatch_minutes++;
      stopwatch_seconds=0;
    }
} 
else if (counter==2)
  {
    lcd.setCursor(0,1);
    lcd.print("DATE:");
    lcd.print(DAYS);
    lcd.print("|");
    lcd.print(month);
    lcd.print("|");
    lcd.print(year);
    stopwatch_seconds=0;
    stopwatch_minutes=0;
  }
 else if (counter==3)
  {
    lcd.setCursor(0,1);
    lcd.print("COUNTDOWN:");
    if (countdown_minutes<10) 
    {
      lcd.print("0");
    }
    lcd.print(countdown_minutes);
    lcd.print(":");
    if (countdown_seconds<10) 
    {
      lcd.print("0");
    }
    lcd.print(countdown_seconds);
    stopwatch_seconds=0;
    stopwatch_minutes=0; 
  }
}