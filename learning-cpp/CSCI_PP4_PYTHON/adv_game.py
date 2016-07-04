 #
 # adv_game (alpha)
 # Adventure game in which a player traverses a retro-style board or grid
 # solving puzzles and avoiding enemies in order to get to the next level.
 #
 # CMS
 # Data created:7/2/16
from random import randint
import time #for time.sleep(ms)
import sys
import os.path

class MainFrame:
    current_grid = (
        ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
        ['#', 'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'], )
    levelTwo = (
        ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
        ['#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
        ['#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', ' ', ' ', ' ', '#'],
        [' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'],
        [' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', '#', '#', '#', ' '],
        [' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' '],
        [' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', 'X', ' ', '#', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '], )
    levelThree = (
        ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#'],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', '#', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', '/', 'H', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'X', '#'],
        ['#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '*', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'],
        ['#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
        ['#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
        ['#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
        ['#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'],
        ['#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
        ['#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' '],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '],
        ['#', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' '],
        ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' '],
        ['#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '], )
    def createSpace(self):
        print "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
    def display(self):
        for col in range(20):
            for row in range(20):
                print self.current_grid[col][row],
            print "\n",
    def generate(self, template, seed, size):
        for col in range(size):
            for row in range(size):
                self.current_grid[col + seed][row + seed] = template[col][row]
    def collisionReporter(self, x, y):
        if self.current_grid[x][y] == '#': return '#'
        if self.current_grid[x][y] == 'X': return 'X'
        if self.current_grid[x][y] == 'M': return 'M'
        if self.current_grid[x][y] == '@': return '@'
        if self.current_grid[x][y] == '^': return '^'
        if self.current_grid[x][y] == '*': return '*'
        if self.current_grid[x][y] == '/': return '/'
        if self.current_grid[x][y] == 'T': return 'T'
        if self.current_grid[x][y] == 'H': return 'H'
    def cleanup(self, fileName):
        if os.path.isfile(fileName): os.remove(fileName)
mainframe = MainFrame()
class entityPlayer:
    health = 400;
    damage = 20;
    x = 10
    y = 10
    prev_x = 10
    prev_y = 10
    skin = '&'
    playerInput = '0'
    currentLevel = 1
    event = "null"
    def SAVE(self, fileName):
        # Save State Formatting Standard
        # Line #      Variable
        #=================================================
        # 1           health
        # 2           damage
        # 3           x coordinate
        # 4           y coordinate
        # 5           previous x coordinate
        # 6           previous y coordinate
        # 7           current Level
        # 8           firstTurn (var, name implies)
        # 9-EOF       however many keys owned by the player
        #
        FILE_OUT = open(fileName, "w")
        FILE_OUT.write(str(self.health) + "\n")
        FILE_OUT.write(str(self.damage) + "\n")
        FILE_OUT.write(str(self.x) + "\n")
        FILE_OUT.write(str(self.y) + "\n")
        FILE_OUT.write(str(self.prev_x) + "\n")
        FILE_OUT.write(str(self.prev_y) + "\n")
        FILE_OUT.write(str(self.currentLevel) + "\n")
        FILE_OUT.write("N/A\n")
        FILE_OUT.write("N/A\n")
        FILE_OUT.close()
    def LOAD(self, fileName):
        FILE_IN = open(fileName, "r")
        self.health = int(FILE_IN.read(3))
        self.damage = int(FILE_IN.read(3))
        self.x = int(FILE_IN.read(3))
        self.y = int(FILE_IN.read(3))
        self.prev_x = int(FILE_IN.read(3))
        self.prev_y = int(FILE_IN.read(3))
        self.currentLevel = int(FILE_IN.read(2))
        FILE_IN.close()
    def movementHandle(self):
        self.prev_x = self.x
        self.prev_y = self.y
        self.playerInput = raw_input("Game: Make a move: ").upper()
        if self.playerInput == 'W': self.x -= 1
        if self.playerInput == 'A': self.y -= 1
        if self.playerInput == 'S': self.x += 1
        if self.playerInput == 'D': self.y += 1
        if self.playerInput == 'C':
            command = raw_input("Game: Enter a command: ")
            if command == "quit":
                print "Game: Exiting game..."
                if player.currentLevel == 1: MainFrame.cleanup("level1")
                if player.currentLevel == 2: MainFrame.cleanup("level2")
                if player.currentLevel == 3: MainFrame.cleanup("level3")
                sys.exit()
            elif command == "restart":
                self.event = "restart"
            else:
                self.event = "invalid"
    def collisionOperator(self):
        if MainFrame.collisionReporter(mainframe, self.x, self.y) == '#':
            self.x = self.prev_x
            self.y = self.prev_y
            self.event = "wall"
        if MainFrame.collisionReporter(mainframe, self.x, self.y) == 'X':
            self.currentLevel += 1
            print "Narrator: Level complete!"
            time.sleep(0.5)
        if MainFrame.collisionReporter(mainframe, self.x, self.y) == '*':
            self.event = "hcharm"
            self.health += 20
        if MainFrame.collisionReporter(mainframe, self.x, self.y) == 'T':
            self.event = "llsword"
            self.damage += 25
        MainFrame.current_grid[self.x][self.y] = self.skin
        MainFrame.current_grid[self.prev_x][self.prev_y] = ' '
class entityEnemyHunter:
    health = 60
    damage = 20
    x = 0
    y = 0
    prev_x = 0
    prev_y = 0
    skin = '0'
    direction = '0'
    alive = True
    override = False
    environment = (
    [" ", " ", " "],
    [" ", " ", " "],
    [" ", " ", " "] )
    def __init__(self, x, y, skin, damage, health):
        self.skin = skin
        self.x = x
        self.y = y
        self.health = health
        self.damage = damage
        self.prev_x = self.x
        self.prev_y = self.y
    def looseHealth(self, value):
        if self.health <= 0:
            self.alive = False
            self.skin = "#"
            self.x = 0
            self.y = 0
            self.prev_x = 0
            self.prev_y = 0
        else: self.health -= value
    def autoAnimate(self, target):
        if self.alive == True:
            self.prev_x = self.x
            self.prev_y = self.y
            if self.direction == 'w': self.x -= 1
            if self.direction == 's': self.x += 1
            if self.direction == 'd': self.y += 1
            if self.direction == 'a': self.y -= 1
            if self.override != False:
                if x > target.x: direction = 'w'
                if x < target.x: direction = 's'
                if y < target.y: direction = 'd'
                if y > target.y: direction = 'a'
            if MainFrame.collisionReporter(mainframe, self.x, self.y) == '#':
                for col in range(3):
                    for row in range(3):
                        self.environment[col][row] = MainFrame.current_grid[col + player.x -1][row + player.y -1]
                #scanned environment
                print self.environment[1][1]
                self.x = self.prev_y
                self.y = self.prev_y
            MainFrame.current_grid[self.x][self.y] = self.skin
            MainFrame.current_grid[self.prev_x][self.prev_y] = ' '
def actionPostProcess(subject):
    if subject.event == "wall":
        print "Game: You cannot move here."
        subject.event = "null"
    if subject.event == "hcharm":
        print "Narrator: You've found a health charm."
        print "Narrator: Your health is now at", subject.health, '.'
        subject.event = "null"
    if subject.event == "llsword":
        print "You: Wow, this should help me next time I see one of those monsters!"
        print "Narrator: You've obtained a wooden sword, your attack damaged has increased to", subject.damage, '.'
        subject.event = "null"
    if subject.event == "restart":
        print "Game: Restarting..."
        time.sleep(0.3)
        if subject.currentLevel == 1: entityPlayer.LOAD(subject, "level1")
        if subject.currentLevel == 2: entityPlayer.LOAD(subject, "level2")
        if subject.currentLevel == 3: entityPlayer.LOAD(subject, "level3")
        subject.event = "null"
    if subject.event == "invalid":
        print "Game: Unrecongnized command"
        subject.event = "null"
player = entityPlayer()
entityPlayer.SAVE(player, "level1")
hunter = entityEnemyHunter(3, 3, 'M', 20, 80)
while player.currentLevel == 1:
    MainFrame.createSpace(mainframe)
    actionPostProcess(player)
    MainFrame.display(mainframe)
    entityPlayer.movementHandle(player)
    entityEnemyHunter.autoAnimate(hunter, player)
    entityPlayer.collisionOperator(player)
MainFrame.cleanup(mainframe, "level1")
MainFrame.generate(mainframe, MainFrame.levelTwo, 0, 19)
entityPlayer.SAVE(player, "level2")
while player.currentLevel == 2:
    MainFrame.createSpace(mainframe)
    actionPostProcess(player)
    MainFrame.display(mainframe)
    entityPlayer.movementHandle(player)
    entityPlayer.collisionOperator(player)
MainFrame.cleanup(self, "level2")
print "Narrator: You've won the game!"
