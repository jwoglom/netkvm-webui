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
    "{f1}": "F1",
    "{f2}": "F2",
    "{f3}": "F3",
    "{f4}": "F4",
    "{f5}": "F5",
    "{f6}": "F6",
    "{f7}": "F7",
    "{f8}": "F8",
    "{f9}": "F9",
    "{f10}": "F10",
    "{f11}": "F11",
    "{f12}": "F12",
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

let keyboardMedia = new Keyboard(".simple-keyboard-media", {
  ...commonKeyboardOptions,
  layout: {
    default: [
        "{prevtrack} {playpause} {stop} {nexttrack}",
        "{mute} {voldown} {volup}"
    ]
  },
  display: {
    "{prevtrack}": "⏪",
    "{playpause}": "▶️⏸️",
    "{stop}": "⏹",
    "{nexttrack}": "⏩",
    "{mute}": "🔇",
    "{voldown}": "🔉-",
    "{volup}": "🔊+",
  }
});

let keyboardNumPadEnd = new Keyboard(".simple-keyboard-numpadEnd", {
  ...commonKeyboardOptions,
  layout: {
    default: []
  }
});