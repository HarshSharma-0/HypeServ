#ifndef VT100
#define VT100

// Define text color codes
#define VT100_COLOR_BLACK       "\033[1;30m"
#define VT100_COLOR_RED         "\033[1;31m"
#define VT100_COLOR_GREEN       "\033[1;32m"
#define VT100_COLOR_YELLOW      "\033[1;33m"
#define VT100_COLOR_BLUE        "\033[1;34m"
#define VT100_COLOR_MAGENTA     "\033[1;35m"
#define VT100_COLOR_CYAN        "\033[1;36m"
#define VT100_COLOR_WHITE       "\033[1;37m"

// Define background color codes
#define VT100_BACKGROUND_BLACK  "\033[1;40m"
#define VT100_BACKGROUND_RED    "\033[1;41m"
#define VT100_BACKGROUND_GREEN  "\033[1;42m"
#define VT100_BACKGROUND_YELLOW "\033[1;43m"
#define VT100_BACKGROUND_BLUE   "\033[1;44m"
#define VT100_BACKGROUND_MAGENTA "\033[1;45m"
#define VT100_BACKGROUND_CYAN   "\033[1;46m"
#define VT100_BACKGROUND_WHITE  "\033[1;47m"

// Define text style codes
#define VT100_TEXT_BOLD         "\033[1m"
#define VT100_TEXT_DIM          "\033[2m"
#define VT100_TEXT_UNDERLINE    "\033[4m"
#define VT100_TEXT_BLINK        "\033[5m"
#define VT100_TEXT_REVERSE      "\033[7m"
#define VT100_TEXT_HIDDEN       "\033[8m"

// Define reset code
#define VT100_COLOR_RESET       "\033[0m"

// Define cursor movement codes
#define VT100_CURSOR_UP(n)        "\033[" #n "A"
#define VT100_CURSOR_DOWN(n)      "\033[" #n "B"
#define VT100_CURSOR_FORWARD(n)   "\033[" #n "C"
#define VT100_CURSOR_BACKWARD(n)  "\033[" #n "D"
#define VT100_CURSOR_NEXT_LINE(n) "\033[" #n "E"
#define VT100_CURSOR_PREV_LINE(n) "\033[" #n "F"
#define VT100_CURSOR_POSITION(x, y) "\033[" #x ";" #y "H"
#define VT100_CURSOR_SAVE         "\033[s"
#define VT100_CURSOR_RESTORE      "\033[u"
#define VT100_CURSOR_UP_ONE       "\x1b[A"

// Define clear screen codes
#define VT100_CLEAR_SCREEN        "\033[2J"
#define VT100_CLEAR_SCREEN_UP     "\033[1J"
#define VT100_CLEAR_SCREEN_DOWN   "\033[0J"
#define VT100_CLEAR_LINE          "\033[2K"
#define VT100_CLEAR_LINE_UP       "\033[1K"
#define VT100_CLEAR_LINE_DOWN     "\033[0K"


#endif // VT100_H
