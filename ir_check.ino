void check()
{
  switch (irSensors)
  {
    case B00000000: // on white paper 
    // rightS();
    stopme();
    break;
  
    case B10000000: // leftmost sensor on the line
    rightS();
    break;
    
    case B01000000:
    rightS();
    break;
    
    case B00100000: 
    rightS();
    break;
    
    case B00010000: 
    rightS();
    break; 
    
    case B00001000: 
    leftS();
    break;     

    case B00000100: 
    leftS();
    break;
    
    case B00000010: 
    leftS();
    break;
    
    case B00000001: 
    leftS();
    break;       
    
    case B11000000:
    rightS();
    break;
    
    case B01100000:
    rightS();
    break;

    case B00110000:
    rightS(); 
    break;
    
    case B00011000: 
    go();
    break;          

    case B00001100:
    leftS();
    break; 

    case B00000110:
    leftS();
    break;   
    
    case B00000011:
    leftS();
    break;          
      
    case B11100000:
    // rightS();  
    stopme(); 
    state_flag=1;
    break;
    
    case B01110000:
    rightS();
    break;
    
    case B00111000:
    rightS();
    break;
    
    case B00011100:
    leftS();
    break;  
    
    case B00001110:
    leftS();
    break; 

    case B00000111:
    // leftS();
    stopme();
    state_flag=1;
    break;   
        
    case B11110000:
    // rightS(); 
    stopme();
    state_flag=1;
    break; 
    
    case B01111000:
    rightS();       
    break;
    
    case B00111100:
    go();
    break;  
    
    case B00011110:
    leftS();
    break;  
    
    case B00001111:
    // leftS();
    stopme();
    state_flag=1;
    break;  
        
    case B11111000:
    // rightS(); 
    stopme();
    state_flag=1;
    break; 
    
    case B01111100:
    rightS(); 
    break;
    
    case B00111110:
    leftS();
    break;
    
    case B00011111:
    // leftS();
    stopme();
    state_flag=1;
    break;
          
    case B11111100:
    rightS(); 
    break;
    
    case B01111110:
    go();
    break;
    
    case B00111111:
    leftS();
    break;
    
    case B11111110:
    rightS();
    break;
    
    case B01111111:
    leftS();
    break;
    
    case B11111111:
    stopme();
    state_flag=1;
    break;

    default:
    break;
  }
}