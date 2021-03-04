from random import randint

MAZE_WIDTH = 8
MAZE_HEIGHT = 8

maze = [[str(randint(0, 1)) for _ in range(MAZE_WIDTH)]
                            for _ in range(MAZE_HEIGHT)]
maze[0][0] = maze[-1][-1] = '0'
with open('maze.init', 'w', encoding='utf-8') as file:
    file.write('\n'.join(map(lambda line: ' '.join(line), maze)))
