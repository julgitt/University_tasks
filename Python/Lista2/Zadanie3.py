import string
import json
from os import listdir
from os.path import isfile, join

ALPHABET = string.ascii_lowercase + "ąćęńłóśżź" + "äöüß"


#  _______________ CREATE STATISTICS ___________________
def save_and_create_stats_from_files(language_to_files):
    stats = create_stats_from_files(language_to_files)
    save_stats_to_files(stats)
    return stats


def create_stats_from_files(language_to_files):
    texts = {}

    for language, files in language_to_files.items():
        texts[language] = [read_text_from_file(
            file_name) for file_name in files]

    return calc_language_statistics(texts)


def calc_language_statistics(language_to_texts):
    return {language: calc_letters_frequency(' '.join(texts)) for language, texts in language_to_texts.items()}


#  ________________ IDENTIFY LANGUAGE ________________
def identify_language_from_file(file_name):
    text = read_text_from_file(file_name)
    return identify_language(text)


def read_text_from_file(file_name):
    try:
        with open(f'Texts/{file_name}', "r", encoding='utf-8') as f:
            return ' '.join(f.readlines())
    except FileNotFoundError:
        print(f'File {file_name} not found')


def identify_language(text):
    input_text_stats = calc_letters_frequency(text)

    language_to_stats = read_all_stats()
    language_scores = {}

    for language, language_stats in language_to_stats.items():
        score = sum((input_text_stats.get(letter) -
                    language_stats.get(letter))**2 for letter in ALPHABET)
        language_scores[language] = score

    most_likely_language = min(language_scores, key=language_scores.get)
    return most_likely_language


#  _________________ LETTERS FREQUENCY ___________________________
def calc_letters_frequency(text):
    alnum_text = ''.join(char for char in text.lower() if char.isalnum())
    letters_total_count = len(alnum_text)

    result = {letter: 0 for letter in ALPHABET}

    for letter in alnum_text:
        if letter in ALPHABET:
            result[letter] += 1

    letter_to_frequency = {letter: round(
        (letter_count * 100) / letters_total_count, 2) for letter, letter_count in result.items()}
    return letter_to_frequency


#  _________________ SAVING STATS TO FILES _________________________
def save_stats_to_files(language_to_stats):
    for language, stats in language_to_stats.items():
        save_stats_to_file(language, stats)


def save_stats_to_file(language, stats):
    with open(f'Stats/{language}-stats.json', 'w') as f:
        json.dump(stats, f)


#  ______________  READING STATS FROM FILES _______________________
def read_all_stats():
    file_names = [f for f in listdir("Stats/") if isfile(join("Stats/", f))]
    language_to_stats = {}

    for file_name in file_names:
        language = file_name[:file_name.index("-stats")]
        language_to_stats[language] = read__stats_from_file(file_name)

    return language_to_stats


def read__stats_from_file(file_name):
    stats = {}
    try:
        with open(f"Stats/{file_name}", 'r', encoding='utf-8') as f:
            stats = json.load(f)
        return stats
    except FileNotFoundError as e:
        raise FileNotFoundError(f'File {file_name} not found') from e


#  ________________   TEST _____________________
statistics = save_and_create_stats_from_files({"deutsch": ["CierpieniaMłodegoWertera_de.txt"],
                                               "english": ["RomeoIJulia_en.txt"],
                                               "polish": ["PanTadeusz_pl.txt"]})

print(identify_language_from_file("SklepyCynamonowe_pl.txt"))
