import requests


def get_synonyms_and_related_words(word: str) -> list:
    """
    Gets synonyms and related words of a given word.
    :param word: A word
    :return: A list of synonyms and similar words (the word passed in is automatically
     added to the list that is returned).
    """
    url = "https://api.datamuse.com/words"
    params = {
        "ml": word,  # ml = find words related to this word
        "max": 200,
    }

    response = requests.get(url, params=params)
    if response.status_code == 200:
        synonyms_and_related_words = [word]
        for word_data in response.json():
            if word_data != word:
                synonyms_and_related_words.append(word_data["word"])

        return synonyms_and_related_words
    else:
        print("Error: " + str(response.status_code) + ":" + str(response.text))
        return []


def get_hobby_similarity_score(this_hobbies: list, other_hobbies: list) -> int:
    this_hobbies_synonyms = []
    for hobby in this_hobbies:
        this_hobbies_synonyms.append(get_synonyms_and_related_words(hobby))

    points = 0
    for synonyms in this_hobbies_synonyms:
        for hobby in other_hobbies:
            if hobby in synonyms:
                points += 1
                break  # stop searching the list and move on to next word
    return points


if __name__ == "__main__":
    print(get_synonyms_and_related_words("computers"))
    hobby1 = ["hi", "rope"]
    hobby2 = ["soccer", "books", "programming"]
    print(get_hobby_similarity_score(hobby1, hobby2))

