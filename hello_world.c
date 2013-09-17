/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <exports.h>

int hello_world (int argc, char *argv[])
{
	int i;

	/* Print the ABI version */
	app_startup(argv);
	printf ("Example expects ABI version %d\n", XF_VERSION);
	printf ("Actual U-Boot ABI version %d\n", (int)get_version());

	printf ("Hello World\n");

	printf ("argc = %d\n", argc);

	for (i=0; i<=argc; ++i) {
		printf ("argv[%d] = \"%s\"\n",
			i,
			argv[i] ? argv[i] : "<NULL>");
	}
	
	volatile unsigned long *GPIO_DATAIN_BOOTKEY = 0x48310038;
	volatile unsigned long *GPIO_OE_SYSLED4 = 0x49058034;
	volatile unsigned long *GPIO_DATAOUT_SYSLED4 = 0x4905803C;
	
	*GPIO_OE_SYSLED4 &= 0xffffffef;
	
	while(!tstc())
	{
	  if((*GPIO_DATAIN_BOOTKEY & 0x00000080) == 0)
	  {
	    printf ("Button NOT pushed: LED OFF\n");
	    *GPIO_DATAOUT_SYSLED4 |= 0x00000010;
	  }
	
	  else
	  {
	    printf ("Button pushed: LED ON\n");
	    *GPIO_DATAOUT_SYSLED4 &= 0xffffffef;
	  }
	}
	
	printf ("Hit any key to exit ... ");
	while (!tstc())
		;
	/* consume input */
	(void) getc();

	printf ("\n\n");
	return (0);
}
