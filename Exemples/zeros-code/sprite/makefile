CC = arm-thumb-elf-gcc
OBJCOPY = arm-thumb-elf-objcopy
CFLAGS = -Wall -marm -mapcs-32 -mcpu=arm7tdmi
PROJECT = sprite

${PROJECT}.mb: ${PROJECT}.c makefile
	${CC} ${PROJECT}.c -o ${PROJECT}.elf -T lnkscript -DMULTIBOOT ${CFLAGS}
	${OBJCOPY} -O binary ${PROJECT}.elf ${PROJECT}.mb
	# MB Image

${PROJECT}.gba: ${PROJECT}.c makefile
	${CC} ${PROJECT}.c -o ${PROJECT}.elf -T lnkscript -Wall ${CFLAGS}
	${OBJCOPY} -O binary ${PROJECT}.elf ${PROJECT}.gba
	# GBA Image

all: ${PROJECT}.mb ${PROJECT}.gba

clean:
	rm -f *~ ${PROJECT}.elf ${PROJECT}.mb ${PROJECT}.gba

send: ${PROJECT}.mb
	mb -w 10 -s ${PROJECT}.mb
