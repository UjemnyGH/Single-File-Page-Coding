NAME?=page

main:
	g++ -o $(NAME) ${NAME}.cpp
	./${NAME}
	rm ${NAME}
	firefox *.html

.SILENT:	