#include "MD5.h"
#include "Hash.h"


const byte numChars = 128;
char receivedChars[numChars];

boolean newData = false;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithEndMarker();
    showNewData();
}

//Note: Serial monitor has to set to Newline mode
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char endStr = '\0';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker && rc != endStr) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}


void showNewData() {
    if (newData == true) {
        Serial.print("Original String: ");
        Serial.println(receivedChars);

        //MD5 hashed input string
        unsigned char* hash = MD5::make_hash(receivedChars);
        char* md5str = MD5::make_digest(hash, 16);
        Serial.print("MD5 hashed: ");
        Serial.println(md5str);
        free(md5str);
        free(hash);

        //SHA1 hashed input string
        Serial.print("SHA1 hashed: ");
        Serial.println(sha1(receivedChars));
        
        
        newData = false;
    }
}
