import math
import sys

# Define size
WIDTH = 1920
HEIGHT = 1080

FDA_origin = 50
FDA_carryOn = False
FDA_speed = 10

SHOW_SCORE = False
ANTS_show_on_start = False
ANTS_speed = 15

# Define
UINT_MAX = 4294967295
ELEM_SIZE = 3

# Define colors
BLACK = ( 0, 0, 0 )
WHITE = ( 255, 255, 255 )
GREEN = ( 140, 255, 60 )
RED = (255, 75, 150 )
LIGHT_GRAY = ( 240, 240, 240 )
GRAY = ( 128, 128, 128 )
DARK_GRAY = ( 30, 30, 30 )
BLUE = ( 50, 150, 255 )
LIGHT_BLUE = ( 60, 180, 255 )
DnARK_BLUE = ( 15, 50, 85 )

DEFAULT = GRAY
C1 = ( 255, 100, 100 )
C2 = ( 255, 175, 100 )
C3 = ( 255, 255, 100 )
C4 = ( 175, 255, 100 )
C5 = ( 100, 255, 175 )
C6 = ( 100, 255, 255 )
C7 = ( 100, 175, 255 )
C8 = ( 100, 175, 255 )
C9 = ( 100, 100, 255 )
CA = ( 175, 100, 255 )
CB = ( 255, 100, 255 )
CC = ( 255, 100, 255 )
CD = ( 255, 100, 175 )

COLORS = [C1, C2, C3, C4, C5, C6, C7, C8, C9, CA, CB, CC, CD]
COLORS_NBR = 13


if len(sys.argv) == 2:
    if sys.argv[1] == '-py2':
        PYTHON_V = 2
    elif sys.argv[1] == '-py3':
        PYTHON_V = 3
    else:
        print('Usage: python2 visu-hex.py -py2')
        print('Usage: python3 visu-hex.py -py3')
        raise SystemExit
else:
    print('Usage: python2 visu-hex.py -py2')
    print('Usage: python3 visu-hex.py -py3')
    raise SystemExit

####################################################################
# CLASSES
####################################################################


class Room:
    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y
        self.fx = 0
        self.fy = 0
        self.links = []
        self.color = DEFAULT


class Lemin_inf:
    rooms = []
    start = Room('', 0, 0)
    end = Room('', 0, 0)
    ants_number = 0
    ants_moves = []
    last_ants_pos = []
    colors = []


class AntPos:
    def __init__(self, name, room):
        self.name = name
        self.room = room


####################################################################
#FUNCTIONS
####################################################################


def get_limits(lemin_inf):
    min_x = UINT_MAX
    min_y = UINT_MAX
    max_x = 0
    max_y = 0

    for room in lemin_inf.rooms:
        if (room.x < min_x):
            min_x = room.x
        if (room.x > max_x):
            max_x = room.x
        if (room.y < min_y):
            min_y = room.y
        if (room.y > max_y):
            max_y = room.y

    return min_x, max_x, min_y, max_y


def rooms_pos_update(lemin_inf, WIDTH, HEIGHT, padding):
    great_step = 0

    min_x, max_x, min_y, max_y = get_limits(lemin_inf)
    delta_x = max_x - min_x
    delta_y = max_y - min_y

    step_y = HEIGHT / (delta_y + padding * 2)
    step_x = WIDTH / (delta_x + padding * 2)

    if (step_x < step_y):
        great_step = step_x
    else:
        great_step = step_y

    for room in lemin_inf.rooms:
        room.x = int((room.x - min_x + padding) * great_step)
        room.y = int((room.y - min_y + padding) * great_step)

    #for turn in lemin_inf.ants_moves:
    #    for move in turn:
    #        for pos in move:
    #            pos[0] = int((pos[0] - min_x + padding) * great_step)
    #            pos[1] = int((pos[1] - min_y + padding) * great_step)

    return (great_step)

def get_pos_inf(lemin_inf, WIDTH, HEIGHT, padding):
    great_step = 0

    min_x, max_x, min_y, max_y = get_limits(lemin_inf)
    delta_x = max_x - min_x
    delta_y = max_y - min_y

    step_y = HEIGHT / (delta_y + padding * 2)
    step_x = WIDTH / (delta_x + padding * 2)

    if (step_x < step_y):
        great_step = step_x
    else:
        great_step = step_y

    return min_x, min_y, great_step


def get_updated_pos(x, y, min_x, min_y, padding, great_step):
    x = int((x - min_x + padding) * great_step)
    y = int((y - min_y + padding) * great_step)
    return x, y


def get_real_pos(pos, min_x, min_y, padding, great_step):
    if great_step == 0:
        great_step = 0.0000001
    x = (pos[0] / great_step) + min_x - padding
    y = (pos[1] / great_step) + min_y - padding
    return x, y


def debug_lemin_inf_print(lemin_inf):
    l = lemin_inf

    print(
            'ants number: ',
            l.ants_number,
            'rooms: ',
            [room.name for room in l.rooms],
            'start: ',
            l.start.name,
            'end: ',
            l.end.name,
            )

    for turn in l.ants_moves:
        for move in turn:
            print('move: ', move[0], move[1])

    for room in l.rooms:
        print(room.name, room.x, room.y,[link.name for link in room.links])


def get_room_by_name(rooms, name):
    for room in rooms:
        if (room.name == name):
            return room
    print('Warning: room not found')
    return 0


def get_ant_pos_by_name(lemin_inf, ant_name):
    for ant_pos in lemin_inf.last_ants_pos:
        if ant_pos.name == ant_name:
            return ant_pos.pos
    return [lemin_inf.start, lemin_inf.start]


def get_room_pos_by_name(lemin_inf, room_name):
    for room in lemin_inf.rooms:
        if room.name == room_name:
            return [room.x, room.y]
    print('Warning: room not found')
    return [0, 0]


def get_ant_room_by_name(lemin_inf, ant_name):
    for ant_pos in lemin_inf.last_ants_pos:
        if ant_pos.name == ant_name:
            return ant_pos.room
    return lemin_inf.start


def lemin_inf_ants_pos_update(lemin_inf, ant_name, new_ant_pos):
    for ant_pos in lemin_inf.last_ants_pos:
        if ant_pos.name == ant_name:
            ant_pos.pos = new_ant_pos
            return
    lemin_inf.last_ants_pos.append(AntPos(ant_name, new_ant_pos))

def lemin_inf_ants_room_update(lemin_inf, ant_name, new_ant_room):
    for ant_pos in lemin_inf.last_ants_pos:
        if ant_pos.name == ant_name:
            ant_pos.room = new_ant_room
            return
    lemin_inf.last_ants_pos.append(AntPos(ant_name, new_ant_room))

def get_color_by_ant_name(lemin_inf, ant_name):
    for color in lemin_inf.colors:
        if color[0] == ant_name:
            return color[1]
    #print('Warning: ant_name not found')
    return DEFAULT

def color_mix(color_a, color_b, percent_a = 0.5):
    #print('percent_a: ', percent_a)
    B = color_a[0] * percent_a
    B += color_b[0] * (1 - percent_a)
    B = int(B)
    G = color_a[1] * percent_a
    G += color_b[1] * (1 - percent_a)
    G = int(G)
    R = color_a[2] * percent_a
    R += color_b[2] * (1 - percent_a)
    R = int(R)
    color_c = (B, G, R)

    return color_c

def lemin_inf_move_update(lemin_inf, moves):
    l = lemin_inf
    curr_turn = []
    i = 0

    for move in moves:
        move_inf = move.split('-')

        ant_name = move_inf[0][1:]
        #ant_pos = get_ant_pos_by_name(l, ant_name)
        room_a = get_ant_room_by_name(l, ant_name)
        #print('room name: ', room_a.name, ', x: ', room_a.x, ', y: ', room_a.y)

        room_name = move_inf[1]
        #room_pos = get_room_pos_by_name(l, room_name)
        room_b = get_room_by_name(l.rooms, room_name)
        #print('room name: ', room_b.name, ', x: ', room_b.x, ', y: ', room_b.y)

        #print(ant_name, room_name, ant_pos, room_pos)

        #lemin_inf_ants_pos_update(l, ant_name, [room_a, room_b])
        lemin_inf_ants_room_update(l, ant_name, room_b)

        curr_turn.append([room_a, room_b])
        if (len(l.ants_moves) == 0): # if it s first turn, initialize color
            l.colors.append([ant_name, COLORS[i % COLORS_NBR]])
            #print('colors: ',l.colors)
        else:
            if room_a.color == DEFAULT:
                #print('set_color')
                room_a.color = get_color_by_ant_name(l, ant_name)
        i += 1
    l.ants_moves.append(curr_turn)


def lemin_inf_room_update(lemin_inf, room_properties, start, end):
    name = room_properties[0]
    x = int(room_properties[1])
    y = int(room_properties[2])
    new_room = Room(name, x, y)

    if start == True:
        lemin_inf.start = new_room
    elif end == True:
        lemin_inf.end = new_room

    lemin_inf.rooms.append(new_room)



def lemin_inf_link_update(rooms, link_properties):
    room_a_name = link_properties[0]
    room_b_name = link_properties[1]

    room_a = get_room_by_name(rooms, room_a_name)
    room_b = get_room_by_name(rooms, room_b_name)

    room_a.links.append(room_b)
    room_b.links.append(room_a)


def rooms_pos_compress(lemin_inf):
	side_length = math.ceil(math.sqrt(len(lemin_inf.rooms)))
	#print('side length: ', side_length)
	for i in range(len(lemin_inf.rooms)):
		lemin_inf.rooms[i].x = i % side_length
		lemin_inf.rooms[i].y = int(i / side_length)
		#print('coord - x: ', lemin_inf.rooms[i].x, ', y: ', lemin_inf.rooms[i].y)

	return (side_length)

def get_room_by_pos(lemin_inf, pos, min_x, min_y, padding, great_step):
    sqrt_min_d = UINT_MAX
    nearest_room = 0
    for room in lemin_inf.rooms:
        room_x, room_y = get_updated_pos(room.x, room.y, min_x, min_y, padding, great_step)
        sqrt_d = (room_x - pos[0]) * (room_x - pos[0]) + (room_y - pos[1]) * (room_y - pos[1])
        if sqrt_d < sqrt_min_d:
            sqrt_min_d = sqrt_d
            nearest_room = room

    return nearest_room, sqrt_min_d


####################################################################
# MAIN
####################################################################


line = ''

start = False
end = False
lemin_inf = Lemin_inf()
turn_number = 0
line_required = ''

while True:
    try:
        if PYTHON_V == 3:
            line = input()
        else:
            line = raw_input()
    except EOFError:
        break
    line = str(line)
    #print('line: ', line)
    # check if it s comment
    if len(line) > 0 and line[0] == '#':
        # check if start
        if '##start' in line:
            start = True
        elif '##end' in line:
            end = True
        elif '##VISUOFF' in line:
            raise SystemExit
        elif 'required' in line:
            line_required = line
    elif '-' in line:
        if (line[0] == 'L'):
            moves = line.split()
            lemin_inf_move_update(lemin_inf, moves)
            turn_number += 1
        elif ' ' in line:
            room_properties = line.split()
            if (len(room_properties) == 3):
                lemin_inf_room_update(lemin_inf, room_properties, start, end)
                start = False
                end = False
        else:
            link_properties = line.split('-')
            lemin_inf_link_update(lemin_inf.rooms, link_properties)
    else:
        if line == 'Error':
            raise SystemExit
        room_properties = line.split()
        if (len(room_properties) == 3):
            lemin_inf_room_update(lemin_inf, room_properties, start, end)
            start = False
            end = False
        elif (len(room_properties) == 1):
            if 'ERROR' in line:
                raise SystemExit
            else:
                lemin_inf.ants_number = int(line)


####################################################################
# DELETE NON CONNECTED ROOMS
####################################################################


to_delete = []

for room in lemin_inf.rooms:
    if len(room.links) == 0:
        to_delete.append(room)

for room in to_delete:
    lemin_inf.rooms.remove(room)

####################################################################
# FORCE DIRECTED ALGO
####################################################################


if FDA_origin > 0 or FDA_carryOn == True:
    rooms_pos_compress(lemin_inf)
step = rooms_pos_update(lemin_inf, WIDTH, HEIGHT, 1)
if step == 0:
    step = 1

import math
import random

def FDA_algorythm(lemin_inf, FDA_i):
    # init the number of iteration. FDA moves nodes iteration after iterationm some
    # greater the number of iteration is, greater will be the precision.
    FDA_Iteration_number = FDA_i

    # define force constants. spring length as L, K sping as KS and K repulsion
    # as KR, friction as KF

    L = 60
    KS = 0.001 * FDA_speed
    KR = 1 * FDA_speed
    KF = 0.2

    #debug_lemin_inf_print(lemin_inf)

    for i in range (FDA_Iteration_number):
        for room_a in lemin_inf.rooms:
            room_a_x = room_a.x
            room_a_y = room_a.y
            #print(room_a_x, room_a_y)
            for room_b in lemin_inf.rooms:
                delta_x = room_b.x - room_a.x
                delta_y = room_b.y - room_a.y
                if (delta_x != 0 or delta_y != 0):
                    distance = math.sqrt(delta_x * delta_x + delta_y * delta_y)
                    if room_b.name in [linked.name for linked in room_a.links]:
                        # calc spring force with linked rooms
                        force = KS * (distance - L)
                        room_a.fx += force * delta_x / distance
                        room_a.fy += force * delta_y / distance
                        room_b.fx -= force * delta_x / distance
                        room_b.fy -= force * delta_y / distance
                        #print('calc spring', 'distance: ', distance, 'fx: ', room_a.fx, 'fy: ', room_a.fy)
                    else:
                        # calc repulsion force with all rooms
                        #print('calc repulsion')
                        force = KR / distance
                        room_a.fx -= force * delta_x / distance
                        room_a.fy -= force * delta_y / distance
                        room_b.fx += force * delta_x / distance
                        room_b.fy += force * delta_y / distance
        if (FDA_i > 1):
            percentage = int(100 * (i + 1) / FDA_i)
            print(percentage, "% done\n")
        # update room position
        for room in lemin_inf.rooms:
            ran = random.randrange(-100, 100, 1)
            #print('x', room.x, 'y', room.y)
            room.x += room.fx 
            room.y += room.fy 
            #print('x', room.x, 'y', room.y)
            # reset f vector
            room.fx /= (1 + KF)
            room.fy /= (1 + KF)


    # debug_lemin_inf_print(lemin_inf)

    # update rooms x and y to fit screen
    #rooms_pos_update(lemin_inf, WIDTH, HEIGHT)
    #return step

# update rooms x and y to fit screen
FDA_algorythm(lemin_inf, FDA_origin)
#rooms_pos_update(lemin_inf, WIDTH, HEIGHT, step)
#print('step: ', step)


lemin_inf.start.color = GREEN
lemin_inf.end.color = RED


####################################################################
# PYGAME INIT
####################################################################


# Import the pygame library and initialise the game engine
import pygame
from pygame import gfxdraw

pygame.init()


# define speed (0 > speed >= 100). Greater the speed is, faster the ants will be.
SPEED = ANTS_speed

# Open a new window
size = (WIDTH, HEIGHT)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("ULTIMATE VISU-HEX - [F]:physics, [SPACE]:ants movements, [ESCAPE]:quit, [WHEEL]:thickness, [S]:score")

# The loop will carry on until the user exit the game (e.g. clicks the close button).
carryOn = True

# The clock will be used to control how fast the screen updates
clock = pygame.time.Clock()


####################################################################
# PYGAME FUNCTIONS
####################################################################


def draw_filled_aa_circle(surf, x, y, r, col):
    if x > 0 and x < WIDTH and y > 0 and y < HEIGHT:
        pygame.gfxdraw.aacircle(surf, int(x), int(y), int(r), col)
        pygame.gfxdraw.filled_circle(surf, int(x), int(y), int(r), col)


####################################################################
# PYGAME MAIN LOOP
####################################################################

elem_size = ELEM_SIZE
# init step of ants movements,
move_step = 0
move_turn = 0
max_move_step = int(500 / SPEED) if SPEED > 0 and SPEED <= 100 else 100

# turn number
font = pygame.font.SysFont("Arial", 18)
required_text = font.render(line_required, True, WHITE)

#FDA_algorythm(lemin_inf, 50)
#if (step == 0):
#    step = 1

show_ants = ANTS_show_on_start
selected_room = 0

while carryOn:
    # --- Main event loop
    # Set SCR var in order to make all element fit to it
    padding = 100 + elem_size
    min_x, min_y, great_step = get_pos_inf(lemin_inf, WIDTH, HEIGHT, padding)
    step = great_step

    #check input
    if step == 0:
        step = 1

    for event in pygame.event.get(): # User did something
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 4:
                elem_size += 1
            elif event.button == 5:
                elem_size -= 1 if elem_size > 0 else elem_size
            elif event.button == 1:
                mouse_pos = pygame.mouse.get_pos()
                selected_room, sqrt_min_d = get_room_by_pos(lemin_inf, mouse_pos, min_x, min_y, padding, great_step)
                print("mouse_down, pos: ", mouse_pos, ", room_name: ", selected_room.name, ", d: ", sqrt_min_d, ", max: ", int(1 + elem_size) * int(1 + elem_size))
                if sqrt_min_d > int(1 + elem_size) * int(1 + elem_size):
                    print("selected_room is too far from pointer...")
                    selected_room = 0
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:
                print("mouse_up")
                selected_room = 0
        if event.type == pygame.QUIT: # If user clicked close
            carryOn = False # Flag that we are done so we exit this loop
        if event.type == pygame.KEYDOWN: # If user clicked close
            pressed = pygame.key.get_pressed()
            if pressed[pygame.K_ESCAPE]:
                carryOn = False # Flag that we are done so we exit this loop
            if pressed[pygame.K_SPACE]:
                if move_turn >= len(lemin_inf.ants_moves):
                    move_step = 0
                    move_turn = 0
                show_ants = True if show_ants == False else False
            if pressed[pygame.K_f]:
                FDA_carryOn = True if FDA_carryOn == False else False
            if pressed[pygame.K_s]:
                SHOW_SCORE = True if SHOW_SCORE == False else False

    if selected_room != 0:
        mouse_pos = pygame.mouse.get_pos()
        selected_room.x, selected_room.y = get_real_pos(mouse_pos, min_x, min_y, padding, great_step)

####################################################################
# PYGAME DRAW
####################################################################


    # First, clear the screen to white.
    screen.fill(BLACK)

    #The you can draw different shapes and lines or add text to your background stage.
    for y in range(720):
        if y % step == 0:
            pygame.draw.line(screen, DARK_GRAY, [0, y], [1280, y], 1)

    for x in range(1280):
        if x % step == 0:
            pygame.draw.line(screen, DARK_GRAY, [x, 0], [x, 720], 1)

    for room in lemin_inf.rooms:
        for link in room.links:
            color = color_mix(room.color, link.color)
            room_x, room_y = get_updated_pos(room.x, room.y, min_x, min_y, padding, great_step)
            link_x, link_y = get_updated_pos(link.x, link.y, min_x, min_y, padding, great_step)
            pygame.draw.line(screen, color, [room_x, room_y], [link_x, link_y], int(1 + elem_size / 8))

    if (move_turn < len(lemin_inf.ants_moves)):
        curr_turn = lemin_inf.ants_moves[move_turn]
        for move in curr_turn:
            move_0_x, move_0_y = get_updated_pos(move[0].x, move[0].y, min_x, min_y, padding, great_step)
            move_1_x, move_1_y = get_updated_pos(move[1].x, move[1].y, min_x, min_y, padding, great_step)
            curr_x = move_0_x + ((move_1_x - move_0_x) * move_step) / max_move_step
            curr_y = move_0_y + ((move_1_y - move_0_y) * move_step) / max_move_step
            #print('color_a: ', move[0].color, ', color_b: ', move[1].color, ', percent_a: ', float(move_step) / float(max_move_step))
            color = color_mix(move[1].color, move[0].color, float(move_step) / float(max_move_step))
            #print('mixed_color: ', color)
            #curr_x = move[0][0] + ((move[1][0] - move[0][0]) * move_step) / max_move_step
            #curr_y = move[0][1] + ((move[1][1] - move[0][1]) * move_step) / max_move_step
            draw_filled_aa_circle(screen, curr_x, curr_y, int(1 + elem_size / 2), color)

    if show_ants == True:
        move_step += 1
        if move_step >= max_move_step:
            move_step = 0
            if move_turn < len(lemin_inf.ants_moves):
                move_turn += 1
            else:
                show_ants = False

    line_text = font.render('Laps: ' + str(move_turn) + '/' + str(turn_number), True, WHITE)

    for room in Lemin_inf.rooms:
        room_x, room_y = get_updated_pos(room.x, room.y, min_x, min_y, padding, great_step)
        draw_filled_aa_circle(screen, room_x, room_y, int(1 + elem_size), room.color)

    l = lemin_inf

    start_x, start_y = get_updated_pos(l.start.x, l.start.y, min_x, min_y, padding, great_step)
    end_x, end_y = get_updated_pos(l.end.x, l.end.y, min_x, min_y, padding, great_step)
    draw_filled_aa_circle(screen, start_x, start_y, int(1 + elem_size), l.start.color)
    draw_filled_aa_circle(screen, end_x, end_y, int(1 + elem_size), l.end.color)

    #text to screen
    if SHOW_SCORE == True:
        screen.blit(line_text, (10, 10))
        screen.blit(required_text, (10, 28))

    if FDA_carryOn == True:
    	#print('true')
        FDA_algorythm(lemin_inf, 1)

    # --- Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # --- Limit to 60 frames per second
    clock.tick(60)

#Once we have exited the main program loop we can stop the game engine:
pygame.quit()
