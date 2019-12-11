#include "mbed.h"
#include "EthernetInterface.h"

#define US_KEYBOARD 1

#include "USBMouseKeyboard.h"
#include "PS2Keyboard.h"
#include "keyboard.h"

USBMouseKeyboard virtkm;
//PS2Keyboard physkbd(p12, p11); // CLK, DAT
Thread ps2thread;
Thread btnThread;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

InterruptIn button(p8);

void runServer();
void runPS2();

EthernetInterface eth;

bool btnLock = false;
bool ethConnected = false;
void btnPressHandle() {
    printf("btnPressHandle\n");
    while (1) {
        while(btnLock == false) {wait(0.01);}
        printf("btnPressHandle trigger\n");

        if (ethConnected)
            virtkm.printf("Status: Listening on IP: %s\n", eth.get_ip_address());
            
        else
            virtkm.printf("Status: Waiting for ethernet\n");
        btnLock = false;
        wait(0.5);
        if (btnLock && ethConnected) {
            virtkm.keyCode('r', KEY_LOGO);
            wait(0.25);
            virtkm.printf("http://kang.wogloms.com/netkvm-webui/?ip=%s", eth.get_ip_address());
            wait(0.1);
            virtkm.keyCode(10, 0);
        }
        wait(0.2);
        btnLock = false;
    }
}
void btnPress() {
    printf("btnPress\n");
    btnLock = true;
}

int main() {
    button.rise(&btnPress);
    printf("Init\n");
    
    ps2thread.start(runPS2);
    btnThread.start(btnPressHandle);
    
    runServer(); // recursive loop
}

bool ps2Enabled = true;

void runPS2() {
    printf("runPS2 init\n");
    keyboard_init();
    while (1) {
        char c = kbd_GetKey();
        if (ps2Enabled) {
            printf("GetKey: %c\n", c);
            if (c >= 'A' && c <= 'Z')
                virtkm.keyCode(c, KEY_SHIFT);
            else if (c == 255)// ctrl
                virtkm.keyCode(0, KEY_CTRL);
            else if (c == 254)
                virtkm.keyCode(0, KEY_ALT); // alt
            else if (c == 253)
                virtkm.keyCode(0, KEY_LOGO); // win
            else if (c == 252)
                virtkm.keyCode(27); // esc
            else if (c == 251)
                virtkm.keyCode(10); // enter
            else if (c == 250)
                virtkm.keyCode(151); // up
            else if (c == 249)
                virtkm.keyCode(150); // down
            else if (c == 248)
                virtkm.keyCode(149); // left
            else if (c == 247)
                virtkm.keyCode(148); // right
            else
                virtkm.keyCode(c);   
        }
    }
    /*
    PS2Keyboard::keyboard_event_t evt_kb;
 
    while (1) {
        if (physkbd.processing(&evt_kb)) {
            printf("[%d]:", evt_kb.type);
            for (int i = 0; i < evt_kb.length; i++) {
                printf("%02x ", evt_kb.scancode[i]);
                int s = evt_kb.scancode[i];
                
                if (s == 0x12) {
                    ps2_shift = !evt_kb.type;
                } else if (s == 0x14) {
                    ps2_ctrl = !evt_kb.type;
                } else if (s == 
                
            }
            printf("\n");
        }
    }*/
}

static char* respNotFound = "HTTP/1.1 404 Not Found\r\nConnection: keep-alive\r\n\r\n";
static char* lenPrefix = "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: POST, GET, OPTIONS\r\nAccess-Control-Allow-Headers:accept, content-type\r\nContent-Length: ";
static char* lenSuffix = "\r\nContent-Type: text/html; charset=utf-8\r\n\r\n";
char* generateResponse(char* body) {
    char* out = (char*)malloc(sizeof(lenPrefix) + sizeof(lenSuffix) + sizeof(body) + 10);
    sprintf(out, "%s%d%s%s", lenPrefix, strlen(body), lenSuffix, body);
    return out;
}

int run_kv(char* key, char* val) {
    printf("run_kv(%s, %s)\n", key, val);
    bool ok = false;
    if (strcmp(key, "printf") == 0) {
        virtkm.printf(val); 
        ok = true;
    } else if (strcmp(key, "move") == 0) {
        char* re = val;
        char* tok = strtok_r(val, ",", &re);
        int cx;
        int cy;
        if (tok != NULL) {
            cx = atoi(tok);
            tok = strtok_r(NULL, ",", &re);
        if (tok != NULL) {
            cy = atoi(tok);
            printf("move: %d %d\n", cx, cy);
            virtkm.move(cx, cy);
            ok = true;
        }
        }  
    } else if (strcmp(key, "click") == 0) {
        if (strcmp(val, "left") == 0) {
            virtkm.click(MOUSE_LEFT); ok=true;
        } else if (strcmp(val, "right") == 0) {
            virtkm.click(MOUSE_RIGHT); ok=true;
        } else if (strcmp(val, "doubleclick") == 0) {
            virtkm.doubleClick(); ok=true;
        }
    } else if (strcmp(key, "keycode") == 0) {
        virtkm.keyCode(atoi(val)); ok=true;
    } else if (strcmp(key, "keycode-ctrl") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL); ok=true;
    } else if (strcmp(key, "keycode-alt") == 0) {
        virtkm.keyCode(atoi(val), KEY_ALT); ok=true;
    } else if (strcmp(key, "keycode-shift") == 0) {
        virtkm.keyCode(atoi(val), KEY_SHIFT); ok=true;
    } else if (strcmp(key, "keycode-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-ctrl-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-alt-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_ALT | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-shift-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_SHIFT | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-ctrl-alt") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_ALT); ok=true;
    } else if (strcmp(key, "keycode-ctrl-alt-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_ALT | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-ctrl-shift") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_SHIFT); ok=true;
    } else if (strcmp(key, "keycode-ctrl-shift-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_SHIFT | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-alt-shift") == 0) {
        virtkm.keyCode(atoi(val), KEY_ALT | KEY_SHIFT); ok=true;
    } else if (strcmp(key, "keycode-alt-shift-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_ALT | KEY_SHIFT | KEY_LOGO); ok=true;
    } else if (strcmp(key, "keycode-ctrl-alt-shift") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_ALT | KEY_SHIFT);
    } else if (strcmp(key, "keycode-ctrl-alt-shift-logo") == 0) {
        virtkm.keyCode(atoi(val), KEY_CTRL | KEY_ALT | KEY_SHIFT | KEY_LOGO);
    } else if (strcmp(key, "media") == 0) {
        // KEY_NEXT_TRACK, KEY_PREVIOUS_TRACK, KEY_STOP, KEY_PLAY_PAUSE, KEY_MUTE, KEY_VOLUME_UP, KEY_VOLUME_DOWN)   
        if (strcmp(val, "next-track") == 0) {
            virtkm.mediaControl(KEY_NEXT_TRACK); ok=true;
        } else if (strcmp(val, "prev-track") == 0) {
            virtkm.mediaControl(KEY_PREVIOUS_TRACK); ok=true;
        } else if (strcmp(val, "stop") == 0) {
            virtkm.mediaControl(KEY_STOP); ok=true;
        } else if (strcmp(val, "play-pause") == 0) {
            virtkm.mediaControl(KEY_PLAY_PAUSE); ok=true;
        } else if (strcmp(val, "mute") == 0) {
            virtkm.mediaControl(KEY_MUTE); ok=true;
        } else if (strcmp(val, "vol-up") == 0) {
            virtkm.mediaControl(KEY_VOLUME_UP); ok=true;
        } else if (strcmp(val, "vol-down") == 0) {
            virtkm.mediaControl(KEY_VOLUME_DOWN); ok=true;
        }
    } else if (strcmp(key, "connect") == 0) {
        ok = true;
    } else if (strcmp(key, "ps2") == 0) {
        if (strcmp(val, "enable") == 0) {
            ps2Enabled = true; ok = true;
            printf("PS2 Enabled\n");
        } else if (strcmp(val, "disable") == 0) {
            ps2Enabled = false; ok = true;
            printf("PS2 Disabled\n");
        }    
    }
    if (ok) return 1;
    return 0;
}

void runServer() {
    int r;
    led1 = 1;
    r = eth.connect();
    printf("eth.connect() = %d\n", r);
    printf("IP Address is %s\n", eth.get_ip_address());
    led2 = 1;
    ethConnected = true;
    TCPServer server;
    server.open(&eth);
    server.bind(eth.get_ip_address(), 80);
    server.listen();
    while (true) {
        led3 = 1;
        led4 = 0;
        printf("waiting\n");
        TCPSocket client;
        SocketAddress addr;
        server.accept(&client, &addr);
        client.set_blocking(false);
        client.set_timeout(250); // Timeout after 250ms
        printf("connect: %s\r\n", addr.get_ip_address());
        led4 = 1;
        char buffer[1024];
        while (true) {
            int n = client.recv(buffer, sizeof(buffer));
            if (n <= 0) break;       
            buffer[n] = '\0';
            
            char* respMsg = respNotFound;
            
            int runcmds = 0;
            
            char* start = strstr(buffer, "STARTCMD;");
            if (start != NULL) {
                start += 9;
                
                char* re1 = start;
                char* cmdarea = strtok_r(start, ";", &re1);
                
                while (cmdarea != NULL) {
                    
                    //printf("cmdarea: %s\n", cmdarea);
                    char* re2 = cmdarea;
                    char* tok = strtok_r(cmdarea, ":", &re2);
                    char* ckey;
                    char* cval;
                    if (tok != NULL) {
                        ckey = tok;
                        tok = strtok_r(NULL, ":", &re2);
                    if (tok != NULL) {
                        cval = tok;
                        runcmds += run_kv(ckey, cval);
                    }
                    }
                    
                    cmdarea = strtok_r(NULL, ";", &re1);
                }
                
                
                if (runcmds > 0) {
                    respMsg = generateResponse("OK");
                } else {
                    respMsg = generateResponse("ERROR");
                }
            }
            
               
            int sentN = client.send(respMsg, strlen(respMsg));
            free(respMsg);

            
            printf("resp: %d\r\n", sentN);
            client.close();
            if (sentN <= 0) break;
        }
        
        client.close();
        printf("closed\r\n");    
    }
    
    //eth.disconnect();
}
