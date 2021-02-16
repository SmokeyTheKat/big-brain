all:
	gcc ./src/main.c -o ./big-brain
install:
	sudo cp ./big-brain /usr/bin/bb
tc: all
	./big-brain "++."
