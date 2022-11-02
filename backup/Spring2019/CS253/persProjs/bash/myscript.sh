#change permissions: chmod +x myscript.sh
#which bash shows me where bash is on my system
# #! is a shibang and /bin/bash is location I found from which

#!/bin/bash

#ECHO COMMAND
#echo Hello World!

#VARIABLES
#Uppercase by convention
#letters, numbers, underscores
#reference variables using $ symbol
#NAME = "Brad"
#echo "My name is ${NAME}"

#user input
#read -p "Enter Your Name: " NAME
#echo "hello $NAME, nice to meet you!"

#simple If statement
#if["$NAME" == "Mark"]
#then
#	echo "Your name is Mark"
#fi

#If-else
#if["$NAME" == "Mark"]
#then
#	echo "Your name is Mark"
#else
#	echo "Your name is not Mark"
#fi

#else-if
#if["$NAME" == "Mark"]
#then
#	echo "Your name is Mark"
#elif["$NAME" == "Mark"]
#then
#	echo "Your name is Jack"
#else
#	echo "Your name is not Mark"
#fi

#Comparison
#######
#val1 -eq val2 ret true if vals are equal
#val1 -ne val2 ret true if vals are NOT equal
#val1 -gt val2 ret true if val1 is greater than val2
#val1 -gt val2 ret true if val1 is greater than or equal to val2
#val1 -gt val2 ret true if val1 is less than val2
#val1 -gt val2 ret true if val1 is less than or equal to val2

#NUM1 = 3
#NUM2 = 5
#if["$NUM1" -gt "$NUM2"]
#then
#	echo "$NUM1 is greater than $NUM2"
#else
#	echo "$NUM1 is less than $NUM2"
#fi
#done

#file conditions
#-f is file
#-e exists
#FILE = "test.txt"
#if [ -f "$FILE" ]
#then
#	echo "$FILE is a file"
#else
#	echo "$FILE is not a file"
#fi

#case statement
#read -p "ARE you 21 or over? Y/N " ANSWER
#case "$ANSWER" in
#	[yY] | [yY][eE][sS]
#		echo "you can have a beer"
#		;;
#	[nN] | [nN][oO]
#		echo "sorry no drinking"
#		;;

#LOOPS









