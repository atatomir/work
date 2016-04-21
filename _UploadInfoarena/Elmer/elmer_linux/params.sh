# FILE: params.sh
# PURPOSE: define problem parameters
# careful! no spaces around equals signs
# all variables must be set (if one is N/A, set it to an empty string)

# file lists may contain any number of files, separated by spaces
# input files
IFILES="elmer.in"

# expected output files
OFILES="elmer.out"

# files used by the verifier
KFILES="elmer.ok"

# time limit in seconds
LIM_TIME="2.000"

# settings that are only honored under Linux
if [ "$ENV" == linux ]; then
	# data segment limit (in Mb, real number)
	LIM_DATA="32.0"

	# stack segment limit (in Mb, real number)
	LIM_STACK="32.0"
fi

# modules don't work under Linux yet
if [ "$ENV" == dos ]; then
	# name of module or empty string
	MODULE=""
fi
