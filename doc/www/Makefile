all:
	date -I > generated.txt
	m4 -Im4 m4/index.m4 > index.html
	m4 -Im4 m4/flow.m4 > flow.html
	m4 -Im4 m4/todo.m4 > todo.html
	rm generated.txt

clean:
	rm *.html
