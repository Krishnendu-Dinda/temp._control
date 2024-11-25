#include<reg51.h>
#define DATA P2
#define adcval P1
unsigned int i,j,k,l,m,n,t,b;

sbit rs=P3^0;
sbit rw=P3^1;
sbit en=P3^2;
sbit rd=P3^3;
sbit wrt=P3^4;
sbit intr=P3^5;
sbit m1=P3^6;
sbit m2=P3^7;

//unsigned int cmd[]={,,,};
unsigned char asc[] ={"0123456789"};
//unsigned char name[]={"Hii"};
unsigned char tmp[]={"temp in ctrl"};
unsigned char title2[]={"Temp value= "};
unsigned char ac[]={    "AC ON       "};
unsigned char heater[]={"HEATER ON   "};

void delay(unsigned int x)
{

	for(i=0;i<x;i++)
		for(j=0;j<1275;j++);
}


void lcddata(unsigned char dat)
{
	DATA=dat;
	rs=1;
	rw=0;
	en=1;
	delay(1);
	en=0;	
}

void lcdcmd(unsigned char comnd)
{
DATA=comnd;
	rs=0;
	rw=0;
	en=1;
	delay(1);
	en=0;	
}

void show_reading()
{
 unsigned int digit;
digit=((adcval*2)%10);
lcdcmd(0x8d);
lcddata(asc[digit]);
digit=((adcval*2)/10)%10;
lcdcmd(0x8c);
lcddata(asc[digit]);
digit=((adcval*2)/100)%10;
lcdcmd(0x8b);
lcddata(asc[digit]);
}

void main(){
	m1=0;
	m2=0;
	P1=0xff;
	for(n=0;n<4;n++){
		lcdcmd(0x38);	
		lcdcmd(0x0E);
		lcdcmd(0x01);
		lcdcmd(0x06);
	}
	
	lcdcmd(0x01);
	lcdcmd(0x80);
	delay(150);
	
	for(m=0;title2[m]!=(0);m++){	
	lcddata(title2[m]);	
		}
	wrt=1;
while(1){
				
			rd=1;
			wrt=0;
			delay(100);
			wrt=1;
			while(intr==1);
			rd=0;
	show_reading();
			RD=1;
		if(adcval>0xC){
			m1=1;
			m2=0;
			lcdcmd(0xC0);
			for(t=0;ac[t]!=(0);t++){	
				lcddata(ac[t]);				
			}		
		}			
		else if(adcval<0xA){
			m1=0;
			m2=1;
			lcdcmd(0xC0);
			for(b=0;heater[b]!=(0);b++){	
				lcddata(heater[b]);				
			}			
		}		
		else{
			m1=0;
			m2=0;
			lcdcmd(0xC0);
				for(b=0;tmp[b]!=(0);b++){	
				lcddata(tmp[b]);
		}	
				
		}
	}
}



