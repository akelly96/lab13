/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
    Cipher03() {
        valueMinimum = ' ';
        valueMaximum = '~';
        sizeAlphabet = valueMaximum - valueMinimum + 1;
    }

    virtual std::string getPseudoAuth() { return "Eric Guerrero"; }
    virtual std::string getCipherName() { return "Vigenere Cipher"; }
    virtual std::string getEncryptAuth() { return "Eric Guerrero"; }
    virtual std::string getDecryptAuth() { return "Eric Guerrero"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string cited;
        cited += "Japp.io. (MAR 2020), ";
        cited += "\"A.Jazib, Vigenere Cipher Algorithm Program in C/C++\", \n   retrieved: ";
        cited += "https://japp.io/cryptography/vigenere-cipher-algorithm-program-in-c-c/";
        return cited;
        return std::string("citation");
    }

    /**********************************************************
     * GET PSEUDOCODE
     * Returns the pseudocode as a string to be used by the caller.
     **********************************************************/
    virtual std::string getPseudocode()
    {
        std::string str;

        // TODO: please format your pseudocode
        // The encrypt pseudocode
        str = "encrypt(plainText, password)\n";
        str += "   key <- generateKey(plainText, password)\n";
        str += "   FOR i is all index of plainText\n";
        str += "      index <- (indexFromCharacter(plainText[i]) + indexFromCharacter(key[i])) % size\n";
        str += "      cipherText.push_back(characterFromIndex(index))\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += "   key <- generateKey(cipherText, password)\n";
        str += "   FOR i is all index of cipherText\n";
        str += "      index <- (indexFromCharacter(plainText[i]) - indexFromCharacter(key[i]) + size) % size\n";
        str += "      plainText.push_back(characterFromIndex(index))\n";
        str += "   RETURN plainText\n\n";

        // helper routine
        str += "generateKey(str, password)\n";
        str += "   passwordSize <- size of password\n";
        str += "   FOR i is all index of str larger than passwordSize and j is all index of password\n";
        str += "     if j equals passwordSize\n";
        str += "        j <- 0\n";
        str += "     password += password[j]\n";
        str += "   RETURN password\n\n";
        return str;

    }

    /**********************************************************
      * ENCRYPT
      * TODO: This function returns the encrypted text
      * generated with the help of the key
      **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {

        std::string cipherText;

        // generate the key from the password
        std::string key = generateKey(plainText, password);

        // convert the plaintext one character at a time
        for (int i = 0; i < plainText.size(); i++)
        {
            // get the index for the cipherText
            int index = ((indexFromCharacter(plainText[i]) + indexFromCharacter(key[i])) % sizeAlphabet);

            // send the index into cipherText
            cipherText.push_back(characterFromIndex(index));
        }
        return cipherText;
    }

    /**********************************************************
    * DECRYPT
    * TODO: This function decrypts the encrypted
    * text and returns the original text
    **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText;

        // generate the key from the password
        std::string key = generateKey(cipherText, password);

        // convert the ciphertext one character at a time
        for (int i = 0; i < cipherText.size(); i++)
        {
            // get the index for the plainText
            int index = ((indexFromCharacter(cipherText[i]) - indexFromCharacter(key[i]) + sizeAlphabet) % sizeAlphabet);

            // send the index into plainText
            plainText.push_back(characterFromIndex(index));
        }
        return plainText;
    }

private:
    /**************************************************
     * INDEX FROM CHARACTER
     * Get an index value from a given letter.
     *************************************************/
    int indexFromCharacter(char letter)
    {
        int index = 0;
        if (letter <= valueMaximum && letter >= valueMinimum)
            index = (int)letter - valueMinimum;
        return index;
    }

    /**************************************************
     * CHARACTER FROM INDEX
     * Get the characer value from a given index.
     *************************************************/
    char characterFromIndex(int index)
    {
        index += valueMinimum;
        return (char)(index);
    }

    /**********************************************************
     * Generate Key
     * This function generates the key in
     * a cyclic manner until it's length is
     * equal to the length of original text
     **********************************************************/
    std::string generateKey(std::string str, std::string password)
    {
        // get the original password size
        int passwordSize = password.size();

        // loop while size of password is less than size of str
        for (int i = passwordSize, j = 0; i < str.size(); i++, j++)
        {
            // return to beginning index of password
            if (j == passwordSize)
                j = 0;
            
            // add onto the password
            password.push_back(password[j]);
        }

        return password;
    }
    // minimum "printable" character
    char valueMinimum;

    // maximum "printable" character
    char valueMaximum;

    int sizeAlphabet;
};

#endif // CIPHER03_H