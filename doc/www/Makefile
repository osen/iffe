all:
	date -I > generated.txt
	m4 -Im4 m4/index.m4 > index.html
	rm generated.txt

clean:
	rm *.html
