 #
 # adv_game (v5.3)
 # Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 # in order to get to the next level and ultimately win the game.
 #
 # CMS
 # Date added: 6/3/16
from random import randint
import time
def make_space():
    print "\n","\n","\n","\n","\n","\n","\n","\n","\n","\n","\n"
class item:
    keyring = (
    [323, 232], [890, 208],
    [157, 176], [225, 755],
    [114, 495], [611, 815],
    [212, 311], [732, 326],
    [985, 860], [615, 524]
    )
    def __init__(self, item_type, meta, submeta):
        self.item_type = item_type
        self.meta = meta
        self.submeta = submeta
        if self.item_type == "key":
            if self.meta == 1:
                self.key = self.keyring[submeta][0]
            if self.meta == 2:
                self.key = self.keyring[submeta][1]
        if item_type == "sword":
            self.damage = submeta
            self.durability = self.submeta
    pass
class ENTITY_PLAYER:
    vanquished = "none"
    skin = "R"
    x = 10
    y = 10
    prev_coord_x = 10
    prev_coord_y = 10
    health = 500
    damage = 20
    direction = 'A'
    keys_owned = 0
    items = []
    levelEnd = False;
    noticed = "none"
    def damage_total(self, powerup):
        return self.damage + powerup.damage
    def attack(self, enemy, level, tick):
        if level == 1: enemy.health -= self.damage
        if level > 1:
            if 'basic_sword' in self.items:
                enemy.health -= self.damage_total(basic_sword)
            else: enemy.health -= self.damage
        print "Take that!"
        self.x = self.prev_coord_x
        self.y = self.prev_coord_y
        if enemy.health <= 0:
            self.vanquished = enemy.name
            del enemy
            tick += 1
            print "You've killed an enemy!"
    def command(self):
        command = raw_input("Enter a command: ")
        if command == "keys":
            if self.keys_owned == 1:
                print "Looks like I have key", key1.key, "."
            elif self.keys_owned == 2:
                print "Looks liek I have keys", key1.key, "and", key2.key, "."
            else:
                print "You don't have any keys."
        if command == "damage":
            if "starter sword" in self.items:
                print "...This sword should increase my damage."
            elif "sword" in self.items:
                print "...This must increase my damage."
            else: print "...I don't know how great I'll stand up to my enemies."
        if command == "health":
            print "My health seems to be", self.health, "."
        time.sleep(2)
    def manual_move(self):
        self.prev_coord_x = self.x
        self.prev_coord_y = self.y
        if self.direction == "W": self.x -= 1
        if self.direction == "A": self.y -= 1
        if self.direction == "S": self.x += 1
        if self.direction == "D": self.y += 1
        if self.direction == "C": self.command()
        current_grid[self.prev_coord_x][self.prev_coord_y] = ' '
    def pickup(self):
        if this_object(character) == '#':
            self.x = self.prev_coord_x
            self.y = self.prev_coord_y
            current_grid[self.x][self.y] = self.skin
            print "You cannot move here."
        if this_object(character) == 'X':
            print "Level complete!"
            self.levelEnd = True
            self.x = 3
            self.y = 3
            self.prev_coord_x = 3
            self.prev_coord_y = 3
        if this_object(character) == '^':
            print "You've picked up a key."
            print "Debug Message: ", randint(1,2)
            if ((randint(1, 2) == 1) & ('key1' in self.items != True)) | ('key2' in self.items):
                key1 = item("key", 1, 0)
                length = len(self.items)
                self.items.insert(length + 1, 'key1')
                print "The number", key1.key, "is on it."
            elif ('key2' in self.items != True):
                key2 = item("key", 2, 0)
                length = len(self.items)
                self.items.insert(length + 1, 'key2')
                print "The number", key2.key, "is on it."
            length = len(self.items) #this really isn't doing anything
            print "Debug Message: ", length
        if this_object(character) == 'M':
            self.attack(basic_monster, gameLevel, tick)
            self.x = self.prev_coord_x
            self.y = self.prev_coord_y
            current_grid[self.x][self.y] = self.skin
        if this_object(character) == '+':
            self.health += 10
            print "Wow, a health shard..."
            print "You now have", self.health, "health."
        if this_object(character) == 'T':
            basic_sword = item("sword", 25, 40)
            self.items.insert(len(self.items) + 1,"starter sword")
            print "Looks like I'll need this if there's any more of those monsters ahead."
            print "You now have a sowrd, increasing your damage to", self.damage, "."
        if this_object(character) == '@':
            self.x = self.prev_coord_x
            self.y = self.prev_coord_y
            print "You've ran into a gate."
            print "Should I unlock it..."
            ans = raw_input("Unlock the gate? Enter (y/n): ")
            if ans == 'y':
                print "Unlocking..."
                time.sleep(2.1)
                #key determination here
                unlock(self)
        if this_object(character) == 'H':
            if (character.x & character.y) == (box1.x & box1.y):
                if box1.deduct_approach() == 'west': box1.y += 1
                if box1.deduct_approach() == 'east': box1.y -= 1
                if box1.deduct_approach() == 'south': box1.x += 1
                if box1.deduct_approach() == 'north': box1.x -= 1
                box1.prev_coord_x = box1.x
                box1.prev_coord_y = box1.y
                if this_object(box1) == '#':
                    box1.x = box1.prev_coord_x
                    box1.y = box1.prev_coord_y
                    self.x = self.prev_coord_x
                    self.y = self.prev_coord_y
                    print "It seems stuck."
            if (character.x & character.y) == (box2.x & box2.y):
                if box2.deduct_approach() == 'west': box2.y += 1
                if box2.deduct_approach() == 'east': box2.y -= 1
                if box2.deduct_approach() == 'south': box2.x += 1
                if box2.deduct_approach() == 'north': box2.x -= 1
                box2.prev_coord_x = box2.x
                box2.prev_coord_y = box2.y
                if this_object(box2) == '#':
                    box2.x = box2.prev_coord_x
                    box2.y = box2.prev_coord_y
                    self.x = self.prev_coord_x
                    self.y = self.prev_coord_y
                    print "It seems stuck."
class ENTITY_ENEMY:
    def __del__(self):
        print "You've killed the monster!"
    name = "none"
    skin = 'M'
    health = 50
    damage = 10
    x = 5
    y = 5
    prev_coord_x = 5
    prev_coord_y = 5
    def attack(self):
        character.health -= self.damage
        print "You've been attacked!"
        print "You now have", character.health, "health left."
    def auto_hunt(self):
        self.prev_coord_x = self.x
        self.prev_coord_y = self.y
        if (self.x % character.x <= 1 & self.x / character.x <= 1) & (self.y % character.y <= 1 & self.y / character.y <= 1):
            self.attack()
        else:
            if self.x < character.x: self.x += 1
            elif self.x > character.x: self.x -= 1
            elif self.y < character.y: self.y += 1
            elif self.y > character.y: self.y -= 1
            current_grid[self.prev_coord_x][self.prev_coord_y] = ' '
        if this_object(basic_monster) == '#':
            self.x = self.prev_coord_x
            self.y = self.prev_coord_y
class GATEKEEPER:
    skin = '@'
    x = 0
    y = 0
    signature = 000
    def unlock(self, client):
        pass
class BOX:
    skin = 'H'
    x = 0
    y = 0
    prev_coord_x = 0
    prev_coord_y = 0
    def deduct_approach(character): #will not take arguments correctly
        if character.y > character.prev_coord_y: return 'east'
        if character.y < character.prev_coord_y: return 'west'
        if character.x > character.prev_coord_x: return 'south'
        if character.x < character.prev_coord_x: return 'north'
def detect(matrix, target):
    coords = [[0], [0]]
    for col in range(20):
        for row in range(20):
            if current_grid[col][row] == target:
                coords[0] = col
                coords[1] = row
                return coords
def print_grid(matrix):
    matrix[character.x][character.y] = character.skin
    if character.noticed == "enemy":
        matrix[basic_monster.x][basic_monster.y] = basic_monster.skin
    for col in range(20):
        for row in range(20):
            print matrix[col][row],
        print "\n",
def generate(matrix, template, seed, size):
    for col in range(size):
        for row in range(size):
            matrix[row + seed][col + seed] = template[row][col]
def this_object(entity):
    if current_grid[entity.x][entity.y] == '#': return '#'
    if current_grid[entity.x][entity.y] == 'X': return 'X'
    if current_grid[entity.x][entity.y] == '^': return '^'
    if current_grid[entity.x][entity.y] == 'M': return 'M'
    if current_grid[entity.x][entity.y] == '+': return '+'
    if current_grid[entity.x][entity.y] == 'H': return 'H'
    if current_grid[entity.x][entity.y] == '@': return '@'
    if current_grid[entity.x][entity.y] == 'T': return 'T'
def decay(tick, matrix):
    if (tick == 5) & (character.vanquished[0] == 'b') & (character.vanquished[1] == 'm'):
        coords = detect(matrix, 'M')
        matrix[coords[0]][coords[1]] = 'H'

        #BEGIN MAIN SCOPE

#grid imports
levelTwo = (
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '@', '=', '=', '@', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', ' ', ' ', 'X', ' ', ' ', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', '#'],
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
)
levelThree = (                   #fist key here
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', '#', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '/', 'H', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', '#'],
    ['#', ' ', ' ', ' ', '#', '#', ' ', ' ', 'H', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
)
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
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']
)
boulder = (
    [' ','#','#','#',' '],
    ['#','#','#','#','#'],
    ['#','#','^','W','W'],
    ['#','#','^','#','#'],
    [' ','#','#','#',' ']
)
#essential variables&objs
character = ENTITY_PLAYER()
basic_monster = ENTITY_ENEMY()
basic_monster.name = "bm1"
tick = 0
gameLevel = 1
#setup level one
generate(current_grid, boulder, randint(4, 8), 5)
character.noticed = "enemy"
while character.levelEnd != True:
    make_space()
    character.pickup()
    print_grid(current_grid)
    character.direction = raw_input("Make a move: ").upper()
    character.manual_move()
    if character.vanquished != "bm1":
        basic_monster.auto_hunt()
    else:
        tick += 1
    decay(tick, current_grid);
#cleanup
del basic_monster
tick = 0
character.noticed = "none"
#setup level two
character.levelEnd = False
generate(current_grid, levelTwo, 0, 20)
gameLevel = 2
lv2_gatekeeper_1 = GATEKEEPER()
lv2_gatekeeper_1.x = 11
lv2_gatekeeper_1.y = 16
lv2_gatekeeper_2 = GATEKEEPER()
lv2_gatekeeper_2.x = 11
lv2_gatekeeper_2.y = 13
while character.levelEnd != True:
    make_space()
    character.pickup()
    print_grid(current_grid);
    character.direction = raw_input("Make a move: ").upper()
    character.manual_move()
    decay(tick, current_grid)
#cleanup
del lv2_gatekeeper_1
del lv2_gatekeeper_2
#setup level three
character.levelEnd = False
generate(current_grid, levelThree, 0, 20)
gameLevel = 3
character.x = 18
character.y = 2
box1 = BOX()
box2 = BOX()
box1.x = 5
box1.y = 2
box2.x = 9
box2.y = 3
current_grid[box1.x][box1.y] = box1.skin
current_grid[box2.x][box2.y] = box2.skin
while character.levelEnd != True:
    make_space()
    character.pickup()
    print_grid(current_grid)
    character.direction = raw_input("Make a move: ").upper()
    character.manual_move()
    decay(tick, current_grid)

print "Congradulations, you won the game. :)"
