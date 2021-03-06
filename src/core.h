/****************************************************************************
*    Copyright © 2014-2015 Xorg
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************/

/*
* PROJECT CPU-X
* FILE core.h
*/

#ifndef _CPUX_H_
#define _CPUX_H_

#include <stdint.h>
#define HAVE_STDINT_H	/* Skip conflicts with <libcpuid/libcpuid_types.h> */
#define BASEFILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) /* Don't show full path of file */
#define MSGVERB(str) msg('v', str, PRGNAME, BASEFILE, __LINE__)
#define MSGSERR(str) msg('e', str, PRGNAME, BASEFILE, __LINE__)
#define MSGPERR(str) msg('p', str, PRGNAME, BASEFILE, __LINE__)
#define MSGROOT _("WARNING:\nroot privileges are required to work properly.")
#define _(str) gettext(str)

#define PRGNAME "CPU-X"
#define PRGAUTH "X0rg"
#define PRGCPYR "Copyright © 2014-2015 Xorg"
#define EXIT_FNO 2	/* Exit when File Not Open */
#define SYS_DMI "/sys/devices/virtual/dmi/id"
#define NAME	0
#define VALUE	1
#define MAXSTR	60	/* Max string */
#define S 10		/* Little string */
#define CACHEFIELDS 3	/* Nb of fields by cache frame */
#define RAMFIELDS 2	/* Nb of fields by bank */
#define GPUFIELDS 3	/* Nb of fields by GPU frame */

#ifdef GTK
# define HAS_GTK 1
#else
# define HAS_GTK 0
#endif

#ifdef NCURSES
# define HAS_NCURSES 1
#else
# define HAS_NCURSES 0
#endif

#ifdef LIBCPUID
# define HAS_LIBCPUID 1
#else
# define HAS_LIBCPUID 0
#endif

#ifdef LIBDMI
# define HAS_LIBDMI 1
#else
# define HAS_LIBDMI 0
#endif

#ifdef LIBBDWT
# define HAS_LIBBDWT 1
#else
# define HAS_LIBBDWT 0
#endif

#ifdef LIBPCI
# define HAS_LIBPCI 1
#else
# define HAS_LIBPCI 0
#endif

#ifdef LIBPROCPS
# define HAS_LIBPROCPS 1
#else
# define HAS_LIBPROCPS 0
#endif

#ifdef LIBSTATGRAB
# define HAS_LIBSTATGRAB 1
#else
# define HAS_LIBSTATGRAB 0
#endif


enum EnTabNumber
{
	NB_TAB_CPU, NB_TAB_CACHE, NB_TAB_MB, NB_TAB_RAM, NB_TAB_SYS, NB_TAB_GPU, NB_TAB_ABOUT
};

enum EnObjects
{
	TABCPU, TABCACHE, TABMB, TABRAM, TABSYS, TABGPU, TABABOUT,
	FRAMPROCESSOR, FRAMCLOCKS, FRAMCACHE,
	FRAMCACHEL1, FRAMCACHEL2, FRAMCACHEL3,
	FRAMMOBO, FRAMBIOS, FRAMCHIP,
	FRAMBANKS,
	FRAMOS, FRAMMEMORY,
	FRAMGPU1, FRAMGPU2, FRAMGPU3, FRAMGPU4,
	FRAMABOUT, FRAMLICENSE,	LABVERSION, LABDESCRIPTION, LABAUTHOR, LABCOPYRIGHT, LABLICENSE,
	LASTOBJ
};

enum EnTabCpu
{
	VENDOR, CODENAME, PACKAGE, TECHNOLOGY, VOLTAGE, SPECIFICATION, FAMILY, EXTFAMILY, MODEL, EXTMODEL, TEMPERATURE, STEPPING, INSTRUCTIONS,
	CORESPEED, MULTIPLIER, BUSSPEED, BOGOMIPS,
	LEVEL1D, LEVEL1I, LEVEL2, LEVEL3,
	SOCKETS, CORES, THREADS,
	LASTCPU
};

enum EnTabCache
{
	L1SIZE, L1DESCR, L1SPEED,
	L2SIZE, L2DESCR, L2SPEED,
	L3SIZE, L3DESCR, L3SPEED,
	LASTCACHE
};

enum EnTabMainboard
{
	MANUFACTURER, MBMODEL, REVISION,
	BRAND, BIOSVER, DATE, ROMSIZE,
	CHIPVENDOR, CHIPNAME,
	LASTMB
};

enum EnTabRam
{
	BANK0_0, BANK0_1, BANK1_0, BANK1_1, BANK2_0, BANK2_1, BANK3_0, BANK3_1,
	BANK4_0, BANK4_1, BANK5_0, BANK5_1, BANK6_0, BANK6_1, BANK7_0, BANK7_1,
	LASTRAM
};

enum EnTabSystem
{
	KERNEL, DISTRIBUTION, HOSTNAME, UPTIME, COMPILER,
	USED, BUFFERS, CACHED, FREE, SWAP,
	LASTSYS
};

enum EnTabGraphics
{
	GPUVENDOR1, GPUNAME1, GPUTEMP1,
	GPUVENDOR2, GPUNAME2, GPUTEMP2,
	GPUVENDOR3, GPUNAME3, GPUTEMP3,
	GPUVENDOR4, GPUNAME4, GPUTEMP4,
	LASTGPU
};

typedef struct
{
	int refr_time;
	char *objects[LASTOBJ];
	char *tabcpu[2][LASTCPU];
	char *tabcache[2][LASTCACHE];
	char *tabmb[2][LASTMB];
	char *tabram[2][LASTRAM];
	char *tabsys[2][LASTSYS];
	char *tabgpu[2][LASTGPU];
} Labels;


/********************************** Core **********************************/

/* Get options */
int menu(int argc, char *argv[]);

/* Print a formatted message */
void msg(char type, char *msg, char *prgname, char *basefile, int line);

/* Initialize all labels pointers to null */
void labels_setnull(Labels *data);

/* Set labels name */
void labels_setname(Labels *data);

/* Replace null pointers by character '\0' */
void labels_delnull(Labels *data);

/* Free memory after display labels */
void labels_free(Labels *data);

/* Dump all data in stdout */
void dump_data(Labels *data);

/* Elements provided by libcpuid library
TAB: CPU. */
int libcpuid(Labels *data);

/* Pretty label CPU Vendor
TAB: CPU. */
void cpuvendor(char *vendor);

/* Remove unwanted spaces in value Specification
TAB: CPU. */
void clean_specification(char *spec);

/* Print some instruction sets
TAB: CPU. */
void catinstr(char **str, char *in);
void instructions(char **instr);

/* Get CPU core voltage
TAB: CPU. */
double cpu_voltage(int core);

/* Get CPU core temprature
TAB: CPU. */
int cpu_temperature(int core);

/* Get CPU technology, in nanometre (nm)
TAB: CPU. */
int cpu_technology(int32_t model, int32_t ext_family, int32_t ext_model);

/* Elements provided by libdmi library (need root privileges)
TAB: CPU, Motherboard. */
int libdmidecode(Labels *data);

/* Alternative for libdmidecode (Linux only)
TAB: Motherboard. */
int libdmi_fallback(Labels *data);

/* Get CPU frequencies (current - min - max)
TAB: CPU. */
void cpufreq(Labels *data);

/* If 'dmidecode' can be called, return CPU multipliers (actual, min and max)
TAB: CPU. */
void mult(char *busfreq, char *cpufreq, char *multmin, char *multmax, char **multsynt);

/* Read value "bobomips" from file /proc/cpuinfo
TAB: CPU. */
void bogomips(char **c);

/* Find the number of existing banks
TAB: RAM. */
int last_bank(Labels *data);

/* Get system informations
TAB: System. */
void tabsystem(Labels *data);

/* Find some PCI devices
TAB: Motherboad, Graphics. */
void pcidev(Labels *data);

/* Pretty label GPU Vendor
TAB: Graphics. */
char *clean_gpuvendor(char *str);

/* Get GPU tempreature
TAB: Graphics. */
double gpu_temperature(void);

/* Find the number of GPU
TAB: Graphics. */
int last_gpu(Labels *data);

/* Check if a command exists */
int command_exists(char *in);

/* Duplicate a not null string */
char *strdupnullok(const char *s);

/* Check if running version is latest */
char *check_lastver(void);

/* Apply new portable version if available */
int update_prg(char *executable);


/********************************** External headers **********************/

/* Start CPU-X in GTK mode */
void start_gui_gtk(int *argc, char **argv[], Labels *data);

/* Start CPU-X in NCurses mode */
void start_tui_ncurses(Labels *data);

/* Call dmidecode library */
int libdmi(char c);

/* Call bandwidth library */
int bandwidth(Labels *data);


#endif /* _CPUX_H_ */
