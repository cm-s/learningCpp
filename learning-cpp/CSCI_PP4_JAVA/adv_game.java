/*
 * adv_game (v5.7.0)
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
import java.awt.event.*;
import javax.swing.JOptionPane;
import java.lang.StringBuilder;

class ENTITY_PLAYER
{
    private int health = 400;
    private int damage = 20;
    byte prev_x;
    byte prev_y;
    byte x;
    byte y;
    char direction;
    Scanner console_buffer = new Scanner(System.in);
    byte currentLevel;
    char skin = '$';
    boolean firstTurn = true;
    char say;
    Vector<Integer> keys = new Vector<Integer>(3, 3);
    Random randGenerator = new Random();
    boolean eventTriggered = false;
    ENTITY_PLAYER(int x, int y) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
    int getHealth() { return health; };
    void addHealth(int input) { health += input; };
    void looseHealth(int input) {
        health -= input;
        say = 'd';
        if (health <= 0) {
            System.out.println("Game: You have died. Game Over.");
            System.exit(0);
        };
    };
    void increaseDamage(int input) { damage += input; };
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
                    System.out.print("Game: Enter a comand: ");
                    String command = console_buffer.nextLine();
                    if (command.equals("health")) { say = 'h'; }
                    else if (command.equals("help")) { say = 'e'; }
                    else if (command.equals("quit")) { say = 'q'; }
                    else { System.out.println("Game: Invalid command."); };
                    break;
                default: System.out.println("Game: That is not a move.");
            };
        } catch(StringIndexOutOfBoundsException ex) {
            System.out.println("Exception: " + ex);
        };
    };
    void object_reaction(char[][] play_board, ENTITY_ENEMY_HUNTER enemy) {
        switch( adv_game.this_object(play_board, x, y) ) {
            case '#':
                System.out.println("Narrator: You cannot move here.");
                x = prev_x; y = prev_y;
                play_board[x][y] = skin;
                break;
            case 'X':
                System.out.println("Narrator: Level passed!");
                currentLevel += 1;
                break;
            case '+':
                addHealth(25);
                System.out.println("You: Wow, a health shard!");
                System.out.println("Narrator: Your health has increased to " + getHealth() + ".");
                break;
            case 'T':
                System.out.println("You: At last! A Sword!");
                System.out.print("Narrator: Your damage has increased from " + damage);
                increaseDamage(25);
                System.out.print(" to " + damage + ".");
                break;
            case 'M':
                System.out.println("You: Take that!");
                enemy.looseHealth(damage);
                if (enemy.getHealth() <= 0) {
                    enemy.die(play_board);
                };
                x = prev_x;
                y = prev_y;
                break;
        };
        play_board[x][y] = skin;
        play_board[prev_x][prev_y] = ' ';
    };
};
interface KEYGUARD {
    int[][] keyring = {
        {323, 232}, {890, 208},
        {157, 176}, {225, 755},
        {114, 495}, {611, 815},
        {212, 311}, {732, 326},
        {985, 860}, {615, 524}
    };
}
class GATEKEEPER implements KEYGUARD
{
    private int key;
    byte keyRing;
    byte player_x;
    byte player_y;
    Vector<Integer> keys;
    byte gateCoord_x;
    byte gateCoord_y;
    char gateSkin;
    boolean partner;
    Random randGenerator = new Random();
    GATEKEEPER(int x, int y, int key, int keyRing, boolean partner) {
        this.gateCoord_x = (byte) x;
        this.gateCoord_y = (byte) y;
        this.key = key;
        this.keyRing = (byte) keyRing;
        this.partner = partner;
    };
    int getKey() { return key; };
    void pickup(char[][] matrix, ENTITY_PLAYER subject) {
        player_x = subject.x;
        player_y = subject.y;
        keys = subject.keys;
        if (adv_game.this_object(matrix, player_x, player_y) == '^') {
            System.out.print("You: A key... The number ");
            if (partner == true) {
                Boolean hasKey = new Boolean(false); hasKey = false;
                if ((randGenerator.nextBoolean() == false) && (hasKey == false)) {
                    keys.addElement(keyring[keyRing][0]);
                    hasKey = true;
                } else { keys.addElement(keyring[0][1]); };
            } else {
                keys.addElement(keyring[keyRing][0]);
            };
            System.out.print(keys.lastElement() + " is on it.");
        };
    };/*
    void gateCheck(char[][] matrix, ENTITY_PLAYER subject) {
            //Pending development
    };*/
};
class MOVABLE
{
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin;
    MOVABLE(int x, int y, char skin) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.skin = skin;
    };
    String deduct_approach(ENTITY_PLAYER subject) {
        if (subject.x > subject.prev_x) {return "south";};
        if (subject.x < subject.prev_x) {return "north";};
        if (subject.y > subject.prev_y) {return "east";};
        if (subject.y < subject.prev_y) {return "west";};
        return "none";
    };
    void react(char[][] matrix, ENTITY_PLAYER aggravator) {
        if (x == aggravator.x && y == aggravator.y) {
            prev_x = x; prev_y = y;
            if (deduct_approach(aggravator) == "south") { x += 1; };
            if (deduct_approach(aggravator) == "north") { x -= 1; };
            if (deduct_approach(aggravator) == "east") { y += 1; };
            if (deduct_approach(aggravator) == "west") { y -= 1; };
            if (adv_game.this_object(matrix, x, y) == '#') {
                aggravator.x = aggravator.prev_x;
                aggravator.y = aggravator.prev_y;
                x = prev_x;
                y = prev_y;
                System.out.println("You: It seems stuck.");
            };
            if (adv_game.this_object(matrix, x, y) == '*') { aggravator.eventTriggered = true; };
        };
        matrix[x][y] = skin;
    };
};

class ENTITY_ENEMY_HUNTER
{
    private int health = 100;
    private int damage = 10;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin;
    boolean alive = true;
    ENTITY_ENEMY_HUNTER(int x, int y, char skin) {
        this.skin = skin;
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
    void looseHealth(int value) { health -= value; };
    int getHealth() { return health; };
    void die(char[][] grid) {
        grid[x][y] = ' ';
        skin = '#';
        x = 19;
        y = 19;
        prev_x = 19;
        prev_y = 19;
        alive = false;
    };
    void auto_hunt(char[][] grid, ENTITY_PLAYER target) {
    if (alive == true) {
        prev_x = x; prev_y = y;
        if (x > target.x) { x -= 1; }
        else if (x < target.x) { x += 1; }
        else if (y < target.y) { y += 1; }
        else if (y > target.y) { y -= 1; };
        if (adv_game.this_object(grid, x, y) == '#') {
            x = prev_x; y = prev_y;
        };
        if (target.x % x <= 1 && target.x / x <= 1 && target.y % y <= 1 && target.y / y <= 1) {
            target.looseHealth(damage);
        };
        grid[x][y] = skin;
        grid[prev_x][prev_y] = ' ';
    };
    };
};
class ENTITY_ENEMY_CRAWLER
{
    private final int damage = 25;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin = '|';
    char direction = 'w';
    Random rgen = new Random();
    ENTITY_ENEMY_CRAWLER(int x, int y) {
        this.x = (byte) x;
        this.y = (byte) y;
    };
    void crawl(char[][] grid, ENTITY_PLAYER aggrogate) {
        prev_x = x; prev_y = y;
        switch (direction) {
            case 'w': x -= 1; break;
            case 'a': y -= 1; break;
            case 's': x += 1; break;
            case 'd': y += 1; break;
        };
        if(adv_game.this_object(grid, x, y) == '#') {
            x = prev_x; y = prev_y;
            switch (direction) {
                case 'w': if (rgen.nextInt(40) >= 25) {direction = 'a';} else {direction = 'd';}; break;
                case 'a': if (rgen.nextInt(40) >= 25) {direction = 's';} else {direction = 'w';}; break;
                case 's': if (rgen.nextInt(40) >= 20) {direction = 'd';} else {direction = 'a';}; break;
                case 'd': if (rgen.nextInt(40) <= 20) {direction = 'w';} else {direction = 's';}; break;
            };
        };
        if (aggrogate.x % x <= 1 && aggrogate.x / x <= 1 && aggrogate.y % y <= 1 && aggrogate.y / y <= 1) {
            aggrogate.looseHealth(damage);
        };
        if (skin == '|') { skin = '-'; }
        else { skin = '|'; };
        grid[x][y] = skin;
        grid[prev_x][prev_y] = ' ';
    };
};

public class adv_game {
    static void display_board(char[][] play_board) {
        for (byte row = 0; row <= 19; row++) {
            System.out.print("\n");
            for (byte col = 0; col <= 19; col++) {
                System.out.print(play_board[row][col] + " ");
            };
        };
    };
    static void welcome() {
        Scanner console_buffer = new Scanner(System.in);
        System.out.println("********************************");
        System.out.println("*           Main Menu          *");
        System.out.println("*     Type anything to start   *");
        System.out.println("* Type \"stats\" for statistics  *");
        System.out.println("*    Type \"help\" for help      *");
        System.out.println("********************************");
        System.out.print(">> ");
        String command = console_buffer.nextLine();
        if (command.equals("stats")) {};
        if (command.equals("help")) {
            String messageBody = "In adv_game you can use the WASD keys to move and the C key to input commands.\n"
            +"Commands include; quit, help, health, restart. Quit will quit the game, Help will show a list of possible commands,\n"
            +"Health will invoke your character to say his health and Restart will restart the current level. In this game you\n"
            +"also encounter enemies that can be attacked by simply moving into them. You will find power-ups that can be\n"
            +"collected the same way and some objects can be moved by moving towards them as well.\n";
            JOptionPane.showMessageDialog(null, messageBody , "Adv_game Manual", JOptionPane.INFORMATION_MESSAGE);
        };
    };
    static void generate_struct(char[][] play_board, char[][] template, int seed, int size) {
        for (int col = 0; col <= size; col++) {
            for (int row = 0; row <= size; row++) {
                play_board[seed + col][seed + row] = template[col][row];
            };
        };
    };
    static char this_object(char[][] matrix, byte x, byte y) {
        switch( matrix[x][y] ) {
            case '#': return '#';
            case 'M': return 'M';
            case 'X': return 'X';
            case '^': return '^';
            case 'T': return 'T';
            case '+': return '+';
            case 'H': return 'H';
            case '*': return '*';
        };
        return ' ';
    };
    static void message_buffer(ENTITY_PLAYER subject) {
        switch( subject.say ) {
            case 'd':
                System.out.println("You: Aaah!");
                System.out.println("Narrator: You've been attacked, your health is now at " + subject.getHealth() + ".");
                subject.say = '0';
                break;
            case 'e':
                System.out.println("Narrator: You can enter the following: help, health, quit, restart");
                break;
            case 'h':
                System.out.println("You: I seem to be at " + subject.getHealth() + " health.");
                break;
            case 'q':
                System.out.println("Exiting."); System.exit(0);
                break;
        };
    };
    static void process_triggers(char[][] matrix, ENTITY_PLAYER player) {
        Vector<String> compilation = new Vector<String>();
        try {
            Path file_path = Paths.get("commands.dat");
            InputStream FILE_IN = Files.newInputStream(file_path);
            BufferedReader READ_HEAD = new BufferedReader(new InputStreamReader(FILE_IN));
            String readData = READ_HEAD.readLine();
            while (readData != null) {
                StringBuilder prefect = new StringBuilder();
                for (int indexer = 0; indexer < readData.length() ;indexer++ ) {
                    if (readData.charAt(indexer) != ' ') {
                        prefect.append(readData.charAt(indexer));
                    } else {
                        compilation.addElement(prefect.toString());
                        prefect.delete(0, prefect.length());
                    };
                };
                compilation.addElement(prefect.toString());
                readData = READ_HEAD.readLine();
            };
            READ_HEAD.close();
            FILE_IN.close();
        } catch (IOException ex) {
            System.out.println(ex);
        };
        if (player.eventTriggered == true)
        {
            String statement1;
            String statement2;
            String statement3;
            String statement4;
            Boolean consider = new Boolean(false);
            for (byte stat_cont = 0; stat_cont < compilation.size() ;stat_cont++ ) {
                System.out.println(compilation.elementAt(stat_cont));
                if (consider == true)
                {
                    if (compilation.elementAt(stat_cont).equals("remove")) {
                        matrix
                        [Integer.parseInt(compilation.elementAt(stat_cont + 1))]
                        [Integer.parseInt(compilation.elementAt(stat_cont + 2))]
                        = ' ';
                    };
                };
                if (compilation.elementAt(stat_cont).equals("level3") && player.currentLevel == 3)
                    {consider = true;};
                if (compilation.elementAt(stat_cont).equals("level2") && player.currentLevel == 2)
                    {consider = true;};
                if (compilation.elementAt(stat_cont).equals("level1") && player.currentLevel == 1)
                    {consider = true;};
            };
            player.eventTriggered = false;
        };
    };
    static void make_space() {
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '@', '=', '=', '@', '#', ' ', '#'},
            {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', 'X', ' ', '#', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
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
        char[][] play_board = {
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
        ENTITY_PLAYER player = new ENTITY_PLAYER(10, 10);
        Random randomGenerator = new Random();
        //KeyEvent keyCode = new KeyListener();

        JOptionPane.showMessageDialog(null, "Narrator: Use the WASD keys to move the player." + "\nAnd use C to enter a command.");
        welcome();

        //setup for level one
        if (randomGenerator.nextBoolean() == true) {
            generate_struct(play_board, boulder, 5, 4);
        } else { generate_struct(play_board, cave, 5, 4); };
        ENTITY_ENEMY_HUNTER monster = new ENTITY_ENEMY_HUNTER(4, 4, 'M');
        GATEKEEPER l1Gate1 = new GATEKEEPER(11, 13, 323, 0, true);
        GATEKEEPER l1Gate2 = new GATEKEEPER(11, 15, 232, 1, true);
        player.currentLevel = 1;
        do {
            make_space();
            l1Gate1.pickup(play_board, player);
            player.object_reaction(play_board, monster);
            message_buffer(player);
            display_board(play_board);
            player.movement_handle();
            monster.auto_hunt(play_board, player);
        } while (player.currentLevel == 1);
        //cleanup and setup for level two
        generate_struct(play_board, levelTwo, 0, 19);
        monster = null;
        ENTITY_ENEMY_CRAWLER snitch = new ENTITY_ENEMY_CRAWLER(5, 15);
        do {
            make_space();
            player.object_reaction(play_board, null);
            message_buffer(player);
            display_board(play_board);
            player.movement_handle();
            snitch.crawl(play_board, player);
        } while (player.currentLevel == 2);
        //cleanup and setup for level three
        l1Gate1 = null; l1Gate2 = null;
        snitch = null;
        generate_struct(play_board, levelThree, 0, 19);
        MOVABLE box1 = new MOVABLE(2, 5, 'H');
        do {
            make_space();
            box1.react(play_board, player);
            player.object_reaction(play_board, null);
            message_buffer(player);
            display_board(play_board);
            player.movement_handle();
            process_triggers(play_board, player);
        } while (player.currentLevel == 3);

        System.out.println("Narrator: Congradulations, you've won the game.");
    };
};
