#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_BUF  256

#define IV  0b10110001
#define KEY 0b11001011
#define CTR 0b00110101

#define true 1
#define false 0

#define C_OK 2 // didnt end up using
#define C_ERROR_ENCRYPTION -1 // didnt end up using
#define C_ERROR_DECRYPTION -2 // didnt end up using
#define C_ERROR_ENCRYPTION_EMPTY -3
#define C_ERROR_DECRYPTION_EMPTY -4
#define C_ERROR_PROCESS_COUNTER -5 // didnt end up using
#define C_ERROR_MENU_SELECTION_INVALID -6
#define C_ERROR_DECRYPTION_INPUT_FLOAT -7
#define C_ERROR_MAX_ENTRIES_REACHED -8

void encode(unsigned char*, unsigned char*, int);
void decode(unsigned char*, unsigned char*, int);

unsigned char processCtr(unsigned char, unsigned char);
unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
void printBits(unsigned char);
void printError(int);


int main()
{
  char str[8] = {0};
  int  choice;
  unsigned char pt[MAX_BUF] = {0};
  unsigned char ct[MAX_BUF] = {0};
  int numBytes = 0;
  int numDecode;
  double userInput;
  double userInputInt;

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\nWhat is your selection: ");

  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &choice);
  if(strlen(str) == 0){
    printError(C_ERROR_MENU_SELECTION_INVALID);
    return 0;
  }
  if(choice > 3 || choice < 0){
    printError(C_ERROR_MENU_SELECTION_INVALID);
    return 0;
  }
  else if (choice == 0)
    return 0;

  switch (choice) {
    case 1:
      printf("Enter text to be encrypted: ");
      fgets(pt, MAX_BUF, stdin);
      pt[strcspn(pt, "\n")] = 0;
      numBytes = strlen(pt);
      if (numBytes >= MAX_BUF-1){
        printError(C_ERROR_MAX_ENTRIES_REACHED);
      }
      else if(numBytes == 0){
        printError(C_ERROR_ENCRYPTION_EMPTY);
        return 0;
      }
      encode(pt,ct,numBytes);
      printf("Your encrypted msg: ");
      for (int i = 0; i < numBytes; i++){
        printf("%u ", ct[i]);
      }
      break;
    case 2:
      printf("Enter #s to be decrypted, when finished enter (-1): ");
      do{
        scanf("%lf", &userInput);
        if(modf(userInput, &userInputInt)){
          printError(C_ERROR_DECRYPTION_INPUT_FLOAT);
          return 0;
        }
        numDecode = (int) userInputInt;
        if (numDecode == -1)
          break;
        ct[numBytes] = (unsigned char) numDecode;
        numBytes++;
      } while (numBytes != MAX_BUF);

      if (numBytes == MAX_BUF){
        printError(C_ERROR_MAX_ENTRIES_REACHED);
      }
      else if (numBytes == 0){
        printError(C_ERROR_DECRYPTION_EMPTY);
        return 0;
      }
      decode(ct,pt,numBytes);
      printf("Your decrypted msg: ");
      for(int i = 0; i < numBytes; i++){
        printf("%c", pt[i]);
      }
      break;
  }
  return 0;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n){
  c = (c & (1 << n)) >> n;
  return c;
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n){
  c = c | ( 1 << n);
  return c;
}

/*  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n){
  c = c & (~(1 << n));
  return c;
}

/* Function: printBits
  Purpose: Prints the value in binary, used for testing
  in: character to be printed
*/
void printBits(unsigned char c){
    int bitsArr[8];
    int remainder;
    int leftover = c;
    for (int i = 7; i >= 0; i--){
        remainder = leftover % 2;
        leftover = leftover /2; // this does floor division by default so we dont minus 1
        bitsArr[i] = remainder;
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
        printf("%d", bitsArr[i]);
    printf("\n");
}

/*  Function:  processCtr
  Purpose:   To process counter and produce new counter to be used in encode or decode
       in:   old counter to be changed
       in:   the key to alter the counter
   return:   new processed counter
*/
unsigned char processCtr(unsigned char ctr, unsigned char key){
  unsigned char tempCounter = ctr;
  unsigned char i = 0;
  
  if (tempCounter % 2 > 0)
    i = 1;

  char skip = false;
  for(i; i < 8; i++){
    if (skip == false){
      tempCounter = tempCounter^(getBit(key, i) << i);
      skip = true;
    }
    else
      skip = false;
  }
  return tempCounter;
}

/*  Function:  encryptByte
  Purpose:   Encrypts the appropriate char in cipher
       in:   plaintext char 
       in:   counter
       in:   char of previous cipher
   return:   char of new cipher
*/
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){
  unsigned char cipherText = 0;
  
  for (int i = 0; i < 8; i++){
    if(getBit(ctr,i) == 0){
      if (getBit(pt, i) ^ getBit(prev, 7-i) == 1){
        cipherText = setBit(cipherText,i);
      }
    }
    else{
      if (getBit(pt,i) ^ getBit(prev,i) == 1){
        cipherText = setBit(cipherText,i);
      }
    }
  }
  return cipherText;
}

/*  Function:  decryptByte
  Purpose:   Decrypts the appropriate char in plaintext
       in:   cipher char 
       in:   counter
       in:   char of previous cipher
   return:   char of new plaintext
*/
unsigned char decryptByte(unsigned char ct, unsigned char ctr, unsigned char prev){
  unsigned char plainText = 0;
  
  for (int i = 0; i < 8; i++){
    if(getBit(ctr,i) == 0){
      if (getBit(ct, i) ^ getBit(prev, 7-i) == 1){
        plainText = setBit(plainText,i);
      }
    }
    else{
      if (getBit(ct,i) ^ getBit(prev,i) == 1){
        plainText = setBit(plainText,i);
      }
    }
  }
  return plainText;
}

/*  Function:  encode
  Purpose:   Uses processCtr and encryptByte to encrypt the list of characters into their corresponding ciphers
       in:   Pointer to plaintext array of chars
   in/out:   Pointer to ciphertext array with ASCII values
       in:   Number of chars to be processed
   return:   None
*/
void encode(unsigned char* pt, unsigned char* ct, int numBytes){
  unsigned char counter = processCtr(CTR,KEY);
  unsigned char prev = IV;
  ct[0] = encryptByte(pt[0],counter,prev);
  prev = ct[0];
  counter++;
  for (int i = 1; i < numBytes; i++){
    counter = processCtr(counter,KEY);
    ct[i] = encryptByte(pt[i],counter,prev);
    prev = ct[i];
    counter++;
  }
}

/*  Function:  decode
  Purpose:   Uses processCtr and decryptByte to decrypt the list of ASCII values into their corresponding plain text
       in:   Pointer to cipher text array of char ASCII values
   in/out:   Pointer to plain text array with chars
       in:   Number of chars to be processed
   return:   None
*/
void decode(unsigned char* ct, unsigned char* pt, int numBytes){
  unsigned char counter = processCtr(CTR,KEY);
  unsigned char prev = IV;
  pt[0] = decryptByte(ct[0],counter,prev);
  prev = ct[0];
  counter++;
  for (int i = 1; i < numBytes; i++){
    counter = processCtr(counter,KEY);
    pt[i] = decryptByte(ct[i],counter,prev);
    prev = ct[i];
    counter++;
  }
}

/*  Function:  printError
  Purpose:   Prints som efriendly msgs if an error occurs
       in:   integer representing an error code defined at the start of the program
   return:   None
*/
void printError(int error){
  if (error == -3){
    printf("\nDecryption msg is empty! Restart program.");
  }
  else if (error == -4){
    printf("\nDecryption msg is empty! Restart program.");
  }
  else if (error == -6){
    printf("\nInvalid Menu Selection. Restart program.");
  }
  else if (error == -7){
    printf("\nYou entered a float. Restart program.");
  }
  else if (error == -8){
    printf("\nMAXIMUM ENTRIES REACHED\n");
  }
}

