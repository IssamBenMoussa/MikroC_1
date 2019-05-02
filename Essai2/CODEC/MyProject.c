#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// LCD module connections
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;
// End LCD module connections



//variables
int cmp=0;
int sec=0,minutes=9,aaa=0;
int equipeA=0,equipeB=0,arbitre=0;
int tmp=1;
char ss[2]="0";

 int x=0,y=0,zz=0; int kk=-5,final=10,final1=90;
 char ch[5],ch2[5],equipe[2];


char snum[5];
char mnum[5];
// convert 123 to string [buf]


//fonctions
 void affiche()
          {
          if(sec==60)
          {
           minutes++;
           sec=0;
          
          }
           ByteToStr(sec, snum);
           ByteToStr(minutes, mnum);

             lcd_out(2,4,mnum);
             lcd_chr(2,8,':');
             lcd_out(2,9,snum);
          }

    void ecrire(char chx[20])
                            {
                            int ok=1;

                            while(ok)
                                   {
                            PORTD.RD0=1;            //tester sur la 3eme colonne
                            if(PORTD.RD4==1) {LCD_CHR_CP(51);strcat(chx,"3");}//3
                            if(PORTD.RD5==1) {LCD_CHR_CP(54);strcat(chx,"6");}//6
                            if(PORTD.RD6==1) {LCD_CHR_CP(57);strcat(chx,"9");}//9
                            if(PORTD.RD7==1) {x++;ok=0;PORTD=0;}//#
                            PORTD=0;//reinit le pavé

                           PORTD.RD1=1;            //tester sur la 2eme colonne
                            if(PORTD.RD4==1) {LCD_CHR_CP(50);strcat(chx,"2");}//2
                            if(PORTD.RD5==1) {LCD_CHR_CP(53);strcat(chx,"5");}//5
                            if(PORTD.RD6==1) {LCD_CHR_CP(56);strcat(chx,"8");}//8
                            if(PORTD.RD7==1) {LCD_CHR_CP(48);strcat(chx,"0");}//0
                            PORTD=0;//reinit le pavé

                           PORTD.RD2=1;            //tester sur la 1ere colonne
                            if(PORTD.RD4==1) {LCD_CHR_CP(49);strcat(chx,"1");}//1
                            if(PORTD.RD5==1) {LCD_CHR_CP(52);strcat(chx,"4");}//4
                            if(PORTD.RD6==1) {LCD_CHR_CP(55);strcat(chx,"7");}//7
                            if(PORTD.RD7==1) {x=0;y=0;zz=0;lcd_cmd(_lcd_clear);strcpy(ch,"");strcpy(ch2,"");break;}//*
                            PORTD=0;//reinit le pavé
                                                          Delay_ms(200);
                                    }
                            }





void main() {
         INTCON.GIE=1;//ACTIVER INTERRUPTION
         INTCON.TMR0IE=1;//ACTIVER TIMER
         INTCON.RBIE=1;//ACTIVER RB4---RB7
         OPTION_REG.PSA=0;//ACTIVER LE PREDIVISEUR
         OPTION_REG.PS2=OPTION_REG.PS1=OPTION_REG.PS0=1;//256 prediviseur
         OPTIOn_reg.NOT_RBPU=1;//concerne rb0;     //not pull up resistors
         OPTION_reg.INTEDG=1;//concerne RB0      1 front montant
         OPTIOn_reg.T0CS=0;  //activer temporisateur
         ADCON1=0X06;//CONFIGURER PORTA Comme digital
         TRISB=0XFF;
         TRISA=0XFF;
         PORTA=0;
         PORTB=0;
         TRISD=0XF0;
         PORTD=0;//Init pour le pavé
         
         
         Lcd_Init();
         lcd_out(1,1,"Temps");
         LCD_cmd(_LCD_CURSOR_OFF);
         while(1)
         {
          if(tmp)
          affiche();

          if(equipeA || equipeB)
          {

           lcd_cmd(_lcd_clear);
           lcd_out(1,1,"Demande");
           if(equipeA)
                      {
                       lcd_out(2,1,"Equipe A");
                       equipeA=0;
                      
                      }
           if(equipeB)
                      {
                       lcd_out(2,1,"Equipe B");
                       equipeB=0;

                      }
            Delay_ms(2000);
          if(x==0)

                        {
                        lcd_cmd(_lcd_clear);
                        lcd_out(1,1,"Joueur 1");

                        lcd_cmd(_LCD_SECOND_ROW);
                         ecrire(ch);
                        } if(x==1)
                        {
                        lcd_cmd(_lcd_clear);
                        lcd_out(1,1,"Joueur 2");

                        lcd_cmd(_LCD_SECOND_ROW);
                         ecrire(ch2);
                        }
                        if(x==2)
                        {
                         x=0;
                                 lcd_cmd(_lcd_clear);
                        LCD_OUT(1,2,"Changement");
                         LCD_out(2,2,ch);
                         lcd_out(2,5,"<---->");
                        lcd_out(2,13,ch2);
                               strcpy(ch,"");
                               strcpy(ch2,"");
                         Delay_ms(2000);
                            y=0;

                        }
            
            
            
            
            
            lcd_cmd(_lcd_clear);
            lcd_out(1,1,"Temps");
            tmp=1;
          
          }

         if(arbitre)
           {
           arbitre=0;
           lcd_cmd(_lcd_clear);
           lcd_out(1,1,"Temps +");
           Delay_ms(2000);
            if(x==0)
            {
                   lcd_cmd(_lcd_clear);
                        lcd_out(1,1,"Ajouter");

                        lcd_cmd(_LCD_SECOND_ROW);
                         ecrire(ch);
            
            }
            if(x==1)
            {
              x=0;
              lcd_cmd(_lcd_clear);
              LCD_OUT(1,2,"Plus");
              LCD_out(2,2,ch);
              kk=atoi(ch);
             // LCD_chr(2,14,kk+final+48);

              strcpy(ch,"");
              Delay_ms(2000);
                            y=0;
            
            
            }
            
            lcd_cmd(_lcd_clear);
            lcd_out(1,1,"Temps");
            tmp=1;
           }


                      if(aaa==1)
                       {
                       aaa=0;
                       lcd_cmd(_lcd_clear);
                      lcd_out(1,1,"Mi temps");
                      Delay_ms(5000);
                      lcd_cmd(_lcd_clear);

                      return;
                      minutes=45;
                      sec=0;
                       }
           }
}



void interrupt()
{
if(INTCON.RBIF==1)
                  {
                  tmp=0;
                  if(PORTB.RB4==1)
                                  {
                                   equipeA=1;
                                   INTCON.RBIF=0;
                                   return;
                                  }
                  if(PORTB.RB5==1)
                                  {
                                   equipeB=1;
                                   INTCON.RBIF=0;
                                   return;
                                  }
                  if(PORTB.RB6==1)
                                  {
                                   arbitre=1;
                                   INTCON.RBIF=0;
                                   return;
                                  }

                  INTCON.RBIF=0;
                  return;

                  }


//temps
 if(INTCON.TMR0IF==1)
                     {
                     INTCON.TMR0IF=0;
                     cmp++;
                     if(minutes==final && sec==0)
                                aaa=1;
                     if(cmp==30)
                                {
                                sec++;

                                 portb.b0=!portb.b0;
                                 cmp=0;

                                 return;
                                }

                      return;
                     }

//fintemps

}