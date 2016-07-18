/*
 * adv_game (v1.0)
 * Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 * in order to get to the next level and ultimately win the game.
 *
 * CMS
 * Date added: 6/3/16
 */
import java.util.Scanner;
import java.awt.event.*;
import javax.swing.JOptionPane;
import java.util.Random;

interface MainGrid
{
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

    static void display_board(ENTITY_PLAYER applicant) { //My goal is to pass the container.
        main_board[applicant.x][applicant.y] = applicant.skin;
        for (byte row = 0; row <= 19; row++) {
            System.out.print("\n");
            for (byte col = 0; col <= 19; col++) {
                System.out.print(main_board[row][col] + " ");
            };
        };
        System.out.print("\n");
    };
    static void make_space() {
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    };
};

class ENTITY_PLAYER implements MainGrid
{
    private int health = 400;
    byte prev_coord_x;
    byte prev_coord_y;
    byte x = 9;
    byte y = 9;
    char skin = '$';
    boolean firstTurn = true;
    public ENTITY_PLAYER() {};
    void looseHealth(int amt) { health -= amt; };
    int getHealth() { return health; };
    void movement_handle(String direction, boolean levelComplete) {
        prev_coord_x = x; prev_coord_y = y;
        try {
            switch(Character.toUpperCase(direction.charAt(0))) {
                case 'W': x -= 1; break;
                case 'A': y -= 1; break;
                case 'S': x += 1; break;
                case 'D': y += 1; break;
                default: System.out.println("\nThat is not a move.");
            };
        } catch (StringIndexOutOfBoundsException ex) {  };
        main_board[prev_coord_x][prev_coord_y] = ' ';
    };
    void justify_move(boolean levelComplete) {
        switch( adv_game.this_object(main_board, x, y) ) {
            case '#':
                System.out.println("\nYou cannot move here.");
                x = prev_coord_x; y = prev_coord_y;
                main_board[x][y] = skin;
                break;
            case 'X':
                System.out.println("\nLevel Complete!");
                levelComplete = true;
                break;
        };
    };
};
class ENTITY_ENEMY_CRAWLER extends Thread implements MainGrid
{
    private final int damage = 25;
    byte x;
    byte y;
    byte prev_x;
    byte prev_y;
    char skin = '|';
    char direction = 'w';
    Random rgen = new Random();
    ENTITY_PLAYER aggrogate;
    ENTITY_ENEMY_CRAWLER(int x, int y, ENTITY_PLAYER character) {
        this.x = (byte) x;
        this.y = (byte) y;
        this.aggrogate = character;
    };
    public void run() {
        while (aggrogate.getHealth() > 0) {
            MainGrid.make_space();
            MainGrid.display_board(aggrogate);
            prev_x = x; prev_y = y;
            switch (direction) {
                case 'w': x -= 1; break;
                case 'a': y -= 1; break;
                case 's': x += 1; break;
                case 'd': y += 1; break;
            };
            if(adv_game.this_object(main_board, x, y) == '#' || adv_game.this_object(main_board, x, y) == 'X') {
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
            try { Thread.sleep(80); } catch (InterruptedException ex) {  };
        };
    };
};

public class adv_game implements MainGrid {
    static void generate_struct(char[][] main_board, char[][] template, byte seed, byte size) {
        for (byte col = 0; col <= size; col++) {
            for (byte row = 0; row <= size; row++) {
                main_board[seed + col][seed + row] = template[col][row];
            };
        };
    };
    static char this_object(char[][] matrix, byte x, byte y) {
        switch( matrix[x][y] ) {
            case '#': return '#';
            case 'M': return 'M';
            case 'X': return 'X';
        };
        return ' ';
    };

    public static void main(String[] args)
    {
        //board/grid inports
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
            {'#','#','^','W','W'},
            {'#','#','^','#','#'},
            {' ','#','#','#',' '},
        };
        final char[][] levelTwo = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '@', '=', '=', '@', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', 'X', ' ', ' ', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        };
        //essensial variables
        ENTITY_PLAYER character = new ENTITY_PLAYER();
        boolean levelComplete = false;
        String direction;
        int randomFiftyPercent = 1 + (int) (Math.random() * 2);
        Scanner console_buffer = new Scanner(System.in);

        JOptionPane.showMessageDialog(null, "\nUse the WASD keys to move the player.");

        (new ENTITY_ENEMY_CRAWLER(3, 3, character)).start();
        //setup for level one
        generate_struct(main_board, boulder, (byte) 3, (byte) 4);
        do {
            MainGrid.make_space();
            character.justify_move(levelComplete);
            MainGrid.display_board(character);
            direction = console_buffer.nextLine(); //keyCode.getKeyChar();
            character.movement_handle(direction, levelComplete);
            character.firstTurn = false;
        } while (levelComplete != true);
    };
};
