from cs50 import get_string
import re

def get_coleman():
    text = get_string("Text: ")
    letters = len(re.findall(r"[a-zA-Z]", text))
    words = len(text.split())
    sentences = len(re.split(r'[.!?]', text)) - 1
    L = (letters / words) * 100
    S = (sentences/ words) * 100
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

def main():
    get_coleman()

main()
