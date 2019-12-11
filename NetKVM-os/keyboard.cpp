/*
<Copyright Header>
Copyright (c) 2012 Jordan "Earlz" Earls  <http://lastyearswishes.com>
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
 
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
This file is part of the MbedConsole project
*/
#include "keyboard.h"
/**This is basically a straight rip off of my x86 OS project AlloyOS. I just ported the keyboard driver from it cause it always treated me well**/
 
 
const char kbdus[0x84] =
{
    0, 
    0, //1 F9
    0, //2 ?
    0, //3 f5
    0, //4 f3
    0, //5 F1
    0, //6 F2
    0, //7 F12
    0, //8 ?
    0, //9 F10
    0, //A F8
    0, //B F6
    0, //C F4
    '\t',
    '`',
    0, //F ?
    0, //10 ?
    0, //11 L alt
    0, //L shift
    0, //13 ?
    0, //14 L CTRL
    'q', '1',
    0, 0, 0, //17-19 ?
    'z', 's', 'a', 'w', '2',
    0, 0, //1F-20 ?
    'c', 'x', 'd', 'e', '4', '3',
    0, 0, //27-28 ? 
    ' ', 'v', 'f', 't', 'r', '5', 
    0, 0, //2F-30 ?
    'n', 'b', 'h', 'g', 'y', '6',
    0, 0, 0, //37-39 ?
    'm','j', 'u', '7', '8',
    0, 0, //3F-40 ?
    ',', 'k', 'i', 'o', '0', '9',
    0, 0, //47-48 ?
    '.', '/', 'l', ';', 'p', '-',
    0, 0, 0, //4f-51 ?
    '\'',
    0, //53 ?
    '[', '=', 
    0, 0, //56-57 ?
    0, //58 caplock
    0, //59 R shift
    '\n', //5A enter
    ']', 
    0, //5C ?
    '\\',
    0, 0, 0, 0, 0, 0, 0, 0, //5E-65 ?
    '\b', //backspace
    0, 0, //67-68
    0, //69 End 1
    0, //6a ?
    '4', //6b left 4
    0, //6c home 7
    0, 0, 0, //6d-6f ?
    '0', //70 ins 0
    0, //71 del .
    '2', //72 down 2
    '5', //73 5
    '6', //74 right 6
    '8', //75 up 8
    27, //76 esc
    0, //77 numlock
    0, //78 f11
    '+', //79 +
    '3', //7A pagedown 3
    '-', //7B
    '*', //7C
    '9', //7D pageup 9
    '0', //7E scroll lock
    0, 0, 0, 0, //7F-82 ?
    0, //83 F7
};
 
 
const char kbdus_caps[0x84] =
{
    0, 
    0, //1 F9
    0, //2 ?
    0, //3 f5
    0, //4 f3
    0, //5 F1
    0, //6 F2
    0, //7 F12
    0, //8 ?
    0, //9 F10
    0, //A F8
    0, //B F6
    0, //C F4
    '\t',
    '~',
    0, //F ?
    0, //10 ?
    0, //11 L alt
    0, //L shift
    0, //13 ?
    0, //14 L CTRL
    'Q', '!',
    0, 0, 0, //17-19 ?
    'Z', 'S', 'A', 'W', '@',
    0, 0, //1F-20 ?
    'C', 'X', 'D', 'E', '#', '$',
    0, 0, //27-28 ? 
    ' ', 'V', 'F', 'T', 'R', '%', 
    0, 0, //2F-30 ?
    'N', 'B', 'H', 'G', 'Y', '^',
    0, 0, 0, //37-39 ?
    'M','J', 'U', '&', '*',
    0, 0, //3F-40 ?
    '<', 'K', 'I', 'O', ')', '(',
    0, 0, //47-48 ?
    '>', '?', 'L', ':', 'P', '_',
    0, 0, 0, //4f-51 ?
    '\"',
    0, //53 ?
    '{', '+', 
    0, 0, //56-57 ?
    0, //58 caplock
    0, //59 R shift
    '\n', //5A enter
    '}', 
    0, //5C ?
    '|',
    0, 0, 0, 0, 0, 0, 0, 0, //5E-65 ?
    '\b', //backspace
    0, 0, //67-68
    0, //69 End 1
    0, //6a ?
    '4', //6b left 4
    0, //6c home 7
    0, 0, 0, //6d-6f ?
    '0', //70 ins 0
    0, //71 del .
    '2', //72 down 2
    '5', //73 5
    '6', //74 right 6
    '8', //75 up 8
    27, //76 esc
    0, //77 numlock
    0, //78 f11
    '+', //79 +
    '3', //7A pagedown 3
    '-', //7B
    '*', //7C
    '9', //7D pageup 9
    '0', //7E scroll lock
    0, 0, 0, 0, //7F-82 ?
    0, //83 F7
};
 
PS2KB_INIT *ps2_kb_init;
PS2KB *ps2_kb;
 
volatile kbd_key *keys;
volatile uint8_t current_key=0;
volatile uint8_t key_got=0;
volatile char pending_key=0;
volatile uint8_t led_status=0;
 
void keyboard_init()
{
    keys=(kbd_key*)malloc(256*sizeof(kbd_key));
    kbd_shifts.shift=0;
    kbd_shifts.caps=0;
    kbd_shifts.num=0;
    kbd_shifts.scroll=0;
    kbd_shifts.ctrl=0;
    kbd_shifts.alt=0;
    ps2_kb_init=new PS2KB_INIT(KEYBOARD_CLOCKPIN, KEYBOARD_DATAPIN);
    ps2_kb=new PS2KB(KEYBOARD_CLOCKPIN, KEYBOARD_DATAPIN, (KeyboardCallback) &keyboard_callback);
}
 
 
 
volatile shift_locks kbd_shifts;
 
 
 
/**The way the keyboard driver works is this:
the buffer is 256 elements big. key_got and current_key are both
bytes. Rather than setting current_key to 0, the entire buffer is constantly
in use. when a key is pushed, current key is incremented. when a key is got(with safety checks)
key_got is incremented. Also, when it reaches the end of the buffer, it simply wraps around
to the beginning due to byte overflow. The worst that can happen is if 256 bytes get
built up, in which case everything will be screwed up.. I should eventually controlt he capture
of these keys to where not all of them are stored, and they are only stored when needed**/
 
int kbd_PutBuffer(uint16_t scan,uint8_t asci){
    keys[current_key].scancode=scan;
    keys[current_key].asci=asci;
    current_key++;
    pending_key++;;
    return 0;
}
 
kbd_key kbd_PopBuffer(){
    kbd_key k;
    while(pending_key==0){
        //hlt();
    //fill in busy code here    
    }
    
    k.scancode=keys[key_got].scancode;
    k.asci=keys[key_got].asci;
    pending_key--;
    key_got++;
    return k;
}
 
uint8_t kbd_GetKey(){ //this will just return the asci code
    kbd_key k;
    k.asci=0;
    k.scancode=0;
    while(k.scancode==0){
        k=kbd_PopBuffer();
    }
        if (k.scancode == 20)
            return 255; // ctrl
        if (k.scancode == 17)
            return 254; // alt
        if (k.scancode == 31)
            return 253; // win
        if (k.scancode == 118)
            return 252; // esc
        if (k.scancode == 90)
            return 251; // enter
        if (k.scancode == 117)
            return 250; // up
        if (k.scancode == 114)
            return 249; // down
        if (k.scancode == 107)
            return 248; // left
        if (k.scancode == 116)
            return 247; // right
        if (k.asci == 0)
            return kbd_GetKey();
    return k.asci;
}
 
 
void kbd_update_leds(uint8_t status){
    uint8_t tmp;
    //TODO
    /*while((inportb(0x64)&2)!=0){}
    outportb(0x60,0xED);
    
    while((inportb(0x64)&2)!=0){}
    outportb(0x60,status);
    */
}
 
 
 
int kbd_DoShifts(uint8_t scan){
    switch(scan){
        case RSHIFT_KEY:
            kbd_shifts.shift++;
            break;
        case LSHIFT_KEY:
            kbd_shifts.shift++;
            break;
        case CTRL_KEY:
            kbd_shifts.ctrl++;
            break;
        case ALT_KEY:
            kbd_shifts.alt++;
            break;
        case CAPS_KEY:
            led_status^=CAPS_LED;
            kbd_update_leds(led_status);
            kbd_shifts.caps^=1;
            break;
        case NUM_KEY:
            led_status^=NUM_LED;
            kbd_update_leds(led_status);
            kbd_shifts.num^=1;
            break;
        case SCROLL_KEY:
            led_status^=SCROLL_LED;
            kbd_update_leds(led_status);
            kbd_shifts.scroll^=1;
            break;
        default:
            return 0;
            break;
    }
    printf("doshifts: shift%d ctrl%d alt%d\n", kbd_shifts.shift, kbd_shifts.ctrl, kbd_shifts.alt);
    return 1;
}
 
int kbd_DoUnshifts(uint8_t scan){
    switch(scan){
        case RSHIFT_KEY:
            kbd_shifts.shift=0;
            break;
        case LSHIFT_KEY:
            kbd_shifts.shift=0;
            break;
        case CTRL_KEY:
            kbd_shifts.ctrl--;
            break;
        case ALT_KEY:
            kbd_shifts.alt--;
            break;
        case CAPS_KEY:
            //kbd_shifts.caps=0;
            break;
        case NUM_KEY:
            //kbd_shifts.num=0;
            break;
        case SCROLL_KEY:
            //kbd_shifts.scroll=0;
            break;
        default:
            return 0;
            break;
    }
    
    printf("dounshifts: shift%d ctrl%d alt%d\n", kbd_shifts.shift, kbd_shifts.ctrl, kbd_shifts.alt);
    return 1;
}
volatile bool expecting_break=false;
void keyboard_callback(PS2KB kb, uint8_t val) //this is called from interrupt! Must be fast
{
        //stopints();
    if(expecting_break){
        //val^=0xF0;
        kbd_DoUnshifts(val);
        expecting_break=false;
    }else{
        if(val>=0xF0){     
            expecting_break=true;
        }else{
            //add check for 0x84 to make sure we don't go over our keymap
            if(val<=0x84 && kbd_DoShifts(val)==0){ //if not a shift-type key
                
                if ((kbd_shifts.caps >0 && kbd_shifts.shift == 0) || (kbd_shifts.caps == 0 && kbd_shifts.shift > 0)) {
                    printf("buf: %d %d (norm: %d)\n", val, kbdus_caps[val], kbdus[val]);
                    kbd_PutBuffer(val,kbdus_caps[val]);
                }else{
                    printf("buf: %d %d (cap: %d)\n", val, kbdus[val], kbdus_caps[val]);
                    kbd_PutBuffer(val,kbdus[val]);
                }
            }
        }
    }
}