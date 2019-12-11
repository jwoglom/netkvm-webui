var Keyboard = window.SimpleKeyboard.default;

let commonKeyboardOptions = {
  onKeyPress: virtKbdPress,
  theme: "simple-keyboard hg-theme-default hg-layout-default",
  
};

let keyboard = new Keyboard(".simple-keyboard-main", {
  ...commonKeyboardOptions,
  /**
   * Layout by:
   * Sterling Butters (https://github.com/SterlingButters)
   */
  layout: {
    default: [
      "{escape} {f1} {f2} {f3} {f4} {f5} {f6} {f7} {f8} {f9} {f10} {f11} {f12}",
      "` 1 2 3 4 5 6 7 8 9 0 - = {backspace}",
      "{tab} q w e r t y u i o p [ ] \\",
      "{capslock} a s d f g h j k l ; ' {enter}",
      "{shiftleft} z x c v b n m , . / {shiftright}",
      "{controlleft} {winleft} {altleft} {space} {altright} {winright} {controlright}"
    ],
    shift: [
      "{escape} {f1} {f2} {f3} {f4} {f5} {f6} {f7} {f8} {f9} {f10} {f11} {f12}",
      "~ ! @ # $ % ^ & * ( ) _ + {backspace}",
      "{tab} Q W E R T Y U I O P { } |",
      '{capslock} A S D F G H J K L : " {enter}',
      "{shiftleft} Z X C V B N M < > ? {shiftright}",
      "{controlleft} {winleft} {altleft} {space} {altright} {winright} {controlright}"
    ]
  },
  display: {
    "{escape}": "esc",
    "{tab}": "tab",
    "{backspace}": "bksp",
    "{enter}": "enter",
    "{capslock}": "caps lock",
    "{shiftleft}": "shift",
    "{shiftright}": "shift",
    "{controlleft}": "ctrl",
    "{controlright}": "ctrl",
    "{altleft}": "alt",
    "{altright}": "alt",
    "{winleft}": "win",
    "{winright}": "win",
  }
});

let keyboardControlPad = new Keyboard(".simple-keyboard-control", {
  ...commonKeyboardOptions,
  layout: {
    default: [
      "{prtscr} {scrolllock} {pause}",
      "{insert} {home} {pageup}",
      "{delete} {end} {pagedown}"
    ]
  }
});

let keyboardArrows = new Keyboard(".simple-keyboard-arrows", {
  ...commonKeyboardOptions,
  layout: {
    default: ["{arrowup}", "{arrowleft} {arrowdown} {arrowright}"]
  }
});

let keyboardNumPad = new Keyboard(".simple-keyboard-numpad", {
  ...commonKeyboardOptions,
  layout: {
    default: [
    ]
  }
});

let keyboardNumPadEnd = new Keyboard(".simple-keyboard-numpadEnd", {
  ...commonKeyboardOptions,
  layout: {
    default: []
  }
});