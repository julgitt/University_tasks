import string
from os import listdir
from os.path import isfile, join

alphabet = string.ascii_lowercase + "ąćęńłóśżź" + "äöüß"


def save_and_create_stats_from_files(language2files):
	stats = create_stats_from_files(language2files)
	save_stats_to_files(stats)
	return stats
	
def create_stats_from_files (language2files):
    texts = {}

    for language, files in language2files.items():
        texts[language] = [read_text_from_file(file_name) for file_name in files]
        
    return calc_language_statistics(texts)


def identify_language_from_file (file_name):
    text = read_text_from_file(file_name)
    return identify_language(text)


def read_text_from_file(file_name):
    try:
        with open(f'Texts/{file_name}', "r", encoding='utf-8') as f:
            return combine_text(f.readlines())
    except FileNotFoundError:
        print(f'File {file_name} not found')


def calc_language_statistics(language2texts):
    return {language: calc_letters_frequency(combine_text(texts)) for language, texts in language2texts.items()}


def combine_text(texts):
    return ' '.join(texts)


def identify_language(text):
    input_text_stats = calc_letters_frequency(text)

    language2stats = read_all_stats()
    language_scores = {}
    
    for language, language_stats in language2stats.items():
        score = sum((input_text_stats.get(letter) - language_stats.get(letter))**2 for letter in alphabet)
        language_scores[language] = score
    
    most_likely_language = min(language_scores, key=language_scores.get)
    return most_likely_language


def calc_letters_frequency(text):
    alnum_text =  ''.join(char for char in text.lower() if char.isalnum())
    letters_total_count = len(alnum_text)

    result = {letter: 0 for letter in alphabet}

    for letter in alnum_text:
        if letter in alphabet: 
            result[letter] += 1

    letter2frequency = {letter: percentAmount(letter_count, letters_total_count) for letter, letter_count in result.items()}
    return letter2frequency
        
def percentAmount(a, b):
    return round((a / b) * 100, 2)


def save_stats_to_files(language2stats):
    for language, stats in language2stats.items():
        save_stats_to_file(language, stats)


def save_stats_to_file(language, stats): 
    with open(f'Stats/{language}-stats.txt', 'w') as f:
        for letter, frequency in stats.items():
            f.write(f"{letter}: {frequency}\n")


def read_all_stats():
    file_names = [f for f in listdir("Stats/") if isfile(join("Stats/", f))]
    language2stats = {}

    for file_name in file_names:
        language = file_name[:file_name.index("-stats")]
        language2stats[language] = read__stats_from_file(file_name)
    
    return language2stats


def read__stats_from_file(file_name):
    stats = {}
    try:
        with open(f"Stats/{file_name}", 'r', encoding='utf-8') as f:
            for line in f:
                (letter, frequency) = line.split(": ")
                stats[letter] = float(frequency)
            return stats
    except FileNotFoundError:
        print(f'File {file_name} not found')



statistics = save_and_create_stats_from_files({"deutsch" : ["CierpieniaMłodegoWertera_de.txt"], 
                                      "english" : ["RomeoIJulia_en.txt"],
                                       "polish" : ["PanTadeusz_pl.txt"]})

print(identify_language_from_file("SklepyCynamonowe_pl.txt"))
