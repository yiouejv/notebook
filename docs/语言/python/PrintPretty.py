import sys
import re


if "__main__" == __name__:
    # print(sys.argv)
    print("========================>\n")
    string = sys.argv[1]
    string = re.sub("\\\\n", "\\n", string)
    print(string)



