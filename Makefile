all:
	mkdir -p bin
	+$(MAKE) -C src
clean:
	rm -r bin
	rm main
