#
# Name:Yanzhuo Cao
#

from Proj2_tree import printTree

#
# The following two trees are useful for testing.
#
smallTree = \
    ("Is it bigger than a breadbox?",
        ("an elephant", None, None),
        ("a mouse", None, None))
mediumTree = \
    ("Is it bigger than a breadbox?",
        ("Is it gray?",
            ("an elephant", None, None),
            ("a tiger", None, None)),
        ("a mouse", None, None))

def main():
    print("Welcome to 20 Questions!")

    while True:
        input1 = input("Would you like to load a tree from a file? yes or no: ").lower()
        if input1 == "yes":
            file_name = input("What's the name of the file? ")
            try:
                treeFile = open(file_name, "r")
                current_tree = loadTree(treeFile)
                treeFile.close()
            except Exception as e:
                print(f"An error occurred: {e},Loading the smallTree instead.")
                current_tree = smallTree
            break
        elif input1 == "no":
            current_tree = smallTree
            break
        else:
            print("Invalid answer. Please respond with 'yes' or 'no'.")

    current_tree = play(current_tree)
    while True:
        input1= input("Would you like to play again? yes or no: ").lower()
        if input1 == "yes":
            current_tree = play(current_tree)
        elif input1 == "no":
            break
        else:
            print("Invalid answer. Please respond with 'yes' or 'no'.")

    while True:
        input1= input("Would you like to save this tree for later? yes or no: ").lower()
        if input1 == "yes":
            try:
                with open(input("Please enter a file name: "), "w") as treeFile:
                    saveTree(current_tree, treeFile)
                print("Thank you! The file has been saved.")
            except Exception as e:
                print(f"An error occurred: {e}. The tree could not be saved.")
            break
        elif input1 == "no":
            break
        else:
            print("Invalid answer. Please respond with 'yes' or 'no'.")

    print("Bye!")

    # Write the "main" function for 20 Questions here.  Although
    # main() is traditionally placed at the top of a file, it is the
    # last function you will write.

def simplePlay(tree):
    '''
        Navigate through a binary decision tree based on user input.

        This function repeatedly presents the user with a yes/no question
        until a leaf node is reached, at which point it guesses the item
        and asks the user to confirm.

        Parameters
        ----------
        tree : list
            The decision tree list, where index 0 is the current question,
            index 1 is the subtree for 'yes' answer, and index 2 is for 'no'.

        Returns
        -------
        bool
            True if the guess is confirmed by the user, False otherwise.
    '''
    while tree[1] or tree[2]:
        answer = input(f"{tree[0]} yes or no: ").lower()
        if answer == "yes":
            tree = tree[1]
        elif answer == "no":
            tree = tree[2]
        else:
            print("Please say yes or no.")
    return input(f"Is it {tree[0]}? yes or no: ").lower() == "yes"


def play(tree):
    '''
        Play a guessing game with the user and expand the decision tree
        with new knowledge based on the user's input.

        This function navigates the decision tree by asking the user yes/no questions
        until it reaches a leaf node. If the guess is wrong, it prompts the user
        for the correct answer and a new question to expand the tree.

        Parameters
        ----------
        tree : tuple
            A tuple representing the decision tree node. It contains the question (str)
            and two subtrees for 'yes' and 'no' branches.

        Returns
        -------
        tuple
            The modified decision tree with any new knowledge added.
    '''
    question, yes_branch, no_branch = tree

    if yes_branch is no_branch is None:
        answer = input(f"Is it {question}? (yes/no): ").lower()
        if answer == "yes":
            print("I got it!")
        else:
            correct_item = input("Drats! What was it? ")
            new_question = input(f"What's a question that distinguishes between {correct_item} and {question}? ")
            correct_answer = input(f"And what's the answer for {correct_item}? (yes/no): ").lower()
            if correct_answer == "yes":
                tree = (new_question, (correct_item, None, None), (question, None, None))
            else:
                tree = (new_question, (question, None, None), (correct_item, None, None))
    else:
        answer = input(f"{question} (yes/no): ").lower()
        if answer == "yes":
            tree = (question, play(yes_branch), no_branch)
        elif answer == "no":
            tree = (question, yes_branch, play(no_branch))
        else:
            print("Invalid answer. Please respond with 'yes' or 'no'.")
            tree = play(tree)
    return tree


def saveTree(tree, treeFile):
    '''
        Save the decision tree to a file.

        This function writes the decision tree to a file, denoting leaf nodes
        with 'Leaf' and internal nodes with 'Internal node'. It then recursively
        saves the subtrees.

        Parameters
        ----------
        tree : tuple
            The decision tree to be saved.
        treeFile : file object
            An open file object for writing the tree to.

        Returns
        -------
        None
    '''
    if tree[1] is None and tree[2] is None:
        treeFile.write("Leaf\n" + tree[0] + "\n")
    else:
        treeFile.write("Internal node\n" + tree[0] + "\n")
        saveTree(tree[1], treeFile)
        saveTree(tree[2], treeFile)

def loadTree(treeFile):
    '''
        Load a decision tree from a file.

        This function reads from a file object and reconstructs the decision tree.
        It identifies 'Leaf' nodes and 'Internal node' to recreate the tree structure.

        Parameters
        ----------
        treeFile : file object
            An open file object for reading the tree from.

        Returns
        -------
        tuple
            The reconstructed decision tree.
    '''
    node_type, value = treeFile.readline().strip(), treeFile.readline().strip()
    return (value, None, None) if node_type == "Leaf" else (value, loadTree(treeFile), loadTree(treeFile)) if node_type == "Internal node" else None

# The following two-line "magic sequence" must be the last thing in
# your file.  After you write the main() function, this line it will
# cause the program to automatically play 20 Questions when you run
# it.
#
if __name__ == '__main__':
    main()
