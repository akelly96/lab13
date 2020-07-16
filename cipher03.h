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
    virtual std::string getPseudoAuth() { return "Eric Guerrero"; }
    virtual std::string getCipherName() { return "Vigenere Cypher"; }
    virtual std::string getEncryptAuth() { return "Eric Guerrero"; }
    virtual std::string getDecryptAuth() { return "Eric Guerrero"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string cited;
        cited += "A.Jazib, Vigenère Cipher Algorithm, Japp.io. MAR 2020\n ";
        cited += "[Online] Available: https://japp.io/cryptography/vigenere-cipher-algorithm-program-in-c-c/";
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
        str = "encrypt(plainText, password) {\n";
        str += " Generate the new key\n";
        str += " FOR the length of the plain text\n";
        str += "    Set character to the plain text + key mod 26\n";
        str += "    Add and set equal to 'A'\n";
        str += "    Push back to cipher text\n";
        str += " RETURN the cipher text }\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += " Generate the new key\n";
        str += " FOR the length of the cipher text\n";
        str += "    Set character to cipher text - key + 26 to mod 26\n";
        str += "    Add and set equal to 'A'\n";
        str += "    Push back to plain text\n";
        str += " RETURN the plain text }\n\n";
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
        std::string key = generateKey(plainText, password);

        // TODO - Add your code here
        for (int i = 0; i < plainText.size(); i++)
        {
            // converting in range 0-25 
            char x = (plainText[i] + key[i]) % 26;

            // convert into alphabet(ASCII) 
            x += 'A';

            cipherText.push_back(x);
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
        std::string key = generateKey(cipherText, password);

        // TODO - Add your code here
        for (int i = 0; i < cipherText.size(); i++)
        {
            // converting in range 0-25 
            char x = (cipherText[i] - key[i] + 26) % 26;

            // convert into alphabets(ASCII) 
            x += 'A';
            plainText.push_back(x);
        }
        return plainText;
    }

private:
    /**********************************************************
     * Generate Key
     * This function generates the key in
     * a cyclic manner until it's length is
     * equal to the length of original text
     **********************************************************/
    virtual std::string generateKey(std::string str, std::string key)
    {

        int x = str.size();

        for (int i = 0; ; i++)
        {
            if (x == i)
                i = 0;
            if (key.size() == str.size())
                break;
            key.push_back(key[i]);
        }
        return key;
    }
};

#endif // CIPHER03_H