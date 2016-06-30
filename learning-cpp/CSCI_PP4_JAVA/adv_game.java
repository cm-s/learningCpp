/*
 * adv_game (v8.4.6)
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

interface MainFrame
{
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
    static void display_board() {
        for (byte row = 0; row <= 19; row++) {
            System.out.print("\n");
            for (byte col = 0; col <= 19; col++)
            { System.out.print(main_board[row][col] + " "); };
        };
    };
    static void generate_struct(char[][] template, int seed, int size) {
        for (int col = 0; col <= size; col++) {
            for (int row = 0; row <= size; row++)
            { main_board[seed + col][seed + row] = template[col][row]; };
        };
    };
    static void cleanup() {
        try {
            Path level1 = Paths.get("level1");
            if (Files.exists(level1)) { Files.delete(level1); };
            Path level2 = Paths.get("level2");
            if (Files.exists(level2)) { Files.delete(level2); };
            Path level3 = Paths.get("level3");
            if (Files.exists(level3)) { Files.delete(level3); };
        } catch (IOException ex) { System.out.println(ex); };
    };
};

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
    Scanner console_buffer = new Scanner(System.in);
    Vector keys = new Vector();
    Random randGenerator = new Random();
    ENTITY_PLAYER(int x, int y) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
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
        for(byte idx=0;idx<keys.size();idx++)
        { FILE_OUT.println(keys.elementAt(idx).toString()); };
        FILE_OUT.close();
        } catch (IOException ex) { System.out.println(ex); };
    };
    int getHealth() { return health; };
    void addHealth(int input) { health += input; };
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
                    else if (command.equals("quit")) { MainFrame.cleanup(); MainFrame.make_space(); System.out.println("Exiting."); System.exit(0); }
                    else if (command.equals("keys")) { say = 'k'; }
                    else if (command.equals("save")) { SAVE("save_state.dat"); }
                    else if (command.equals("restart")) {
                        switch( currentLevel ) {
                            case 1: LOAD("level1"); break;
                            case 2: LOAD("level2"); break;
                            case 3: LOAD("level3"); break;
                        };
                    }
                    else { System.out.println("Game: Invalid command."); };
                    break;
                default:
                    say = 'm';
                    break;
            };
        } catch(StringIndexOutOfBoundsException ex) {
            System.out.println("Exception: " + ex);
        };
    };
    void object_reaction(ENTITY_ENEMY_HUNTER enemy) {
        switch( adv_game.this_object(x, y) ) {
            case '#':
                System.out.println("Narrator: You cannot move here.");
                x = prev_x; y = prev_y;
                main_board[x][y] = skin;
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
                    enemy.die();
                };
                x = prev_x;
                y = prev_y;
                break;
            case '/':
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
        main_board[x][y] = skin;
        main_board[prev_x][prev_y] = ' ';
        if (x % enemy.x <= 1 && x / enemy.x <= 1 && y % enemy.y <= 1 && y / enemy.y <= 1) {
            System.out.println("You: Take that!");
            enemy.looseHealth(damage);
            if (enemy.getHealth() <= 0) {
                enemy.die();
            };
            x = prev_x;
            y = prev_y;
        };
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
};
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
    GATEKEEPER(int x, int y, int key, int keyRing, boolean partner) {
        this.gateCoord_x = (byte) x;
        this.gateCoord_y = (byte) y;
        this.keyRing = (byte) keyRing;
        this.partner = partner;
        this.key = key;
    };
    int getKey() { return key; };
    void pickup(ENTITY_PLAYER subject) {
        player_x = subject.x;
        player_y = subject.y;
        if (adv_game.this_object(player_x, player_y) == '^') {
            System.out.print("You: A key... The number ");
            if (partner == true) {
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
    void gateCheck(ENTITY_PLAYER subject) {
        player_x = subject.x;
        player_y = subject.y;//might not need this
        if (player_x == gateCoord_x && player_y == gateCoord_y && unlocked == false) {
            subject.x = subject.prev_x;
            subject.y = subject.prev_y;
            System.out.println("Narrator: There's a gate.");
            System.out.println("You: it seems to be unlocked...");
            System.out.println("Narrator: Try to unlock it? y/n > ");
            char response = subject.console_buffer.nextLine().charAt(0);
            if (response == 'y')
            {
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
};
class MOVABLE implements MainFrame
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
        if (subject.x > subject.prev_x) { return "south"; };
        if (subject.x < subject.prev_x) { return "north"; };
        if (subject.y > subject.prev_y) { return "east"; };
        if (subject.y < subject.prev_y) { return "west"; };
        return "none";
    };
    void react(ENTITY_PLAYER aggravator) {
        if (x == aggravator.x && y == aggravator.y) {
            prev_x = x; prev_y = y;
            if (deduct_approach(aggravator) == "south") { x += 1; };
            if (deduct_approach(aggravator) == "north") { x -= 1; };
            if (deduct_approach(aggravator) == "east") { y += 1; };
            if (deduct_approach(aggravator) == "west") { y -= 1; };
            if (adv_game.this_object(x, y) == '#') {
                aggravator.x = aggravator.prev_x;
                aggravator.y = aggravator.prev_y;
                x = prev_x;
                y = prev_y;
                System.out.println("You: It seems stuck.");
            };
            if (adv_game.this_object(x, y) == '*') { aggravator.eventTriggered = true; };
        };
        main_board[x][y] = skin;
    };
};

class ENTITY_ENEMY_HUNTER implements MainFrame
{
    private int health = 100;
    private int damage = 10;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin;
    boolean alive = true;
    char direction;
    boolean override;
    boolean clear = true;
    char[][] environment = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    int[][][] underlay = {
        { {0,0},{0,0},{0,0} },
        { {0,0},{0,0},{0,0} },
        { {0,0},{0,0},{0,0} }
    };
    ENTITY_ENEMY_HUNTER(int x, int y, char skin) {
        this.skin = skin;
        this.x = (byte) x;
        this.y = (byte) y;
        this.prev_x = (byte) x;
        this.prev_y = (byte) y;
    };
    void looseHealth(int value) { health -= value; };
    int getHealth() { return health; };
    void die() {
        main_board[x][y] = ' ';
        skin = '#';
        x = 19;
        y = 19;
        prev_x = 19;
        prev_y = 19;
        alive = false;
    };
    void scan(char[][] template, int x, int y) {
        for (int col = 0; col <= 2; col++) {
            for (int row = 0; row <= 2; row++)
            { underlay[row][col][0] = (col + x - 1);
              underlay[row][col][1] = (row + y - 1);
              template[col][row] = main_board[col + x -1][row + y -1]; };
        };
    };
    char assume() {
        if (environment[2][1] != '#') { return 's'; }
        else if (environment[1][0] != '#') { return 'd'; }
        else if (environment[0][1] != '#') { return 'w'; }
        else if (environment[1][2] != '#') { return 'a'; };
        return '0';
    };
    void auto_hunt(ENTITY_PLAYER target) {
    if (alive == true) {
        prev_x = x; prev_y = y;
        switch ( direction ) {
            case 'w': x -= 1; break;
            case 's': x += 1; break;
            case 'd': y += 1; break;
            case 'a': y -= 1; break;
        };
        if (!override) {
            if (x > target.x) { direction = 'w'; }
            else if (x < target.x) { direction = 's'; }
            else if (y < target.y) { direction = 'd'; }
            else if (y > target.y) { direction = 'a'; };
        } else {
            scan(environment, x, y);
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++)
                { if (environment[col][row] == '#') { clear = false; }; };
            };
            if (clear) { override = false; };
        };
        if (adv_game.this_object(x, y) == '#') {
            x = prev_x; y = prev_y;
            scan(environment, x, y);
            direction = assume();
            override = true;
        };
        if (target.x % x <= 1 && target.x / x == 1 && target.y % y <= 1 && target.y / y == 1) {
            target.looseHealth(damage);
        };
        main_board[x][y] = skin;
        main_board[prev_x][prev_y] = ' ';
    };
    };
};
class ENTITY_ENEMY_CRAWLER implements MainFrame
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
    void crawl(ENTITY_PLAYER aggrogate) {
        prev_x = x; prev_y = y;
        switch (direction) {
            case 'w': x -= 1; break;
            case 'a': y -= 1; break;
            case 's': x += 1; break;
            case 'd': y += 1; break;
        };
        if(adv_game.this_object(x, y) == '#' || adv_game.this_object(x, y) == 'X') {
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
        main_board[x][y] = skin;
        main_board[prev_x][prev_y] = ' ';
    };
};
class FileCommandInterpreter implements MainFrame
{
    String lastRun = new String();
    Integer times = new Integer(0);
    void main_(ENTITY_PLAYER player)
    {
    if (player.eventTriggered == true)
    {
        Vector<String> compilation = new Vector<String>();
        String last = new String();
        Integer indexer = new Integer(0);
        adv_game.processFile("commands.dat", compilation);
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

public class adv_game implements MainFrame {
    static void processFile(String file_name, Vector<String> compilation) {
        try {
            Path file_path = Paths.get(file_name);
            InputStream FILE_IN = Files.newInputStream(file_path);
            BufferedReader READ_HEAD = new BufferedReader(new InputStreamReader(FILE_IN));
            String readData = READ_HEAD.readLine();
            Integer cnt = new Integer(0);
            while (readData != null) {
                cnt++;
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
                //System.out.println(compilation.elementAt(cnt));
            };
            READ_HEAD.close();
            FILE_IN.close();
        } catch (IOException ex) {
            System.out.println(ex);
        };
    };
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
        };
        return ' ';
    };
    static void message_postProcessor(ENTITY_PLAYER subject) {
        switch( subject.say ) {
            case 'd':
                System.out.println("You: Aaah!");
                System.out.println("Narrator: You've been attacked, your health is now at " + subject.getHealth() + ".");
                subject.say = '0';
                break;
            case 'e':
                System.out.println("Narrator: You can enter the following: help, health, quit, restart");
                subject.say = '0';
                break;
            case 'h':
                System.out.println("You: I seem to be at " + subject.getHealth() + " health.");
                subject.say = '0';
                break;
            case 'k':
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
                System.out.println("Game: That is not a move.");
                subject.say = '0';
                break;
        };
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
        player.currentLevel = 1;
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
        MainFrame.cleanup();

        System.out.println("Narrator: Congradulations, you've won the game.");
    };
};
