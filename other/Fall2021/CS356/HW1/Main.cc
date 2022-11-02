#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

//message that I can print that explains how the code works
string usageMessage()
{
    return "Usage: ('B'|'S') inputFile outputFile keyFile ('E'|'D')\n";
}

//Given a file and its name, it opens the file and complains if the file doesn't exist
void openFile(ifstream &file, const string &filename)
{
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "File \"" << filename << "\" could not be opened!" << '\n';
        cerr << usageMessage();
        exit(1);
    }
}
//overloaded version for ofstreams because I don't know how to use the same method for both.
void openFile(ofstream &file, const string &filename)
{
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "File \"" << filename << "\" could not be opened!" << '\n';
        cerr << usageMessage();
        exit(1);
    }
}

//takes an argument and 2 strings.
//ensures that the argument is equivalent to either string.
//If not, it complains
void limitArg(const char *arg, const char *l1, const char *l2)
{
    if (!(strcmp(arg, l1) == 0 || strcmp(arg, l2) == 0))
    {
        cerr << "Argument \"" << arg << "\" must be '" << l1 << " or '" << l2 << "!" << '\n';
        cerr << usageMessage();
        exit(1);
    }
}

//checks to ensure arguments are correct and complains if they are not.
void checkArguments(int argc, char *argv[])
{
    //Ensure exactly 5 arguments
    if (argc != 6)
    {
        cerr << "You must provide exactly 5 arguments!" << '\n';
        cerr << usageMessage();
        exit(1);
    }
    limitArg(argv[1], "B", "S");
    limitArg(argv[5], "E", "D");
}

//opens key file and returns the contents as a string
string setKey(const string &keyFileName)
{
    //Ensure argument 4 is a file that exists
    ifstream keyFile;
    openFile(keyFile, keyFileName);

    char c;
    string contents = "";
    while (keyFile.get(c))
        contents += c;

    keyFile.close();

    return contents;
}

//fills block with the first 128 bits of the inFile.
//If there are less than 128 bits remaining, it fills what it can.
//returns false if no bits were able to be read (end of file) and true otherwise.
bool readBlock(ifstream &inFile, string &block)
{
    char c;
    block = "";

    //if end of file was hit last time
    if (inFile.eof())
        return false;

    //read 16 bytes or until end of file.
    for (int i = 0; i < 16 && inFile.get(c); i++)
        block += c;

    //if end of file was hit and nothing was read.
    if (block == "")
        return false;

    return true;
}

//takes block and adds char(129) onto the end of it until its size is a multiple of 16
void padBlock(string &block)
{
    while (block.size() % 16 != 0)
        block += char(129);
}

//removes all char(129) characters at the end of block
void removePadding(string &block)
{
    int pos = block.find(char(129));
    if (pos != string::npos)
        block.erase(pos, block.size() - pos);
}

//XOR's the block with the key.
void XORBlock(string &block, const string &key)
{
    for (int i = 0; i < block.size(); i++)
        block[i] = key[i % 16] ^ block[i];
}

//takes a block and 2 indeces and swaps the indeces with eachother.
void swapIndeces(string &block, const int &i1, const int &i2)
{
    char temp;
    temp = block[i1];
    block[i1] = block[i2];
    block[i2] = temp;
}

//encrypts/decrypts block using the swapping algorithm as described by assignment
void swap(string &block, const string &key)
{
    int end = block.size() - 1;
    for (int start = 0; start < end; start++)
    {
        int asciiVal = int(key[start % key.size()]);
        if ((asciiVal % 2) == 1)
        {
            swapIndeces(block, start, end);
            end -= 1;
        }
    }
}

//Encrypts message (using block encryption) in inFile using key and places the encryption in outFile
void blockEncryption(ifstream &inFile, ofstream &outFile, const string &key)
{
    string block;
    string output = "";

    while (readBlock(inFile, block))
    {
        padBlock(block);
        XORBlock(block, key);

        output += block;
    }
    swap(output, key);
    outFile << output;
}

//Decrypts encrypted message (using block encryption) in inFile using key and places the decryption in outFile
void blockDecryption(ifstream &inFile, ofstream &outFile, const string &key)
{
    string input = "";
    char c;
    while (inFile.get(c))
        input += c;
    swap(input, key);

    int i;
    for (i = 0; i < input.length(); i += 16)
    {
        string block;
        if (input.length() - i >= 16)
            block = input.substr(i, 16);
        else
            block = input.substr(i, input.length() - i);
        XORBlock(block, key);
        removePadding(block);
        outFile << block;
    }
}

//Encrypts/decrypts message (using stream encryption) in inFile using key and puts the result in outFile.
void streamCipher(ifstream &inFile, ofstream &outFile, const string &key)
{
    char c;
    for (int i = 0; inFile.get(c); i++)
    {
        c = c ^ key[i % key.size()];
        outFile << c;
    }
}

//opens and closes input and output stream
//processes the message using the correct cipher depending on arguments given.
void encryptMsg(const string &inFilename, const string &outFilename, const bool &isBlock, const bool &isEncrypting, const string &key)
{
    ifstream inFile;
    openFile(inFile, inFilename);

    ofstream outFile;
    openFile(outFile, outFilename);

    if (isBlock && isEncrypting)
        blockEncryption(inFile, outFile, key);
    else if (isBlock && !isEncrypting)
        blockDecryption(inFile, outFile, key);
    else
        streamCipher(inFile, outFile, key);

    inFile.close();
    outFile.close();
}

int main(int argc, char *argv[])
{
    checkArguments(argc, argv);

    bool isBlock = (strcmp(argv[1], "B") == 0);
    string inFilename = argv[2];
    string outFilename = argv[3];
    string key = setKey(argv[4]);
    bool isEncrypting = (strcmp(argv[5], "E") == 0);

    encryptMsg(inFilename, outFilename, isBlock, isEncrypting, key);
    return 0;
}