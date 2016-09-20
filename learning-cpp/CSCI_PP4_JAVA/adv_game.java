/*
 * adv_game (v8.8.8)
 * Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 * in order to get to the next level and ultimately win the game.
 *
 * CMS
 * Date added: 6/3/16
 */
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.Random;
import java.util.Vector;
import java.lang.StringBuilder;
import java.lang.Byte;
import java.lang.Integer;
import javax.swing.JOptionPane;

/**
 * The MainFrame holds essential algorithms and functions used by all subsystems of the game
 * as well as the 'main_board' data set that always holds all the tiles in the game at their
 * current state.
 */
interface MainFrame
{
    //declaring grid and structure datasets to be copied and manipulated later
    final char[][] cave = {
        {'#','#','#','#','#'},
        {'#','^',' ',' ','#'},
        {'#','#','#',' ','#'},
        {'#','^',' ',' ','#'},
        {'#','#','#','_','#'},
    };
    final char[][] boulder = {
        {' ','#','#','#',' '},
        {'#','#','#','#','#'},
        {'#','#','^',' ',' '},
        {'#','#','^','#','#'},
        {' ','#','#','#',' '},
    };
    final char[][] levelTwo = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', ' ', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', '#', '#', '#', ' '},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' '},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', 'X', ' ', '#', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '},
    };
    final char[][] levelThree = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '/', 'H', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'X', '#'},
        {'#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '*', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    final char[][] levelFour = {
        {'#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#'},
        {'#', '[', ' ', ']', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '+', '+', '#', ' ', ' ', 'E', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '_', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '/', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '8', '=', '='},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', 'H', '#', ' ', ' ', ' ', ' ', '8', '=', '='},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '=', '='},
        {'#', '#', '#', '#', '#', '#', '#', 'B', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '-', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '[', ' ', ']', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
        {' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' '},
    };
    char[][] main_board = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
    Random randomGenerator = new Random();
    static void make_space() {
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    };
    /**
     * display_board
     *
     * Generic algorithm to display two dimensional grid.
     * The function works by executing a loop that invokes a second loop upon each full cycle
     * after printing a new line for the row that will be printed by the second loop.
     * The second loop simply prints each tile or character followed by a space.
     *
     */
    static void display_board() {
        for (byte row = 0; row <= 19; row++) {
            System.out.print("\n");
            for (byte col = 0; col <= 19; col++)
            { System.out.print(main_board[row][col] + " "); };
        };
    };
    /**
     * generate_struct
     *
     * As the name implies, this function takes a template dataset and uses it to overwrite a portion of the main_board
     *
     * @param template to be written upon the grid, in the form of a two dimensional array as corresponds
     * @param seed, representing where the top-left corner of the template will be printed in the main_board.
     *   e.x. (A seed of 3 will begin to print the template at coordinates (3,3) on the main_board)
     * @return
     */
    static void generate_struct(char[][] template, int seed, int size) {
        for (int col = 0; col <= size; col++) {
            for (int row = 0; row <= size; row++)
            { main_board[seed + col][seed + row] = template[col][row]; };
        };
    };
    /**
     * cleanup
     *
     * sequentally checks if there are save files for levels one through four and deletes them.
     *
     */
    static void cleanup() {
        try {
            Path level1 = Paths.get("level1");
            if (Files.exists(level1)) { Files.delete(level1); };
            Path level2 = Paths.get("level2");
            if (Files.exists(level2)) { Files.delete(level2); };
            Path level3 = Paths.get("level3");
            if (Files.exists(level3)) { Files.delete(level3); };
            Path level4 = Paths.get("level4");
            if (Files.exists(level4)) { Files.delete(level4); };
        } catch (IOException ex) { System.out.println(ex); };
    };
};

/**
 * ENTITY_PLAYER
 *
 * Class holding the player entity, implementing MainFrame to allow access to the main_board
 * and subsequent methods.
 *
 * @SuppressWarnings flags this class because of its use of raw type vectors holding three digit integer values.
 */
@SuppressWarnings("unchecked")
class ENTITY_PLAYER implements MainFrame
{
    private int health = 400;
    private int damage = 20;
    byte prev_x;
    byte prev_y;
    byte x;
    byte y;
    byte currentLevel;
    byte keyTaken = 0;
    char direction;
    char skin = '$';
    char say;
    boolean firstTurn = true;
    boolean eventTriggered = false;
    boolean levelOverride = false;
    Scanner console_buffer = new Scanner(System.in);
    Vector keys = new Vector();
    Random randGenerator = new Random();
    /**
     * Constructor for ENTITY_PLAYER
     *
     * @param the x coordinate that the player will start at upon initialization
     * @patam the y coordinate that the player will start at upon initialization
     */
    ENTITY_PLAYER(int x, int y) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
    /**
     * SAVE
     *
     * Method for saving save-state files of the player in it's current state.
     * Format for save file is described within the function body.
     * Calls within this method are done in accordance to the save-state formatting standard,
     * printing errors where errors are encountered.
     *
     * @param file_name of the file to which all data will be saved
     */
    void SAVE(String file_name) {
        // Save State Formatting Standard
        /*  Line #      Variable
         ----------------------------------------------------
         *  1           health
         *  2           damage
         *  3           x coordinate
         *  4           y coordinate
         *  5           previous x coordinate
         *  6           previous y coordinate
         *  7           current Level
         *  8           firstTurn (var, name implies)
         *  9-EOF       however many keys owned by the player
         */
        try {
            PrintWriter FILE_OUT = new PrintWriter(file_name);
            FILE_OUT.println(health);
            FILE_OUT.println(damage);
            FILE_OUT.println(x);
            FILE_OUT.println(y);
            FILE_OUT.println(prev_x);
            FILE_OUT.println(prev_y);
            FILE_OUT.println(currentLevel);
            FILE_OUT.println(firstTurn);
            for(byte idx=0;idx<keys.size();idx++) {
                FILE_OUT.println(keys.elementAt(idx).toString());
            };
            FILE_OUT.close();
        } catch (IOException ex) {
            System.out.println(ex);
        };
    };
    /**
     * LOAD
     *
     * Save-state loading method. All calls perform necessicary action to assign values loaded from the
     * input file to their respective values in accordance with the save-state formatting standard described in the
     * function body above.
     *
     * @param file_name of file from which all data will be loaded
     *
     */
    void LOAD(String file_name) {
        Vector<String> aspects = new Vector<String>();
        adv_game.processFile(file_name, aspects);
        health = Integer.parseInt(aspects.elementAt(0));
        damage = Integer.parseInt(aspects.elementAt(1));
        x = Byte.valueOf(aspects.elementAt(2));
        y = Byte.valueOf(aspects.elementAt(3));
        prev_x = Byte.valueOf(aspects.elementAt(4));
        prev_y = Byte.valueOf(aspects.elementAt(5));
        currentLevel = Byte.valueOf(aspects.elementAt(6));
        if (aspects.elementAt(7) == "false") { firstTurn = false; } else { firstTurn = true; };
        Vector newKeyset = new Vector();
        for (byte line = 8; line < aspects.size(); line++)
            { newKeyset.addElement(Integer.parseInt(aspects.elementAt(line))); };
        keys = newKeyset;
    };
    int getHealth() { return health; };
    void addHealth(int input) { health += input; };
    /**
     * looseHealth
     *
     * Function to mutate the health value of the player and perform checks that the player has any health left
     *
     * @param input value to be subtracted from the player's health
     */
    void looseHealth(int input) {
        health -= input;
        say = 'd';
        if (health <= 0) {
            System.out.println("Game: You have died. Game Over.");
            MainFrame.cleanup();
            System.exit(0);
        };
    };
    void increaseDamage(int input) { damage += input; };
    /**
     * movement_handle
     *
     * Method for recieving and processing movement calls and commands from the user's input.
     *
     */
    void movement_handle() {
        System.out.print("\nGame: Enter an action: ");
        try {
            direction = console_buffer.nextLine().charAt(0); //keyCode.getKeyChar();
            prev_x = x; prev_y = y;
            switch(Character.toUpperCase(direction)) {
                case 'W': x -= 1; break;
                case 'A': y -= 1; break;
                case 'S': x += 1; break;
                case 'D': y += 1; break;
                case 'C':
                    // Processing for command system
                    // The assignment of a mere letter to the 'say' variable is to represent a string of subsequent logic processed in main()
                    System.out.print("Game: Enter a comand: ");
                    String command = console_buffer.nextLine();
                    if (command.equals("health")) {
                        say = 'h';
                    }
                    else if (command.equals("help")) {
                        say = 'e';
                    }
                    else if (command.equals("quit")) {
                        MainFrame.cleanup(); MainFrame.make_space(); System.out.println("Exiting."); System.exit(0);
                    }
                    else if (command.equals("keys")) {
                        say = 'k';
                    }
                    else if (command.equals("save")) {
                        SAVE("save_state.dat");
                    }
                    else if (command.equals("restart")) {

                        //block logic for loading the level, specified by the user after giving the 'restart' command
                        switch( currentLevel ) {
                            case 1: LOAD("level1"); break;
                            case 2: LOAD("level2"); break;
                            case 3: LOAD("level3"); break;
                            case 4: LOAD("level4"); break;
                            case 5: LOAD("level5"); break;
                            case 6: LOAD("level6"); break;
                            default:
                                System.out.println("Game: Error in player movement handling system: The level you are on does not match any case.");
                                System.out.println("This can be fixed by adding a case for level " + currentLevel + " to the list of levels to be reloaded by the restart command.");
                                try { Thread.sleep(8000); } catch (InterruptedException ex) { System.exit(0); };
                        };

                    } //notice partner for encasing bracket

                    //spitting "Invalid commmand." string if the command given doesn't match any cases of the residing if-else chain above.
                    else { System.out.println("Game: Invalid command."); };
                    break;
                default:
                    say = 'm';
                    break;
            };
            // This catches an unknown error that has/had occured somewhat frequently in regards to the system not processsing
            // user input correctly.
        } catch(StringIndexOutOfBoundsException ex) {
            System.out.println("Exception: " + ex);
        };
    };
    /**
     * object_reaction
     *
     * Methodology ruleing all ways that the player reacts to it's environment.
     *
     * @param the subject, (an enemy) whom the player will be reacting from
     */
    void object_reaction(ENTITY_ENEMY_HUNTER enemy) {
        switch( adv_game.this_object(x, y) ) {
            case '#':
                // The '#' symbol representing a wall most commonly in the game.
                // This block keeps the player from running through the wall.
                System.out.println("Narrator: You cannot move here.");
                x = prev_x; y = prev_y;
                main_board[x][y] = skin;
                break;
            case 'B':
                // The 'B' symbol representing an old 'mechanism'. This is implemented to add more variety to the environment.
                // The logic treats this object as a wall, but presenting a chance to print a statement describing it.
                if ( MainFrame.randomGenerator.nextBoolean() )
                { System.out.println("You: Telling by this old mechanism, nobody's been here in a while."); }
                else { System.out.println("Narrator: You cannot move here."); };
                x = prev_x; y = prev_y;
                main_board[x][y] = skin;
                break;
            case '8':
                // The '8' symbol in the game stands for a similar object as above and the logic acts accordingly.
                if ( MainFrame.randomGenerator.nextBoolean() )
                { System.out.println("You: A rusted valve."); }
                else { System.out.println("Narrator: You cannot move here."); };
                x = prev_x; y = prev_y;
                main_board[x][y] = skin;
                break;
            case 'X':
                // The 'X' symbol is an exit token for all levels.
                // Logic in this passes the player to the next level with a notification of waht is happening.
                System.out.println("Narrator: Level passed!");
                currentLevel += 1;
                break;
            case '+':
                // The plus symbol increases the player's health when passed over.
                addHealth(25);
                System.out.println("You: Wow, a health shard!");
                System.out.println("Narrator: Your health has increased to " + getHealth() + ".");
                break;
            case 'T':
                // The 'T' stands for a sword. This object will increase the damage the player can do.
                System.out.println("You: At last! A Sword!");
                System.out.print("Narrator: Your damage has increased from " + damage);
                increaseDamage(25);
                System.out.print(" to " + damage + ".");
                break;
            case 'M':
                // 'M' is the skin of a hunter in this game.
                // Code in this block will refelect that the player has damaged an enemy. Reducing from the opponent's life
                // and killing the enemy in the case that it doesn't have any health left.
                System.out.println("You: Take that!");
                enemy.looseHealth(damage);
                if (enemy.getHealth() <= 0) {
                    enemy.die();
                };
                x = prev_x;
                y = prev_y;
                break;
            case '/':
                // A slash stands for a door.
                // The block below will open the door if the player consents, while preventing the player to move through it
                // if unopened.
                byte doorX = x;
                byte doorY = y;
                x = prev_x;
                y = prev_y;
                System.out.println("You: There's a door, it seems to be unlocked.");
                System.out.println("Narrator: Open it? y/n > ");
                char response = console_buffer.nextLine().charAt(0);
                if (response == 'y') { main_board[doorX][doorY] = ' '; };
                break;
            case '_':
                // The underscore represents a door as well, from a different perspective.
                // Logic in this block performs identically with that above.
                doorX = x;
                doorY = y;
                x = prev_x;
                y = prev_y;
                System.out.println("You: There's a door, it seems to be unlocked.");
                System.out.println("Narrator: Open it? y/n > ");
                response = console_buffer.nextLine().charAt(0);
                if (response == 'y') { main_board[doorX][doorY] = ' '; };
                break;
        };
        // setting coordinates wherever they have ended
        main_board[x][y] = skin;
        // casting skin onto main_board being in the new coordinate location
        main_board[prev_x][prev_y] = ' ';
    };
};
/**
 * KEYGUARD
 *
 * This interface will allow multiple classes access to the keys within the 'keyring'.
 * This variable isn't integrated into any class in order to keep the list of parameters for some functions shorter.
 *
 */
interface KEYGUARD {
    int[][] keyring = {
        {323, 232}, {890, 208},
        {157, 176}, {225, 755},
        {114, 495}, {611, 815},
        {212, 311}, {732, 326},
        {985, 860}, {615, 524}
    };
};
/**
 * GATEKEEPER
 *
 * This class all functionallity of the gate structure in this game.
 * This class implements the MainFrame to access the main_board and implements KEYGUARD
 * in order to check keys agains values currently owned by the plyer.
 *
 * @SuppressWarnings flags this class to permit it's use of raw type vectors.
 *
 */
@SuppressWarnings("unchecked")
class GATEKEEPER implements KEYGUARD, MainFrame
{
    private int key;
    byte keyRing;
    boolean unlocked = false;
    byte player_x;
    byte player_y;
    byte gateCoord_x;
    byte gateCoord_y;
    char gateSkin;
    boolean partner;
    Random randGenerator = new Random();
    /**
     * Constructor for the GATEKEEPER structure
     *
     * @param x coordinate that the structure will be placed at upon initialization
     * @param y coordinate that the structure will be placed at upon initialization
     * @param key that will be needed to unlock the gate
     * @param partner, boolean defining weiter or not the gate is part of a pair
     */
    GATEKEEPER(int x, int y, int key, int keyRing, boolean partner) {
        this.gateCoord_x = (byte) x;
        this.gateCoord_y = (byte) y;
        this.keyRing = (byte) keyRing;
        this.partner = partner;
        this.key = key;
    };
    int getKey() { return key; };
    /**
     * pickup
     *
     * Method to perform monitorization for the player picking up a key and for determining what key they have
     * picked up.
     *
     * @param subject that will be monitored for movement over a key symbol (constituted as picking up the key)
     *
     */
    void pickup(ENTITY_PLAYER subject) {
        player_x = subject.x;
        player_y = subject.y;
        if (adv_game.this_object(player_x, player_y) == '^') {
            System.out.print("You: A key... The number ");
            if (partner == true) {

                // This block performs the somewhat more complex determinations of what key the player will have picked
                // up when the given GATEKEEPER structure has a partner.
                if (((randGenerator.nextBoolean() == false) && (subject.keyTaken != 1) || subject.keyTaken == 2)) {
                    subject.keys.addElement(new Integer(keyring[keyRing][0]));
                    subject.keyTaken = 1;
                } else if (subject.keyTaken != 2) {
                    subject.keys.addElement(new Integer(keyring[keyRing][1]));
                    subject.keyTaken = 2;
                };

            } else {
                subject.keys.addElement(new Integer(keyring[keyRing][0]));
            };
            System.out.print(subject.keys.lastElement() + " is on it.");
        };
    };
    /**
     * gateCheck
     *
     * Method for attempting to unlock the gate and for determining weiter or not that action will be permitted
     *
     * @param subject that has invoked the method by attempting to unlock the gate
     *
     */
    void gateCheck(ENTITY_PLAYER subject) {
        player_x = subject.x;
        player_y = subject.y;

        if (player_x == gateCoord_x && player_y == gateCoord_y && unlocked == false) {
            subject.x = subject.prev_x;
            subject.y = subject.prev_y;
            System.out.println("Narrator: There's a gate.");
            System.out.println("You: it seems to be unlocked...");
            System.out.println("Narrator: Try to unlock it? y/n > ");
            char response = subject.console_buffer.nextLine().charAt(0);
            if (response == 'y')
            {

                // This block, permitted by the user will determine if the user's character has the appropriate keys
                // to unlock the gate.
                for (byte indexer = 0; indexer < subject.keys.size(); indexer++)
                {
                    if (subject.keys.elementAt(indexer).equals(key)) {
                        main_board[gateCoord_x][gateCoord_y] = ' ';
                        gateCoord_x = 0;
                        gateCoord_y = 0;
                        gateSkin = '#';
                        unlocked = true;
                    };
                    if (unlocked == true) { System.out.println("You: Unlocked!"); }
                    else { System.out.println("You: These keys don't fit..."); };
                };

            };

        };
    };
}; // Note; closing bracket defining the end of this class.

/**
 * MOVABLE
 *
 * Structure that can be moved by the player.
 *
 */
class MOVABLE implements MainFrame
{
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin;
    /**
     * Constructor for the MOVABLE object structure.
     *
     * @param x coordinate that the object will be visually placed
     * @param y coordinate that teh object will be visually placed
     * @param skin that will represent the object
     *
     */
    MOVABLE(int x, int y, char skin) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.skin = skin;
    };
    /**
     * deduct_approach
     *
     * Utility function that will return a string indicating which direction the player is approaching from
     *
     * @param subject that will be factored into the determination process
     * @return string indicator of which direction the subject is moving
     *
     */
    String deduct_approach(ENTITY_PLAYER subject) {
        if (subject.x > subject.prev_x) { return "south"; };
        if (subject.x < subject.prev_x) { return "north"; };
        if (subject.y > subject.prev_y) { return "east"; };
        if (subject.y < subject.prev_y) { return "west"; };
        return "none";
    };
    /**
     * FUNCTION DESCRIPTION
     *
     * Method facilitating the logical reaction to another object moving into it.
     * This funciton, moves the aggravated movable object in the opposite direction of whatever is moving into it.
     *
     * @param aggravator of the funcition. What the current movable object is reacting to.
     *
     */
    void react(ENTITY_PLAYER aggravator) {
        if (x == aggravator.x && y == aggravator.y) {

            // This section of the block enforces the movement of the object in the opposite direction of whatever
            // is moving into it. Conceptualized and visualized as if the aggravator is pushing the movable.
            prev_x = x; prev_y = y;
            if (deduct_approach(aggravator) == "south") { x += 1; };
            if (deduct_approach(aggravator) == "north") { x -= 1; };
            if (deduct_approach(aggravator) == "east") { y += 1; };
            if (deduct_approach(aggravator) == "west") { y -= 1; };

            // This section of the block, keeps all inert objects in the same place if there is a wall blocking
            // the movable from moving. This being in a visual sense only.
            if (adv_game.this_object(x, y) == '#') {
                aggravator.x = aggravator.prev_x;
                aggravator.y = aggravator.prev_y;
                x = prev_x;
                y = prev_y;
                System.out.println("You: It seems stuck.");
            };
            // This last section of the block triggers an arbitraty sequentially processed event, if the movable
            // passes over a trigger token ('*' symbol)
            if (adv_game.this_object(x, y) == '*') {
                aggravator.eventTriggered = true;
            };

        };
        // Final statement ensuring the player is desplayed in their (now current) position.
        main_board[x][y] = skin;
    };
};

/**
 * ENTITY_ENEMY_HUNTER
 *
 * The hunter enemy entity in adv_game. As the name implies, this enemy's purpose is to track down and defeat the
 * player.
 *
 */
class ENTITY_ENEMY_HUNTER implements MainFrame
{
    private int health = 100;
    private int damage = 10;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    boolean alive = true;
    char skin;
    // wether or not to override evasive behavior
    boolean override;
    // variable holding the decesion of wether or not any objects are in the hunters path
    boolean clear = true;
    // direction that will be dictate which way the hunter has decided to go
    char direction;
    // the axis of the new
    char mutedAxis = '0';
    // array to be continously refreshed with data that will serve as the hunter's field of view
    char[][] environment = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    // variable to delimit certain behaviors from being ran continously
    int ran;
    /**
     * Constructor for hunter entity
     *
     * @param x coordinate to which the hunter will be initially positioned
     * @param y coordinate to which the hunter will be initially positioned
     * @param the skin that will visually represent the hunter on the main_board
     *
     */
    ENTITY_ENEMY_HUNTER(int x, int y, char skin) {
        this.skin = skin;
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
    void looseHealth(int value) { health -= value; };
    int getHealth() { return health; };
    /**
     * die
     *
     * Method that will nutralize the hunter upon invocation
     *
     */
    void die() {
        main_board[x][y] = ' ';
        skin = '#';
        x = 19;
        y = 19;
        prev_x = 19;
        prev_y = 19;
        alive = false;
    };
    /**
     * scan
     *
     * Method to copy displayed values of the hunter's environment (main_board) into it's environment variable
     *
     * @param data template that will be filled wiht data from the field of consideration
     * @param x coordinate value defining the center of the hunter's field of consideration
     * @param y coordinate value defining the center of the hunter's field of consideration
     *
     */
    void scan(char[][] template, int x, int y) {
        try {
            for (int col = 0; col <= 2; col++) {
                for (int row = 0; row <= 2; row++) {
                    template[col][row] = main_board[col + x -1][row + y -1];
                };
            };
        } catch (ArrayIndexOutOfBoundsException ex) {
            // Ensure weighted behioral variables are preset to not override any of the hunter's methods of interpretation
            clear = true; override = false;
        };
    };
    /**
     * assume
     *
     * Method to perform case-sesitive logical operations determining what direction the hunter needs to move
     * in, to avoid getting stuck in corners.
     *
     * @param target being sought by the hunter
     * @return the concluded direction that the hunter will then move in
     */
    char assume(ENTITY_PLAYER target) {
        int cornerdetect = 0;
        char conclusion = '0';
        if (environment[2][1] == '#') {
            if (target.y < y && mutedAxis != 'y') {
                conclusion = 'a';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            } else {
                conclusion = 'd';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            };
        }
        if (environment[1][0] == '#') {
            if (target.x > x && mutedAxis != 'x') {
                conclusion = 's';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            } else {
                conclusion = 'w';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            };
        }
        if (environment[0][1] == '#') {
            if (target.y < y && mutedAxis != 'y') {
                conclusion = 'a';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            } else {
                conclusion = 'd';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            };
        }
        if (environment[1][2] == '#') {
            if (target.x > x && mutedAxis != 'x') {
                conclusion = 's';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            } else {
                conclusion = 'w';
                cornerdetect = (cornerdetect == 0) ? 1 : 2;
            };
        };
        // if a corner has been detected, decide to move in the opposite direction to avoid it.
        if (cornerdetect == 2) {
            switch ( direction ) {
                case 'w': return 's';
                case 's': return 'w';
                case 'a': return 'd';
                case 'd': return 'a';
            };
        };
        return conclusion;
    };
    /**
     * auto_hunt
     *
     * Method facilitating all core processsing for the Hunter.
     *
     * @param target to be hunted
     *
     */
    void auto_hunt(ENTITY_PLAYER target) {
    if (alive) {
        prev_x = x; prev_y = y;
        // move positions depending on the way decided
        switch ( direction ) {
            case 'w': x -= 1; break;
            case 's': x += 1; break;
            case 'd': y += 1; break;
            case 'a': y -= 1; break;
        };
        // prevent getting stuck in a particular direction
        if ( ran > 5 ) { override = false; mutedAxis = '0'; ran = 0; };
        // if not avoiding an object, move in the direction of the target
        if (!override) {
            if (x > target.x) { direction = 'w'; }
            else if (x < target.x && mutedAxis != 'x') { direction = 's'; }
            else if (y < target.y && mutedAxis != 'y') { direction = 'd'; }
            else if (y > target.y && mutedAxis != 'y') { direction = 'a'; };
        } else {
            // otherwise, look at the environment and decide wether or not there's a corner
            scan(environment, x, y);
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++)
                { if (environment[col][row] == '#') { clear = false; }; System.out.println("Env: " + environment[col][row]); };
            };
            if (clear) { override = false; }
            else { override = true; };
            ran++;
        };
        // if there's a wall, move away from it and scan the environment to determine how to avoid it
        if (adv_game.this_object(x, y) == '#') {
            x = prev_x; y = prev_y;
            scan(environment, x, y);
            direction = assume(target);
            override = true;
            switch ( direction ) {
                case 'w': mutedAxis = 'x'; break;
                case 'a': mutedAxis = 'y'; break;
                case 's': mutedAxis = 'x'; break;
                case 'd': mutedAxis = 'y'; break;
            };
        };
        // attack if the player is close
        if (target.x % x <= 1 && target.x / x == 1 && target.y % y <= 1 && target.y / y == 1) {
            target.looseHealth(damage);
        };
        // ensure that the hunter is properly displayable
        main_board[x][y] = skin;
        main_board[prev_x][prev_y] = ' ';
    };
    };
};
/**
 * ENTITY_ENEMY_CRAWLER
 *
 * The crawler enemy entity in adv_game. It's primary funciton is to move blindly around the grid
 * to the chance of hitting the player.
 *
 */
class ENTITY_ENEMY_CRAWLER implements MainFrame
{
    private final int damage = 25;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin = '|';
    char direction = 'w';
    /**
     * Constructor for ENTITY_ENEMY_CRAWLER
     *
     * @param x coordinate by which the crawler will be initially positioned.
     * @param y coordinate by which the crawler will be initially positioned.
     *
     */
    ENTITY_ENEMY_CRAWLER(int x, int y) {
        this.x = (byte) x;
        this.y = (byte) y;
    };
    /**
     * crawl
     *
     * Method governing all actions the entity makes
     *
     * @param
     *
     */
    void crawl(ENTITY_PLAYER aggrogate) {
        prev_x = x; prev_y = y;
        // Move in the direction decided
        switch (direction) {
            case 'w': x -= 1; break;
            case 'a': y -= 1; break;
            case 's': x += 1; break;
            case 'd': y += 1; break;
        };
        // Change direction randomly if there is a wall or exit token object
        if(adv_game.this_object(x, y) == '#' || adv_game.this_object(x, y) == 'X') {
            x = prev_x; y = prev_y;
            switch (direction) {
                case 'w': if (randomGenerator.nextInt(40) >= 25) { direction = 'a'; } else { direction = 'd'; }; break;
                case 'a': if (randomGenerator.nextInt(40) >= 25) { direction = 's'; } else { direction = 'w'; }; break;
                case 's': if (randomGenerator.nextInt(40) >= 20) { direction = 'd'; } else { direction = 'a'; }; break;
                case 'd': if (randomGenerator.nextInt(40) <= 20) { direction = 'w'; } else { direction = 's'; }; break;
            };
        };
        // Attack if the aggrogate is close
        if (aggrogate.x % x <= 1 && aggrogate.x / x <= 1 && aggrogate.y % y <= 1 && aggrogate.y / y <= 1) {
            aggrogate.looseHealth(damage);
        };
        // Create spinning effect
        if (skin == '|') { skin = '-'; }
        else { skin = '|'; };
        // Ensure that the entity is properly displayable
        main_board[x][y] = skin;
        main_board[prev_x][prev_y] = ' ';
    };
};
/**
 * FileCommandInterpreter
 *
 * Class encasing all methodological structures necessicary to read and interpret an input file
 * in the desired manner.
 *
 */
class FileCommandInterpreter implements MainFrame
{
    String lastRun = new String();
    Integer times = new Integer(0);
    /**
     * main_
     *
     * Method for executing the entirety of the funcitonallity that this class offers.
     *
     * @param player that the effects of the interpreted actions will be imposed upon
     *
     */
    void main_(ENTITY_PLAYER player)
    {
    if (player.eventTriggered)
    {
        Vector<String> compilation = new Vector<String>();
        // String for holding the last call in memory
        String last = new String();
        // Variable holding the current read position in the file
        Integer indexer = new Integer(0);

        adv_game.processFile("commands.dat", compilation);

        // Run loop for every statement present in the compiled file's code
        for (String statement : compilation) {
            if (last.equals("level3") && player.currentLevel == 3) {
                if (lastRun != "level3" && times < 2) {
                    if (statement.equals("teleport")) {
                        System.out.println("teleporting");
                        lastRun = "level3";
                        break;
                    };
                    if (statement.equals("remove")) {
                        main_board
                        [Integer.parseInt(compilation.elementAt(indexer + 1))]
                        [Integer.parseInt(compilation.elementAt(indexer + 2))]
                        = ' ';
                        lastRun = "level3";
                        break;
                    };
                } else if (times < 2) {
                    lastRun = "none";
                    times += 1;
                } else { times -= 1; };
            };
            last = statement;
            indexer++;
        };
        last = "null";
        player.eventTriggered = false;
    };
    };
};

// Main class corresponding to this file's filename
public class adv_game implements MainFrame {
    /**
     * processFile
     *
     * Function to deconstruct textual data from a file into sections, that are sequentially dumped into a vector string array.
     * These sections that are copied from the input file are delimited by a space.
     *
     * @param the name of the file to be processed
     * @param a vector array to hold the contents of the input file
     *
     */
    static void processFile(String file_name, Vector<String> compilation) {
        try {

            // Create necessicary objects to perform required actions
            Path file_path = Paths.get(file_name);
            InputStream FILE_IN = Files.newInputStream(file_path);
            BufferedReader READ_HEAD = new BufferedReader(new InputStreamReader(FILE_IN));
            String readData = READ_HEAD.readLine();

            // While the READ_HEAD isn't at the end of the file (READ_HEAD operates in readData)
            while (readData != null) {
                StringBuilder prefect = new StringBuilder();

                // Read each individual symbol of the word or section being read and add it to the
                // prefect data store, to be then concatenated onto the compilation
                for (int indexer = 0; indexer < readData.length() ;indexer++ ) {
                    if (readData.charAt(indexer) != ' ') {
                        prefect.append(readData.charAt(indexer));
                    } else {
                        compilation.addElement(prefect.toString());
                        prefect.delete(0, prefect.length());
                    };
                };
                // Add the newly read data to the compilation
                compilation.addElement(prefect.toString());
                // Read the next line
                readData = READ_HEAD.readLine();
            };
            READ_HEAD.close();
            FILE_IN.close();
        } catch (IOException ex) {
            System.out.println(ex);
        };
    };
    /**
     * this_object
     *
     * Simple funciton to print out the tile at a given coordinate location on the main_board
     *
     * @param the x coordinate to be inspected
     * @param the y coordinate to be inspected
     * @return the value of the object or tile of the main_board at the specified coordinates
     * (This accounts for all return statements)
     */
    static char this_object(byte x, byte y) {
        switch( main_board[x][y] ) {
            case '#': return '#';
            case 'M': return 'M';
            case 'X': return 'X';
            case '^': return '^';
            case 'T': return 'T';
            case '+': return '+';
            case 'H': return 'H';
            case '*': return '*';
            case '/': return '/';
            case '@': return '@';
            case '_': return '_';
            case '8': return '8';
            case '=': return '=';
            case 'B': return 'B';
        };
        return ' ';
    };
    /**
     * message_postProcessor
     *
     * Function to print out pending text strings and to carry out corresponding actions based on those statements
     * based on a preset of cases. This function is necessicary to avoid scope issues with printing all text and
     * performing all actions within the ENTITY_PLAYER class.
     *
     * @param the subject to be inspected for pending statements
     *
     */
    static void message_postProcessor(ENTITY_PLAYER subject) {
        switch( subject.say ) {
            case 'd':
                // Print damage notification message along with new current health
                System.out.println("You: Aaah!");
                System.out.println("Narrator: You've been attacked, your health is now at " + subject.getHealth() + ".");
                subject.say = '0';
                break;
            case 'e':
                // Print a help statement
                System.out.println("Narrator: You can enter the following: help, health, quit, restart");
                subject.say = '0';
                break;
            case 'h':
                // Print the player's health
                System.out.println("You: I seem to be at " + subject.getHealth() + " health.");
                subject.say = '0';
                break;
            case 'k':
                // Print any and all keys the player may have
                if (subject.keys.isEmpty()) {
                    System.out.println("You: I haven't picked up any keys.");
                } else {
                    System.out.print("You: I have keys ");
                    for (byte indexer = 0; indexer < subject.keys.size(); indexer++ ) {
                        String currentItem = subject.keys.elementAt(indexer).toString();
                        System.out.print(currentItem + ' ');
                    };
                };
                subject.say = '0';
                break;
            case 'm':
                // 
                System.out.println("Game: That is not a move.");
                subject.say = '0';
                break;
        };
    };
    static void argparser(String[] args, ENTITY_PLAYER player) {
        try {
            if (args[0].equals("-l")) {
                try {
                    player.currentLevel = Byte.parseByte(args[1]);
                    player.levelOverride = true;
                } catch (ArrayIndexOutOfBoundsException ex) {
                    System.out.println("Invalid argument list: The -l argument must be followed by the level to be skipped to.");
                    System.exit(1);
                };
            };
        } catch (ArrayIndexOutOfBoundsException ex) {};
    };
    static void welcome(Path saveState) {
        Scanner console_buffer = new Scanner(System.in);
        System.out.println("******************************************");
        System.out.println("*                Main Menu               *");
        System.out.println("*         Type anything to start         *");
        System.out.println("*        Type \"stats\" for statistics     *");
        System.out.println("*          Type \"help\" for help          *");
        if (Files.exists(saveState))
      { System.out.println("* Save state detected, game will resume. *");
        System.out.println("*    Type \"delete\" to delete your save   *"); };
        System.out.println("******************************************");
        System.out.print(">> ");
        String command = console_buffer.nextLine();
        if (command.equals("stats")) {};
        if (command.equals("help")) {
            String messageBody = "In adv_game you can use the WASD keys to move and the C key to input commands.\n"
            + "Commands include; quit, help, health, restart, save, keys. Quit will quit the game, Help will \n"
            + "show a list of possible commands, Health will invoke your character to say his health, Restart will\n"
            + "restart the current level and finally Save will save the game in it's current state to be resumed the\n"
            + " next time the program is run. In this game you also encounter enemies that can be attacked by\n"
            + " simply moving into them. You will find power-ups that can be collected the same way and some objects\n"
            + " can be moved by moving towards them as well.\n";
            JOptionPane.showMessageDialog(null, messageBody , "Adv_game Manual", JOptionPane.INFORMATION_MESSAGE);
            welcome(saveState);
        };
        if (command.equals("delete")) { try { Files.delete(saveState); MainFrame.make_space(); welcome(saveState); }
        catch(IOException ex) { System.out.println(ex); MainFrame.make_space(); welcome(saveState); } };
    };
    public static void main(String[] args) throws IOException
    {
        InputStream FILE_IN = null;
        OutputStream FILE_OUT = null;
        try {
            int times_ran = 1;
            FILE_IN = new FileInputStream("stats.dat");
            times_ran += FILE_IN.read(); //FILE_IN.read() returns -1 after being called as second time?
            FILE_OUT = new FileOutputStream("stats.dat");
            FILE_OUT.write(times_ran);
            System.out.println("Times ran since v.1.9.5: " + times_ran);
        } catch (IOException ex) {
            System.out.println(ex);
        } finally {
            FILE_IN.close();
            FILE_OUT.close();
        };
        //essensial variables
        ENTITY_PLAYER player = new ENTITY_PLAYER(10, 10);
        FileCommandInterpreter processor_t = new FileCommandInterpreter();
        Path saveState = Paths.get("save_state.dat");

            //  Check for arguments
            argparser(args, player);

        //KeyEvent keyCode = new KeyListener();

        JOptionPane.showMessageDialog(null, "Narrator: Use the WASD keys to move the player." + "\nAnd use C to enter a command.");
        welcome(saveState);
        if (Files.exists(saveState)) { player.LOAD("save_state.dat"); };

        //setup for level one
        if (randomGenerator.nextBoolean() == true) {
            MainFrame.generate_struct(boulder, 5, 4);
        } else { MainFrame.generate_struct(cave, 5, 4); };
        ENTITY_ENEMY_HUNTER monster = new ENTITY_ENEMY_HUNTER(4, 4, 'M');
        GATEKEEPER l1Gate1 = new GATEKEEPER(9, 14, 323, 0, true);
        GATEKEEPER l1Gate2 = new GATEKEEPER(11, 14, 232, 1, true);
        if (!player.levelOverride) { player.currentLevel = 1; };
        player.SAVE("level1");
        while (player.currentLevel == 1) {
            MainFrame.make_space();
            l1Gate1.pickup(player);
            player.object_reaction(monster);
            message_postProcessor(player);
            MainFrame.display_board();
            player.movement_handle();
            monster.auto_hunt(player);
            processor_t.main_(player);
        };

        //cleanup and setup for level two
        MainFrame.generate_struct(levelTwo, 0, 19);
        monster = null;
        ENTITY_ENEMY_CRAWLER snitch = new ENTITY_ENEMY_CRAWLER(5, 15);
        player.SAVE("level2");
        while (player.currentLevel == 2) {
            MainFrame.make_space();
            l1Gate1.gateCheck(player); l1Gate2.gateCheck(player);
            player.object_reaction(null);
            message_postProcessor(player);
            MainFrame.display_board();
            player.movement_handle();
            snitch.crawl(player);
            processor_t.main_(player);
        };

        //cleanup and setup for level three
        l1Gate1 = null; l1Gate2 = null;
        snitch = null;
        MainFrame.generate_struct(levelThree, 0, 19);
        MOVABLE box1 = new MOVABLE(2, 5, 'H');
        GATEKEEPER l2Gate = new GATEKEEPER(9, 4, 890, 1, false);
        player.SAVE("level3");
        while (player.currentLevel == 3) {
            MainFrame.make_space();
            box1.react(player);
            l2Gate.pickup(player);
            l2Gate.gateCheck(player);
            player.object_reaction(null);
            message_postProcessor(player);
            MainFrame.display_board();
            player.movement_handle();
            processor_t.main_(player);
        };

        //cleanup and setup for level four
        box1 = null;
        l2Gate = null;
        MainFrame.generate_struct(levelFour, 0, 19);
        player.SAVE("level4");
        while (player.currentLevel == 4) {
            MainFrame.make_space();
            player.object_reaction(null);
            message_postProcessor(player);
            MainFrame.display_board();
            player.movement_handle();
        };
        MainFrame.cleanup();

        System.out.println("Narrator: Congradulations, you've won the game.");
    };
};
