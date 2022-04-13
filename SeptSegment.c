
int etape;

     void afficheChiffre(char chiffre,char position){
      LATA = 0x01 << position;             //Registre de sortie active les 4 afficheurs 7segments en fonction de la position
      switch(chiffre){                                // Etat du registre en sortie
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
       case 6:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 7:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
       break;
       case 8:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 9:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 10:LATD0_bit = 0;LATD1_bit = 0;LATD2_bit = 0;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 1;
       break;
       default:
       break;
      }
     }



void afficheNombre(int var){
      char chiffre0,chiffre1,chiffre2,chiffre3;
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
      afficheChiffre(chiffre2,2);
      Delay_ms(1);
      afficheChiffre(chiffre3,3);
      Delay_ms(1);
     }
      //déclaration de variables globales
      int compte;
      char tab[5];    //déclaration d'un tableau de type char de dimension 5
      int nombreaffiche;

void main(void) {
     UART1_Init(9600);   //initialisation du module UART1 a une vitesse(fréquence) de 9600bd
     Delay_ms(1);       // temporisation pour que UART1 soit stabilisé
     compte = 0;
     nombreaffiche = 0;

      ANSELB = 0x00;      //   toutes les entrées sont numeriques
      TRISA  = 0x00;      //
      TRISB  = 0x01;      //   Entrée Microcontrôleur
      TRISD  = 0x00;      //

      LATA = 0x00;        // attribution des valeurs
      LATB = 0x00;
      LATD = 0x00;
      ANSELC = 0x00;
      TRISC.B6 = 0;
      TRISC.B7 = 1;

      etape = 0;          // initialisation de l'étape impulsion et calcul

      //afficheNombre((int)nombreaffiche);
      while(1){

        switch(etape) {

         case 0:  // génération d'une impulsion vers US
         LATB1_bit = 1;
         compte = 0;
         etape++ ;
         break;


         case 1: // attente 1ms et retour à zéro
              Delay_ms(1);
              LATB1_bit = 0;
              etape++ ;
              break;

         case 2 : // vérifier si RB0 =1 (existence d'un ECHO sur le PORTB puis attendre 10ms
              if(PORTB & 0x01){ // verification de la valeur du registre d'entree
                       while(PORTB & 0x01){
                                delay_us(10);
                                compte++;
                        }
              etape++;
              }
              break;

         default : // calcul de la distance via le modèle constructeur
              nombreaffiche = (int)compte*10/58.0;
              afficheNombre(nombreaffiche);
              IntToStr(nombreaffiche,tab); // conversion de l'entier into une chaine de caractère
              //UART1_Write_Text(tab);
              UART1_Write(nombreaffiche);   // definir et détérminer les données a envoyer
              //UART1_Write(13);        //commande pour entrer les données
              //UART1_Write(10);  //Commande pour retourner à la ligne selon le code ASCII
              /*if(UART1_Data_Ready()) {      // si les données sont pretes (reçue)
              char uart_rd = UART1_read(); // Lecture des données
              UART1_Write(uart_rd);       // transmission de données via UART1
              } */

              etape=0;
              break;
        }
      }
}
