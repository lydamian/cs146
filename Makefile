all: every srm unrm trash

every: every.c
	gcc -std=c99 every.c -o every

srm: srm.c
	gcc -std=c99 srm.c -o srm

unrm: unrm.c
	gcc -std=c99 unrm.c -o unrm

trash: trash.c
	gcc -std=c99 trash.c -o trash

clean:
	rm every srm unrm trash
