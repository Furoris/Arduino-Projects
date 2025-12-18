//Joystick configuration
#define ANALOG_X_PIN A0
#define ANALOG_Y_PIN A1
#define ANALOG_BUTTON_PIN A2
#define ANALOG_X_CORRECTION 125
#define ANALOG_Y_CORRECTION 128
#define MOVE_THRESHOLD 50  // minimal value from joystick to move
#define MOVING_TIME 500    //Time in miliseconds

struct button {
	byte pressed = 0;
};

struct analog {
	short x, y;

	button button;
};

struct position {
	short x, y;
};

position currentPosition{ 0, 0 };

//Dot matrix 8x8 config
//ROW x Arduino PIN for example row[0] = PIN 22, row[5] = PIN 9
const int row[8] = {
	22, 34, 2, 28, 9, 3, 8, 5
};
//COLUMN x Arduino PIN for example col[0] = PIN 32, row[5] = PIN 4
const int col[8] = {
	32, 7, 6, 24, 4, 26, 36, 38
};

void setup() {
	pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP);

	resetPosition(currentPosition);

	Serial.begin(9600);
}

void loop() {
	analog analog;

	analog.x = readAnalogAxisLevel(ANALOG_X_PIN) - ANALOG_X_CORRECTION;
	analog.y = readAnalogAxisLevel(ANALOG_Y_PIN) - ANALOG_Y_CORRECTION;
	analog.y = analog.y * -1;  //reverse axis

	analog.button.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN);

	Serial.print("Analog X:");
	Serial.println(analog.x);

	Serial.print("Analog Y:");
	Serial.println(analog.y);

	if (analog.button.pressed) {
		Serial.println("Button pressed");
		resetPosition(currentPosition);
	} else {
		Serial.println("Button not pressed");
	}

	move(analog.x, analog.y);

	Serial.println("Current Dot Position x:" + (String)currentPosition.x + " y:" + (String)currentPosition.y);

	delay(MOVING_TIME);
}

byte readAnalogAxisLevel(int pin) {
	return map(analogRead(pin), 0, 1023, 0, 255);
}

bool isAnalogButtonPressed(int pin) {
	return digitalRead(pin) == 0;
}

void resetPosition(position &pos) {
	for (int thisPin = 0; thisPin < 8; thisPin++) {
		pinMode(col[thisPin], OUTPUT);
		pinMode(row[thisPin], OUTPUT);
		digitalWrite(col[thisPin], HIGH);
		digitalWrite(row[thisPin], LOW);
	}

	digitalWrite(row[0], HIGH);
	digitalWrite(col[0], LOW);
	pos.x = 0;
	pos.y = 0;
}

void move(short x, short y) {
	position oldPosition = currentPosition;

	if (x > MOVE_THRESHOLD && oldPosition.x < 7) {
		digitalWrite(col[oldPosition.x + 1], LOW);
		digitalWrite(col[oldPosition.x], HIGH);
		currentPosition.x = oldPosition.x + 1;
	}

	if (x < -1 * MOVE_THRESHOLD && oldPosition.x > 0) {
		digitalWrite(col[oldPosition.x - 1], LOW);
		digitalWrite(col[oldPosition.x], HIGH);
		currentPosition.x = oldPosition.x - 1;
	}

	if (y < -1 * MOVE_THRESHOLD && oldPosition.y < 7) {
		digitalWrite(row[oldPosition.y + 1], HIGH);
		digitalWrite(row[oldPosition.y], LOW);
		currentPosition.y = oldPosition.y + 1;
	}

	if (y > MOVE_THRESHOLD && oldPosition.y > 0) {
		digitalWrite(row[oldPosition.y - 1], HIGH);
		digitalWrite(row[oldPosition.y], LOW);
		currentPosition.y = oldPosition.y - 1;
	}
}
