/*
 * adv_game (v2.5.9)
 * Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 * in order to get to the next level and ultimately win the game.
 *
 * CMS
 * Date added: 6/3/16
 */
import java.io.*;
import java.util.Scanner;
import java.awt.event.*;
import javax.swing.JOptionPane;

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
    public ENTITY_PLAYER(int x, int y) {
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
                    System.out.println("Debug: " + command); //control structures beyond this point don't seem to function as desired
                    if (command == "health") { System.out.println("You: I seem to be at " + getHealth() + " health."); }
                    else if (command == "help") {
                        System.out.println("Narrator: You can enter the following: help, health");
                    } else { System.out.println("Game: Invalid command."); };
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
                case 'w': direction = 'a'; break;
                case 'a': direction = 's'; break;
                case 's': direction = 'd'; break;
                case 'd': direction = 'w'; break;
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
        };
    };
    static void make_space() {
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    };
    static int flip() { return (int) (Math.random() + 2); };

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
        //KeyEvent keyCode = new KeyListener();

        JOptionPane.showMessageDialog(null, "Narrator: Use the WASD keys to move the player." + "\nAnd use C to enter a command.");

        //setup for level one
        if (flip() == 1) {
            generate_struct(play_board, boulder, 5, 4);
        } else { generate_struct(play_board, cave, 5, 4); };
        ENTITY_ENEMY_HUNTER monster = new ENTITY_ENEMY_HUNTER(4, 4, 'M');
        player.currentLevel = 1;
        do {
            make_space();
            player.object_reaction(play_board, monster);
            display_board(play_board);
            player.movement_handle();
            monster.auto_hunt(play_board, player);
        } while (player.currentLevel == 1);
        //cleanup and setup for level two
        generate_struct(play_board, levelTwo, 0, 19);
        monster = null;
        ENTITY_ENEMY_CRAWLER snitch = new ENTITY_ENEMY_CRAWLER(4, 2);
        do {
            make_space();
            player.object_reaction(play_board, null);
            message_buffer(player);
            display_board(play_board);
            player.movement_handle();
            snitch.crawl(play_board, player);
        } while (player.currentLevel == 2);

        System.out.println("Narrator: Congradulations, you've won the game.");
    };
};
