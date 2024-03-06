import matplotlib.ticker as ticker
import matplotlib.pyplot as plt


class Plotter:
    def __init__(self, df):
        self.df = df

    def plot_data(self):
        fig, ax1 = plt.subplots(figsize=(28, 12))
        ax2 = ax1.twinx()

        color1 = 'tab:red'
        color2 = 'tab:blue'

        self.plot_person_years(ax1, color1)
        self.plot_total_cost(ax2, color2)
        self.annotate_points(ax1, color1)

        fig.tight_layout()
        self.set_plot_title()
        self.add_legend(ax1, ax2)
        plt.show()

    def plot_person_years(self, ax, color):
        ax.set_xlabel('Version')
        ax.set_ylabel('Person-Years', color=color)
        ax.plot(self.df['Version'], self.df['Person-Years'], color=color, label='Person-Years', marker='o')
        ax.tick_params(axis='y', labelcolor=color)
        plt.xticks(rotation=45)

    def annotate_points(self, ax, color):
        for i, (person_year, total_cost) in enumerate(zip(self.df['Person-Years'], self.df['Total Cost ($)'])):
            ax.annotate(f'{person_year:.2f}\n$ {total_cost:,.0f}', (i, person_year), textcoords="offset points",
                        xytext=(0, 10), ha='center', color=color)

    def plot_total_cost(self, ax, color):
        ax.set_ylabel('Total Cost ($)', color=color)
        ax.plot(self.df['Version'], self.df['Total Cost ($)'], color=color, label='Total Cost ($)',
                marker='x')
        ax.tick_params(axis='y', labelcolor=color)
        ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, p: f'${x:,.0f}'))

    @staticmethod
    def set_plot_title():
        plt.title('Development Effort and Total Cost over Different Versions of Linux Kernel')

    @staticmethod
    def add_legend(ax1, ax2):
        lines1, labels1 = ax1.get_legend_handles_labels()
        lines2, labels2 = ax2.get_legend_handles_labels()
        ax1.legend(lines1 + lines2, labels1 + labels2, loc="upper left")
