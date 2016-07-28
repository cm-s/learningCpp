echo "Building adv_game..."
javac adv_game.java
java adv_game $1 $2 $3
rm *.class
if [ -e level1 ]; then
    rm level1
fi
if [ -e level2 ]; then
    rm level2
fi
if [ -e level3 ]; then
    rm level3
fi
if [ -e level4 ]; then
    rm level4
fi
if [ -e level5 ]; then
    rm level5
fi
if [ -e level6 ]; then
    rm level6
fi
