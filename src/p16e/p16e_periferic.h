/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gamboa Lopes

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

#ifndef P16E_PERIFERIC_H
#define P16E_PERIFERIC_H

#ifdef __cplusplus
extern "C" {
#endif
#include"../../include/periferic16e.h"
        
int interrupt16E(void);    
int interrupt16E_2(void);   

void p16e_mssp_rst(void);
void p16e_mssp(void);

void p16e_adc_rst(void);
void p16e_adc(void);

void p16e_tmr0_rst(void);
void p16e_tmr0(void);
void p16e_tmr0_2(void);

void p16e_tmr1_rst(void);
void p16e_tmr1(void);

void p16e_tmr2_rst(void);
void p16e_tmr2(void);

void p16e_eeprom_rst(void);
void p16e_eeprom(void);
void p16e_eeprom_2(void);

void p16e_wdt_rst(void);
void p16e_wdt(void);    

void p16e_int_pin_rst(void); 
void p16e_int_pin(void);

void p16e_int_portb_rst(void);
void p16e_int_portb(void);

void p16e_uart_rst(void);
void p16e_uart_rst_2(void);
#define p16e_uart serial


#ifdef __cplusplus
}
#endif

#endif /* P16E_PERIFERIC_H */
