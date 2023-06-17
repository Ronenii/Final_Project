<h1 style="text-decoration: underline;"> Advanced C programming Final Project </h1>
<h3> The objective of the program is to organize performances by scheduling musicians from the data model for each performance. </h3>
This project  is a programming assignment that focuses on managing a data model of musicians for performances. Given a text file ("Musicians File"), each line in the file contains the name of a musician composed of multiple words. This is followed by the musical instruments they play (at least one), and after each instrument, the price the musician charges for performing with that instrument is mentioned.

The words that make up the musician's name, the musical instruments, and the prices are separated by spaces and other delimiters ("separating characters").

In addition, there is another text file ("Instruments File") that contains a collection of musical instruments, with each instrument listed on a separate line. It is guaranteed that every instrument mentioned in the Musicians File is included in the Instruments File.

The program will accept input from the user regarding performances. Each performance will have a name, date, the necessary musical instruments, and the required quantity for each instrument. Additionally, each instrument in the performance will be assigned importance (1/0), where if the instrument is considered "important," expensive musicians will be preferred (assuming they are of higher quality), and otherwise, cheaper musicians will be preferred.
<img src="https://media.istockphoto.com/id/1247853982/photo/cheering-crowd-with-hands-in-air-at-music-festival.jpg?s=612x612&w=0&k=20&c=rDVKf3hTryuVgUZUme9wuwfsegfJptAvVEKsDwppvJc=" style="width:100vw; height:500px;">

Below is an explanation of the tasks and data structures that need to be implemented:

### Building a binary tree of musical instruments:

The program receives two text file names as arguments. The first file is the Instruments File, where each line represents a musical instrument. It can be assumed that the length of each line does not exceed 150 characters.
Each node in the tree stores a specific musical instrument (instrument field). The insId field is a unique identifier number for each instrument, starting from 0 (meaning no two instruments have the same insId).
The left pointer in a node points to the left subtree where all instrument values are smaller (in lexicographic order) than the instrument value in the current node (or NULL if the left subtree is empty). Similarly, the right pointer in a node points to the right subtree where all words are larger (in lexicographic order) than the instrument value in the current node (or NULL if the right subtree is empty).
Each musical instrument mentioned in the Instruments File needs to be stored in a structure called TreeNode, which will be inserted into the binary search tree structure called InstrumentTree.
Converting the name of a musical instrument to its corresponding identifier, Using the function: int findInsId(InstrumentTree tree, char *instrument).
This function takes a musical instrument name and a tree as arguments and returns the unique identifier number of the instrument.

<img src=https://thumbs.dreamstime.com/b/music-instruments-tree-sketch-your-design-vector-illustration-89837672.jpg  style="width:100vw; height:500px;">

### Building the data model of musicians:

The second argument of the program is the name of the Musicians File.
Each line in the file contains the name of a musician, composed of multiple words (at least two). It may include first and last names, middle names, and sometimes two last names. For example: "John Smith," "Anna and Violet De Paris Heir," etc.
This is followed by the musical instruments the musician plays (at least one), and after each instrument, the price the musician charges for performing with that instrument is mentioned.
Extract the words from each line using the specified delimiters: ",.;:?!-\t'()[]{}<>~_".
Store all musicians listed in the file in an array of pointers to the Musician structure called MusiciansGroup, using the following structure definitions:

<img src=https://images.ctfassets.net/pdf29us7flmy/2UIUuDUnrvflYWPv4FBNmF/a7512b5f8620c5fbd6e312481b3f44f7/Playing_Guitar.png  style="width:100vw; height:500px;">
