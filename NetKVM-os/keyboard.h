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
 
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "PS2KB.h"
#include "PS2KB_INIT.h"
 
#include "stdint.h"
/**This is basically a straight rip off of my x86 OS project AlloyOS. I just ported the keyboard driver from it cause it always treated me well**/
 
 
#define KEYBOARD_DATAPIN p11
#define KEYBOARD_CLOCKPIN p12
 
//how many keys the buffer can hold
#define KBD_BUFFER_SIZE 128 
 
//key defines
#define LSHIFT_KEY 0x12
#define RSHIFT_KEY 0x59
 
#define CTRL_KEY 0xF3
#define ALT_KEY 0xF4
#define CAPS_KEY 0x58
#define NUM_KEY 0x77
#define SCROLL_KEY 0xF7
//#define F_BASE_KEY 0xFF //59 is F1, 60 is F2, and so on until F10
#define HOME_KEY 0xFF
#define UP_KEY 0xFF
#define PAGE_UP_KEY 0xFF
#define LEFT_KEY 0xFF
#define RIGHT_KEY 0xFF
#define END_KEY 0xFF
#define DOWN_KEY 0xFF
#define PAGE_DOWN_KEY 0xFF
#define INSERT_KEY 0xFF
#define DEL_KEY 0xFF
#define F11_KEY 0xFF
#define F12_KEY 0xFF
 
#define SCROLL_LED 1
#define NUM_LED 2
#define CAPS_LED 4
 
 
extern const char kbdus[0x84];
extern const char kbdus_caps[0x84];
 
typedef struct {
    unsigned char caps;
    unsigned char shift;
    unsigned char scroll;
    unsigned char num;
    unsigned char ctrl;
    unsigned char alt;
}
shift_locks; /*for simplicity and speed*/
 
extern volatile shift_locks kbd_shifts;
 
typedef struct {
    uint16_t scancode;
    uint8_t asci;
}kbd_key;
 
void keyboard_callback(PS2KB kb, uint8_t val);
void keyboard_init();
 
int kbd_PutBuffer(uint16_t scan,uint8_t asci);
 
kbd_key kbd_PopBuffer();
uint8_t kbd_GetKey();
void kbd_update_leds(uint8_t status);
int kbd_DoShifts(uint8_t scan);
int kbd_DoUnshifts(uint8_t scan);
void keyboard_callback(PS2KB kb, uint8_t val);
 
 
 
#endif