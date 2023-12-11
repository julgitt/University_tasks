import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random


class SnakeGame:
    def __init__(self, width, height, num_blocks, num_points, snake_interval):
        self.width = width
        self.height = height
        self.num_blocks = num_blocks
        self.num_points = num_points
        self.snake_interval = snake_interval

        self.snake = [(width // 2, height // 2)]
        self.direction = random.choice([(0, 1), (0, -1), (1, 0), (-1, 0)])
        self.blocks = [self.generate_point() for _ in range(num_blocks)]
        self.points = [self.generate_point() for _ in range(num_points)]
        self.game_over = False
        self.game_started = False


    def generate_point(self):
        return (random.randint(1, width-2),random.randint(1, height-2))
    
    #region gameLogic
    def update(self, frame):
        if self.game_over:
            plt.title("Game Over")
            return

        if self.game_started == True:
            head_x, head_y = self.snake[-1]
            new_head = (head_x + self.direction[0], head_y + self.direction[1])
    
            if self.check_for_collision(new_head):
                self.game_over = True
                return
        
            self.move(new_head)
            
        self.update_plot()


    def check_for_collision(self, new_head):
        with_snake = new_head in self.snake[:-1]
        with_map_border = not (0 <= new_head[0] <= self.width) or not (0 <= new_head[1] <= self.height)
        with_blocks = new_head in self.blocks
        return with_snake or with_map_border or with_blocks
    

    def move (self, new_head):
        self.snake.append(new_head)

        if new_head in self.points:
            self.points.remove(new_head)
            self.points.append(self.generate_point())
        else:
            self.snake.pop(0)
    #endregion
    
    #region plot
    
    def update_plot(self):
        plt.clf()
        self.plot_points()
        self.set_plot_properties()
       
    
    def plot_points(self):
        plt.scatter([x for x, y in self.blocks], [y for x, y in self.blocks], color='red', marker='s', s=100)
        plt.scatter([x for x, y in self.snake], [y for x, y in self.snake], color='blue', marker='s', s=100)
        plt.scatter([x for x, y in self.points], [y for x, y in self.points], color='green', marker='s', s=100)
    
    
    def set_plot_properties(self):
        plt.xlim(0, self.width)
        plt.ylim(0, self.height)
        plt.tick_params(
            axis='both', which='both', bottom=False, top=False,
            left=False, right=False, labelbottom=False, labelleft=False
        )
        plt.title(f"Points: {len(self.snake) - 1}")
    #endregion
        
    #region userInterface
    
    def change_direction_on_key(self, event):
        new_direction = self.direction
        if event.key == 'up':
            new_direction = (0, 1)
        elif event.key == 'down':
            new_direction = (0, -1)
        elif event.key == 'right':
            new_direction = (1, 0)
        elif event.key == 'left':
            new_direction = (-1, 0)
        if (self.direction[0] + new_direction[0] != 0) or (self.direction[1] + new_direction[1] != 0):    
            self.game_started = True
            self.direction = new_direction
           
    #endregion
    
    def start_game(self):
        fig = plt.figure(num="Snake", figsize=(8, 8))
        fig.canvas.mpl_connect('key_press_event', self.change_direction_on_key)
        anim = animation.FuncAnimation(fig, self.update, frames=1000, interval=self.snake_interval)
        def stop_animation(event):
            self.game_over = True
            print("Game Over")

        fig.canvas.mpl_connect('close_event', stop_animation)
        plt.show()


width = 25
height = 25
num_blocks = 0
num_points = 1
snake_interval = 50

game = SnakeGame(width, height, num_blocks, num_points, snake_interval)
game.start_game()