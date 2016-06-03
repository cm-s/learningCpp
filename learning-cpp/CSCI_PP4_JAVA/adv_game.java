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
//Really don't known what I'm doing
/* class directionalEngine extends JFrame
    implements KeyListener
{
    @Override
    public void KeyTyped(KeyEvent e) {
        char c = e.getKeyChar();
    };
    @Override
    public void KeyPressed(KeyEvent e) {};
    @Override
    public void KeyReleased(KeyEvent e) {};
}*/
class ENTITY_PLAYER
{
    byte prev_coord_x;
    byte prev_coord_y;
    byte x = 9;
    byte y = 9;
    char skin = '$';
    boolean firstTurn = true;
    public ENTITY_PLAYER() {};
    void movement_handle(char[][] play_board, String direction, boolean levelComplete) {
        prev_coord_x = x; prev_coord_y = y;
        switch(Character.toUpperCase(direction.charAt(0))) {
            case 'W': x -= 1; break;
            case 'A': y -= 1; break;
            case 'S': x += 1; break;
            case 'D': y += 1; break;
            default: System.out.println("\nThat is not a move.");
        };
        justify_move(play_board, levelComplete);
        play_board[prev_coord_x][prev_coord_y] = ' ';
    };
    void justify_move(char[][] play_board, boolean levelComplete) {
        switch( fxnCtrl.this_object(play_board, x, y) ) {
            case '#':
                System.out.println("\nYou cannot move here.");
                x = prev_coord_x; y = prev_coord_y;
                play_board[x][y] = skin;
                break;
            case 'X':
                System.out.println("\nLevel Complete!");
                levelComplete = true;
                break;
        };
    };
};

class fxnCtrl
{
    static void display_board(char[][] play_board) {
        for (byte row = 0; row <= 19; row++) {
            System.out.print("\n");
            for (byte col = 0; col <= 19; col++) {
                System.out.print(play_board[row][col] + " ");
            };
        };
        System.out.print("\n");
    };
    static void generate_struct(char[][] play_board, char[][] template) {
        int rnum = 4 + (int)(Math.random() * 13);
        for (byte col = 0; col <= 19; col++) {
            for (byte row = 0; row <= 19; row++) {
                play_board[rnum + col][rnum + row] = template[col][row];
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
    static void make_space() {
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    };
    static String obj_approach(char[][] matrix) {
        System.out.println("Testing");
        return "null";
    };
};

public class adv_game {
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
        //essensial variables
        ENTITY_PLAYER character = new ENTITY_PLAYER();
        boolean levelComplete = false;
        String direction;
        //KeyEvent keyCode = new KeyListener();
        int randomFiftyPercent = 1 + (int) (Math.random() * 2);
        Scanner console_buffer = new Scanner(System.in);

        JOptionPane.showMessageDialog(null, "\nUse the WASD keys to move the player.");

        //setup for level one
        //fxnCtrl.generate_struct(play_board, boulder);
        do {
            fxnCtrl.make_space();
            fxnCtrl.display_board(play_board);
            direction = console_buffer.nextLine(); //keyCode.getKeyChar();
            character.movement_handle(play_board, direction, levelComplete);
            play_board[character.x][character.y] = character.skin;
            character.firstTurn = false;
        } while (levelComplete != true);
    };
};
