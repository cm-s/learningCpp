$main_grid = [
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
  ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]

def display
  col = 0
  row = 0
  loop do #Wow, so if the loopy loop could loop a loop, how many loops would the loopy loop loop?
    loop do
      print $main_grid[col][row]
      print ' '
      row += 1
      if row >= 20
        row = 0
        break;
      end
    end
    puts ' '
    col += 1
    break if col >= 20
  end
end

def collision_report(object)
  return $main_grid[object.pos_x][object.pos_y]
end

class CHARACTER
  @health = 100
  @damage = 10
  direction = ''
  skin = '%'
  @current_level = 0
  def initialize(preinit_x, preinit_y)
    @x = preinit_x
    @y = preinit_y
    @prev_X = @x
    @prev_y = @y
  end
  def setLevel=(input)
    @current_level = input
  end
  def getLevel
    return @current_level
  end
  def pos_x
    return @x
  end
  def pos_y
    return @y
  end
  def obj_skin
    return @skin
  end
  def movement_handle
    direction = gets.chomp
    case direction
    when 'w'
      @x -= 1
    when 'a'
      @y -= 1
    when 's'
      @x += 1
    when 'd'
      @y += 1
    else
      puts "Unrecognized command"
    end
  end
  def position_assigner
    case collision_report(self)
    when '#'
      puts "You cannot move here"
      @x = @prev_X
      @y = @prev_y
    when 'X'
      puts "You've passed the level"
    else
      $main_grid[pos_x][pos_y] = obj_skin
      $main_grid[@prev_X][@prev_y] = ' '
    end
  end
end

puts "Use the WASD keys to move."
player = CHARACTER.new(10, 10)
player.setLevel = 1
while player.getLevel == 1
  player.movement_handle
  player.position_assigner
  display
  #and ruby doesn't handle multidimensoinal arrays well.. or at all technically
end
