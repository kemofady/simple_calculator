/* library **/
#include<util/delay.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"
/* mcal */

#include"DIO_driver/Dio_Interface.h"

/* own  drive*/
#include"LCD_driver/LCD_interface.h"
#include "KPD_driver/KPD_interface.h"


void main()
{
	u8 local_u8key=0xff;   // not pressed
	LCD_voidinit();
	KPD_voidInit();
	u8 local_u8positionlcd = 0; //know the position to print on LCD
	u8 local_u8secondOPFlag=0; //if second operand is filled
	u8 operation=0;
	f32 op1=0;  //first operand
	f32 op2=0;  //second operand
	f32 result=0;

	while(1)
	{

		//lcd Boxes to write
		while(local_u8positionlcd<16)
		{
			do{
				local_u8key = KPD_u8GETPressedKey();

					}while(local_u8key == 0xff);

			if(local_u8key=='o')
			{
				 LCD_voidclearscrean();
				 local_u8positionlcd = 0;
				 operation=0;
				 op1=0;
				 op2=0;
				 result=0;
			}

			else if((local_u8key>=0)&&(local_u8key<=9))
			{
				 if(operation==0)
				 {
				LCD_gotoxy(0, local_u8positionlcd);
				op1=(op1*10)+(u16)local_u8key;
				LCD_voidWriteNumber(local_u8key);
				local_u8positionlcd++;
				 }
				 else
				 {
					 local_u8secondOPFlag=1;
					 LCD_gotoxy(0, local_u8positionlcd);
					 op2=(op2*10)+(u16)local_u8key;
					 LCD_voidWriteNumber(local_u8key);
					 local_u8positionlcd++;
				 }
			}

			else if((local_u8key=='/')||(local_u8key=='*')||(local_u8key=='/')||(local_u8key=='-'))
			{
				 LCD_gotoxy(0, local_u8positionlcd);
				 operation=local_u8key;
				 local_u8positionlcd++;
				 LCD_voidsenddata(local_u8key);
			}
			else if((local_u8key=='=')&&(local_u8secondOPFlag==1))
			{
				LCD_gotoxy(0, local_u8positionlcd);
				LCD_voidsenddata(local_u8key);
				LCD_gotoxy(1, 0);
				switch(operation){
						case'+':
						result=op1+op2;
						LCD_voidWriteNumber(result);
						break;
						case'-':
						result=op1-op2;
						LCD_voidWriteNumber(result);
						break;
						case'*':
						result=op1*op2;
						LCD_voidWriteNumber(result);
						break;
						case'/':
							if(op2==0){
								LCD_voidsendstring("MATH ERROR YA HOMAR");
								break;
							}
							else{
								result=op1/op2;
								LCD_voidWriteNumber(result);
							}
						break;
								}
			}

		}
	}
}


