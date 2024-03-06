from pathlib import Path
import re


class DataLoader:
    def __init__(self, results_path):
        self.results_path = Path(results_path)
        self.total_cost_regex = re.compile(r'Total Estimated Cost to Develop\s+= \$ ([\d,]+)')
        self.person_years_regex = re.compile(
            r'Development Effort Estimate, Person-Years \(Person-Months\) = ([\d,]+\.?\d*) \(([\d,]+\.?\d*)\)')

    def load_data_from_file(self, file_path):
        with open(file_path, 'r') as file:
            data = file.read()
            total_cost = self.total_cost_regex.search(data)
            person_years = self.person_years_regex.search(data)
            return total_cost, person_years

    @staticmethod
    def clean_data(versions, person_years, person_months, total_costs):
        cleaned_versions = [f'{version.split("-")[1]}-{version.split("-")[0]}' for version in versions]
        cleaned_person_years = [float(year.replace(',', '')) for year in person_years]
        cleaned_person_months = [float(month.replace(',', '')) for month in person_months]
        cleaned_total_costs = [int(cost.replace(',', '')) for cost in total_costs]
        return cleaned_versions, cleaned_person_years, cleaned_person_months, cleaned_total_costs

    def load_data(self):
        versions = []
        person_years = []
        person_months = []
        total_costs = []

        for version_dir in self.results_path.iterdir():
            sloccount_file = version_dir / "sloccount_results.txt"
            if sloccount_file.is_file():
                total_cost_match, person_years_match = self.load_data_from_file(sloccount_file)
                if person_years_match and total_cost_match:
                    versions.append(version_dir.name)
                    person_years.append(person_years_match.group(1))
                    person_months.append(person_years_match.group(2))
                    total_costs.append(total_cost_match.group(1))

        return self.clean_data(versions, person_years, person_months, total_costs)
