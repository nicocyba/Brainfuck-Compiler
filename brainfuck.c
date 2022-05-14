#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Interpreter state
struct BFState {
  // The array and the size of the array.
  size_t array_len;
  uint8_t* array;

  // Pointer to the current position, points into array..array+array_len.
  uint8_t* cur;
};

int brainfuck(struct BFState* state, const char* program) {
  // TODO: your implementation. :)
  int pc = 0;
  int bracketCounter = 0;
  int pcTemp = 0;
  bool bracketFlag = false;
  
  if (state->cur < state->array) {
      return -1;
  }
  
  while (pc < 8192 && *(program + pc) != 0x0) {
    	bracketFlag = false;
        switch (*(program+pc)) {
            case 0x0: break; // 0
            case 0x3e: (state->cur)++; break; // >
            case 0x3c: (state->cur)--; break; // <
            case 0x2b: (* (state->cur))++; break; // +
            case 0x2d: (*(state->cur))--; break; // -
            case 0x5b: // [
            	pcTemp = pc+1;
            	while (pcTemp < 8192 && *(program + pcTemp) != 0x0){
                	if (bracketCounter > 255 || bracketCounter < 0){
                    	return -1; 
                    }
                  	switch (*(program+pcTemp)) {
                    	case 0x5b: // [
                        	bracketCounter++;
                        	break;
                        case 0x5d: // ]
                        	bracketCounter--;
                        	break;
                    }
                  	pcTemp++;
                  	if (bracketCounter == 0){
                    	bracketFlag = true;
                    	break;
                    }    
                }
            	if (bracketFlag) {
                	if (*((state->array)+pcTemp) == 0){
                    	pc = pcTemp; 
                    }
                }else{
                	return -1; 
                }
            	break; 
            case 0x5d: // ]
            	pcTemp = pc+1;
            	while (pcTemp < 8192 && *(program + pcTemp) != 0x0){
                	if (bracketCounter > 255 || bracketCounter < 0){
                    	return -1; 
                    }
                  	switch (*(program+pcTemp)) {
                    	case 0x5b: // [
                        	bracketCounter++;
                        	break;
                        case 0x5d: // ]
                        	bracketCounter--;
                        	break;
                    }
                  	pcTemp++;
                  	if (bracketCounter == 0){
                    	bracketFlag = true;
                    	break;
                    }    
                }
            	if (*(program + pcTemp) == 0x0){
                	break; 
                }
            	if (*((state->array)+pcTemp) != 0){
                  	if (bracketFlag) {
                		pc = pcTemp; 
                    }else{
                        return -1; 
                    }
                }
            	break; 
            //default: continue; break; // rest
        }
        if (state->cur >= ((state->array)+(state->array_len))) {
            return -1;
        } else if (state->cur < state->array){
            return -1;
        }
        pc++;
    }

  if (state->cur >= ((state->array)+(state->array_len))) {
      return -1;
  } else if (state->cur < state->array){
      return -1;
  } else {
      return 0;
  }
}
