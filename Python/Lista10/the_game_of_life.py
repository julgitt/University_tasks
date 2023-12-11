import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pickle
from enum import Enum
from datetime import datetime
import tkinter as tk
from tkinter import filedialog
import os


class TheGameOfLife:
    def __init__(self, width, height, mode):
        self.width = width
        self.height = height
        self.interval = 100
        self.living_cells = set()
        self.newborn_cells = set()
        self.dead_cells = set()
        self.game_is_running = False
        self.anim = None
        self.fig = None
        self.rule_of_death = mode[0]
        self.rule_of_life = mode[1]
    

    def update(self, frame):
        if self.game_is_running:
            self.time_tick()
        self.update_plot()

    #region plot
    def update_plot(self):
        plt.clf()
        plt.grid(True)
        self.plot_living_cells()
        self.set_plot_properties()


    def plot_living_cells(self):
        plt.scatter(
            [x for x, y in self.living_cells],
            [y for x, y in self.living_cells],
            color='black', marker='s', s=(50 * 40) // self.width, zorder=2
        )


    def set_plot_properties(self):
        plt.xlim(0, self.width)
        plt.ylim(0, self.height)
        plt.xticks(range(0, self.width, 1))
        plt.yticks(range(0, self.height, 1))
        plt.tick_params(
            axis='both', which='both', bottom=False, top=False,
            left=False, right=False, labelbottom=False, labelleft=False
        )
        plt.title('The game has started' if self.game_is_running else 'Press space to start the game')
        plt.xlabel('Change interval to:\n    1ms: 1\n    100ms: 2\n    500ms: 3\nSave state: F5\nLoad state: F8', loc='left')
  
    #endregion

    #region userInterface

    def manage_cells_on_mouse_click(self, event):
        if (self.game_is_running == True):
            return
        if (event.xdata == None or event.ydata == None):
            return
        x, y = int(event.xdata), int(event.ydata)
        if event.button == 1:
            self.living_cells.add((x,y))
        elif event.button == 3:
            if (x,y) in self.living_cells:
                self.living_cells.remove((x,y))
    

    def start_game_on_space(self, event):
        if event.key == ' ':
            self.game_is_running = not self.game_is_running
        

    def change_interval_on_key(self, event):
        if event.key == '1':
            self.interval = 500
        if event.key == '2':
            self.interval = 100
        elif event.key == '3':
            self.interval = 1

        if event.key.isnumeric():
            self.anim.event_source.stop()
            print(f'interval = {self.interval}')
            self.anim = animation.FuncAnimation(self.fig, self.update, frames=1000, interval=self.interval)
            plt.show()
    
    
    def save_or_load_state_on_key(self, event):
        if event.key == 'f5':
            self.save_state()
        if event.key == 'f8':
            self.load_state()


        if event.key.isnumeric():
            self.anim.event_source.stop()
            print(f'interval = {self.interval}')
            self.anim = animation.FuncAnimation(self.fig, self.update, frames=1000, interval=self.interval)
            plt.show()
            

        if event.key.isnumeric():
            self.anim.event_source.stop()
            print(f'interval = {self.interval}')
            self.anim = animation.FuncAnimation(self.fig, self.update, frames=1000, interval=self.interval)
            plt.show()

    #endregion

    #region gameLogic
    def time_tick(self):
        self.remove_dead_cells()
        self.add_newborn_cells()
        self.handle_cells_states()


    def remove_dead_cells(self):
        self.living_cells -= self.dead_cells
        self.dead_cells.clear()


    def add_newborn_cells(self):
        self.living_cells.update(self.newborn_cells)
        self.newborn_cells.clear()


    def handle_cells_states(self):
        all_neighbours = self.get_all_neighbours()
        for (x,y) in self.living_cells:
            self.handle_living_cell(x,y)
        for (x,y) in all_neighbours.difference(self.living_cells):
            if ( 0 < x < width and 0 < y < height):
                self.handle_dead_cell(x,y)


    def handle_living_cell(self, x, y):
        if self.living_neighbours_count(x,y) not in self.rule_of_death:
            self.dead_cells.add((x,y))


    def handle_dead_cell(self, x, y):
        if self.living_neighbours_count(x,y) in self.rule_of_life:
            self.newborn_cells.add((x,y))


    def living_neighbours_count(self, x,y):
        neighbours = self.get_neighbours(x, y)
        living_neighbours = neighbours.intersection(self.living_cells)
        return len(living_neighbours)


    def get_all_neighbours(self):
        all_neighbours = set()
        for (x, y) in self.living_cells:
            all_neighbours |= self.get_neighbours(x, y)
        return all_neighbours


    def get_neighbours(self, x, y):
        deltas = [(1, 0), (0, 1), (0, -1), (-1, 0), (-1, 1), (1, -1), (1, 1), (-1, -1)]
        neighbours = {(x + dx, y + dy) for dx, dy in deltas}
        return neighbours

    #endregion    
    
    #region savingToFile
    
    def save_state(self):
        state = {
            'living_cells': self.living_cells,
            'game_is_running': self.game_is_running,
            'interval': self.interval
        }
        current_datetime = datetime.now()
        formatted_date = current_datetime.strftime("%Y-%m-%d_%H-%M-%S")
        with open(f"game_save_{formatted_date}.pkl", "wb") as file:
            pickle.dump(state,file)
        print(f'state saved in file: game_save{formatted_date}.plk')
    
    
    def load_state(self):
        initial_dir = os.path.dirname(os.path.abspath(__file__))
        root = tk.Tk()
        root.withdraw()
        filename = filedialog.askopenfilename(initialdir=initial_dir, title="Select file",
                                                  filetypes=(("Pickle files", "*.pkl"), ("All files", "*.*")))
        if not filename:
            return
        with open(filename, "rb") as file:
            state = pickle.load(file)
            self.living_cells = state['living_cells']
            self.game_is_running = state['game_is_running']
            self.interval = state['interval']
        print(f'state loaded from file: {filename}')
    
    #endregion
    
    def start_game(self):
        self.fig = plt.figure(num="The game of life", figsize=(12, 12))
        self.fig.canvas.mpl_connect('button_press_event', self.manage_cells_on_mouse_click)
        self.fig.canvas.mpl_connect('key_press_event', self.start_game_on_space)
        self.fig.canvas.mpl_connect('key_press_event', self.change_interval_on_key)
        self.fig.canvas.mpl_connect('key_press_event', self.save_or_load_state_on_key)

        self.anim = animation.FuncAnimation(self.fig, self.update, frames=1000, interval=self.interval)

        plt.show()



class Modes():
    game_of_life = ([2,3], [3])
    cities = ([2,3,4,5], [4,5,6,7,8])
    labirynth = ([1,2,3,4,5], [3])
    coral = ([4,5,6,7,8], [3])
    seed = ([], [2])



if __name__ == '__main__':
    width = 100
    height = 100
    modes = Modes

    game = TheGameOfLife(width, height, modes.game_of_life)
    game.start_game()