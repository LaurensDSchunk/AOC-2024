# Check if DAY and PART are provided as arguments
if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Usage: $0 <DAY> <PART>"
  exit 1
fi

# Assign day and part from arguments
DAY=$1
PART=$2

# Check for optional development parameter
if [ "$3" == "DEV" ]; then
  INPUT_FILE="test.txt"
else
  INPUT_FILE="input.txt"
fi

# Create a build directory if it doesn't exist
mkdir -p build

# Navigate into the build directory
cd build

# Run cmake to configure the project
cmake -DDAY=$DAY -DPART=$PART ..

# Run make to compile the project
make

# Check if the executable exists and run it
EXECUTABLE="day${DAY}/day${DAY}_part${PART}"
PATH="day${DAY}"

if [ -f "$EXECUTABLE" ]; then
  ./$EXECUTABLE "${PATH}/${INPUT_FILE}"
else
  echo "Executable not found: $EXECUTABLE"
  exit 1
fi
