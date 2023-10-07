import string
letters = string.ascii_lowercase + "ąćęńłóśżź" + "äöüß"


def calc_letters_frequency(text):
    result = {element: 0 for index, element in enumerate(letters)}
    for letter in text.lower():
        if letter in letters: 
            result[letter] += 1
    return result


#  {german: {..,...,}, ...} 
def calc_language_statistics(language_texts):
    language_statistics = {}
    for language, texts in language_texts.items():
        combined_text = " ".join(texts)
        
        letter_frequency = calc_letters_frequency(combined_text)
        language_statistics[language] = letter_frequency
        
    return   language_statistics
    #return {language: calc_letters_frequency(''.join(texts)) for language, texts in language_texts.items()}


def identify_language(text, statistics):
    letters_frequency = calc_letters_frequency(text)
    language_scores = {}
    
    for language, stats in statistics.items():
        score = sum((letters_frequency.get(letter) - stats.get(letter))**2 for letter in letters)
        language_scores[language] = score
    
    most_likely_language = min(language_scores, key=language_scores.get)
    return most_likely_language


def return_file_content(file):
    try:
        with open(f'Texts/{file}', "r", encoding='utf-8') as f:
            return " ".join(f.readlines())
    except FileNotFoundError:
        print(f'File {file} not found')


def create_stats_from_files (files_languages):
    texts = {}
    for language, file_names in files_languages.items():
        texts[language] = [return_file_content(name) for name in file_names]
    return calc_language_statistics(texts)


def identify_language_from_file (file, stats):
    text = return_file_content(file)
    return identify_language(text, stats)
        

statistics = create_stats_from_files({"deutsch" : ["CierpieniaMłodegoWertera_de.txt"], 
                                      "english" : ["RomeoIJulia_en.txt"],
                                       "polish" : ["PanTadeusz_pl.txt"]})
print(identify_language_from_file("SklepyCynamonowe_pl.txt",statistics))
