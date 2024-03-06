import pandas as pd
import matplotlib.pyplot as plt

from dataLoader import DataLoader
from plotter import Plotter


def main():
    results_path = "./results/"
    loader = DataLoader(results_path)
    versions, person_years, person_months, total_costs = loader.load_data()

    df = pd.DataFrame({
        'Version': versions,
        'Person-Years': person_years,
        'Person-Months': person_months,
        'Total Cost ($)': total_costs
    })
    df.sort_values(by='Version', inplace=True)

    plotter = Plotter(df)
    plotter.plot_data()
    plt.show()


if __name__ == "__main__":
    main()
