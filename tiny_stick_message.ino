/*=================================================
 * Tiny Stick Message
 * 
 * Display a "ghost message" on the tiny stick RGB Leds.
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN 3

// We have 8 output LEDs in our current incarnation.
#define OUTPUT_LINES 8


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(OUTPUT_LINES, LED_PIN, NEO_GRB+NEO_KHZ800);

typedef enum
{
  TEXT_DIR_FWD = 1,
  TEXT_DIR_BACK
} text_dir_type;

typedef enum
{
  LETTER_DIR_1_BOTTOM = 1,
  LETTER_DIR_1_TOP = 2
} letter_dir_type;

text_dir_type text_dir = TEXT_DIR_FWD;
letter_dir_type letter_dir = LETTER_DIR_1_TOP;

uint8_t char_index=0;
uint8_t column_index=0;

// A:
// 0 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 1 1 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
uint8_t A[] = {0, 0x3f, 0x48, 0x48, 0x3f, 0};

// B:
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 1 1 0
uint8_t B[] = {0, 0x7F, 0x49, 0x49, 0x36, 0};

// C
// 0 1 1 1
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0
// 0 1 1 1
uint8_t C[] = {0, 0x3E, 0x41, 0x41, 0x41, 0};


// D:
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 1 1 0
uint8_t D[] = {0, 0x7F, 0x41, 0x41, 0x3E, 0};


// E:
// 1 1 1 1
// 1 0 0 0
// 1 0 0 0
// 1 1 1 1
// 1 0 0 0 
// 1 0 0 0
// 1 1 1 1
uint8_t E[] = {0, 0x7F, 0x49, 0x49, 0x49, 0};

// F:
// 1 1 1 1
// 1 0 0 0
// 1 0 0 0
// 1 1 1 1
// 1 0 0 0 
// 1 0 0 0
// 1 0 0 0
uint8_t F[] = {0, 0x7F, 0x48, 0x48, 0x48, 0};

// G
// 0 1 1 0
// 1 0 0 1
// 1 0 0 0
// 1 0 0 0
// 1 0 1 1
// 1 0 0 1
// 0 1 1 0
uint8_t G[] = {0, 0x3E, 0x41, 0x45, 0x26, 0};

// H:
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 1 1 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
uint8_t H[] = {0, 0x7F, 0x08, 0x08, 0x7f, 0};

// I:
// 1 1 1 0
// 0 1 0 0
// 0 1 0 0 
// 0 1 0 0
// 0 1 0 0
// 0 1 0 0 
// 1 1 1 0
uint8_t I[] = {0, 0x41, 0x7F, 0x41, 0x0, 0};

// J:
// 0 0 0 1
// 0 0 0 1
// 0 0 0 1 
// 0 0 0 1
// 0 0 0 1
// 1 0 0 1
// 0 1 1 0
uint8_t J[] = {0, 0x02, 0x01, 0x01, 0x3E, 0};

// K:
// 1 0 0 0 1
// 1 0 0 1 0
// 1 0 1 0 0 
// 1 1 0 0 0
// 1 0 1 0 0
// 1 0 0 1 0
// 1 0 0 0 1
uint8_t K[] = {0, 0x7f, 0x08, 0x14, 0x22, 0x41};

// L:
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0 
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0
// 1 1 1 1
uint8_t L[] = {0, 0x7f, 0x01, 0x01, 0x01, 0};

// M:
// 1 0 0 0 1
// 1 1 0 1 1
// 1 0 1 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
uint8_t M[] = {0, 0x7f, 0x20, 0x10, 0x20, 0x7F};

// N:
// 1 0 0 0 1
// 1 1 0 0 1
// 1 0 1 0 1
// 1 0 1 0 1
// 1 0 1 0 1
// 1 0 0 1 1
// 1 0 0 0 1
uint8_t N[] = {0, 0x7F,0x20, 0x1C, 0x02, 0x7F};

// O:
// 0 1 1 1 0
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 0 1 1 1 0
uint8_t O[] = {0, 0x3E, 041, 0x41, 0x41, 0x3E};


// P
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 1 1 0
// 1 0 0 0
// 1 0 0 0
// 1 0 0 0
uint8_t P[] = {0, 0x7f, 0x48, 0x48, 0x30, 0};

// Q:
// 0 1 1 1 0
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 1 0 1
// 1 0 0 1 1
// 0 1 1 1 1
uint8_t Q[] = {0, 0x3E, 041, 0x45, 0x43, 0x3F};

// R
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 1 1 0
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
uint8_t R[] = {0, 0x7f, 0x48, 0x48, 0x37, 0};

// S
// 0 1 1 0
// 1 0 0 1
// 1 0 0 0
// 0 1 1 0
// 0 0 0 1
// 1 0 0 1
// 0 1 1 0
uint8_t S[] = {0, 0x32, 0x49, 0x49, 026, 0};


// T
// 1 1 1 0
// 0 1 0 0
// 0 1 0 0
// 0 1 0 0
// 0 1 0 0
// 0 1 0 0
// 0 1 0 0
uint8_t T[] = {0, 0x40, 0x7f, 0x40, 0, 0};

// U
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 1 0 0 1
// 0 1 1 0
uint8_t U[] = {0, 0x7e, 0x01, 0x01, 0x7e, 0};

// V
// 1 0 0 0 1
// 1 0 0 0 1
// 0 1 0 1 0
// 0 1 0 1 0
// 0 1 0 1 0
// 0 0 1 0 0
// 0 0 1 0 0
uint8_t V[] = {0, 0x60, 0x1c, 0x03, 0x1c, 0x60};

// W
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 0 0 1
// 1 0 1 0 1
// 1 0 1 0 1
// 0 1 0 1 0
uint8_t W[] = {0, 0x7E, 0x01, 0x06, 0x01, 0x7E};

// X
// 1 0 0 0 1
// 0 1 0 1 0
// 0 1 0 1 0
// 0 0 1 0 0
// 0 1 0 1 0
// 0 1 0 1 0
// 1 0 0 0 1
uint8_t X[] = {0, 0x41, 0x36, 0x04, 0x36, 0x41};

// Y
// 1 0 0 0 1
// 0 1 0 1 0
// 0 1 0 1 0
// 0 0 1 0 0
// 0 0 1 0 0
// 0 0 1 0 0
// 0 0 1 0 0
uint8_t Y[] = {0, 0x40, 0x30, 0x0F, 0x30, 0x40};

// Z
// 1 1 1 1 1
// 0 0 0 1 0
// 0 0 0 1 0
// 0 0 1 0 0
// 0 1 0 0 0
// 0 1 0 0 0
// 1 1 1 1 1
uint8_t Z[] = {0, 0x41, 0x47, 0x49, 0x71, 0x41};

// empty:
uint8_t blank[] = {0, 0, 0, 0, 0, 0};

uint8_t *char_map[] = {A, B, C, D, E, F, G, H, I, J, 
                   K, L, M, N, O, P, Q, R, S, T,
                   U, V, W, X, Y, Z};

char display_string[] = "stay safe  ";

//==============================================================================================
// FUNCTION:  write_and_latch_byte
//
// Writes an entire byte to the RGB LEDs.  Note this function
// goes MSB first.
//==============================================================================================
#define BITS_IN_BYTE 8
void write_and_latch_byte( int data, uint32_t color )
{
  int temp_bit;
  int temp_data;
  int i;

  // Make sure it's only one byte of data...mask off the rest.
  data &= 0xFF;
    
  temp_data = data;
  
  for (i = 0; i < BITS_IN_BYTE; i++)
  {
    // we only want the MSB
    temp_bit = temp_data & 0x80;
    temp_bit = temp_bit >> 7;

    if (temp_bit) pixels.setPixelColor(i, color);
    else pixels.setPixelColor(i, 0x00);
    
    // now shift our byte to get the next bit
    temp_data = temp_data << 1;     
  }

  pixels.show();

}

//==============================================================================================
// FUNCTION:  write_and_latch_byte_lsb_first
//
// Writes an entire byte to the rgb LEDs.  Note this function
// goes LSB first.
//==============================================================================================
void write_and_latch_byte_lsb_first( int data, uint32_t color)
{
  int temp_bit;
  int temp_data;
  int i;

  // Make sure we're just grabbing one byte
  data &= 0xFF;
    
  temp_data = data;
  
  for (i = 0; i < BITS_IN_BYTE; i++)
  {
    // we only want the LSB
    temp_bit = temp_data & 0x01;

    if (temp_bit) pixels.setPixelColor(i, color);
    else pixels.setPixelColor(i, 0x00);
    
    // now shift our byte to get the next bit
    temp_data = temp_data >> 1;     
  }

  pixels.show();
  
}

//==============================================================================================
// FUNCTION:  setup
//==============================================================================================
void setup() 
{
  int i;
  
  pixels.begin();
  
  // now a quick LED test...write a 1 to all registers.
  for (i=0; i<OUTPUT_LINES; i++)
  {
    pixels.setPixelColor(i, 0x0000FF);  
    pixels.show();
    delay(500);
  }

  // ...and now put them back to black before starting for real.
  for (i=0; i<OUTPUT_LINES; i++)
  {
    pixels.setPixelColor(i, 0x0);
  }
  pixels.show();
  delay(1000);
}

//==============================================================================================
// FUNCTION:  loop
//==============================================================================================
void loop() 
{
  uint8_t *array;
  uint8_t display_strlen;
  char display_char;

  display_strlen = strlen(display_string);
  
  if (char_index == display_strlen)
  {
    array = blank;
  }
  else
  {
    display_char = display_string[char_index];
    
    //Serial.print("display char:");
    //Serial.println(display_char);

    if ((display_char >= 'A') && (display_char <= 'Z')) 
    {
      // upper case...use 'A' as a reference into our array.
      array = char_map[display_char - 'A'];  
    }
    else if ((display_char >= 'a') && (display_char <= 'z'))
    {
      // lower case char.  Use 'a' to reference into our array.
      array = char_map[display_char - 'a'];
    }
    else 
    {
      // invalid character.  Make it a blank.
      array = blank;
    }
  }

  // by default, we're latching in from LED 1 to 8...meaning that write_and_latch_byte
  // will display the row with 1 being the bottom and 8 being the top.  
  if (letter_dir == LETTER_DIR_1_BOTTOM)
  {
    write_and_latch_byte(array[column_index], 0xFF0000);
  }
  // Otherwise, we want to do the writes LSB first, so that 8 is the bottom and 1 is the top.
  else
  {
    write_and_latch_byte_lsb_first(array[column_index], 0xFF0000);
  }
  
  //Serial.print("byte: ");
  //Serial.println(array[column_index]);

  if (text_dir == TEXT_DIR_FWD)
  {
    column_index++;
    if (column_index == 6)
    {
      column_index = 0;
      char_index++;
      if (char_index == display_strlen + 1) char_index = 0;
    }
  }
  else
  {
    if (column_index == 0)
    {
      column_index = 5;
      if (char_index == 0)
      {
        char_index = display_strlen;
      }
      else
      {
        char_index--;
      }
    }
    else
    {
      column_index--;
    }
  }

  delayMicroseconds(500);

  
 
}
