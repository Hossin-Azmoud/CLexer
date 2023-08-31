#! /usr/bin/python3

import random

Hangman_cases = [
    """
    +---+
        |
        |
        |
       ===
    """,
    """
    +---+
    O   |
        |
        |
       ===
    """,
    """
    +---+
    O   |
    |   |
        |
       ===
    """,
    """
    +---+
    O   |
   /|   |
        |
       ===
    """,
    """
    +---+
    O   |
   /|\\  |
        |
       ===
    """,
    """
    +---+
    O   |
   /|\\  |
   /    |
       ===
    """,
    """
    +---+
    O   |
   /|\\  |
   / \\  |
       ===
    """
]
def choose_words():
    words_list = ['apple', 'banana', 'dog', 'frog', 'woman', 'coffee', 'python', 'code', 'challenge', 'cat', 'star', 'bed', 'fish', 'moon', 'sun', 'world', 'car', 'book', 'spoon', 'man', 'milk', 'rain', 'snow', 'bike', 'cake', 'knife', 'table', 'fork', 'window', 'smile', 'black', 'photo', 'cream', 'chess', 'queen', 'sugar', 'king', 'planet', 'bishop', 'wolf', 'lion', 'bear', 'bat', 'zoo', 'tiger', 'pawn', 'water']
    return random.choice(words_list)

def display_word(words_list, guessed_letters):
    displayed_word = '_'

    for letter in words_list:
        if letter in guessed_letters:
            displayed_word += letter
        else:
            displayed_word += '_'

    return displayed_word

def hangman():
    word = "hii"
    guessed_letters = []
    attempts_left = 6

    print('Welcome to Hangman!')

    while attempts_left >= 1:
        print(Hangman_cases[6 - attempts_left])
        print(display_word(word, guessed_letters))

        if '_' not in display_word(word, guessed_letters):
            print("Congratulations! You've guessed the word:", word)
            break

        guess = input("Guess a letter: ").lower()

        if guess in guessed_letters:
            print("You've already guessed that letter!")
            continue

        guessed_letters.append(guess)

        if guess not in word:
            attempts_left -= 1
            print("Incorrect guess! You have", attempts_left, "attempts left.")

        if attempts_left == 0:
            print("Game over! You're out of attempts. The word you were trying to guess was:", word)
            break 
hangman()
