
//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528




#!/bin/bash

# Check to see which version the user wishes to run.
VERSION="$1"
INPUT="user_input"
THREADS=NULL
DEADLINE=NULL
SIZE=NULL
LOOP_COUNT=0

# Check version function
check_version() {
	if [ "$VERSION" == "A1" ]
	then
		./wthread.exe $THREADS $DEADLINE $SIZE
	elif [ "$VERSION" == "A2" ]
	then
		./pthread $THREADS $DEADLINE $SIZE
	elif [ "$VERSION" == "A3" ]
	then
		./pthread $THREADS $DEADLINE $SIZE
	else
		printf "usage: partB.bash <version>\n"
	fi
}

# Check to see if the user provided an input file
if ! [ -t 0 ]
then
	while read INPUTFILE
	do
		# THIS IS SOME SERIOUSLY HACKY BULLSHIT BUT IT WORKS
		# Begin by checking the loop count
		# If it's 0 it means we're reading in the first argument
		# for the program, if it's 1 we're on the second argument
		# and finally if it's 2 we're on the third argument
		if [ "$LOOP_COUNT" -eq 0 ]
		then
			# Make sure the supplied data is actually an integer.
			if [[ "$INPUTFILE" =~ ^[0-9]+$ ]]
			then
				# If it's good data we assign it to one of the three variables.
				THREADS=$INPUTFILE
			else

				# If at any point we read incorrect data exit the program.
				printf "Incorrect file format.\n"
				printf "Please provide 3 positive integers on separate lines.\n"
				printf "Exiting...\n"

				exit 1
			fi

		# Rinse and repeat for second argument.
		elif [ "$LOOP_COUNT" -eq 1 ]
		then
			if [[ "$INPUTFILE" =~ ^[0-9]+$ ]]
			then
				DEADLINE=$INPUTFILE
			else
				printf "Incorrect file format.\n"
				printf "Please provide 3 positive integers on separate lines.\n"
				printf "Exiting...\n"

				exit 1
			fi

		# Rinse and repeat for third argument.
		elif [ "$LOOP_COUNT" -eq 2 ]
		then
			if [[ "$INPUTFILE" =~ ^[0-9]+$ ]]
			then
				SIZE=$INPUTFILE
			else
				printf "Incorrect file format.\n"
				printf "Please provide 3 positive integers on separate lines.\n"
				printf "Exiting...\n"

				exit 1
			fi
		else
			printf "Incorrect file format.\n"
			printf "Please provide 3 positive integers on separate lines.\n"
			printf "Exiting...\n"

			exit 1
		fi

		let LOOP_COUNT=LOOP_COUNT+1
	done

	# Check which version the user selected and execute the appropriate program.
	check_version

	# If no input file was provided run the program interactively.
else
	# Loop functions for parameter input.
	thread_function() {
		# Check to see whether $THREADS is a positive integer
		# If it's not loop and ask the user for correct input
		while ! [[ "$THREADS" =~ ^[0-9]+$ ]]
		do
			printf "Please input a positive integer for the number of threads: \n"
			read THREADS
		done
	}

	deadline_function() {
		# Check to see whether $DEADLINE is a positive integer
		# If it's not loop and ask the user for correct input
		while ! [[ "$DEADLINE" =~ ^[0-9]+$ ]]
		do
			printf "Please input a positive integer the deadline: \n"
			read DEADLINE
		done
	}

	size_function() {
		# Check to see whether $SIZE is a positive integer
		# If it's not loop and ask the user for correct input
		while ! [[ "$SIZE" =~ ^[0-9]+$ ]]
		do
			printf "Please input a positive integer for the number of squares: \n"
			read SIZE
		done
	}

	# Main script loop
	# Check to see if the user whishes to quit at any time.
	while [ $INPUT != "q" ]
	do
		printf "(s)tart - Start entering parameters for the program.\n"
		printf "(q)uit - Exit the program.\n"
		read INPUT

		if [ $INPUT == "s" ]
		then
			thread_function
			deadline_function
			size_function
			check_version
		fi
	done
fi
