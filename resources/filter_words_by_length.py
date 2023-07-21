import argparse
import os

def filter_words_by_length(file_path, delimiter, lengths):
    """Read the given file to filter out all words that are not of the
    specified lengths.

    Args:
        file_path (string): the file to process
        delimiter (string): the delimiter used to separate words
        lengths (list[int]): the lengths of the words to filter for

    Returns:
        list[int]: the words of the specified lengths
    """
    with open(file_path, 'r') as file:
        words = file.read().split(delimiter)
    return [word for word in words if len(word) in lengths]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Filter words by length.")
    parser.add_argument("file_path", help="The path to the file to be processed.")
    args = parser.parse_args()
    file_path = args.file_path
    if not os.path.isfile(file_path):
        print("The file path you entered does not point to a file.")
        exit(1)

    delimiter = input("Input the delimiter this file uses to separate words (\\n for newline): ")
    delimiter = delimiter if delimiter != '\\n' else '\n'
    lengths = list(map(int, input("Input the word lengths to filter for, separated by commas: ").split(',')))
    output_file_path = input("Input the path to the output file: ")
    
    filtered_words = filter_words_by_length(file_path, delimiter, lengths)
    
    with open(output_file_path, 'w') as file:
        for word in filtered_words[:-1]:
            file.write(word + delimiter)
        file.write(filtered_words[-1])
