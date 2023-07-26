import argparse
import os

def find_words(file_path, lengths):
    """Find words of a given length in a file. The approach is to find
    all whitespace-separated tokens and filter for ones composed of
    alphabetic characters and of the desired length.

    Args:
        file_path (string): the file
        lengths (list[int]): the lengths of the words to find

    Returns:
        list[string]: the words found in the file
    """
    with open(file_path, 'r') as file:
        words = file.read().split()
    return [word for word in words if len(word) in lengths and word.isalpha()]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Find words.")
    parser.add_argument("file_path", help="The path to the file to be processed.")
    args = parser.parse_args()
    file_path = args.file_path
    if not os.path.isfile(file_path):
        print("The file path you entered does not point to a file.")
        exit(1)

    delimiter = input("Input the delimiter the generated file should use (\\n for newline): ")
    delimiter = delimiter if delimiter != '\\n' else '\n'
    lengths = list(map(int, input("Input the word lengths to find, separated by commas: ").split(',')))
    output_file_path = input("Input the path to the output file: ")
    
    filtered_words = find_words(file_path, lengths)
    
    with open(output_file_path, 'w') as file:
        for word in filtered_words[:-1]:
            file.write(word + delimiter)
        file.write(filtered_words[-1])
