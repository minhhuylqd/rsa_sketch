#include "utils.h"

String str_message = "";
char* chr_message = "";
//char command[1000] = {0};
char* command = "";

const byte numChars = 64;
char receivedChars[numChars];
char tempChars[numChars];

//char message[numChars] = {0};
char* message = "";
int key = 0;
int n = 0;

boolean newData = false;

void setup() {
  Serial.begin(115200);
  while(!Serial); 
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    showParsedData();
    newData = false;
  }
}



void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; 
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}



void parseData() {      

  char * strtokIndx; 

  strtokIndx = strtok(tempChars,",");      
  //strcpy(command, strtokIndx);
  command = strtokIndx;
    
  strtokIndx = strtok(NULL, ",");
  //strcpy(message, strtokIndx);
  message = strtokIndx;
 
  strtokIndx = strtok(NULL, ",");
  n = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  key = atoi(strtokIndx);

}

//============

void showParsedData() {
  
  Serial.print("Command: ");
  Serial.println(command);
  Serial.println("Message: ");
  Serial.println(message);
  
  Serial.print("n: ");
  Serial.println(n);
  Serial.print("Key: ");
  Serial.println(key);
  

  if (strstr(command, "encrypt") != NULL) {
    int length = strlen(message);
    int* cipher_list = encrypt(message, key, n);
    Serial.print("Encrypted ascii list: ");
    for (int i = 0; i < length; i++) {
      Serial.print(cipher_list[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }

  else if (strstr(command, "decrypt") != NULL) {
     while (message[0] == ' ') {
       memmove(message, message+1, strlen(message));
     }
     int index = 0;
     int cipher_list[1000] = {0};

     for (int i = 0; message[i] != '\0'; i++) {
       if (message[i] == ' ') {
          index++;
       }
       else {
          cipher_list[index] = cipher_list[index] * 10 + (message[i] - 48);
       }
     }

    /* for (int i = 0; i <= index; i++) {
      Serial.println(cipher_list[i]);
    } */
     
    Serial.print("Decrypted string: ");
    char* decrypt_string = decrypt(cipher_list, key, n, index + 1);
    Serial.println(decrypt(cipher_list, key, n, index + 1));
    
  }

//  int hello_list[11] = {154, 43, 166, 166, 232, 223, 159, 232, 95, 166, 237};
//  int cipher_list[1000] = {154, 43, 166, 166, 232, 223, 159, 232, 95, 166, 237};
//  Serial.println(cipher_list[1]);
//  Serial.println(cipher_list[21]);
//
//  Serial.println(decrypt(cipher_list, 173, n, 11));

}
