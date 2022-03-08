int S1pin = A0; 
int S2pin = A1;
int S3pin = A2;
int S4pin = A3;
int  id_to_check, id0, id1, id2, id3, id4, id5, id6, id7 = -1; // startowe id to -1
unsigned long DisplayTime = 0; //potrzebne do odliczania co jaki czas bedzie sie wyswietlal podglad wynikow
void setup(){
  Serial.begin(9600);
}

void loop() {
 int S1Reading = analogRead(S1pin); // front_right
 int S2Reading = analogRead(S2pin); // front_left
 int S3Reading = analogRead(S3pin); // back_right
 int S4Reading = analogRead(S4pin); // back_left

 int relation1 = relation_front_right(S1Reading, S2Reading, S3Reading, S4Reading);
 int relation2 = relation_front_left(S1Reading, S2Reading, S3Reading, S4Reading);  
 int relation3 = relation_back_right(S1Reading, S2Reading, S3Reading, S4Reading);  
 int relation4 = relation_back_left(S1Reading, S2Reading, S3Reading, S4Reading);   
 
 double relations_array[4] = {relation1, relation2, relation3, relation4}; 

 int rel5 = relation_front(S1Reading, S2Reading, S3Reading, S4Reading);  
 int rel6 = relation_right(S1Reading, S2Reading, S3Reading, S4Reading);  

//-------Data to graph----------------
   Serial.print(rel5);
   Serial.print("\t");
   Serial.print(rel6);
   Serial.println("\t");
  
//-------CHECKING POSITIONS-------------------------------
// gdy ktoras z pozycji zwroci "true" to wyswietlimy komunikat
  
 if(millis()-DisplayTime >= 1000){ // aby wyswietlaly sie wyniki co 1 s ale nie wstrzymywaly programu
    if(position_left_leg_on_right_knee(relations_array)){ 
      Serial.println("ZDEJMIJ LEWA NOGE Z PRAWEGO KOLANA");
      id0 = 0;  //id pozycji
      id_to_check = id0; // pobranie id do sprawdzenia
    }
    if(position_right_leg_on_left_knee(relations_array)){ 
      Serial.println("ZDEJMIJ PRAWA NOGE Z LEWEGO KOLANA");
      id1 = 1;
      id_to_check = id1;
     }
     if(position_left_lean(relations_array)){ 
      Serial.println("NIE POCHYLAJ SIE NA LEWO");
      id2 = 2;
      id_to_check = id2;
     }
    if(position_right_lean(relations_array)){
      Serial.println("NIE POCHYLAJ SIE NA PRAWO");
      id3 = 3;
      id_to_check = id3;
     }
    if(position_back_lean(relations_array)){
      Serial.println("NIE POCHYLAJ SIE DO TYŁU");
      id4 = 4;
      id_to_check = id4; 
     }
    if(position_forward_lean(relations_array)){ 
      Serial.println("NIE POCHYLAJ SIE DO PRZODU");
      id5 = 5;
      id_to_check = id5;
     }
    if(position_absent(relations_array)){ 
      Serial.println("NIEOBECNY");
       id6 = 6;
       id_to_check = id6;
     }
    if(position_good(relations_array)){
      Serial.println("DOBRA POZYCJA");
      id7 = 7;
      id_to_check = id7;
    }
     DisplayTime = millis();
     }
  }

//------------POSITIONS-----------------------------------------
// w zależności od procentowej wartosci odczytow do sumy odczytow mozna dowiedziec sie jaka pozycje przyjal uzytkownik

bool position_left_leg_on_right_knee(double relations[]){ 
 if (relations[0]<=22 && relations[1]<=10 && relations[2]>=35 && relations[3]>=35){ 
        if(id_to_check == id0) {   
          return false; 
         }
         else{return true;}
 }
 else {return false;}
}

bool position_right_leg_on_left_knee(double relations[]){   
 if (relations[0]<=10 && relations[1]<=22 && relations[2]>=35 && relations[3]>=35){     
        if(id_to_check == id1) {
          return false;
         }
      else{return true;}
 }
 else {return false;}
}
bool position_left_lean(double relations[]){ 
 if (relations[0]<=20 && relations[1]>=20 && relations[2]<=27 && relations[3]>=33){      
        if(id_to_check == id2) {       
         return false;
         }
  else{return true;}
 }
 else {return false;}
}

bool position_right_lean(double relations[]){ 
 if (relations[0]>=20 && relations[1]<19 && relations[2]>=27 && relations[3]<27){ 
        if(id_to_check == id3) {      
          return false;
         }
  else{return true;}
 }
 else {return false;}
}

bool position_back_lean(double relations[]){
 if (relations[0]<=18 && relations[1]<=18 && relations[2]>=30 && relations[3]>=30){ 
        if(id_to_check == id4) {      
          return false;
         }
  else{return true;}
 }
 else {return false;}
}

bool position_forward_lean(double relations[]){ 
 if (relations[0]>23 && relations[1]>23 && relations[2]<=27 && relations[3]<=27){ 
        if(id_to_check == id5) {      
        return false;
         }
  else{return true;}
 }
 else {return false;}
}

bool position_absent(double relations[]){
 if (relations[0]<=10 && relations[1]<=10 && relations[2]<=10 && relations[3]<=10){ 
         if(id_to_check == id6) {      
         return false;
         }
  else{return true;}
 }
 else {return false;}
}

bool position_good(double relations[]){
 if (relations[0]>=19 && relations[0]<=23 && relations[1]>=19 && relations[1]<=23 &&
     relations[2]>=24 && relations[2]<=32 && relations[3]>=24 && relations[3]<=32){ 
         if(id_to_check == id7) {
           return false;
         }
  else{return true;}
 }
 else {return false;}
}

//------------RELATIONS------------------------------------------------
 double relation_front_right(double front_right, double front_left, double back_right, double back_left){ 
       if(front_right+front_left+back_right+back_left > 0){
       double relation = front_right*100/(front_right+front_left+back_right+back_left); 
       return relation;    
       }
       else{return 0;}
  }

 double relation_front_left(double front_right, double front_left, double back_right, double back_left){ 
       if(front_right+front_left+back_right+back_left > 0){
       double relation = front_left*100/(front_right+front_left+back_right+back_left); 
       return relation;    
       }
       else{return 0;}
  }
  
 double relation_back_right(double front_right, double front_left, double back_right, double back_left){ 
       if(front_right+front_left+back_right+back_left > 0){
       double relation = back_right*100/(front_right+front_left+back_right+back_left); 
       return relation; 
       }
       else{return 0;}   
  }

 double relation_back_left(double front_right, double front_left, double back_right, double back_left){ 
       if(front_right+front_left+back_right+back_left > 0){
       double relation = back_left*100/(front_right+front_left+back_right+back_left); 
       return relation; 
       }
       else{return 0;}
  }

//-----Relation to graph--------------------------

double relation_front(double front_right, double front_left, double back_right, double back_left){
  if(front_right+front_left+back_right+back_left > 0){
       double relation = (front_right+front_left)*100/(front_right+front_left+back_right+back_left); 
       return relation; 
       }
       else{return 0;}
}

double relation_right(double front_right, double front_left, double back_right, double back_left){
  if(front_right+front_left+back_right+back_left > 0){
       double relation = (front_right+back_right)*100/(front_right+front_left+back_right+back_left); 
       return relation; 
       }
       else{return 0;}
}
