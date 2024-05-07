#pragma region LIBRARY INITIALIZATION
// WATER SENSOR
#include <RBD_Capacitance.h>
#include <RBD_Threshold.h>
#include <RBD_WaterSensor.h>
// BUTTON
#include <ezButton.h>
// OLED SCREEN
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#pragma endregion

#pragma region PIN DECLARATION
// WATER SENSOR
int level_send_pin = 3;
int level_receive_pin = 2;
RBD::WaterSensor water_sensor(level_send_pin, level_receive_pin, 0);

// LED
int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;

// BUTTON
ezButton count_button(13);
ezButton cal_button(12);

// OLED SCREEN
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#pragma endregion

#pragma region SETTING
// SETTINGS
bool screen_toggle = true;
bool led_test_toggle = true;
bool calibration_toggle = true;
bool countdown_toggle = true;
bool water_sensor_toggle = true;
bool show_raw_value_toggle = true;
bool timer_toggle = true;


#pragma endregion

#pragma region SETUP FUNCTION
void setup() {
	// INTIALIZE SERIAL
	Serial.begin(115200);
	Serial.println(" BOOTING SYSTEM  ");
	
	// LEDS
	pinMode(red_light_pin, OUTPUT);
	pinMode(green_light_pin, OUTPUT);
	pinMode(blue_light_pin, OUTPUT); 

	// CALIBRATION
	if (calibration_toggle == true){
		cal_button.setDebounceTime(50); // set debounce time to 50 milliseconds
	}

	// COUNTDOWN
	if (countdown_toggle == true){
		count_button.setDebounceTime(50); // set debounce time to 50 milliseconds
	}

	// OLED SCREEN
	if (screen_toggle == true){
		if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
			Serial.println("SSD1306 allocation failed");
			for(;;);
		}
		display.clearDisplay();
		display.display();
		display_text(0,0,1,"KEVIN'S DRINKING GAME");
		display_text(0,8,1,"Version 69.420");
		draw_star();
	}

}
#pragma endregion

#pragma region VARIABLE DECLARATIONS
// CALLIBRATION
int raw_value = 0;
int holding_value = 65;
int drinking_value = 150;
int temp_value = 0;

// COUNTDOWN VARIABLES

// BUTTON VARIABLES
bool cal_button_state = HIGH;
double cal_button_time = 0;
bool prev_cal_button_state = HIGH;
bool count_button_state = HIGH;
double count_button_time = 0;
bool prev_count_button_state = HIGH;


// TIMER VARIABLES
bool drinking = false;
bool done_drinking = false;
bool prev_drinking = false;
double drink_time = 0;


#pragma endregion

#pragma region MAIN LOOP
void loop() {
	// TEST RGB LIGHT
	if (led_test_toggle == true){
		rainbow();
		rainbow();
		rainbow();
		RGB_color(255, 255, 255);
		led_test_toggle = false;
	}
	
	// CALIBRATION
	if (calibration_toggle == true){
		// BUTTON INITALIZATION
		cal_button.loop();
		cal_button_state = cal_button.getStateRaw();
		if (cal_button_state != prev_cal_button_state){
			if (cal_button_state == LOW){
				temp_value = raw_value+3;
				cal_button_time = millis();
			}
			else if (cal_button_state == HIGH){
				cal_button_time = 0;
			}
			prev_cal_button_state = cal_button_state;
		}
		if(cal_button_state == LOW){
			long diff = millis()-cal_button_time;
			if(diff>1500){
				holding_value = temp_value;
			}
		}
	}

	// COUNTDOWN
	if (countdown_toggle == true){
		count_button.loop();
		count_button_state = count_button.getStateRaw();
		if (count_button_state != prev_count_button_state){
			if (count_button_state == LOW){
				count_button_time = millis();
			}
			else if (count_button_state == HIGH){
				count_button_time = 0;
			}
			prev_count_button_state = count_button_state;
		}
		if(count_button_state == LOW){
			long diff = millis()-count_button_time;
			if(diff>1500){
				countdown();
			}
		}

	}

    // WATER SENSOR
	if (water_sensor_toggle == true){
		water_sensor.update();
		if(water_sensor.onRawValueChange()) {
			// GET RAW VALUE
			raw_value = (raw_value+(water_sensor.getRawValue()))/2;
			if (show_raw_value_toggle == true){
				display_text(0,48,1,(("RV: ")+(String(raw_value))+(" T: ")+(String(holding_value))));
			}
			
			// DETERMINE STATE OF CUP
			drinking = false;
			if (raw_value<holding_value){
				RGB_color(50, 50, 50);  // IDLE // LOW WHITE
			}
			else if (raw_value<drinking_value){
				RGB_color(0, 0, 255);  // DRINKING // BLUE
				drinking = true;
			}
            
            // TIMER
			if (timer_toggle == true){
				// DETERMINE WHEN TO START TIMER
				done_drinking = false;
				if (drinking != prev_drinking){
					if (drinking == true){
						done_drinking = false;
						drink_time = millis();
					}
					else if (drinking == false){
						done_drinking = true;
						timer_toggle = false;
					}
					prev_drinking = drinking;
				}

				// END TIMER AND PRINT TIME
				if (done_drinking == true){
					drink_time = millis()-drink_time;
					display_text(0,16,2,(String(drink_time/1000)));
					display_text(0,32,1,"SECONDS");
					done_drinking = false;
					drink_time = 0;
                }
            }
        }
    }
}
#pragma endregion

void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
	analogWrite(red_light_pin, red_light_value);
	analogWrite(green_light_pin, green_light_value);
	analogWrite(blue_light_pin, blue_light_value);
}

void countdown(){
	draw_star();
	RGB_color(0, 0, 0);
	delay(3000);
	RGB_color(255, 0, 0);
	delay(200);
	RGB_color(0, 0, 0);
	delay(1000);
	RGB_color(255, 255, 0);
	delay(200);
	RGB_color(0, 0, 0);
	delay(1000);
	RGB_color(0, 255, 0);
	delay(200);
	RGB_color(0, 0, 0);
	delay(1000);
	RGB_color(255, 255, 255);
	timer_toggle = true;
}

void display_text(int x, int y, int tsize, String str){
	display.fillRect(x, y, 128, tsize*8, BLACK);
	display.setTextSize(tsize);             
	display.setTextColor(WHITE);        
	display.setCursor(x,y);
	//display.print(str);
	drawCentreString(str,x,y);
	display.display();
}

void drawCentreString(const String &buf, int x, int y){
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor((x - w/ 2)+64, y);
    display.print(buf);
}

void draw_star(void) {
	static const unsigned char PROGMEM logo_bmp[] =
  { 0b00000000, 0b11000000,
	0b00000001, 0b11000000,
	0b00000001, 0b11000000,
	0b00000011, 0b11100000,
	0b11110011, 0b11100000,
	0b11111111, 0b11111000,
	0b01111111, 0b11111111,
	0b00111111, 0b11111111,
	0b00011111, 0b11111100,
	0b00001111, 0b11110000,
	0b00011111, 0b11100000,
	0b00111111, 0b11100000,
	0b00111111, 0b11110000,
	0b01111100, 0b11110000,
	0b01110000, 0b01110000,
	0b00000000, 0b00110000 };
	display.fillRect(0, 16, 128, 112, BLACK);
	display.drawBitmap(
	(display.width()  - 16 ) / 2,
	(display.height() - 16 ) / 2,
	logo_bmp, 16, 16, 1);
	display.display();
}

void rainbow(){
	int i = 0;
	// red to orange
	for (i = 0; i <= 127; i++) {
		RGB_color(255, i, 0);
		delay(2);
	}
	// yellow to orange
	for (i = 127; i <= 255; i++) {
		RGB_color(255, i, 0);
		delay(2);
	}
	// yellow to green
	for (i = 255; i>= 0; i--) {
		RGB_color(i, 255, 0);
		delay(1);
	}
	// green to blue
	for (i = 255;  i>= 0; i--) {
		RGB_color(0, i, 255-i);
		delay(1);
	}
	// blue to purple
	for (i = 0;  i<= 127; i++) {
		RGB_color(i, 0, 255-i);
		delay(2);
	}
	// purple to red
	for (i = 0;  i<= 127; i++) {
		RGB_color(127+1, 0, 127-i);
		delay(2);
	}
}