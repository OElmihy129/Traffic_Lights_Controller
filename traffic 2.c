#define switch1  porta.B0 // switch1=1:auto // switch1=0:manual
#define switch2  porta.B1 // switch2=1:south // switch2=0:west
/*
i : counter of for loops
prev : to  check the case of road
flag : to check if for loop is broken
*/
int i,prev=1,flag=0;
/*
The array of numbers being displayed on the 7-Segments converted from binary
to 2decoders (ex:00010101= 21 on 7segment)
*/
int arr[24]={0,1,2,3,4,5,6,7,8,9,16,17,18,19,20,21,22,23,24,25,32,33,34,35};
void main() {
adcon1=0x07;
  trisb=trisc=trise=0x00;
  trisa=0xff;
  //the least 4bits in portc is 7segments control
  while(1)
  {
          if (!switch1)//manual
          {
            if (switch2)//south
            {   if (prev==0)// if true : the westroad was open
                {  /*
                   - turn on yellow led in west road and keep red in south road
                   for 3s .
                   -turn on the 2 7segment in west road
                   */
                   portc=0b0011100;
                   porte=0b010;
                  for(i=3;i>0;i--)
                    {
                       portb=arr[i];
                       delay_ms(1000);
                    }
                }
                 /*
                   - turn off yellow led in west road and
                   turn on red in west road .
                   -turn on green in south road
                   -turn off all 7segment in west road
                   */
                 portc=0b1000000;
                 porte=0b001;
                 prev=1 ;

            }
            else //west
            {   if (prev==1)// if true : the south road was open
                {  /*
                   - turn on yellow led in south road and keep red in west road
                   for 3s .
                   -turn on the 2 7segment in south road
                   */
                   portc=0b0100011;
                   porte=0b001;
                  for(i=3;i>0;i--)
                    {
                       portb=arr[i];
                       delay_ms(1000);
                    }
                }
                 /*
                   - turn off yellow led in south road and
                   turn on red in south road .
                   -turn on green in west road
                   -turn off all 7segment in south road
                   */
                 portc=0b0010000;
                 porte=0b100;
                 prev=0 ;
            }
          }
          else //auto
          {
                porte=0b001;   //red west for 15s
                portc=0b1001111;//green south for 12s
                 prev=1 ;
                for(i=15;i>0;i--)
                  {
                     if (!switch1)// if true : manual mode is on
                       {
                       flag=1;
                       break;
                       }
                     if (i==3)//yellow south for 3s
                       {
                        portc=0b0101111;
                       }
                     portb=arr[i];
                     delay_ms(1000);
                  }
               if(flag) // if true the "for loop" was broken & manual mode is on
                  {
                  flag=0;
                  continue;// continue while loop
                  }
                portc=0b0011111;  //red south for 23s
                porte=0b100;   //green west for 20s
                prev=0 ;
                for(i=23;i>0;i--)
                {  switch1=porta.B0;
                   if (!switch1)// if true : manual mode is on
                   {
                   break;
                   }
                   if (i==3)//yello west for 3s
                   {
                    porte=0b010;
                   }
                   portb=arr[i];
                   delay_ms(1000);
                }
                if(flag) // if true the "for loop" was broken & manual mode is on
                  {
                  flag=0;
                  continue;// continue while loop
                  }

          }
  }

}