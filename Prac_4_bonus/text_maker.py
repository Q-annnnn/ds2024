import random
import string
from collections import defaultdict

# Predefined set of words
words = ["apple", "banana", "orange", "grape", "pear", "peach", "kiwi", "strawberry", "melon", "blueberry"]

# Generate a large text file with random words
def generate_large_file(file_path, num_words):
    with open(file_path, 'w') as f:
        for _ in range(num_words):
            word = random.choice(words)
            f.write(word + ' ')

# Count the occurrences of each word in the file
def count_word_occurrences(file_path):
    word_counts = defaultdict(int)
    with open(file_path, 'r') as f:
        for line in f:
            words = line.split()
            for word in words:
                word_counts[word] += 1
    return word_counts

# Define the file path and the number of words
file_path = 'large_text.txt'
num_words = 1000000  # Adjust the number of words as needed

# Generate the large text file
generate_large_file(file_path, num_words)

# Count the occurrences of each word in the file
word_counts = count_word_occurrences(file_path)

# Print the count of each word
for word, count in word_counts.items():
    print(f"{word}: {count}")
