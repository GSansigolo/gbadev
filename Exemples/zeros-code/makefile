all:
	make -C ./dot all
	make -C ./blit all
	make -C ./sprite all
	make -C ./keypad all
	make -C ./background all
	make -C ./moving all
	make -C ./chaos all
	make -C ./dma-simple all
	make -C ./dma-complex all
	make -C ./timer-irq all
	make -C ./sound-dma all
	make -C ./tools all

backup:
	make clean
	tar cfvj ../backup.tar.bz2 /gba/*

clean:
	rm -f *~
	make -C ./dot clean
	make -C ./blit clean
	make -C ./sprite clean
	make -C ./keypad clean
	make -C ./background clean
	make -C ./moving clean
	make -C ./chaos clean
	make -C ./dma-simple clean
	make -C ./dma-complex clean
	make -C ./timer-irq clean
	make -C ./sound-dma clean
	make -C ./tools clean
