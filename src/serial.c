/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2016  Luis Claudio Gamb�a Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef _WIN_
#include <conio.h>
#include <time.h>
#include <windows.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#endif

#include "picsim.h"
//#include "periferic16.h"
//#include "periferic16e.h"
//#include "periferic18.h"
        
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
        


int 
serial_open(void)
{
      if(pic->SERIALDEVICE[0] == 0)
      { 	
#ifdef _WIN_
        strcpy(pic->SERIALDEVICE,"COM2");
#else
        strcpy(pic->SERIALDEVICE,"/dev/tnt2");
#endif
      }

  pic->bc=0;
  pic->sr=0;
  pic->serialc=0;
  pic->recb=0;
  pic->s_open=0;

#ifdef _WIN_
  pic->serialfd = CreateFile(pic->SERIALDEVICE, GENERIC_READ | GENERIC_WRITE,
0, // exclusive access
NULL, // no security
OPEN_EXISTING,
0, // no overlapped I/O
NULL); // null template
  if( pic->serialfd == INVALID_HANDLE_VALUE)
  {
     pic->serialfd=0;
//     printf("Erro on Port Open:%s!\n",pic->SERIALDEVICE);
     return 0; 
  }
#else
  pic->serialfd = open(pic->SERIALDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
 
  if (pic->serialfd < 0) 
  {
    pic->serialfd=0;
    perror(pic->SERIALDEVICE); 
//    printf("Erro on Port Open:%s!\n",pic->SERIALDEVICE);
    return 0; 
  }
//  printf("Port Open:%s!\n",pic->SERIALDEVICE);
#endif
  return 1;
}

int 
serial_close(void)
{
  if (pic->serialfd != 0) 
  {
#ifdef _WIN_
  CloseHandle(pic->serialfd);
#else    
    close(pic->serialfd);
#endif
    pic->serialfd=0;
  }
  return 0;
}



int
serial_cfg(void)
{
    unsigned int BAUDRATE;
   
    
    if(*pic->serial_TXSTA & 0x04) //BRGH=1 
    {
        pic->serialexbaud=pic->freq/(16*((*pic->serial_SPBRG) +1));
    }
    else
    {
        pic->serialexbaud=pic->freq/(64*((*pic->serial_SPBRG) +1));
    }
      



    switch(((int)((pic->serialexbaud/300.0)+0.5))) 
    {
       case 0 ... 1:
          pic->serialbaud=300;
          #ifndef _WIN_
          BAUDRATE=B300;
          #else
          BAUDRATE=300;
          #endif  
          break; 
       case 2 ... 3:
          pic->serialbaud=600;
          #ifndef _WIN_
          BAUDRATE=B600;
          #else
          BAUDRATE=600;
          #endif  
          break; 
       case 4 ... 7:
          pic->serialbaud=1200;
          #ifndef _WIN_
          BAUDRATE=B1200;
          #else
          BAUDRATE=1200;
          #endif  
          break; 
       case 8 ... 15:
          pic->serialbaud=2400;
          #ifndef _WIN_
          BAUDRATE=B2400;
          #else
          BAUDRATE=2400;
          #endif  
          break; 
       case 16 ... 31:
          pic->serialbaud=4800;
          #ifndef _WIN_
          BAUDRATE=B4800;
          #else
          BAUDRATE=4800;
          #endif  
          break; 
       case 32 ... 63:
          pic->serialbaud=9600;
          #ifndef _WIN_
          BAUDRATE=B9600;
          #else
          BAUDRATE=9600;
          #endif  
          break; 
       case 64 ... 127:
          pic->serialbaud=19200;
          #ifndef _WIN_
          BAUDRATE=B19200;
          #else
          BAUDRATE=19200;
          #endif  
          break; 
       case 128 ... 191:
          pic->serialbaud=38400;
          #ifndef _WIN_
          BAUDRATE=B38400;
          #else
          BAUDRATE=38400;
          #endif  
          break; 
       case 192 ... 383:
          pic->serialbaud=57600;
          #ifndef _WIN_
          BAUDRATE=B57600;
          #else
          BAUDRATE=57600;
          #endif  
          break; 
       default:
          pic->serialbaud=115200;
          #ifndef _WIN_
          BAUDRATE=B115200;
          #else
          BAUDRATE=115200;
          #endif  
          break; 
    } 

#ifdef _WIN_
  BOOL bPortReady;
  DCB dcb;
  COMMTIMEOUTS CommTimeouts;

bPortReady = GetCommState(pic->serialfd , &dcb);
dcb.BaudRate = BAUDRATE;
dcb.ByteSize = 8;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;
dcb.fAbortOnError = TRUE;

// set XON/XOFF
dcb.fOutX = FALSE; // XON/XOFF off for transmit
dcb.fInX = FALSE; // XON/XOFF off for receive
// set RTSCTS
dcb.fOutxCtsFlow = FALSE; // turn off CTS flow control
//dcb.fRtsControl = RTS_CONTROL_HANDSHAKE; //
dcb.fRtsControl = RTS_CONTROL_DISABLE; //
// set DSRDTR
dcb.fOutxDsrFlow = FALSE; // turn off DSR flow control
//dcb.fDtrControl = DTR_CONTROL_ENABLE; //
dcb.fDtrControl = DTR_CONTROL_DISABLE; //
// dcb.fDtrControl = DTR_CONTROL_HANDSHAKE; //

bPortReady = SetCommState(pic->serialfd , &dcb);

// Communication timeouts are optional

bPortReady = GetCommTimeouts (pic->serialfd , &CommTimeouts);

CommTimeouts.ReadIntervalTimeout = MAXDWORD;
CommTimeouts.ReadTotalTimeoutConstant = 0;
CommTimeouts.ReadTotalTimeoutMultiplier = 0;
CommTimeouts.WriteTotalTimeoutConstant = 0;
CommTimeouts.WriteTotalTimeoutMultiplier = 0;

bPortReady = SetCommTimeouts (pic->serialfd , &CommTimeouts);
	

EscapeCommFunction(pic->serialfd ,SETRTS );

#else
   struct termios newtio;
   int cmd;   
        
//        tcgetattr(fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));
        newtio.c_cflag = BAUDRATE |CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR|IGNBRK;
        newtio.c_oflag = 0;
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
         
        newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */
        
        tcflush(pic->serialfd, TCIFLUSH);
        tcsetattr(pic->serialfd,TCSANOW,&newtio);
        
	cmd=TIOCM_RTS;
	ioctl(pic->serialfd, TIOCMBIS ,&cmd);
#endif

	return 0; 
}


      
unsigned long serial_send(unsigned char c)
{
  if(pic->serialfd)
  {
#ifdef _WIN_
   unsigned long nbytes;
    
   WriteFile(pic->serialfd, &c, 1, &nbytes,NULL);
   return nbytes;
#else
  return write (pic->serialfd,&c,1);   
#endif
  }
  else
    return 0;
}

unsigned long serial_rec(_pic * pic, unsigned char * c)
{
  if(pic->serialfd)
  {
#ifdef _WIN_
    unsigned long nbytes;
      
    ReadFile(pic->serialfd, c, 1,&nbytes, NULL);
#else
    long nbytes;

     nbytes = read (pic->serialfd,c,1);   
     if(nbytes<0)nbytes=0;
#endif    
    return nbytes;
   }
   else
     return 0;
}

unsigned long serial_rec_tout( unsigned char * c)
{
 unsigned int tout=0;

  if(pic->serialfd)
  {
#ifdef _WIN_
    unsigned long nbytes;
    do
    { 
      Sleep(1);	
      ReadFile(pic->serialfd, c, 1,&nbytes, NULL);
#else
    long nbytes;
    do
    { 
      usleep(100);
      nbytes = read (pic->serialfd,c,1);   
      if(nbytes<0)nbytes=0;
#endif    
      tout++;
    }while((nbytes == 0 )&&(tout < 1000));
    return nbytes;
   }
   else
     return 0;
}


unsigned long serial_recbuff( unsigned char * c)
{
int i;


  if(pic->flowcontrol)
  {
  
   if(serial_rec(pic,&pic->buff[pic->bc]) == 1)
    {
     pic->bc++;

     if(pic->bc > BUFFMAX)
     {
       printf("serial buffer overflow \n") ;
       pic->bc = BUFFMAX-1;  
//       getchar();	
     };
    }


    if((pic_get_pin(pic->ctspin) == 0)&&(pic->bc > 0))
    {
      *c=pic->buff[0];

      pic->bc--;
      for(i=0;i<pic->bc;i++)
        pic->buff[i]=pic->buff[i+1]; 
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
     return serial_rec(pic,c);
  }
  
}




void serial(void)
{
  unsigned char rctemp;

   if(pic->lram == pic->serial_TXREG_ADDR)    
    {
      pic->txtc++;
      if(pic->txtc > 1)pic->txtc=1; 
      pic->txtemp[(unsigned char)pic->txtc]= *pic->serial_TXREG;
      *pic->serial_TXSTA &=~0x02; //TRMT=0 full   
      *pic->serial_PIR1 &=~0x10; //TXIF=0 trasmiting
    }

   if(pic->lram == pic->serial_RCSTA_ADDR)
   {               //CREN 
      if((*pic->serial_RCSTA & 0x10) == 0)
      {  
       *pic->serial_RCSTA &=~0x02; //clear OERR
       pic->serialc=0;
      }
   }    


   if(pic->rram == pic->serial_RCREG_ADDR)    
    { 
      switch(pic->recb)
      {
        case 1:
          *pic->serial_RCREG=0;
          *pic->serial_PIR1 &=~0x20; //clear RCIF
          pic->recb--;    
          break;
        case 2:
          *pic->serial_RCREG=pic->RCREG2;
          pic->RCREG2=0; 
	  pic->recb--;    
          break;
        default:
        break; 
      }

    }



  if((*pic->serial_RCSTA & 0x80)==0x80)
  {
    if(pic->s_open == 0) 
    {

      if(pic->serialfd > 0)
      {
        serial_cfg();
        pic->s_open=1;
       if(pic->print)printf("#Open Port:%s!\n",pic->SERIALDEVICE);
      }
      else
      {
        if(pic->print)printf("#Erro Open Port:%s!\n",pic->SERIALDEVICE);
        pic->s_open=-1;
      }
      *pic->serial_TXSTA |=0x02; //TRMT=1 empty 
      *pic->serial_PIR1 |=0x10; //TXIF=1  
      pic->txtc=-1;
      
      pic->pins[pic->usart[0]-1].ptype=PT_USART;
      pic->pins[pic->usart[1]-1].ptype=PT_USART;
      if(pic->flowcontrol)pic_set_pin( pic->rtspin,0); //enable send
    }

  
  
    //envia byte para TSTR
    if((*pic->serial_TXSTA & 0x02)&&(pic->txtc >= 0)) 
    {
         pic->txtc--;
         
         if(!pic->txtc)
         {
           pic->txtemp[(unsigned char)pic->txtc]= *pic->serial_TXREG;
           *pic->serial_TXSTA &=~0x02; //TRMT=0 full   
           *pic->serial_PIR1 &=~0x10; //TXIF=0 trasmiting
         }
    }


    pic->serialc++;

    if(*pic->serial_TXSTA & 0x04)
    {
       //BRGH=1  start + 8 bits + stop
       if(pic->serialc >= (((*pic->serial_SPBRG)+1)*40))pic->sr =1;
    }
    else
    {
       //BRGH=0  start + 8 bits + stop
       if(pic->serialc >= (((*pic->serial_SPBRG)+1)*160))pic->sr =1;
    }

  
    if(pic->sr ==1 )
    {
    
     pic->serialc=0;
     
      
      if((pic->s_open != 0)&&(( *pic->serial_TRIS_RX &  pic->serial_TRIS_RX_MASK) != 0)) //work only if RX tris bit is set
     {
      if(serial_recbuff(&rctemp) == 1)
      {

        if((*pic->serial_RCSTA & 0x12) == 0x10)//CREN=1  OERR=0 
        { 
         switch(pic->recb)
         {
         case 0: 
           *pic->serial_RCREG=rctemp;
	   pic->RCREG2=0;
           pic->recb++;
           break;
         case 1: 
           pic->RCREG2=rctemp;
           pic->recb++;
           break; 
         default: 
           *pic->serial_RCSTA |=0x02; //set OERR
           break; 
          }
        }
        
   //       printf("reb=%i temp=%02X RCREG=%02X RECREG2=%02X  RCSTA=%02X\n",pic->recb,rctemp,pic->ram[RCREG],pic->RCREG2,pic->ram[RCSTA]);
        
         if(((*pic->serial_PIE1 & 0x20) == 0x20)&&((*pic->serial_PIR1 & 0x20) != 0x20))
         {
           if(pic->print)printf("serial rx interrupt (%#04X)\n",rctemp);
         }
         //set RCIF
         *pic->serial_PIR1 |=0x20;  
      }
     } 
    
      //if(((pic->ram[P18_TXSTA] & 0x02) == 0 ) &&((pic->ram[pic->pins[pic->usart[1]-1].port+0x12] &  (0x01 << pic->pins[pic->usart[1]-1].pord)) == 0))
      if((*pic->serial_TXSTA & 0x02) == 0 )
       {   
        if(pic->s_open == 1 ) serial_send(pic->txtemp[0]);
        *pic->serial_TXSTA |=0x02; //TRMT=1 empty  
        
        if(((*pic->serial_PIE1 & 0x10) == 0x10)&&((*pic->serial_PIR1 & 0x10) != 0x10))
        {
          if(pic->print)printf("serial tx interrupt (%#04X)\n",pic->txtemp[0]);
        }
        *pic->serial_PIR1 |=0x10; //TXIF=1  
      }   
      pic->sr=0;
    }

//Hardware flowcontrol
    
   }
  else
  {
    if(pic->s_open == 1)
    {
      pic->s_open=0;
      pic->pins[pic->usart[0]-1].ptype=PT_CMOS;
      pic->pins[pic->usart[1]-1].ptype=PT_CMOS;
      if(pic->flowcontrol)pic_set_pin( pic->rtspin,1); //disable send
    }
  }

}

void 
pic_set_serial(_pic * pic_,const char * name, int flowcontrol,int ctspin,int  rtspin)
{
  pic=pic_;   
  strcpy(pic->SERIALDEVICE,name);
  
  pic->flowcontrol=flowcontrol;
  pic->serialfd=0;
  if(flowcontrol == 1)
  {
    pic->ctspin=ctspin;
    pic->rtspin=rtspin;
  }
};
