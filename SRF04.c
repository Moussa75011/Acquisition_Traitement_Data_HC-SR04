//////////////////////////////////////////////////////////////////////////
//--------------------Capteur Ultrason SR04---------------------//
//////////////////////////////////////////////////////////////////////////

// char counter;
    int etape;

     void afficheChiffre(char chiffre,char position){
      LATA = 0x01 << position;
      
      switch(chiffre){
      
       case 0:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 0;LATD7_bit = 0;
       break;
       case 1:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
       break;

       case 2:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 0;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 3:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 4:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 5:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 7:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
       break;
       case 8:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       default:
       break;
      }

      void afficheNombre(float var){
      char chiffre0,chiffre1,chiffre3;
      chiffre3 = var/1000;
      var -= chiffre3*1000;
      chiffre2 = var/100;
      var -= chiffre2*100;
      chiffre1 = var/10;
      var -= chiffre1*10;
      chiffre0 = (char)var;
      afficheChiffre(chiffre0,0);
      Delay_ms(1);
      afficheChiffre(chiffre1,1);
      Delay_ms(1);
      afficheChiffre(chiffre3,3);
      Delay_ms(1);
     }

    void main(void) {
    int compte = 0;
      float nombreaffiche = 0;
      ANSELB = 0x00;  ////   toutes les entrées sont numeriques
      TRISA = 0x00;
      TRISB = 0x00;
      LATA = 0x00;
      LATB = 0x00;
      etape = 0;

     //////////////////////////////////////////////////////////////////////////
      afficheNombre((int)nombreaffiche);
      while(1){
        switch(etape) {
         case 0:
         LATB1_bit = 1;
         compte = 0;
         etape++ ;
         break;
         case 1:
              Delay_ms(1);
              LATB1_bit = 0;
              etape++ ;
              break;
         case 2:
                 if(PORTB & 0x01){
                    while(PORTB & 0x01){
                                compte++;
                                delay_us(10);
                                }
                                etape++;
                                 }
                                break;
         case 3:
          nombreaffiche = (float)compte*10/58.0;
         Delay_ms(1);
         etape=0;
         break;
        }
        if(etape == 3)afficheNombre((int)nombreaffiche);
      }
    }
