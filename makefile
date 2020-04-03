comp:
	gcc -Wall -g prog4.c -o prog4
run:
	./prog4 RampDown.txt RampDownNegShift.txt output.txt
clean:
	clear
	echo All Clean!
open:
	vim prog4.c


