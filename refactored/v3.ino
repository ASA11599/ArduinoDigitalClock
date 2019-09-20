#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

// variables for the clock
int hours = 0;
int minutes = 0;
int seconds = 0;

// a number to identify which button is being pressed.
int button ;

// text
const String txt = "TIME: ";

/*
displays the time
*/
void displayTime(void)
{
	if (hours < 10) {
		lcd.print("0");
	}
	lcd.print(hours);
	lcd.print(":");

	if (minutes < 10) {
		lcd.print("0");
	}
	lcd.print(minutes);
	lcd.print(":");

	if (seconds < 10) {
		lcd.print("0");
	}
	lcd.print(seconds);
}

/*
adjusts time variables
*/
void adjustTime(void)
{
	if (seconds == 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes == 60) {
		minutes = 0;
		hours++;
	}
	if (hours == 24) {
		hours = 0;
	}
}

// runs only once
void setup()
{

	// initialize the display with 16 columns and 2 rows
	lcd.begin(16,2);

	// ?????
	Serial.begin(9600);
	pinMode(10,OUTPUT);
	digitalWrite(10, HIGH);

}


// main loop
void loop()
{

	// clears the LCD to erase any previous text
	lcd.clear();

	// prints text on the LCD
	lcd.print(txt);

	/*
	The value being assigned to "button" depends on
	which button is being pressed when "analogRead()"
	is called. Each button produces a number that is
	expected to be within a specific range depending on
	the button. If no button is pressed, the number
	will be 0.
	*/
	button = analogRead(A5);

	// display the current time
	displayTime();

	// increment the seconds at each loop
	seconds++;

	// adjusting the time variables
	adjustTime();

	// wait a second before looping again
	delay(1000 /* milliseconds */ );

}