import matplotlib.pyplot as plt
import matplotlib.animation as animation


class LangtonAnt:
    def __init__(self, width, height, max_steps, color, interval, direction):
        self.width = width
        self.height = height
        self.interval = interval
        self.color = color
        self.direction = direction
        self.max_steps = max_steps
        self.steps_count = 0
        self.ant_pos = (width // 2, height // 2)
        self.dead_points = []


    def update(self, frame):
        if self.steps_count == self.max_steps:
            plt.title(f"Simulation Completed\nSteps: {self.steps_count}")
            return

        if self.ant_pos in self.dead_points:
            self.handle_dead_point()
        else:
            self.handle_living_point()

        self.move()
        self.steps_count += 1
        self.update_plot()
    
    
    def handle_dead_point(self):
        self.dead_points.remove(self.ant_pos)
        self.turn_left()
    
    
    def handle_living_point(self):
        self.dead_points.append(self.ant_pos)
        self.turn_right()
        
        
    def turn_left(self):
        dx, dy = self.direction
        self.direction = (-dy, dx)
    
    def turn_right(self):
        dx, dy = self.direction
        self.direction = (dy, -dx)

   
    def move(self):
        new_x = self.ant_pos[0] + self.direction[0]
        new_y = self.ant_pos[1] + self.direction[1]
        self.ant_pos = (new_x,new_y)


    def update_plot(self):
        plt.clf()
        plt.scatter([x for x, y in self.dead_points], [y for x, y in self.dead_points], color=self.color, marker='s', s=5)
        plt.scatter(self.ant_pos[0], self.ant_pos[1], color='red', marker='s', s=5)
        plt.tick_params(
            axis='both', which='both', bottom=False, top=False,
            left=False, right=False, labelbottom=False, labelleft=False
        )
        plt.xlim(0, self.width)
        plt.ylim(0, self.height)
        plt.title(f"Steps: {self.steps_count}")
    
    
    def start_simulation(self):
        fig = plt.figure(num="Langton Ant", figsize=(8, 8))
        anim = animation.FuncAnimation(fig, self.update, frames=1000, interval=self.interval)
        def stop_animation(event):
            print("Simulation Completed")

        fig.canvas.mpl_connect('close_event', stop_animation)
        plt.show()


width = 100
height = 100
steps = 11500
color = 'black'
interval = 1
direction = (1,0)

simulation = LangtonAnt(width, height, steps, color, interval, direction)
simulation.start_simulation()